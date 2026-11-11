.section .text
.global _start

.macro expect reg, value
  li t1, \value
  bne \reg, t1, fail
.endm

_start:
  li a0, 1
  li sp, 0x80001000
  li t0, 0x80ff7f01
  sw t0, 0(sp)

  lw a1, 0(sp)
  expect a1, 0x80ff7f01
  lb a1, 0(sp)
  expect a1, 1
  lb a1, 1(sp)
  expect a1, 127
  lb a1, 2(sp)
  expect a1, -1
  lb a1, 3(sp)
  expect a1, -128
  lbu a1, 2(sp)
  expect a1, 255
  lbu a1, 3(sp)
  expect a1, 128
  lh a1, 0(sp)
  expect a1, 0x7f01
  lh a1, 2(sp)
  expect a1, 0xffff80ff
  lhu a1, 2(sp)
  expect a1, 0x80ff

  li t0, 0xa5
  sb t0, 1(sp)
  lw a1, 0(sp)
  expect a1, 0x80ffa501
  li t0, 0x1234
  sh t0, 2(sp)
  lw a1, 0(sp)
  expect a1, 0x1234a501

  sw zero, 4(sp)
  lw a1, 4(sp)
  expect a1, 0
  li t0, -1
  sb t0, 5(sp)
  sh t0, 6(sp)
  lw a1, 4(sp)
  expect a1, 0xffffff00

  # Taken and non-taken branches must both fetch from the committed PC.
  li t2, 3
loop:
  addi t2, t2, -1
  bne t2, zero, loop

  jal ra, helper
  expect a5, 42

  # CSR writes must happen once, at commit, despite long fetch waits.
  li t0, 0x800
  csrrw a1, mtvec, t0
  expect a1, 0
  csrrs a1, mtvec, zero
  expect a1, 0x800

  li a0, 0
  ebreak
fail:
  li a0, 1
  ebreak
helper:
  li a5, 42
  ret
