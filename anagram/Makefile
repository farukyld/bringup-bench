
LOCAL_CFLAGS=
LOCAL_LIBS=
# NOT: anagram_input_files.S dosyasi, sadece libmin'le derlenecegi zaman kulalnilmalidir.
LOCAL_OBJS=anagram.o anagram_input_files.o

anagram_input_files.o: anagram_input_files.S
	$(TARGET_CC) $(TARGET_CFLAGS) -c anagram_input_files.S -o anagram_input_files.o

PROG=anagram

include ../Makefile

test: $(TARGET_EXE)
	-$(TARGET_SIM) ./$(TARGET_EXE) words > FOO 
	$(TARGET_DIFF) FOO anagram.out
	rm -f FOO

