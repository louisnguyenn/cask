#ifndef ERROR_H
#define ERROR_H
typedef enum
{
    CASK_OK = 0,    // operation success (0 = success, -1 = error)
    CASK_ERR_IO,    // file read/write error
    CASK_ERR_NOT_FOUND, // key not found
    CASK_ERR_INVALID_FORMAT,    // invalid format (file or record corrupted)
    CASK_ERR_FULL   // storage is full
} cask_error_t;

const char* cask_strerror(cask_error_t err);

#endif // ERROR_H
