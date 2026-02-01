#ifndef ERROR_H
#define ERROR_H

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
typedef enum
{
    CASK_OK = 0,              // operation success (0 = success, -1 = error)
    CASK_ERR_IO,              // file read/write error
    CASK_ERR_NOT_FOUND,       // key not found
    CASK_ERR_INVALID_FORMAT,  // invalid format (file or record corrupted)
    CASK_ERR_FULL,            // storage is full
    CASK_ERR_KEY_TOO_LARGE,   // record key is too large
    CASK_ERR_VALUE_TOO_LARGE, // record value is too large
    CASK_ERR_INVALID_INPUT,   // invalid input from user
    CASK_ERR_INIT_STORAGE     // database is not yet initialized
} cask_error_t;

const char *cask_strerror(cask_error_t err);

#endif // ERROR_H
