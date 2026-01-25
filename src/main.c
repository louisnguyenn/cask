#include <stdio.h>
#include "error.h"

int main()
{
    cask_error_t err = CASK_ERR_IO;
    printf("Error: %s", cask_strerror(err));
    return 0;
}
