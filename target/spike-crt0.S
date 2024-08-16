# Copyright lowRISC contributors.
# Licensed under the Apache License, Version 2.0, see LICENSE for details.
# SPDX-License-Identifier: Apache-2.0

#define SIM_CTRL_BASE 0x20000
#define SIM_CTRL_OUT 0x0
#define SIM_CTRL_CTRL 0x8

#define TIMER_BASE 0x30000
#define TIMER_MTIME 0x0
#define TIMER_MTIMEH 0x4
#define TIMER_MTIMECMP 0x8
#define TIMER_MTIMECMPH 0xC

.section .text

default_exc_handler:
  # addi sp, sp, -256
  # sd x1,    0(sp)
  # sd x2,    8(sp)
  # sd x3,   16(sp)
  # sd x4,   24(sp)
  # sd x5,   32(sp)
  # sd x6,   40(sp)
  # sd x7,   48(sp)
  # sd x8,   56(sp)
  # sd x9,   64(sp)
  # sd x10,  72(sp)
  # sd x11,  80(sp)
  # sd x12,  88(sp)
  # sd x13,  96(sp)
  # sd x14, 104(sp)
  # sd x15, 112(sp)
  # sd x16, 120(sp)
  # sd x17, 128(sp)
  # sd x18, 136(sp)
  # sd x19, 144(sp)
  # sd x20, 152(sp)
  # sd x21, 160(sp)
  # sd x22, 168(sp)
  # sd x23, 176(sp)
  # sd x24, 184(sp)
  # sd x25, 192(sp)
  # sd x26, 200(sp)
  # sd x27, 208(sp)
  # sd x28, 216(sp)
  # sd x29, 224(sp)
  # sd x30, 232(sp)
  # sd x31, 240(sp)
  csrr t0, mepc
  sd t0, -8(sp)
  
  # sd t0, 248(sp)
  la t0, wait
  li t1, 0x1
  sw t1, 0(t0)
  call libtarg_debug_wait_loop
  # call libtarg_fail

timer_handler:
  jal x0, timer_handler

reset_handler:
#if GDB_DEBUG
  call libtarg_debug_wait_loop
#endif
  /* set all registers to zero */
  la t0, _vectors_start
  csrw mtvec,t0
#if PRINT_CYCLES_ON_EXIT
  csrr t0, mcycle
  la t1, start_cycles
  sd t0, 0(t1)
#endif
  mv  x1, x0
  mv  x2, x1
  mv  x3, x1
  mv  x4, x1
  mv  x5, x1
  mv  x6, x1
  mv  x7, x1
  mv  x8, x1
  mv  x9, x1
  mv x10, x1
  mv x11, x1
  mv x12, x1
  mv x13, x1
  mv x14, x1
  mv x15, x1
  mv x16, x1
  mv x17, x1
  mv x18, x1
  mv x19, x1
  mv x20, x1
  mv x21, x1
  mv x22, x1
  mv x23, x1
  mv x24, x1
  mv x25, x1
  mv x26, x1
  mv x27, x1
  mv x28, x1
  mv x29, x1
  mv x30, x1
  mv x31, x1

  /* stack initilization */
  # l1: lui x2, %pcrel_hi(_stack_start)
  # addi x2, x2, %lo(l1)
  la   sp, _stack_start
  # sp'yi 8 byte hizala
  li t0, 7
  xori t0, t0, -1
  and sp, sp, t0
  
_start:
  .global _start

  /* clear BSS */
  la x26, _bss_start
  la x27, _bss_end

  bge x26, x27, zero_loop_end

zero_loop:
  sw x0, 0(x26)
  addi x26, x26, 4
  ble x26, x27, zero_loop
zero_loop_end:


main_entry:
  /* jump to main program entry point (argc = argv = 0) */
  addi x10, x0, 0
  addi x11, x0, 0
  call serial_output_init
#if HARD_FLOAT
  li t1, 0x6000
  csrrs x0, mstatus, t1
#endif

  jal x1, main
  /* Halt simulation */
  li a0, 0 # sfflush null arguman ile cagrildiginda butun dosyalari flush'lar.
  call libmin_sfflush
  call libmin_success

  /* If execution ends up here just put the core to sleep */
sleep_loop:
  wfi
  j sleep_loop

/* =================================================== [ exceptions ] === */
/* This section has to be down here, since we have to disable rvc for it  */

  .section .vectors, "ax"
  .option norvc;

  // All unimplemented interrupts/exceptions go to the default_exc_handler.
  .org 0x00
  .rept 7
  jal x0, default_exc_handler
  .endr
  jal x0, timer_handler
  .rept 23
  jal x0, default_exc_handler
  .endr

  // reset vector
  .org 0x80
  jal x0, reset_handler

.section .data
# fmt_string:  .string "\nmcycle difference: %d\n"
.global start_cycles
.balign 8
start_cycles: .dword 0x0000000000000000
