#include "Vtop.h"         // 必须包含这个，编译器才认识 Vtop
#include "verilated.h"    // 包含 Verilator 的基本定义
#include <iostream>
#include <string>
#include <readline/readline.h>
#include <readline/history.h>
#include "../include/generated/autoconf.h"
#define ARRLEN(arr) (int)(sizeof(arr) / sizeof(arr[0]))


// 引用外部函数和指针

extern "C" void pmem_read (int raddr, int *rdata, char rmask);
extern "C" void pmem_write(int waddr, int wdata, char wmask);
extern "C" uint32_t paddr_read(uint32_t addr, int len);





extern uint32_t *cpu_gpr;
bool single_step();
void isa_reg_display();


extern Vtop *top_ptr;


static char *rl_gets()
{
  static char *line_read = NULL;

  if (line_read) {
    free(line_read);
    line_read = NULL;
  }

  line_read = readline("(npc) ");

  if (line_read && *line_read) {// 如果 line_read 不为 NULL 且字符串不为空（即 *line_read != '\0'），
    add_history(line_read);     // 则将其添加到历史记录中。
  }

  return line_read;
}

extern void difftest_step(uint32_t npc_pc, void *npc_regs);

void cpu_exec(uint64_t n) {
    for (uint64_t i = 0; i < n; i++) {
        const bool committed = single_step();
        #ifdef CONFIG_DIFFTEST
        if (committed) {
            difftest_step(top_ptr->pc, NULL);
        }
        #endif
        
// #ifdef CONFIG_ITRACE
//   char *p = s->logbuf;
//   p += snprintf(p, sizeof(s->logbuf), FMT_WORD ":", s->pc);
//   int ilen = s->snpc - s->pc;
//   int i;
//   uint8_t *inst = (uint8_t *)&s->isa.inst;
// #ifdef CONFIG_ISA_x86
//   for (i = 0; i < ilen; i ++) {
// #else
//   for (i = ilen - 1; i >= 0; i --) {
// #endif
//     p += snprintf(p, 4, " %02x", inst[i]);
//   }
//   int ilen_max = MUXDEF(CONFIG_ISA_x86, 8, 4);
//   int space_len = ilen_max - ilen;
//   if (space_len < 0) space_len = 0;
//   space_len = space_len * 3 + 1;
//   memset(p, ' ', space_len);
//   p += space_len;

//   void disassemble(char *str, int size, uint64_t pc, uint8_t *code, int nbyte);
//   disassemble(p, s->logbuf + sizeof(s->logbuf) - p,
//       MUXDEF(CONFIG_ISA_x86, s->snpc, s->pc), (uint8_t *)&s->isa.inst, ilen);


// #endif


    }
}









static int cmd_x(char *args) {
    // 1. 获取第一个参数 N (数量)
    char *arg_n = strtok(args, " ");
    if (arg_n == NULL) {
        printf("Usage: x N EXPR\n");
        return 0;
    }

    // 2. 获取第二个参数 EXPR (起始地址)
    char *arg_expr = strtok(NULL, " ");
    if (arg_expr == NULL) {
        printf("Usage: x N EXPR\n");
        return 0;
    }

    int n = atoi(arg_n);
    uint32_t addr = 0;

    // 3. 简易表达式解析 (支持十六进制和特定的寄存器)
    if (arg_expr[0] == '$') {
        if (strcmp(arg_expr, "$pc") == 0) {
            addr = top_ptr->pc;
        } else if (strcmp(arg_expr, "$sp") == 0 || strcmp(arg_expr, "$x2") == 0) {
            if (cpu_gpr) addr = cpu_gpr[2];
        } else {
            printf("Unknown register: %s\n", arg_expr);
            return 0;
        }
    } else {
        // 解析十六进制地址，例如 0x80000000
        if (sscanf(arg_expr, "0x%x", &addr) != 1 && sscanf(arg_expr, "%x", &addr) != 1) {
            printf("Invalid address format: %s\n", arg_expr);
            return 0;
        }
    }

    // 4. 循环读取并打印
    printf("Memory scan at 0x%08x:\n", addr);
    for (int i = 0; i < n; i++) {
        // 读取 4 字节数据
        uint32_t val = paddr_read(addr, 4);
        printf("  0x%08x:  0x%08x\n", addr, val);
        addr += 4; // 步进 4 字节
    }

    return 0;
}


static int cmd_info(char *args){
  char *arg = strtok(args, " ");
  if (arg == NULL || (strcmp(arg, "r") != 0 && strcmp(arg, "w") != 0))
  {
    printf("Only 'r' or 'w' allowed\n");
  }
  else if (strcmp(arg, "r") == 0)
  {
    isa_reg_display();
  }
  // else if (strcmp(arg, "w") == 0)
  // {
  //   sdb_watchpoint_display();
  // }

    return 0;
}
static int cmd_si(char *args)
{
  int N = 1;
  if(args != NULL){
    sscanf(args, "%d", &N);
  }
  cpu_exec(N);
  return 0;
}

static int cmd_c(char *args) {
  cpu_exec(-1);
  return 0;
}


static int cmd_q(char *args) {
  exit(0);
  return -1;
}

static int cmd_help(char *args);

static struct {
  const char *name;
  const char *description;
  int (*handler) (char *);
} cmd_table [] = {
  { "help", "Display information about all supported commands", cmd_help },
  { "c", "Continue the execution of the program", cmd_c },
  { "q", "Exit NEMU", cmd_q },
  {"si", "Execute next N instructions", cmd_si},
  {"info","Display values of regs",cmd_info},
  {"x","scan memory",cmd_x},
//   {"p","Expression evaluation",cmd_p},
//   {"w","create watchpoint",cmd_w},
//   {"d","delete watchpoint",cmd_d}
  /* TODO: Add more commands */

};

#define NR_CMD ARRLEN(cmd_table)              //获取cmd_table长度

static int cmd_help(char *args) {
  /* extract the first argument */
  char *arg = strtok(NULL, " ");
  int i;

  if (arg == NULL) {
    /* no argument given */
    for (i = 0; i < NR_CMD; i ++) {
      printf("%s - %s\n", cmd_table[i].name, cmd_table[i].description);
    }
  }
  else {
    for (i = 0; i < NR_CMD; i ++) {
      if (strcmp(arg, cmd_table[i].name) == 0) {
        printf("%s - %s\n", cmd_table[i].name, cmd_table[i].description);
        return 0;
      }
    }
    printf("Unknown command '%s'\n", arg);
  }
  return 0;

}






void sdb_mainloop(bool batch) {
  if(batch){
    cmd_c(NULL);
    return;
  }

  for (char *str; (str = rl_gets()) != NULL; ) {
    char *str_end = str + strlen(str);

    /* extract the first token as the command */
    char *cmd = strtok(str, " ");
    if (cmd == NULL) { continue; }

    /* treat the remaining string as the arguments,
     * which may need further parsing
     */
    char *args = cmd + strlen(cmd) + 1;//+1 因为有空格，
    if (args >= str_end) {
      args = NULL;
    }

    int i;
    for (i = 0; i < NR_CMD; i ++) {
      if (strcmp(cmd, cmd_table[i].name) == 0) {
        if (cmd_table[i].handler(args) < 0) { return; }
        break;
      }
    }

    if (i == NR_CMD) { printf("Unknown command '%s'\n", cmd); }
  }
}
