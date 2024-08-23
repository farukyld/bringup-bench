#include "libmin.h"
#include "libtarg.h"

/* in-memory file I/O */

typedef struct {
    const char *file_name;           // Pointer to the file name
    const uint8_t *content_start;    // Pointer to the start of the content
    const uint8_t *content_end;      // Pointer to the end of the content
} index_entry_t;

extern const char _index_start;
extern const char _index_end;

static const index_entry_t *find_file(const char *file_name) {
  // _index_start ve _index_end sembolleri linler'da tanimlanmistir.
  static const index_entry_t *index_start = (const index_entry_t *)&_index_start;
  static const index_entry_t *index_end = (const index_entry_t *)&_index_end;
  const index_entry_t *index = index_start;
  // include_input_files.S'te, REGISTER_FILE(name) makrosu ile acilmak istenen dosyalar listelenir.
  while (index < index_end) {
    if (libmin_strcmp(index->file_name, file_name) == 0) {
      return index;
    }
    index++;
  }

  return NULL;
}

/* Open an in-memory file */
MFILE *libmin_mopen(const char *file_name, const char *mode) {
  if (libmin_strcmp(mode, "r") != 0) {
    libmin_printf("ERROR: libmin MFILE only supports file reads\n");
    libmin_fail(1);
    return NULL;  // Ensure function returns even on error
  }

  const index_entry_t *entry = find_file(file_name);
  if (entry == NULL) {
    libmin_printf("ERROR: File %s not found\n", file_name);
    libmin_fail(1);
    return NULL;  // Ensure function returns even on error
  }

  /* Allocate memory for the MFILE structure */
  MFILE *m_file = (MFILE *)libmin_malloc(sizeof(MFILE));
  if (m_file == NULL) {
    libmin_printf("ERROR: Memory allocation failed\n");
    libmin_fail(1);
    return NULL;  // Ensure function returns even on error
  }

  /* Initialize the mfile structure */
  m_file->fname = entry->file_name;
  m_file->data = entry->content_start;
  m_file->data_sz = (size_t)(entry->content_end - entry->content_start);
  m_file->rdptr = 0;

  return m_file;
}
