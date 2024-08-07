#include "libmin_sfile.h"
#include "libmin.h"
#include "libtarg.h"
#include <stdarg.h>

static char *escape_sequences[MAX_OUT_FILES] = {
    ESC_DEFAULT,
    ESC_RED,
    ESC_GREEN,
    ESC_YELLOW,
    ESC_BLUE,
    ESC_MAGENTA,
    ESC_CYAN,
    ESC_WHITE};
static bool esc_seq_in_use[MAX_OUT_FILES] = {false};

SFILE *live_files_head = NULL; // bagli listenin basi.
SFILE *live_files_tail = NULL; // bagli listenin sonu.
static size_t live_files_count;
static int64_t file_desc_file;

SFILE *stdout = NULL;
SFILE *stderr = NULL;

int libmin_sfputs(const char *str, SFILE *file)
{
  if (file == NULL || file->file_mode != FMODE_W)
  {
    // errno = EBADF;
    return EOF;
  }
  size_t n = libmin_strlen(str);
  while (file->write_idx + n >= BUFF_SIZE - 1)
  {
    size_t k = BUFF_SIZE - 1 - file->write_idx;
    libmin_strncpy(file->out_buff + file->write_idx, str, k);
    file->write_idx += k;
    sflush_safe(file);
    str += k;
    n -= k;
  }
  libmin_strncpy(file->out_buff + file->write_idx, str, n);
  file->write_idx += n;
  return 0;
}

int libmin_sfputc(int c, SFILE *file)
{
  if (file == NULL || file->file_mode != FMODE_W)
  {
    // errno = EBADF;
    return EOF;
  }
  if (file->write_idx >= BUFF_SIZE - 1)
  {
    sflush_safe(file);
  }
  file->out_buff[file->write_idx++] = c;
  return c;
}

SFILE *create_sfile(char *file_name, char escape, sfile_mode_e mode)
{
  if (!libmin_strfits(file_name, MAX_NAME_LEN))
  {
    libmin_printf("file name cannot exceed %d characters.\n", MAX_NAME_LEN);
    return NULL;
  }

  if (live_files_count >= MAX_OUT_FILES)
  {
    libmin_printf("maximum number of files reached.\n");
    return NULL;
  }

  if (__libmin_file_exists(file_name))
  {
    libmin_printf("cannot create two files with same name.\n");
    return NULL;
  }

  SFILE *fp = (SFILE *)libmin_malloc(sizeof(SFILE));

  fp->file_desc = file_desc_file++;
  libmin_strcpy(fp->file_name, file_name);
  fp->escape_sequence = escape;
  libmin_memset(fp->out_buff, '\0', BUFF_SIZE);
  fp->write_idx = 0;
  fp->file_mode = mode;
  fp->next = NULL;

  if (live_files_head == NULL) // ilk defa eleman ekleniyor.
  {
    live_files_head = fp;
    live_files_tail = fp;
    fp->prev = NULL;
  }
  else if (live_files_head == live_files_tail) // ikinci eleman ekleniyor.
  {
    live_files_tail = fp;
    live_files_head->next = fp;
    fp->prev = live_files_head;
  }
  else // en az iki farkli eleman var
  {
    live_files_tail->next = fp;
    fp->prev = live_files_tail;
  }

  live_files_count++;

  return fp;
}

char *request_escape_sequence()
{
  for (size_t i = 0; i < MAX_OUT_FILES; i++)
  {
    if (!esc_seq_in_use[i])
    {
      esc_seq_in_use[i] = true;
      return escape_sequences[i];
    }
  }
  return NULL;
}

SFILE *find_file(char *file_name)
{
  SFILE *file = live_files_head;
  while (file != NULL)
  {
    if (libmin_strncmp(file->file_name, file_name, MAX_NAME_LEN) == 0)
    {
      return file;
    }
    file = file->next;
  }
  return NULL;
}

void sflush_safe(SFILE *file)
{
  char *s = file->out_buff;
  for (; *s; s++)
    libtarg_putc(*s);
  file->out_buff[file->write_idx] = '\0';
  s = file->out_buff;
  for (; *s; s++)
    libtarg_putc(*s);
  s = ESC_DEFAULT;
  for (; *s; s++)
    libtarg_putc(*s);
  file->write_idx = 0;
}

int libmin_sfflush(SFILE *file)
{
  // file argumani null'sa butun acik dosyalari bosalt.
  if (file == NULL)
  {
    SFILE *file = live_files_head;
    while (file != NULL)
    {
      sflush_safe(file);
      file = file->next;
    }
  }
  else
  {
    sflush_safe(file);
  }
  return 0;
}

SFILE *libmin_sfopen(const char *fname, const char *mode)
{
  sfile_mode_e mode = get_file_mode(mode);
  char *esc_seq = request_escape_sequence();
  return create_sfile((char *)fname, esc_seq, mode);
}

sfile_mode_e get_file_mode(char *mode)
{
  if (libmin_strncmp(mode, "w", 2) == 0)
  {
    return FMODE_W;
  }
  else
  {
    libmin_printf("libmin sfile only support mode.\n");
    libmin_exit(1);
  }
}

void serial_output_init()
{
  file_desc_file = 1; // 0, stdin icin ayrilmistir.
  stdout = create_sfile("stdout", ESC_DEFAULT, FMODE_W);
  stderr = create_sfile("stderr", ESC_RED, FMODE_W);
  for (size_t i = 0; i < MAX_OUT_FILES; i++)
  {
    if (libmin_strncmp(ESC_DEFAULT, escape_sequences[i], MAX_ESCAPE_LEN) == 0)
    {
      esc_seq_in_use[i] = true;
    }
    else if (libmin_strncmp(ESC_RED, escape_sequences[i], MAX_ESCAPE_LEN) == 0)
    {
      esc_seq_in_use[i] = true;
    }
  }
}
