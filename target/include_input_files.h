#ifndef INCLUDE_INPUT_FILES_H
#define INCLUDE_INPUT_FILES_H



#ifdef THREE_ARGUMENT_VERSION


#define REGISTER_FILE(access_path,include_path, no_dots_name) \
    .section .rodata; \
    file_##no_dots_name: .string #access_path; \
    .section .content; \
    content_##no_dots_name##_start:; \
    .incbin #include_path; \
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
// access_path: kodun icinde fopen("access_path", "r") seklinde acilacak.
// include_path: bu makronun kullanildigi dosyaya gore idhal edilecek dosyanin konumu
// no_dots_name: assembly kodunun icinde sembol isimlendirmede kulllanilacak olan isim
// REGISTER_FILE(asdfasdf.txt, ../input/asdfasdf.txt, asdfasdf_txt)

#else


#define REGISTER_FILE(include_path, no_dots_name) \
    .section .rodata; \
    file_##no_dots_name: .string #include_path; \
    .section .content; \
    content_##no_dots_name##_start:; \
    .incbin #include_path; \
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
// include_path: bu makronun kullanildigi dosyaya gore idhal edilecek dosyanin konumu, kodun icinde de ayni konumla erismelisiniz
// no_dots_name: assembly kodunun icinde sembol isimlendirmede kulllanilacak olan isim
// REGISTER_FILE(asdfasdf.txt, ../input/asdfasdf.txt, asdfasdf_txt)


#endif

#endif