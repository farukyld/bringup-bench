
LOCAL_CFLAGS=
LOCAL_LIBS=
LOCAL_OBJS=health_check.o health_check_include_input_files.o

PROG=health_check

health_check_include_input_files.o: health_check_include_input_files.S
	$(TARGET_CC) $(CFLAGS) -c $< -o $@

include ../Makefile

test: $(TARGET_EXE)
	-$(TARGET_SIM) ./$(TARGET_EXE) > FOO 
	$(TARGET_DIFF) FOO health_check.out
	rm -f FOO
