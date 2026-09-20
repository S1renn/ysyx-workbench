.section .text
.global _start

_start:
  lui x2, 0x80000
  addi x2, x2, 0x20
  
  lw x5, 0(x2)

  addi x10, x0, 0
  ebreak
  
  .org  0x20

data:
  .word 0x12345678

