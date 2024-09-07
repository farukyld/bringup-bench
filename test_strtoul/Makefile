
LOCAL_CFLAGS=
LOCAL_GDB_FLAGS=
LOCAL_LIBS=
LOCAL_OBJS=test_strtoul.o

PROG=test_strtoul

include ../Makefile

test: $(TARGET_EXE)
	-$(TARGET_SIM) ./$(TARGET_EXE) > FOO 
	$(TARGET_DIFF) FOO test_strtoul.out
	rm -f FOO

