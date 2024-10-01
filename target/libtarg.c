#include "libtarg.h"
#include "libmin.h"

#if GDB_DEBUG
// bu fonksiyon, gdb ile birlikte kullanilmak uzere tasarlandi
volatile int wait = 1;
void libtarg_debug_wait_loop()
{
  while (wait)
    ;
}
#endif

time_t libtarg_get_cycles()
{
  time_t result;
  __asm__ volatile("csrr %0, mcycle" : "=r"(result));
  return result;
}

void *
memcpy(void *dest, const void *src, size_t len)
{
  return libmin_memcpy(dest, src, len);
}

int uart_putchar(char c)
{
  // TODO NS16550_BASE spike'tan alinacak. riscv/platform.h
  // TODO [NS16550_BASE + UART_LSR][UART_LSR_THRE] == 0 degilse bekle
  // TODO assembly yerine c ile yaz.
  __asm__ volatile(
      "li t0, 0x10000000\n"
      "sb a0, 0(t0)\n");
  return c;
}

volatile static long long int magic_mem[8]; // ismi onemli degil.

volatile static long long int *tohost __attribute__((used));   // bunlarin ismi onemli
volatile static long long int *fromhost __attribute__((used)); //

#if PRINT_CYCLES_ON_EXIT
extern uint64_t start_cycles;
#endif

#ifdef PRINT_MAX_HEAP_ON_EXIT
static uint64_t max_heap_pointer;
#endif

void baremetal_exit(long long int exit_code)
{
#if PRINT_CYCLES_ON_EXIT
  uint64_t current_cycles = libtarg_get_cycles();
  libmin_printf("\nmcycle difference: %llu\n", current_cycles - start_cycles);
#endif
#ifdef PRINT_MAX_HEAP_ON_EXIT
  libmin_printf("\nmax heap_ptr: %llu\n", max_heap_pointer);
#endif
  magic_mem[1] = exit_code;
  magic_mem[0] = 93; // 93: exit
  // see riscv-isa-sim/fesvr/syscall.cc }}
  // syscall_t::syscall_t
  for (int i = 2; i < 8; i++)
    magic_mem[i] = 0;

  tohost = magic_mem;

  while (!fromhost)
    ;
  fromhost = 0;
  while (1)
    ;
}

/* benchmark completed successfully */
void libtarg_success(void)
{
  baremetal_exit(0);
}

/* benchmark completed with error CODE */
void libtarg_fail(int code)
{
  baremetal_exit(code);
}

/* output a single character, to wherever the target wants to send it... */
void libtarg_putc(char c)
{
  uart_putchar(c);
}
#ifndef HEAP_LENGTH
#define HEAP_LENGTH 0x1000
#endif
extern uint8_t _heap_start;
static uint32_t __heap_ptr = 0;

/* get some memory */
void *
libtarg_sbrk(size_t inc)
{
  static uint8_t *__heap = &_heap_start;
  uint8_t *ptr = &__heap[__heap_ptr];
  if (inc == 0)
    return ptr;

  __heap_ptr += inc;
  // check if 8 byte aligned
  if (__heap_ptr % 8 != 0)
  {
    // libmin_printf("heap_ptr not aligned: %d\n", __heap_ptr);
    __heap_ptr += 8 - (__heap_ptr % 8);
  }
#ifdef PRINT_MAX_HEAP_ON_EXIT
  if (__heap_ptr > max_heap_pointer)
  {
    max_heap_pointer = __heap_ptr;
  }
#endif

  if (__heap_ptr >= HEAP_LENGTH)
  {
    libmin_printf("sbrk failed, requested inc: %d\n", inc);
    libtarg_fail(1);
  }

  return ptr;
}
