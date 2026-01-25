#include "error.h"

/**
 * this function defines each error case and returns readable messages for debugging
 */
const char *cask_strerror(cask_error_t err)
{
    switch (err)
    {
    case CASK_OK:
        return "Success";
    case CASK_ERR_IO:
        return "I/O error";
    case CASK_ERR_NOT_FOUND:
        return "Key not found";
    case CASK_ERR_INVALID_FORMAT:
        return "Invalid file format";
    case CASK_ERR_FULL:
        return "Storage full";
    default:
        return "Unknown error";
    }
}
