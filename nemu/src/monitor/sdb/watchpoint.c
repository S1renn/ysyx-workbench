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

#include "watchpoint.h"
#include "expr.h"

//uint32_t expr(char *e, bool *flag);

WP wp_pool[NR_WP];
static WP *head = NULL,
          *free_ = NULL;

void init_wp_pool() {
  int i;
  for (i = 0; i < NR_WP; i ++) {
    wp_pool[i].NO = i;
    wp_pool[i].next = (i == NR_WP - 1 ? NULL : &wp_pool[i + 1]);
  }

  head = NULL;
  free_ = wp_pool;
}

/* TODO: Implement the functionality of watchpoint */
 //new_wp()从free_链表中返回一个空闲的监视点结构,
WP* new_wp(){
  for(WP* p = free_; p -> next != NULL; p = p -> next){ //遍历free_
    if (p -> flag == false){
      p -> flag = true;
      if (head == NULL){
        head = p;
      }
      return p;
    }
  }
  printf("No free watchpoints existing!\n");
  assert(0);
  return NULL;
}

void free_wp(WP *wp)
{
  if (!wp)
  {
    printf("Error: wp is NULL!\n");
    return;
  }

  // 检查 wp 是否在 wp_pool 范围内（可选）
  if (wp < wp_pool || wp >= wp_pool + NR_WP)
  {
    printf("Error: wp is not in wp_pool!\n");
    return;
  }

  // 情况1：链表为空
  if (!head)
  {
    printf("Error: head is NULL, no watchpoints to free!\n");
    return;
  }

  // 情况2：释放头节点
  if (head->NO == wp->NO)
  {
    WP *to_free = head;
    head = head->next;     // 更新 head
    to_free->next = free_; // 放回 free_ 链表
    to_free->flag = false;
    free_ = to_free;
    printf("Free head watchpoint succeed! %d\n", wp->NO);
    return;
  }

  // 情况3：释放中间或尾节点
  WP *prev = head;
  WP *curr = head->next;
  while (curr)
  {
    if (curr->NO == wp->NO)
    {
      prev->next = curr->next; // 跳过要删除的节点
      curr->next = free_;      // 放回 free_ 链表
      free_ = curr;
      curr->flag = false;
      printf("Free watchpoint %d succeed!\n", wp->NO);
      return;
    }
    prev = curr;
    curr = curr->next;
  }

  // 情况4：未找到 wp
  printf("Error: Watchpoint %d not found in active list!\n", wp->NO);
}

void sdb_watchpoint_display()
{
  bool flag = true;
  for (int i = 0; i < NR_WP; i++)
  {
    if (wp_pool[i].flag)
    {
      printf("Watchpoint.No: %d, expr = \"%s\", old_value = %d, new_value = %d\n",
             wp_pool[i].NO, wp_pool[i].expr, wp_pool[i].old_value, wp_pool[i].new_value);
      flag = false;
    }
  }
  if (flag)
  {
    printf("No watchpoints existing!\n");
  }
}
void watchpoint_create(char *args)
{
  //printf("%s\n", args);
  bool flag = false;
  int tmp = expr(args, &flag);
  if (flag)
  {
    WP *p = new_wp();
    strncpy(p->expr, args, sizeof(p->expr) - 1); // 安全复制
    p->expr[sizeof(p->expr) - 1] = '\0';
    p->old_value = tmp;
    printf("Create watchpoint No.%d success.\n", p->NO);
  }
  else
    printf("Error in EVAL!\n");

}

void watchpoint_delete(int no)
{
  for (int i = 0; i < NR_WP; i++)
    if (wp_pool[i].NO == no)
    {
      free_wp(&wp_pool[i]);
      return;
    }
}
