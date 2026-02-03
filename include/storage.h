#ifndef STORAGE_H
#define STORAGE_H

#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define MAGIC_STRING_SIZE 4
#define KEY_SIZE 32
#define VALUE_SIZE 128
#define CASK_FORMAT_VERSION 1 // define version

/**
 * define storage file layout
 */
typedef struct {
    char magic[MAGIC_STRING_SIZE]; // file signature (magic number) makes sure
                                   // it reads the correct file as a database
    uint32_t version; // file format version (future-proofing, when changing the
                      // record structure)
    uint32_t max_records; // max number of records the file supports
    uint32_t record_size; // size (in bytes) of one cask_record_t
} cask_header_t;

/**
 * each record contains the following
 */
typedef struct {
    uint32_t in_use;    // flag for empty slot to place a new record (empty = 0,
                        // in-use = 1)
    char key[KEY_SIZE]; // record key ('user1')
    char value[VALUE_SIZE]; // record value (name, username, email, etc.)
} cask_record_t;

#endif // STORAGE_H
