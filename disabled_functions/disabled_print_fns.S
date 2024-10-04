.section .text


#ifdef ALIAS_RM_LIBMIN
#define ALIAS_ADD_LIBMIN
#else
#define ADD_LIBMIN
#endif

#include "assembly_function_macros.h"


ASM_FUNCTION_LABEL(printf)
  li a0,0
  ret

ASM_FUNCTION_LABEL(vprintf)
  li a0,0
  ret

ASM_FUNCTION_LABEL(sprintf)
  li a0,0
  ret

ASM_FUNCTION_LABEL(vsprintf)
  li a0,0
  ret

ASM_FUNCTION_LABEL(snprintf)
  li a0,0
  ret

ASM_FUNCTION_LABEL(vsnprintf)
  li a0,0
  ret

ASM_FUNCTION_LABEL(puts)
  li a0,0
  ret

ASM_FUNCTION_LABEL(putc)
  # birinci argumani dondurecek (a0)
  ret

ASM_FUNCTION_LABEL(put_char)
  # birinci argumani dondurecek (a0)
  ret

#undef ASM_FUNCTION_LABEL
#undef ALIAS_ADD_LIBMIN
#undef ADD_LIBMIN
#undef ASSEMBLY_FUNCTION_MACROS_H
#include "assembly_function_macros.h"

# bu asagidakiler icin alias tanimlamiyoruz. onlar sadece kendi isimleriyle mevcut
ASM_FUNCTION_LABEL(uart_putchar)
  # birinci argumani dondurecek (a0)
  ret

ASM_FUNCTION_LABEL(libtarg_putc)
  # void
  ret
