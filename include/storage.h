#ifndef STORAGE_H
#define STORAGE_H
#define MAGIC_STRING_SIZE 5
#define KEY_SIZE 32
#define VALUE_SIZE 128
#define CASK_FORMAT_VERSION 1   // define version

#include <stdint.h>
#include "error.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

/**
 * define storage file layout 
 */
typedef struct {
    char magic[MAGIC_STRING_SIZE];
    uint32_t version;
    uint32_t max_records;
    uint32_t record_size;
}  cask_header_t;

/**
 * each record contains the following
 */
typedef struct {
    char key[KEY_SIZE];
    char value[VALUE_SIZE];
    bool flag;
} cask_record_t;

// function prototypes

/**
 * initialize storage function
 */
cask_error_t cask_storage_init(const char *filename, uint32_t max_records);

/**
 * HELPER FUNCTION: returns position/offset of a record
 */
long cask_record_offset(uint32_t index);

#endif // STORAGE_H
