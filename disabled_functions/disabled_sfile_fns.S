
.section .text

libmin_fputc:
fputc:
libmin_sfputc:
sfputc:
# birinci argumanini dondurecek (a0)
  ret

libmin_fputs:
fputs:
libmin_sfputs:
sfputs:
  li a0,0
  ret

libmin_fwrite:
fwrite:
libmin_sfwrite:
sfwrite:
  mv a0,a2
  ret

libmin_fprintf:
fprintf:
libmin_vfprintf:
vfprintf:
  li a0,0
  ret

libmin_fflush:
fflush:
libmin_sfflush:
sfflush:
  li a0,0
  ret

create_sfile:
  li a0,0
  ret

request_escape_sequence:
  li a0,0
  ret

find_file:
  li a0,0
  ret

sflush_safe:
  ret

libmin_sfopen:
sfopen:
  li a0,0
  ret

str_to_file_mode:
  li a0,0
  ret

serial_output_init:
  ret

libmin_sfclose:
sfclose:
  li a0,0
  ret

release_escape_sequence:
  ret
