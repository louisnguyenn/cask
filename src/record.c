#include "storage.h"

cask_error_t cask_record_put(const char *key, const char *value)
{
    FILE *fptr;
    cask_record_t record;
    cask_header_t header;
    uint32_t pos = 0;
    int empty_index = -1;
    long offset = 0;
    uint32_t header_size;
    uint32_t record_size;

    fptr = fopen("../data/store.bin", "rb+"); // open in write binary mode

    fread(&header, sizeof(cask_header_t), 1, fptr); // read the header

    // read the record
    for (int i = 0; i < header.max_records; i += 1)
    {
        fread(&record, header.record_size, 1, fptr);
        if (record.in_use == 0) // look for an empty slot to define a new record with inputted values
        {
            empty_index = i;
            break;
        }
    }

    // check if no records are found
    if (empty_index == -1)
    {
        fclose(fptr);
        return CASK_ERR_FULL; // return error: db is full
    }

    header_size = sizeof(header);
    record_size = header.record_size;
    offset = cask_record_offset(empty_index, header_size, record_size); // calculate offset
    fseek(fptr, offset, SEEK_SET);                                      // seek to the empty record

    // initalize record
    record.in_use = 0;
    record.key[0] = '\0';
    record.value[0] = '\0';

    // update record with new values if applicable
    if (strlen(key) < KEY_SIZE) // validate key

    {
        strcpy(record.key, key);
    }
    else
    {
        fclose(fptr);
        return CASK_ERR_KEY_TOO_LARGE;
    }

    if (strlen(value) < VALUE_SIZE) // validate value
    {
        fclose(fptr);
        strcpy(record.value, value);
    }
    else
    {
        return CASK_ERR_VALUE_TOO_LARGE;
    }

    record.in_use = 1; // update flag to tell db that the record is in use

    // write the updated record into the database
    fwrite(&record, sizeof(record), 1, fptr);

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

long cask_record_offset(uint32_t index, uint32_t header_size, uint32_t record_size)
{
    long offset = sizeof(header_size) + (index * record_size);

    return offset;
}
