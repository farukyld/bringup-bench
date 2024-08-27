
LOCAL_CFLAGS=
LOCAL_GDB_FLAGS=
LOCAL_LIBS=
LOCAL_OBJS=satomi.o cnf_reader.o solver.o satomi_include_input_files.o

PROG=satomi

satomi_include_input_files.o: satomi_include_input_files.S
	$(TARGET_CC) $(CFLAGS) -c $< -o $@


include ../Makefile

test: $(TARGET_EXE)
	-$(TARGET_SIM) ./$(TARGET_EXE) zebra_v155_c1135.cnf > FOO 
	$(TARGET_DIFF) FOO satomi.out
	rm -f FOO

