#include "storage.h"

cask_error_t cask_storage_init(const char *filename, uint32_t max_records)
{
    FILE *fptr;
    cask_header_t header;
    char *key = NULL;
    char *value = NULL;
    long curr_posn, end_posn = 0;
    char *magic = NULL;
    uint32_t version = NULL;

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
        memset(header.magic, "CSK1", sizeof(char) * MAGIC_STRING_SIZE);
        header.magic[4] = '\0'; // null terminate
        header.version = CASK_FORMAT_VERSION; // version 1
        header.max_records = max_records;
        header.record_size = sizeof(cask_record_t);

        // preallocate space for records
        key = malloc(sizeof(char) * KEY_SIZE);
        value = malloc(sizeof(char) * VALUE_SIZE);

        // write header
        fwrite(&header, sizeof(header), 1, fptr);
    }

    // TODO:
    /**
     * CASE 2: if file exists
     * read header
     * verify magic number
     * verify version
     */
    // find the end position of the records
    fseek(fptr, 0, SEEK_END);
    end_posn = ftell(fptr);

    fseek(fptr, 0, SEEK_SET); // seek back to the beginning of the file
    while (curr_posn != end_posn)
    {
        fread(&header, sizeof(header), 1, fptr);

        // read magic number identifier
        fseek(fptr, sizeof(char) * MAGIC_STRING_SIZE, SEEK_SET);
        fread(magic, sizeof(char), MAGIC_STRING_SIZE, fptr);
        if (magic != header.magic)
        {
            return CASK_ERR_INVALID_FORMAT;
        }

        // read version
        fseek(fptr, sizeof(uint32_t) + sizeof(char) * MAGIC_STRING_SIZE, SEEK_SET);
        fread(&version, sizeof(uint32_t), 1, fptr);
        if (version != header.version)
        {
            return CASK_ERR_INVALID_FORMAT;
        }

        curr_posn = ftell(fptr);
    }

    fclose(fptr);
    return CASK_OK;
}
