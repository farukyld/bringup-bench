
LOCAL_CFLAGS=
LOCAL_GDB_FLAGS=
LOCAL_LIBS=
LOCAL_OBJS=checkers.o consttypes.o functions.o checkers_include_input_files.o

checkers_include_input_files.o: checkers_include_input_files.S
	$(TARGET_CC) $(CFLAGS) -c $< -o $@


PROG=checkers

include ../Makefile

test: $(TARGET_EXE)
	-$(TARGET_SIM) ./$(TARGET_EXE) > FOO 
	$(TARGET_DIFF) FOO checkers.out
	rm -f FOO

