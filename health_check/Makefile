
LOCAL_CFLAGS=
LOCAL_LIBS=
LOCAL_OBJS=health_check.o

PROG=health_check

include ../Makefile

test: $(TARGET_EXE)
	-$(TARGET_SIM) ./$(TARGET_EXE) > FOO 
	$(TARGET_DIFF) FOO health_check.out
	rm -f FOO

gdb: $(TARGET_EXE)
	riscv64-unknown-elf-gdb \
	-ex "target extended-remote:3333" \
	-ex "lay split" \
	-ex "print wait=0" \
	$(TARGET_EXE)

disassembled.s: $(TARGET_EXE)
	riscv64-unknown-elf-objdump -D $(TARGET_EXE) > disassembled.s; code disassembled.s

.PHONY: test gdb disassembled.s