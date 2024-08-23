
LOCAL_CFLAGS=
LOCAL_LIBS=
LOCAL_OBJS=lz-compress.o lz_compress_include_input_files.o

lz_compress_include_input_files.o: lz_compress_include_input_files.S
	$(TARGET_CC) $(CFLAGS) -c $< -o $@

PROG=lz-compress

include ../Makefile

test: $(TARGET_EXE)
	-$(TARGET_SIM) ./$(TARGET_EXE) > FOO 
	$(TARGET_DIFF) FOO lz-compress.out
	rm -f FOO

