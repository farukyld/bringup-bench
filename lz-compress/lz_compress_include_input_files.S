#define REGISTER_FILE(name) \
    .section .rodata; \
    file_##name: .string #name; \
    .section .content; \
    content_##name##_start:; \
    .incbin #name; \
    content_##name##_end:; \
    .section .index; \
    .dword file_##name; \
    .dword content_##name##_start; \
    .dword content_##name##_end;


REGISTER_FILE("Lamia.txt")
