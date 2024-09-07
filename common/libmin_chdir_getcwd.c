#include "libmin.h"


#define PATH_MAX 512
static char cwd[PATH_MAX] = ".";
int libmin_chdir(const char *path)
{
  if (path == NULL) {
    libmin_printf("chdir: No such file or directory\n");
    return -1;
  }
  if (path[0] == '/') {
    if (strlen(path) >= PATH_MAX) {
      libmin_printf("chdir: Path too long\n");
      return -1;
    }
    strcpy(cwd, path);
  } else {
    if (strlen(cwd) + strlen(path) + 1 >= PATH_MAX) {
      libmin_printf("chdir: Path too long\n");
      return -1;
    }
    strcat(cwd, "/");
    strcat(cwd, path);
  }
  return 0;
}

char *libmin_getcwd(char *buf, size_t size)
{
  if (buf == NULL) {
    libmin_printf("getcwd: buf is NULL\n");
    return NULL;
  }
  if (size < strlen(cwd) + 1) {
    libmin_printf("getcwd: Path too long\n");
    return NULL;
  }
  strcpy(buf, cwd);
  return buf;
}
