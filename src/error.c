#include "error.h"

/**
 * this function defines each error case and returns readable messages for
 * debugging
 */
const char* cask_strerror(cask_error_t err) {
    switch (err) {
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
    case CASK_ERR_KEY_TOO_LARGE:
        return "Key is too large";
    case CASK_ERR_VALUE_TOO_LARGE:
        return "Value is too large";
    case CASK_ERR_INVALID_INPUT:
        return "Invalid input";
    case CASK_ERR_INIT_STORAGE:
        return "Database not initialized";
    default:
        return "Unknown error";
    }
}
