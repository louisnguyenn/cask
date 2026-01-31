#ifndef STORAGE_H
#define STORAGE_H
#define MAGIC_STRING_SIZE 4
#define KEY_SIZE 32
#define VALUE_SIZE 128
#define CASK_FORMAT_VERSION 1 // define version

#include <stdint.h>
#include "error.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/**
 * define storage file layout
 */
typedef struct
{
    char magic[MAGIC_STRING_SIZE]; // file signature (magic number) makes sure it reads the correct file as a database
    uint32_t version;              // file format version (future-proofing, when changing the record structure)
    uint32_t max_records;          // max number of records the file supports
    uint32_t record_size;          // size (in bytes) of one cask_record_t
} cask_header_t;

/**
 * each record contains the following
 */
typedef struct
{
    uint32_t in_use;        // flag for empty slot to place a new record (empty = 0, in-use = 1)
    char key[KEY_SIZE];     // record key ('user1')
    char value[VALUE_SIZE]; // record value (name, username, email, etc.)
} cask_record_t;

// function prototypes
/**
 * initialize storage function
 * parameters: filename/name of the database, max number of records
 */
cask_error_t cask_storage_init(const char *filename, uint32_t max_records);

/**
 * create record function
 * parameters: record key, values to put in the record
 */
cask_error_t cask_record_put(const char *key, const char *value);

/**
 * get a record function
 * parameters: record key, values of the record
 */
cask_error_t cask_record_get(const char *key, char *out_value);

/**
 * delete a record function
 * parameters: record key
 */
cask_error_t cask_record_delete(const char *key);

/**
 * clean/close the storage function
 * parameters: none
 */
cask_error_t cask_storage_close();

/**
 * HELPER FUNCTION: returns position/offset of a record
 * parameters: current index
 */
long cask_record_offset(uint32_t index, uint32_t header_size, uint32_t record_size);

#endif // STORAGE_H
