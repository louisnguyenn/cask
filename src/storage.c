#include "storage.h"
#include "cask.h"
#include "error.h"

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
