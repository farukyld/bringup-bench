.section .text


#ifdef ALIAS_RM_LIBMIN
#define ALIAS_ADD_LIBMIN
#else
#define ADD_LIBMIN
#endif

#include "assembly_function_macros.h"


ASM_FUNCTION_LABEL(fputc)
ASM_FUNCTION_LABEL(sfputc)
  # birinci argumanini dondurecek (a0)
  ret

ASM_FUNCTION_LABEL(fputs)
ASM_FUNCTION_LABEL(sfputs)
  li a0,0
  ret

ASM_FUNCTION_LABEL(fwrite)
ASM_FUNCTION_LABEL(sfwrite)
  mv a0,a2
  ret

ASM_FUNCTION_LABEL(fprintf)
ASM_FUNCTION_LABEL(sfprintf)
  li a0,0
  ret

ASM_FUNCTION_LABEL(vfprintf)
ASM_FUNCTION_LABEL(vsfprintf)
  li a0,0
  ret

ASM_FUNCTION_LABEL(fflush)
ASM_FUNCTION_LABEL(sfflush)
  li a0,0
  ret

ASM_FUNCTION_LABEL(sfopen)
  li a0,0
  ret

ASM_FUNCTION_LABEL(sfclose)
  li a0,0
  ret

#undef ASM_FUNCTION_LABEL
#undef ALIAS_ADD_LIBMIN
#undef ADD_LIBMIN
#undef ASSEMBLY_FUNCTION_MACROS_H
#include "assembly_function_macros.h"

# bu asagidakiler icin alias tanimlamiyoruz. onlar sadece kendi isimleriyle mevcut
ASM_FUNCTION_LABEL(create_sfile)
  li a0,0
  ret

ASM_FUNCTION_LABEL(request_escape_sequence)
  li a0,0
  ret

ASM_FUNCTION_LABEL(find_file)
  li a0,0
  ret

ASM_FUNCTION_LABEL(sflush_safe)
  ret


ASM_FUNCTION_LABEL(str_to_file_mode)
  li a0,0
  ret

ASM_FUNCTION_LABEL(serial_output_init)
  ret

ASM_FUNCTION_LABEL(release_escape_sequence)
  ret
