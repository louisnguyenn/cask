#include "storage.h"
#include "error.h"
#include "cask.h"

/**
 * initialize storage and check for valid storage if already exists
 */
cask_error_t cask_storage_init(const char *filename, uint32_t max_records)
{
    FILE *fptr;
    cask_header_t header;
    unsigned long file_size = 0;
    long pos = 0;

    fptr = fopen(filename, "rb+"); // open file in read mode (read binary)

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
        {
            return CASK_ERR_IO; // return err if file could not be created
        }

        // initalize header
        memcpy(header.magic, "CSK1", sizeof(char) * MAGIC_STRING_SIZE);
        header.version = CASK_FORMAT_VERSION; // version 1
        header.max_records = max_records;
        header.record_size = sizeof(cask_record_t);

        // write header
        if (fwrite(&header, sizeof(header), 1, fptr) != 1)
        {
            return CASK_ERR_IO;
        }

        long total_size = sizeof(cask_header_t) + ((long)max_records * sizeof(cask_record_t)); // get size of file
        fseek(fptr, total_size - 1, SEEK_SET);
        fputc(0, fptr); // allocate space by seeking to the end of the file and marking the 'end point' with a byte of 0
        fflush(fptr);   // force data writing to be written in disk immediately
    }
    else
    {
        /**
         * CASE 2: if file exists
         * read header
         * verify magic number
         * verify version
         */
        // get file size
        fseek(fptr, 0, SEEK_END);
        file_size = ftell(fptr);
        if (file_size < sizeof(cask_header_t)) // check if file is big enough to write a header
        {
            // printf('filesize: %llu', file_size);
            // printf('size of header: %llu', sizeof(cask_header_t));
            return CASK_ERR_INVALID_FORMAT;
        }

        fseek(fptr, 0, SEEK_SET);                         // seek to the beginning of the file
        if (fread(&header, sizeof(header), 1, fptr) != 1) // read header information
        {
            return CASK_ERR_IO;
        }

        // read magic number identifier
        // printf("header magic: %s\n", header.magic);
        if (memcmp(header.magic, "CSK1", MAGIC_STRING_SIZE) != 0)
        {
            printf("magic error\n");
            return CASK_ERR_INVALID_FORMAT;
        }

        // read version
        printf("header version: %d\n", header.version);
        if (header.version != CASK_FORMAT_VERSION)
        {
            printf("header error\n");
            return CASK_ERR_INVALID_FORMAT;
        }
    }

    fclose(fptr);

    return CASK_OK;
}
