#include "Vtop.h"
#include "verilated.h"
#include <stdio.h>
#include "verilated_vcd_c.h"
#include "svdpi.h"
#include "Vtop__Dpi.h"
#include <sys/time.h>
#include <assert.h> 
#include "device/dev.h"
#include "../include/generated/autoconf.h"



// 1. 定义内存
#define MEM_SIZE (64 * 1024 * 1024) // 64 MB
#define MEM_BASE 0x80000000
#define DEVICE_BASE 0xa0000000
#define RTC_ADDR (DEVICE_BASE + 0x00000048)
#define VGACTL_ADDR (DEVICE_BASE + 0x0000100)
#define SERIAL_PORT (0x10000000)
extern uint8_t pmem[];
//uint8_t pmem[MEM_SIZE];

//global ptr
Vtop *top_ptr = NULL;
uint32_t *cpu_gpr = NULL;
VerilatedVcdC *tfp = NULL;

// 在 sim_main.cpp 中保留声明即可
extern void init_vga();
extern void difftest_step(uint32_t npc_pc);
extern void init_difftest(char *ref_so_file, long img_size, void *img);
// 2. 加载镜像文件
long load_img(char *img_file) {
  if (img_file == NULL) {
      printf("No image file specified.\n");

      return 0;
  }
  
  FILE *fp = fopen(img_file, "rb");
  if (fp == NULL) {
      printf("Can not open '%s'\n", img_file);
      return 0;
  }

  fseek(fp, 0, SEEK_END);
  long size = ftell(fp);

  printf("The image is %s, size = %ld\n", img_file, size);

  fseek(fp, 0, SEEK_SET);
  // 读入 pmem 数组开头
  int ret = fread(pmem, size, 1, fp);
  assert(ret == 1);


  fclose(fp);
  return size;
}


static uint64_t boot_time = 0;
static uint64_t get_time_internal() {
  struct timeval now;
  gettimeofday(&now, NULL);
  uint64_t us = now.tv_sec * 1000000 + now.tv_usec;
  if (boot_time == 0) boot_time = us;
  return us - boot_time;
}


extern "C" void ebreak(){
   uint32_t a0 = top_ptr->x10; 
  
  if(a0 == 0) {
      printf("\033[1;32mHit good trap\033[0m\n"); // 绿色
#ifdef CONFIG_WAVE
      if(tfp) tfp->close();
#endif
      exit(0);
  } else {
      printf("\033[1;31mHit bad trap (exit code = %d)\033[0m\n", a0); // 红色
#ifdef CONFIG_WAVE
      if(tfp) tfp->close();
#endif
      exit(1);
  }
}


extern "C" void invalid_inst_trap(int pc, int inst) {
    printf("\033[1;31m[ERROR] Invalid instruction 0x%08x at PC=0x%08x\033[0m\n", inst, pc);
    exit(1);
}




// 在 global ptr 附近增加一个全局变量记录 context
VerilatedContext* contextp = NULL;

bool single_step() {
    if (top_ptr == NULL || contextp == NULL) return false;

    // 1. 下降沿 -> 上升沿 (触发硬件寄存器更新) // 假设你的寄存器堆数组叫 gpr，a5 对应 RISC-V 的 x15
 
    update_keyboard_state();
    // 上升沿前稳定组合逻辑，记录本次上升沿是否会提交指令。
    top_ptr->clk = 0;
    top_ptr->eval();
    const bool will_commit = top_ptr->commit;

    top_ptr->clk = 1;
    top_ptr->eval();
    contextp->timeInc(1);

    // Debug print
    //printf("PC=%08x INST=%08x\n", top_ptr->pc, top_ptr->inst);
#ifdef CONFIG_WAVE
     if(tfp) tfp->dump(contextp->time()); // 如果有波形就记录
#endif

    // 2. 上升沿 -> 下降沿 (准备下一次触发)
    top_ptr->clk = 0;
    top_ptr->eval();
    contextp->timeInc(1);
#ifdef CONFIG_WAVE
     if(tfp) tfp->dump(contextp->time());
#endif


#ifdef CONFIG_ITRACE
    printf("pc = 0x%08x, inst = 0x%08x\n",top_ptr->pc, top_ptr->inst);
#endif
    return will_commit;
}




void init_sim(int argc, char** argv) {
    contextp = new VerilatedContext;
    contextp->commandArgs(argc, argv); 
    top_ptr = new Vtop{contextp};



#ifdef CONFIG_WAVE
    contextp->traceEverOn(true);
    tfp = new VerilatedVcdC;
    top_ptr->trace(tfp, 99);
    tfp->open("npc_dump.vcd"); // 生成的波形文件名
#else
    // printf("Wave trace is disabled by Kconfig\n");
#endif




    char *img_file = argv[1];
    char *so_file  = argv[2]; 
    char *elf_file = argv[3]; // 建议把 ELF 路径放在第三个参数

    // 1. 加载镜像到 NPC 内存
    long img_size = load_img(img_file);

    // 2. Difftest 开关逻辑
#ifdef CONFIG_DIFFTEST
    if (so_file != NULL) {
        init_difftest(so_file, img_size, pmem);
    } else {
        printf("\033[1;33m[NPC] Warning: CONFIG_DIFFTEST is on, but no .so file provided!\033[0m\n");
    }
#else
    printf("[NPC] Difftest is disabled by Kconfig.\n");
#endif

    // 3. Ftrace 开关逻辑
#ifdef CONFIG_FTRACE
    printf("[NPC] Ftrace is enabled by Kconfig.elf_file = %s\n", elf_file);
    void init_ftrace(const char *elf_file);

    if (elf_file != NULL) {
        init_ftrace(elf_file);
    } else {
        // 如果没传第三个参数，尝试把 .bin 换成 .elf 试试
        init_ftrace(img_file); 
    }
#endif
    init_vga();
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return ;
    }
    SDL_Window *window = SDL_CreateWindow("NPC Simulation", 
                         SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
                         400, 300, SDL_WINDOW_SHOWN);



    // Reset 过程 (保持不变)
    top_ptr->rst = 1;
    top_ptr->clk = 0;
    for(int i = 0; i < 6; i++){
        top_ptr->clk = !top_ptr->clk;
        top_ptr->eval();
        contextp->timeInc(1);
    }
    top_ptr->rst = 0;
}
