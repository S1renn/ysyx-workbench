#include "Vtop.h"
#include "verilated.h"
#include "svdpi.h"
#include "Vtop__Dpi.h"
#include "verilated_dpi.h"
#include <sys/time.h>
#include "device/dev.h"
#include "../include/generated/autoconf.h"
#include "define.h"



uint8_t pmem[MEM_SIZE];

extern Vtop* top_ptr;
extern uint32_t *cpu_gpr;
extern void difftest_skip_ref();


static uint64_t boot_time = 0;
static uint64_t get_time_internal() {
  struct timeval now;
  gettimeofday(&now, NULL);
  uint64_t us = now.tv_sec * 1000000 + now.tv_usec;
  if (boot_time == 0) boot_time = us;
  return us - boot_time;
}






extern "C" void set_gpr_ptr(const svOpenArrayHandle r) {
    // 使用 Verilator 提供的专用 API 提取真正的数组首地址
    // svGetArrayPtr 在某些版本中可用，但 datap() 是最稳妥的底层拿法
    cpu_gpr = (uint32_t *)(((VerilatedDpiOpenVar*)r)->datap());
    
    // printf("C++ side: GPR pointer received at %p\n", r);
    // printf("C++ side: GPR data actual address at %p\n", cpu_gpr);
}



extern "C" uint32_t paddr_read(uint32_t addr, int len) {
    int data = 0;
    // 根据 len 生成对应的 rmask
    char rmask = (len == 4) ? 0xf : (len == 2 ? 0x3 : 0x1);
    
    // 调用上面已经写好的 pmem_read 逻辑
    pmem_read(addr, rmask);
    
    return (uint32_t)data;
}

// 在 mem.cpp 中
extern bool gpu_read(uint32_t addr, uint32_t *data);
extern bool gpu_write(uint32_t addr, uint32_t data, uint8_t wmask);
extern "C" uint32_t keyboard_read();
extern "C" int pmem_read(int raddr, char rmask) {
    // --- 1. 设备区拦截 (0xa0000000 - 0xafffffff) ---
    if (raddr >= 0xa0000000 && raddr <= 0xafffffff) {
        #ifdef CONFIG_DIFFTEST
        difftest_skip_ref();
        #endif

        // 先交给 GPU 处理 (内部会处理 VGACTL 和 整个显存范围)
        uint32_t gpu_data;
        if (gpu_read(raddr, &gpu_data)) {
            return gpu_data;
        }

        // 处理 RTC
        if (raddr == RTC_ADDR || raddr == RTC_ADDR + 4) {
            uint64_t us = get_time_internal();
             return (raddr == RTC_ADDR) ? (uint32_t)us : (uint32_t)(us >> 32);
        }

    // 处理键盘
        if (raddr == 0xa0000000) { return 1;}
        if (raddr == 0xa0000060) { return keyboard_read(); }

        return  0; // 其他设备地址默认返回0
    }

    // --- 2. 内存区访问 (0x80000000 - 0x84000000) ---
    if (raddr >= MEM_BASE && raddr < MEM_BASE + MEM_SIZE) {
        uint32_t index = raddr - MEM_BASE;
        uint8_t *p = (uint8_t *)(pmem + index);
        int data = 0;
        if (rmask & 0x01) data |= (p[0]);
        if (rmask & 0x02) data |= (p[1] << 8);
        if (rmask & 0x04) data |= (p[2] << 16);
        if (rmask & 0x08) data |= (p[3] << 24);
        return data;

    }

    // --- 3. 非法地址 ---
    #ifdef CONFIG_DIFFTEST
    difftest_skip_ref();
    #endif
    return 0;
}

extern "C" void pmem_write(int waddr, int wdata, char wmask) {
    // --- 1. 串口 (注意串口通常不在 0xa 范围，独立判断) ---
    if (waddr == SERIAL_PORT) {
        #ifdef CONFIG_DIFFTEST
        difftest_skip_ref();
        #endif
        fputc((char)wdata, stdout);
        fflush(stdout);
        return;
    }

    // --- 2. 设备区拦截 (GPU/RTC 等) ---
    if (waddr >= 0xa0000000 && waddr <= 0xafffffff) {
        #ifdef CONFIG_DIFFTEST
        difftest_skip_ref();
        #endif
        // 只要是这个范围的写，都交给 gpu_write (它内部会过滤 FB_ADDR 和 SYNC_ADDR)
        gpu_write(waddr, wdata, wmask);
        return;
    }

    // --- 3. 内存区访问 ---
    if (waddr >= MEM_BASE && waddr < MEM_BASE + MEM_SIZE) {
        uint32_t index = waddr - MEM_BASE;
        uint8_t *p = (uint8_t *)(pmem + index);
        if (wmask & 0x01) p[0] = (wdata) & 0xFF;
        if (wmask & 0x02) p[1] = (wdata >> 8) & 0xFF;
        if (wmask & 0x04) p[2] = (wdata >> 16) & 0xFF;
        if (wmask & 0x08) p[3] = (wdata >> 24) & 0xFF;
        return;
    }
}




void isa_reg_display() {
    printf("DEBUG: cpu_gpr address is %p\n", cpu_gpr);
    if (cpu_gpr == NULL) {
        printf("ERROR: Bridge broken! The interaction layer cannot see the hardware registers.\n");
        return;
    }
  for (int i = 0; i < 32; i++) { // 必须是 < 32，不能是 <= 32
    if (cpu_gpr != NULL) {
      printf("x%-2d: 0x%08x\n", i, cpu_gpr[i]);
    } else {
      printf("Error: cpu_gpr is NULL!\n");
      return;
    }
  }
}
