#include "storage.h"
#include "cask.h"
#include "error.h"
#include "helper.h"

/**
 * initialize storage and check for valid storage if already exists
 */
cask_error_t cask_storage_init(const char *filename, uint32_t max_records)
{
  cask_storage_t g_cask = { 0 };

  g_cask.fptr = fopen(filename, "rb+");

  /**
   * CASE 1: if file does not exist
   * create a file
   * write the header
   * preallocate space for records
   */
  if (g_cask.fptr == NULL) {
    g_cask.fptr = fopen(filename, "wb+");// create a new file (write binary)
    if (g_cask.fptr == NULL) {
      return CASK_ERR_IO;// return err if file could not be created
    }

    // initalize header
    memcpy(g_cask.header.magic, "CSK1", sizeof(char) * MAGIC_STRING_SIZE);
    g_cask.header.version = CASK_FORMAT_VERSION;// version 1
    g_cask.header.max_records = max_records;
    g_cask.header.record_size = sizeof(cask_record_t);

    // write header
    if (fwrite(&g_cask.header, sizeof(g_cask.header), 1, g_cask.fptr) != 1) { return CASK_ERR_IO; }

    // initalize empty records
    cask_record_t empty_record;
    memset(&empty_record, 0, sizeof(empty_record));

    for (uint32_t i = 0; i < max_records; i += 1) { fwrite(&empty_record, sizeof(empty_record), 1, g_cask.fptr); }
  } else {
    /**
     * CASE 2: if file exists
     * read header
     * verify magic number
     * verify version
     */

    // get file size
    fseek(g_cask.fptr, 0, SEEK_END);
    unsigned long file_size = ftell(g_cask.fptr);

    // check if file is big enough to write a header
    if (file_size < sizeof(cask_header_t)) {
      // printf('filesize: %llu', file_size);
      // printf('size of header: %llu', sizeof(cask_header_t));
      return CASK_ERR_INVALID_FORMAT;
    }

    fseek(g_cask.fptr, 0, SEEK_SET);// seek to the beginning of the file

    // read header information
    if (fread(&g_cask.header, sizeof(g_cask.header), 1, g_cask.fptr) != 1) { return CASK_ERR_IO; }

    // read magic number identifier
    // printf("header magic: %s\n", header.magic);
    if (memcmp(g_cask.header.magic, "CSK1", MAGIC_STRING_SIZE) != 0) {
      printf("magic error\n");
      return CASK_ERR_INVALID_FORMAT;
    }

    // read version
    // printf("header version: %d\n", header.version);
    if (g_cask.header.version != CASK_FORMAT_VERSION) {
      printf("header error\n");
      return CASK_ERR_INVALID_FORMAT;
    }
  }

  fseek(g_cask.fptr, 0, SEEK_SET);// seek back to the beginning of file
  g_cask.is_open = 1;

  return CASK_OK;
}


cask_storage_t g_cask = { 0 };

cask_error_t cask_record_put(const char *key, const char *value)
{
  cask_record_t record;
  int empty_index = -1;
  long offset = 0;
  uint32_t header_size;
  uint32_t record_size;

  // read the header
  if (fread(&g_cask.header, sizeof(cask_header_t), 1, g_cask.fptr) != 1) { return CASK_ERR_IO; }

  // read the record
  for (uint32_t i = 0; i < g_cask.header.max_records; i += 1) {
    fread(&record, g_cask.header.record_size, 1, g_cask.fptr);

    // look for an empty slot to define a new record with inputted
    // values
    if (record.in_use == 0) {
      empty_index = i;
      break;
    }
  }

  // check if no records are found
  if (empty_index == -1) {
    return CASK_ERR_FULL;// return error: db is full
  }

  header_size = sizeof(g_cask.header);
  record_size = g_cask.header.record_size;

  // calculate offset
  offset = cask_record_offset(empty_index, header_size, record_size);
  fseek(g_cask.fptr, offset, SEEK_SET);// seek to the empty record

  // initalize record to 0 bytes
  memset(&record, 0, sizeof(record));

  // update record with new values if applicable
  // validate key
  if (strlen(key) >= KEY_SIZE) { return CASK_ERR_KEY_TOO_LARGE; }

  // validate value
  if (strlen(value) >= VALUE_SIZE) { return CASK_ERR_VALUE_TOO_LARGE; }

  strcpy(record.key, key);
  strcpy(record.value, value);
  record.in_use = 1;// update flag to tell db that the record is in use

  // write the updated record into the database
  fwrite(&record, g_cask.header.record_size, 1, g_cask.fptr);

  fseek(g_cask.fptr, 0, SEEK_SET);

  return CASK_OK;
}

cask_error_t cask_record_get(const char *key, char *out_value)
{
  cask_record_t record;
  int record_index = -1;
  char buffer[100];
  char input[1];

  // read header information
  if (fread(&g_cask.header, sizeof(cask_header_t), 1, g_cask.fptr) != 1) { return CASK_ERR_IO; }

  // loop through the file to find the record
  for (uint32_t i = 0; i < g_cask.header.max_records; i += 1) {
    fread(&record, g_cask.header.record_size, 1, g_cask.fptr);
    if (strcmp(record.key, key) == 0) {
      record_index = i;
      break;
    }
  }

  if (record_index == -1) { return CASK_ERR_RECORD_NOT_FOUND; }

  long offset = cask_record_offset(record_index, sizeof(g_cask.header), g_cask.header.record_size);

  do {
    printf("Record found!\nWould you like to see its contents? [Y/n]: ");
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strlen(buffer) - 1] = '\0';
    strcpy(input, buffer);

    if (strcmp(input, "Y") == 0) {
      // seek to the record
      if (fseek(g_cask.fptr, offset, SEEK_SET) != 0) { return CASK_ERR_IO; }

      printf("\n");
      strcpy(out_value, record.value);

      printf("Record information:\n");
      printf("Key: %s\n", key);
      printf("Value: %s\n", out_value);

      return CASK_OK;
    } else if (strcmp(input, "n") == 0) {
      return CASK_OK;
    } else {
      return CASK_ERR_INVALID_INPUT;
    }
  } while (strcmp(input, "n") != 0);

  return CASK_OK;
}

cask_error_t cask_record_delete(const char *key)
{
  cask_record_t record;
  int record_index = -1;
  char buffer[100];
  char input[1];

  // read header information
  if (fread(&g_cask.header, sizeof(cask_header_t), 1, g_cask.fptr) != 1) { return CASK_ERR_IO; }

  // loop through the file to find the record
  for (uint32_t i = 0; i < g_cask.header.max_records; i += 1) {
    fread(&record, g_cask.header.record_size, 1, g_cask.fptr);
    if (strcmp(record.key, key) == 0) {
      record_index = i;
      break;
    }
  }

  if (record_index == -1) { return CASK_ERR_RECORD_NOT_FOUND; }

  long offset = cask_record_offset(record_index, sizeof(g_cask.header), g_cask.header.record_size);

  do {
    printf(
      "Record found!\nAre you sure you want to delete the record? "
      "[Y/n]: ");
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strlen(buffer) - 1] = '\0';
    strcpy(input, buffer);

    if (strcmp(input, "Y") == 0) {
      if (fseek(g_cask.fptr, offset, SEEK_SET) != 0) { return CASK_ERR_IO; }

      if (fread(&record, sizeof(record), 1, g_cask.fptr) != 1) { return CASK_ERR_IO; }

      if (record.in_use == 0) { return CASK_ERR_EMPTY_RECORD; }

      record.in_use = 0;

      // seek back to record position and overwrite the record
      // with the new information
      fseek(g_cask.fptr, offset, SEEK_SET);
      fwrite(&record, sizeof(record), 1, g_cask.fptr);

      return CASK_OK;
    } else if (strcmp(input, "n") == 0) {
      return CASK_OK;
    } else {
      return CASK_ERR_INVALID_INPUT;
    }
  } while (strcmp(input, "n") != 0);

  return CASK_OK;
}

cask_error_t cask_storage_close(void)
{
  if (g_cask.is_open != 1) { return CASK_ERR_NOT_OPEN; }

  fflush(g_cask.fptr);
  fclose(g_cask.fptr);
  g_cask.fptr = NULL;
  g_cask.is_open = 0;

  return CASK_OK;
}
