.section .text
.global _start

# No loads: the host checks memory after every instruction.
.macro exercise value
  li x5, \value
  sw x5, 0(x2)
  sw x5, 4(x2)
  sw x5, 8(x2)
  sw x5, 12(x2)

  sb x5, 16(x2)
  sb x5, 17(x2)
  sb x5, 18(x2)
  sb x5, 19(x2)
  sb x5, 20(x2)
  sb x5, 21(x2)
  sb x5, 22(x2)
  sb x5, 23(x2)

  sh x5, 24(x2)
  sh x5, 26(x2)
  sh x5, 28(x2)
  sh x5, 30(x2)
  sw x5, -4(x2)

  sb x0, 32(x2)
  sh x0, 34(x2)
  sw x0, 36(x2)
.endm

_start:
  li x2, 0x80001400
  exercise 0x12345678
  exercise 0x89abcdef
  exercise 0xffffffff
  exercise 0

  # Both ends of the signed 12-bit immediate, with natural alignment.
  li x2, 0x80001800
  li x5, 0x87654321
  sb x5, -2048(x2)
  sh x5, -2048(x2)
  sw x5, -2048(x2)
  sb x5, 2047(x2)
  sh x5, 2046(x2)
  sw x5, 2044(x2)

  # Use another base register; rs1 and rs2 can be the same register.
  li x6, 0x80001500
  sw x6, 0(x6)
  sb x6, 5(x6)
  sh x6, 6(x6)
  ebreak
