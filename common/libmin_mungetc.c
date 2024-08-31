#include "libmin.h"
#include "libtarg.h"

/* push a character back to the in-memory file */
int
libmin_mungetc(int c, MFILE *mfile)
{
    if (mfile->rdptr == 0)
        return EOF; // No space to push back the character

    mfile->rdptr--;
    return c;
}
