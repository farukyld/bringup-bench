#include "libmin.h"

void libmin_abort() {
    libmin_fail(1);
}

strong_alias(libmin_abort, abort)
