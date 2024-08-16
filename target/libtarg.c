#include "libtarg.h"
#include "libmin.h"

#if defined(TARGET_HOST)
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#elif defined(TARGET_SA)
/* standalone */
#include <stdio.h>
#include <stdlib.h>
#define MAX_SPIN 10000 /* make this larger for a real hardware platform */
#elif defined(TARGET_SPIKE)

// bu fonksiyon, gdb ile birlikte kullanilmak uzere tasarlandi
volatile int wait = 1;
void libtarg_debug_wait_loop()
{
  while (wait)
    ;
}

time_t libtarg_get_cycles()
{
  time_t result;
  __asm__ volatile("csrr %0, mcycle" : "=r"(result));
  return result;
}

void *
memset(void *dest, int val, size_t len)
{
  return libmin_memset(dest, val, len);
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

#ifdef PRINT_CYCLES_ON_EXIT
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

#elif defined(TARGET_SIMPLE) || defined(TARGET_SPIKE_TODDMAUSTIN)
#include <stdlib.h>

/* simple system MMAP'ed registers */
#define SIMPLE_CTRL_BASE 0x20000
#define SIMPLE_CTRL_OUT 0x0
#define SIMPLE_CTRL_CTRL 0x8

/* MMAP'ed register accessors */
#define SIMPLE_DEV_WRITE(addr, val) (*((volatile uint32_t *)(addr)) = val)
#define SIMPLE_DEV_READ(addr, val) (*((volatile uint32_t *)(addr)))

extern inline int
simple_putchar(char c)
{
  SIMPLE_DEV_WRITE(SIMPLE_CTRL_BASE + SIMPLE_CTRL_OUT, (unsigned char)c);
  return c;
}

extern inline void
simple_halt(void)
{
  SIMPLE_DEV_WRITE(SIMPLE_CTRL_BASE + SIMPLE_CTRL_CTRL, 1);
}

void *
memset(void *dest, int val, size_t len)
{
  return libmin_memset(dest, val, len);
}

void *
memcpy(void *dest, const void *src, size_t len)
{
  return libmin_memcpy(dest, src, len);
}

extern inline uint32_t
simple_get_mepc(void)
{
  uint32_t result;
  __asm__ volatile("csrr %0, mepc" : " = r "(result));
  return result;
}

extern inline uint32_t
simple_get_mcause(void)
{
  uint32_t result;
  __asm__ volatile("csrr %0, mcause" : "=r"(result));
  return result;
}

extern inline uint32_t
simple_get_mtval(void)
{
  uint32_t result;
  __asm__ volatile("csrr %0, mtval" : "=r"(result));
  return result;
}

void simple_exc_handler(void)
{
  libmin_printf("EXCEPTION!!!\n");
  libmin_printf("============\n");
  libmin_printf("MEPC:0x%08x, CAUSE:0x%08x, MTVAL:0x%08x\n", simple_get_mepc(), simple_get_mcause(), simple_get_mtval());

  simple_halt();
  while (1)
    ;
}

void simple_timer_handler(void)
{
  libmin_printf("TIMER EXCEPTION!!!\n");

  simple_halt();
  while (1)
    ;
}

#else /* undefined target */
#error Co-simulation platform not defined, define TARGET_HOST or a target-dependent definition.
#endif

#ifdef TARGET_SA
#define MAX_OUTBUF (128 * 1024)
static uint8_t __outbuf[MAX_OUTBUF];
static uint32_t __outbuf_ptr = 0;
#endif /* TARGET_SA */

/* benchmark completed successfully */
void libtarg_success(void)
{
#if defined(TARGET_HOST)
  exit(0);
#elif defined(TARGET_SA)
  uint64_t spincnt = 0;
  /* spin @ SPIN_SUCCESS_ADDR */
SPIN_SUCCESS_ADDR:
  spincnt++;
  if (spincnt < MAX_SPIN)
    goto SPIN_SUCCESS_ADDR;

  /* output any outbuf data */
  for (uint32_t i = 0; i < __outbuf_ptr; i++)
    fputc(__outbuf[i], stdout);

  /* exit if we ever get here */
  exit(0);
#elif defined(TARGET_SPIKE)
  baremetal_exit(0);
#elif defined(TARGET_SIMPLE) || defined(TARGET_SPIKE_TODDMAUSTIN)
  // libmin_printf("EXIT: success\n");
  simple_halt();
#else
#error Co-simulation platform not defined, define TARGET_HOST or a target-dependent definition.
#endif
}

/* benchmark completed with error CODE */
void libtarg_fail(int code)
{
#ifdef TARGET_HOST
  exit(code);
#elif defined(TARGET_SA)
  uint64_t spincnt = 0;
  /* spin @ SUCCESS_SPIN_ADDR */
SPIN_FAIL_ADDR:
  spincnt++;
  if (spincnt < MAX_SPIN)
    goto SPIN_FAIL_ADDR;
  /* exit if we ever get here */
  exit(code);
#elif defined(TARGET_SPIKE)
  baremetal_exit(code);
#elif defined(TARGET_SIMPLE) || defined(TARGET_SPIKE_TODDMAUSTIN)
  // libmin_printf("EXIT: fail code = %d\n", code);
  simple_halt();
#else
#error Co-simulation platform not defined, define TARGET_HOST or a target-dependent definition.
#endif
}

/* output a single character, to wherever the target wants to send it... */
void libtarg_putc(char c)
{
#if defined(TARGET_HOST)
  fputc(c, stdout);
#elif defined(TARGET_SA)
  /* add to outbuf pool */
  if (__outbuf_ptr >= MAX_OUTBUF)
    libtarg_fail(1);
  __outbuf[__outbuf_ptr++] = c;
#elif defined(TARGET_SPIKE)
  uart_putchar(c);
#elif defined(TARGET_SIMPLE) || defined(TARGET_SPIKE_TODDMAUSTIN)
  simple_putchar(c);
#else
#error Co-simulation platform not defined, define TARGET_HOST or a target-dependent definition.
#endif
}

#if defined(TARGET_SA)
#define MAX_HEAP (8 * 1024 * 1024)
#endif /* TARGET_SA */

#if defined(TARGET_SIMPLE) || defined(TARGET_SPIKE_TODDMAUSTIN)
#define MAX_HEAP (32 * 1024)

static uint8_t __heap[MAX_HEAP];
static uint32_t __heap_ptr = 0;
#endif /* TARGET_SIMPLE || TARGET_SPIKE_TODDMAUSTIN */

#if defined(TARGET_SPIKE)
#define MAX_HEAP (4llu * 1024llu * 1024llu * 1024llu)
static uint8_t __heap[MAX_HEAP] __attribute__((section(".heap")));
// extern uint8_t _heap_start;
// extern uint8_t _heap_end;
// static uint8_t *__heap = &_heap_start;
static uint32_t __heap_ptr = 0;
#endif

/* get some memory */
void *
libtarg_sbrk(size_t inc)
{
#if defined(TARGET_HOST)
#if __clang__
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
#endif /* __clang__ */
  return sbrk(inc);
#elif defined(TARGET_SA) || defined(TARGET_SIMPLE) || defined(TARGET_SPIKE_TODDMAUSTIN) || defined(TARGET_SPIKE)
  uint8_t *ptr = &__heap[__heap_ptr];
  if (inc == 0)
    return ptr;

  __heap_ptr += inc;
#ifdef PRINT_MAX_HEAP_ON_EXIT
  if (__heap_ptr > max_heap_pointer)
  {
    max_heap_pointer = __heap_ptr;
  }
#endif

  if (__heap_ptr >= MAX_HEAP)
  {
    libmin_printf("sbrk failed, requested inc: %d\n", inc);
    libtarg_fail(1);
  }

  return ptr;
#else
#error Co-simulation platform not defined, define TARGET_HOST or a target-dependent definition.
#endif
}
