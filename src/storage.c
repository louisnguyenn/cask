#include "storage.h"

cask_error_t cask_storage_init(const char *filename, uint32_t max_records)
{
    FILE *fptr;
    cask_header_t header;
    char *key = NULL;
    char *value = NULL;
    char magic[MAGIC_STRING_SIZE];
    uint32_t version;

    fptr = fopen(filename, "rb"); // open file in read mode (read binary)

    /**
     * CASE 1: if file does not exist
     * create a file
     * write the header
     * preallocate space for records
     */
    if (fptr == NULL)
    {
        fptr = fopen(filename, "wb+"); // create a new file (write binary)
        if (fptr == NULL)
            return CASK_ERR_IO; // return err if file could not be created

        // initalize header
        memcpy(header.magic, "CSK1", sizeof(char) * MAGIC_STRING_SIZE);
        header.magic[4] = '\0';               // null terminate
        header.version = CASK_FORMAT_VERSION; // version 1
        header.max_records = max_records;
        header.record_size = sizeof(cask_record_t);

        // preallocate space for records
        key = malloc(sizeof(char) * KEY_SIZE);
        value = malloc(sizeof(char) * VALUE_SIZE);

        // write header
        fwrite(&header, sizeof(header), 1, fptr);
    }
    else
    {
        /**
         * CASE 2: if file exists
         * read header
         * verify magic number
         * verify version
         */
        fseek(fptr, 0, SEEK_SET); // seek to the beginning of the file
        fread(&header, sizeof(header), 1, fptr);

        // read magic number identifier
        fread(magic, sizeof(char), MAGIC_STRING_SIZE, fptr);
        if (strcmp(magic, "CSK1") != 0)
        {
            return CASK_ERR_INVALID_FORMAT;
        }

        // read version
        fread(&version, sizeof(uint32_t), 1, fptr);
        if (version != CASK_FORMAT_VERSION)
        {
            return CASK_ERR_INVALID_FORMAT;
        }
    }

    fclose(fptr);
    return CASK_OK;
}
