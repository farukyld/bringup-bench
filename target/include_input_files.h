#define REGISTER_FILE(name, no_dots_name) \
    .section .rodata; \
    file_##no_dots_name: .string #name; \
    .section .content; \
    content_##no_dots_name##_start:; \
    .incbin #name; \
    content_##no_dots_name##_end:; \
    .section .index; \
    .balign 8; \
    .global index_##no_dots_name##_fname;\
    index_##no_dots_name##_fname: .dword file_##no_dots_name; \
    .balign 8; \
    .global index_##no_dots_name##_content_start; \
    index_##no_dots_name##_content_start: .dword content_##no_dots_name##_start; \
    .balign 8; \
    .global index_##no_dots_name##_content_end; \
    index_##no_dots_name##_content_end: .dword content_##no_dots_name##_end; \


// kullanim:
// REGISTER_FILE(asdfasdf.txt, asdfasdf_txt)
