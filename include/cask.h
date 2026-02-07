#ifndef CASK_H
#define CASK_H

#include "error.h"
#include "storage.h"
typedef struct
{
  FILE *fptr;// file pointer
  cask_header_t header;// storage header
  int is_open;// is open flag (0 = close, 1 = open)
} cask_storage_t;

extern cask_storage_t g_cask;// global variable

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
cask_error_t cask_storage_close(void);

#endif// CASK_H
