
LOCAL_CFLAGS=
LOCAL_GDB_FLAGS=
LOCAL_LIBS=
LOCAL_OBJS=c-interp.o c_interp_include_input_files.o

PROG=c-interp

c_interp_include_input_files.o: c_interp_include_input_files.S
	$(TARGET_CC) $(CFLAGS) -c $< -o $@

include ../Makefile

test: $(TARGET_EXE)
	-$(TARGET_SIM) ./$(TARGET_EXE) hello.c > FOO 
	$(TARGET_DIFF) FOO c-interp.out
	rm -f FOO

