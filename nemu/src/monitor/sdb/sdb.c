/***************************************************************************************
* Copyright (c) 2014-2024 Zihao Yu, Nanjing University
*
* NEMU is licensed under Mulan PSL v2.
* You can use this software according to the terms and conditions of the Mulan PSL v2.
* You may obtain a copy of Mulan PSL v2 at:
*          http://license.coscl.org.cn/MulanPSL2
*
* THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
* EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
* MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
*
* See the Mulan PSL v2 for more details.
***************************************************************************************/

#include <isa.h>
#include <cpu/cpu.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <memory/host.h>
#include <memory/paddr.h>
#include <device/mmio.h>
#include <isa.h>
#include "watchpoint.h"
#include "expr.h"

static int is_batch_mode = false;

void init_regex();
void init_wp_pool();
void watchpoint_create();
void sdb_watchpoint_display();
void free_wp();
void watchpoint_delete();
//uint32_t expr(char *e, bool *success);

/* We use the `readline' library to provide more flexibility to read from stdin. */
static char *rl_gets()
{
  static char *line_read = NULL;

  if (line_read) {
    free(line_read);
    line_read = NULL;
  }

  line_read = readline("(nemu) ");

  if (line_read && *line_read) {// 如果 line_read 不为 NULL 且字符串不为空（即 *line_read != '\0'），
    add_history(line_read);     // 则将其添加到历史记录中。
  }

  return line_read;
}
static int cmd_w(char *args)
{
  watchpoint_create(args);
  return 0;
}

static int cmd_d(char *args)
{
  if (args == NULL)
    printf("No args.\n");
  else
  {
    watchpoint_delete(atoi(args));
  }
  return 0;
}
static int cmd_p(char *args){
  if (args == NULL){
    printf("NO ARGS.\n");
    return 0;
  }
  bool flag = false;
  
  uint32_t res = expr(args, &flag);
  printf("Result of expression is %u.\n", res);

  return 0;

}

static int cmd_x(char *args){
    // 第一个参数：N
    char *N = strtok(args, " ");
    if (N == NULL) {
        printf("Usage: x N EXPR\n");
        return 0;
    }

    // 第二个参数：EXPR
    char *EXPR = strtok(NULL, " ");
    if (EXPR == NULL) {   // 没有提供地址参数
        printf("Missing address argument!\n");
        return 0;
    }
    EXPR = N + strlen(N) + 1;
    int n = 0;
    paddr_t addr = 0;
    sscanf(N, "%d", &n);
    sscanf(EXPR, "%x", &addr);
    if(addr < 0x80000000){
      printf("address = 0x%08x is out of bound of pmem [0x80000000, 0x87ffffff] at pc = 0x80000000\n",addr);
      return 0;
    }else{
    for (; n > 0; n--)
    {
      printf("%08x:  0x%08x\n",addr,paddr_read(addr, 4));
      addr += 4;
    }
  return 0;

    }
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
  else if (strcmp(arg, "w") == 0)
  {
    sdb_watchpoint_display();
  }

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
  nemu_state.state = NEMU_QUIT;
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
  {"p","Expression evaluation",cmd_p},
  {"w","create watchpoint",cmd_w},
  {"d","delete watchpoint",cmd_d}
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

void sdb_set_batch_mode() {
  is_batch_mode = true;
}

void sdb_mainloop() {
  if (is_batch_mode) {
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

#ifdef CONFIG_DEVICE
    extern void sdl_clear_event_queue();
    sdl_clear_event_queue();
#endif

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

void init_sdb() {
  /* Compile the regular expressions. */
  init_regex();

  /* Initialize the watchpoint pool. */
  init_wp_pool();
}
