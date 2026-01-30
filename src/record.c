#include "storage.h"

cask_error_t cask_record_put(const char *key, const char *value)
{
    FILE *fptr;
    cask_record_t record;
    cask_header_t header;
    uint32_t pos = 0;
    int empty_index = 0;

    fptr = fopen("../data/store.bin", "rb+"); // open in write binary mode

    fread(&header, sizeof(cask_header_t), 1, fptr); // read the header

    // read the record
    for (int i = 0; i < header.max_records; i += 1)
    {
        fread(&record, header.record_size, 1, fptr);
        // look for an empty slot to define a new record with inputted values
        if (record.in_use == 0)
        {
            empty_index = i;
            break;
        }
    }

    fseek(fptr, cask_record_offset(empty_index), SEEK_SET); // seek to the empty record

    return CASK_OK;
}

cask_error_t cask_record_get(const char *key, char *out_value)
{
}

cask_error_t cask_record_delete(const char *key)
{
}

cask_error_t cask_storage_close()
{
}

long cask_record_offset(uint32_t index)
{
    cask_header_t header;
    cask_record_t record;

    const offset = sizeof(header) + (index * header.record_size);
    return offset;
}
