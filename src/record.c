#include "cask.h"
#include "error.h"
#include "helper.h"
#include "storage.h"

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

cask_error_t cask_storage_close()
{
  if (g_cask.is_open != 1) { return CASK_ERR_NOT_OPEN; }

  fflush(g_cask.fptr);
  fclose(g_cask.fptr);
  g_cask.fptr = NULL;
  g_cask.is_open = 0;

  return CASK_OK;
}
