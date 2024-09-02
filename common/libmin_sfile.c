#include "libmin_sfile.h"
#include "libmin.h"
#include "libtarg.h"
#include <stdarg.h>

static const char *const escape_sequences[MAX_OUT_FILES] = {
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
  if (file == NULL || !(file->file_mode == FMODE_W || file->file_mode == FMODE_A))
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

SFILE *create_sfile(const char *file_name, const char *escape, sfile_mode_e mode)
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
  // mode append ise ayni isimde dosya olabilir.
  SFILE *found_file = find_file(file_name);
  if (found_file != NULL)
  {
    if (mode != FMODE_A)
    {
      libmin_printf("cannot create two files with same name.\n");
      return NULL;
    }
    else
    {
      // ayni isimde dosya varsa ve append modda tekrar acilmak isteniyorsa
      // mevcut dosyayi dondur.
      return found_file;
    }
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
    SFILE *old_tail = live_files_tail;
    old_tail->next = fp;
    fp->prev = old_tail;
    live_files_tail = fp;
  }

  live_files_count++;

  return fp;
}

const char *request_escape_sequence(const char *requested)
{
  if (requested != NULL)
  {
    for (size_t i = 0; i < MAX_OUT_FILES; i++)
    {
      if (!esc_seq_in_use[i] && libmin_strncmp(requested, escape_sequences[i], MAX_ESCAPE_LEN) == 0)
      {
        esc_seq_in_use[i] = true;
        return escape_sequences[i];
      }
    }
  }
  else
  {
    for (size_t i = 0; i < MAX_OUT_FILES; i++)
    {
      if (!esc_seq_in_use[i])
      {
        esc_seq_in_use[i] = true;
        return escape_sequences[i];
      }
    }
  }
  return NULL;
}

SFILE *find_file(const char *file_name)
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
  if (file->write_idx == 0)
    return;
  const char *s = file->escape_sequence;
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

SFILE *libmin_sfopen(const char *fname, const char *mode_str)
{
  sfile_mode_e mode = str_to_file_mode(mode_str);
  const char *esc_seq = request_escape_sequence(NULL);
  return create_sfile((char *)fname, esc_seq, mode);
}

sfile_mode_e str_to_file_mode(const char *mode)
{
  if (libmin_strncmp(mode, "w", 2) == 0)
  {
    return FMODE_W;
  }
  else if (libmin_strncmp(mode, "a", 2) == 0)
  {
    return FMODE_A;
  }
  else
  {
    libmin_printf("libmin sfile only support w and a mode.\n");
    libmin_exit(1);
    return FMODE_W;
  }
}

void serial_output_init()
{
  file_desc_file = 1; // 0, stdin icin ayrilmistir.
  const char *stdout_escape = request_escape_sequence(ESC_DEFAULT);
  const char *stderr_escape = request_escape_sequence(ESC_RED);
  if (stdout_escape == NULL || stderr_escape == NULL)
  {
    libmin_printf("requested escape sequences for stdout and stderr are not available");
    libmin_fail(1);
  }
  stdout = create_sfile("stdout", stdout_escape, FMODE_W);
  stderr = create_sfile("stderr", stderr_escape, FMODE_W);
}

int libmin_sfclose(SFILE *file)
{
  if (file == NULL)
  {
    return -1;
  }
  release_escape_sequence(file->escape_sequence);
  if (file->prev == NULL && file->next == NULL) // sistemdeki tek output dosyasi kapatiliyor.
  {
    live_files_head = NULL;
    live_files_tail = NULL;
  }
  else if (file->prev == NULL) // dosya head ise
  {
    live_files_head = file->next;
    live_files_head->prev = NULL;
  }
  else if (file->next == NULL) // dosya tail ise
  {
    live_files_tail = file->prev;
    live_files_tail->next = NULL;
  }
  else // dosya arada ise
  {
    file->prev->next = file->next;
    file->next->prev = file->prev;
  }

  libmin_free(file);
  live_files_count--;

  return 0;
}

void release_escape_sequence(const char *esc_seq)
{
  for (size_t i = 0; i < MAX_OUT_FILES; i++)
  {
    if (libmin_strncmp(esc_seq, escape_sequences[i], MAX_ESCAPE_LEN) == 0)
    {
      esc_seq_in_use[i] = false;
      return;
    }
  }
}
