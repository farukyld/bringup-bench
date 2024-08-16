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
  csrr t0, mepc
  sd t0, -8(sp)

#if GDB_DEBUG
  # sd t0, 248(sp)
  la t0, wait
  li t1, 0x1
  sw t1, 0(t0)
  call libtarg_debug_wait_loop
#else
  call libtarg_fail
#endif

timer_handler:
  jal x0, timer_handler

reset_handler:
#if GDB_DEBUG
  call libtarg_debug_wait_loop
#endif
  /* set all registers to zero */
  la t0, _vectors_start
  csrw mtvec,t0
  csrr t1,mtvec
  beq t1,t0,mtvec_set_successfull
  la   sp, _stack_start
  # sp'yi 8 byte hizala
  li t0, 7
  xori t0, t0, -1
  and sp, sp, t0
  call libtarg_fail
mtvec_set_successfull:
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
