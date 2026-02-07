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
    case CASK_ERR_RECORD_NOT_FOUND:
        return "Record not found";
    case CASK_ERR_EMPTY_RECORD:
        return "Record already empty";
    case CASK_ERR_NOT_OPEN:
        return "Cannot close an uninitialized storage";
    case CASK_ERR_CLOSE_STORAGE:
        return "Please close the storage before exiting";
    default:
        return "Unknown error";
    }
}
