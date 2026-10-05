#include <Vtop__Dpi.h>
#include <elf.h>
#include "../utils.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cstddef>
#include "../../include/generated/autoconf.h"

typedef struct {
  char name[64];
  uint32_t addr;
  size_t size;
} Symbol;

static Symbol *sym_table = NULL;
static int nr_sym = 0;
static int stack_depth = 0;







void init_ftrace(const char *elf_file) {
  if (elf_file == NULL) return;

  FILE *fp = fopen(elf_file, "rb");
  
  assert(fp != NULL);

  Elf32_Ehdr ehdr;
  if (fread(&ehdr, sizeof(Elf32_Ehdr), 1, fp) != 1) assert(0);

  fseek(fp, ehdr.e_shoff, SEEK_SET);
  Elf32_Shdr *shdrs = (Elf32_Shdr *)malloc(ehdr.e_shnum * sizeof(Elf32_Shdr));
  if (fread(shdrs, sizeof(Elf32_Shdr), ehdr.e_shnum, fp) != ehdr.e_shnum) assert(0);

  for (int i = 0; i < ehdr.e_shnum; i++) {
    if (shdrs[i].sh_type == SHT_SYMTAB) {
      nr_sym = shdrs[i].sh_size / sizeof(Elf32_Sym);
      sym_table = (Symbol *)malloc(nr_sym * sizeof(Symbol));
      
      Elf32_Sym *elf_syms = (Elf32_Sym *)malloc(shdrs[i].sh_size);
      fseek(fp, shdrs[i].sh_offset, SEEK_SET);
      if (fread(elf_syms, shdrs[i].sh_size, 1, fp) != 1) assert(0);

      Elf32_Shdr *str_sh = &shdrs[shdrs[i].sh_link];
      char *strtab = (char *)malloc(str_sh->sh_size);
      fseek(fp, str_sh->sh_offset, SEEK_SET);
      if (fread(strtab, str_sh->sh_size, 1, fp) != 1) assert(0);

      int k = 0;
      for (int j = 0; j < nr_sym; j++) {
        unsigned char type = ELF32_ST_TYPE(elf_syms[j].st_info);
        char *sym_name = strtab + elf_syms[j].st_name;
        if ((type == STT_FUNC || type == STT_NOTYPE) && elf_syms[j].st_name != 0 && elf_syms[j].st_value != 0) {
          if (strncmp(sym_name, "$", 1) == 0) continue;
          
          sym_table[k].addr = elf_syms[j].st_value;
          sym_table[k].size = elf_syms[j].st_size;
          strncpy(sym_table[k].name, sym_name, 63);
          k++;
        }
      }
      nr_sym = k;
      free(elf_syms);
      free(strtab);
      break;
    }
  }
  printf("[ftrace] Loaded %d symbols from %s\n", nr_sym, elf_file);
  free(shdrs);
  fclose(fp);
}

















static __attribute__((unused)) const char* find_func_name(uint64_t addr) { //告诉编译器：“我知道它可能没被用到，别报错”。

  int target_idx = -1;
  uint32_t min_diff = (uint32_t)-1;

  for (int i = 0; i < nr_sym; i++) {
    if (addr >= sym_table[i].addr) {
      uint32_t diff = addr - sym_table[i].addr;
      if (diff < min_diff) {
        min_diff = diff;
        target_idx = i;
      }
    }
  }

  if (target_idx != -1) {
    return sym_table[target_idx].name;
  }
  return "???";
}

extern "C" void log_ftrace(int pc, int target, svBit is_return) {
  //printf("DEBUG: DPI-C Trigggered! PC=0x%08x\n", pc);
    uint32_t u_pc = (uint32_t)pc;
    uint32_t u_target = (uint32_t)target;
    //printf("DEBUG: pc=0x%08x, is_ret=%d\n", pc, is_return);
  if (is_return) {
    stack_depth--;
    if (stack_depth < 0) stack_depth = 0;
 
    #ifdef CONFIG_FTRACE
    printf("0x%08x: %*s \033[1;34mret\033[0m  [%s]\n", 
       pc, 
       stack_depth * 2, "", 
       find_func_name(pc));
  } else {
    printf("0x%08x: %*s \033[1;32mcall\033[0m [%s@0x%08x]\n", 
       pc, 
       stack_depth * 2, "", 
       find_func_name(target), 
       target);
      #endif
       
    stack_depth++;
  }
}
