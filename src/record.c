#include "storage.h"

cask_error_t cask_record_put(const char *key, const char *value)
{
    FILE *fptr;
    cask_record_t record;
    cask_header_t header;
    uint32_t curr_record = 0;

    fptr = fopen("../data/store.bin", "rb+");   // open in write binary mode

    fread(&header, sizeof(cask_header_t), 1, fptr); // read the header

    // read the record
    for (int i = 0; i < header.max_records; i += 1)
    {
        fread(&record, )
    }

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
    const offset = sizeof(cask_record_t) + index;
    return offset;
}
