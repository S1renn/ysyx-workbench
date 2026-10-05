.section .text
.global _start

_start:
  lui x2, 0x80000
  addi x2, x2, 0x100

  lui x5, 0x12345
  addi x5, x5, 0x678

  sw x5, 0(x2)
  lw x7, 0(x2)
  ebreak

