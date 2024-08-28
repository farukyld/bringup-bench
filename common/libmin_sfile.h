// dont include this header in other than libmin_sfile.c
#ifndef LIBMIN_SFILE_H
#define LIBMIN_SFILE_H

#include "libmin.h"
#include "libtarg.h"

#ifndef NULL
#define NULL ((void *)0)
#endif

#define MAX_NAME_LEN 80

// tek bir uart bulundugu ve butun putchar islemleri onun uzerinden tyapildigi icin
// farkli dosyalara yazma islemlerini ayirt etmek icin
// bir dosyaya yazmadan once
// o dosyayla eslestirilmis kacis dizisi (esc. seq.) ile baslanacak.
// terminalde farkli renklerde bastirilmis olacak,
// baremetal ortamda da farkli karakter dizileriyle baslandigi icin
// ayirt edebilmis olacagiz.
// ornegin:
// ```c
// fprintf(stderr, "gonderilen mesaj");
// fflush(stderr);
// ```
// seklinde kullanildiginda,
// uart'tan su sekilde mesaj yayimlanacak:
// "\033[31mgonderilen mesaj\033[0m"

// sonda default kacis dizisinin kullanilmasinin sebebi, (burayi tam anlatamayacagim biliyorum)
// varsayilan olarak (printf'ten gelen) mesajlarin, stdout ile eslestirilmesi icin.

// MAX_OUT_FILES kacis dizilerinin sayisindan kucuk veya esit olmali.
// aksi halde dosyalari ayirt edecek kadar kacis dizisine sahip olmayacagiz
// #define MAX_OUT_FILES 9 // beyaz arka fon uzeri siyah font dahil.
#define MAX_OUT_FILES 8
#define MAX_ESCAPE_LEN 13
#define ESC_DEFAULT  "\033[0m"
// #define ESC_BLACK   "\033[40;47m"
#define ESC_RED      "\033[31m"
#define ESC_GREEN    "\033[32m"
#define ESC_YELLOW   "\033[33m"
#define ESC_BLUE     "\033[34m"
#define ESC_MAGENTA  "\033[35m"
#define ESC_CYAN     "\033[36m"
#define ESC_WHITE    "\033[37m"


#define BUFF_SIZE 256


// r	rb		open for reading (The file must exist)	beginning
// w	wb		open for writing (creates file if it doesn't exist). Deletes content and overwrites the file.	beginning
// a	ab		open for appending (creates file if it doesn't exist)	end
// r+	rb+	r+b	open for reading and writing (The file must exist)	beginning
// w+	wb+	w+b	open for reading and writing. If file exists deletes content and overwrites the file, otherwise creates an empty new file	beginning
// a+	ab+	a+b	open for reading and writing (append if file exists)	end
typedef enum sfile_mode_e
{
  // FMODE_R,
  // FMODE_RB,
  FMODE_W, 
  // FMODE_WB,
  FMODE_A,
  // FMODE_AB,
  // FMODE_RP,
  // FMODE_RBP,
  // FMODE_WP,
  // FMODE_WBP,
  // FMODE_AP,
  // FMODE_ABP
} sfile_mode_e;

struct serial_output_file_t
{
  int64_t file_desc;

  char file_name[MAX_NAME_LEN];

  // butun file'lar tek kanaldan bosaltilacagindan
  // uart vasitasiyla terminale yayinlanan
  // string'in hangi file'a ait oldugu, string'in
  // ilk karakterlerine gore anlasilacak.
  // ayrica terminalde renkli cikti verilmesini de saglayacak.
  // file'a gonderilen string tamamlaninca
  // bir dizi karakter gonderilecek. (default color seq.)
  const char *escape_sequence;

  // kisa kisa string'ler yazildiginda her bir karakter icin
  // tek tek kacis dizisi koymasin,
  // topluca gondersin.
  char out_buff[BUFF_SIZE];

  size_t write_idx;
  sfile_mode_e file_mode;

  struct serial_output_file_t *next;
  struct serial_output_file_t *prev;
};

SFILE *find_file(const char *file_name);

SFILE* create_sfile(const char *file_name,const char *escape, sfile_mode_e mode);

sfile_mode_e str_to_file_mode(const char *mode_str);

void serial_output_init();

const char* request_escape_sequence();

void sflush_safe(SFILE *file);

void release_escape_sequence(const char *esc_seq);


// NOT: bu komponentin (libmin_sfile.c ve libmin_sfile.h) public arayuzu, libmin.h'da tanimli.
#endif // LIBMIN_SFILE_H
