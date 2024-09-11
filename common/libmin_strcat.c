#include "libmin.h"
#include "libtarg.h"

char *
libmin_strcat(char *dest, const char *src)
{
	libmin_strcpy(dest + libmin_strlen(dest), src);
	return dest;
}

strong_alias(libmin_strcat, strcat);
