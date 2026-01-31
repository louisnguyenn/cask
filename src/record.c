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
    if (fptr == NULL)
    {
        return CASK_ERR_IO;
    }

    if (fread(&header, sizeof(cask_header_t), 1, fptr) != 1) // read the header
    {
        fclose(fptr);
        return CASK_ERR_IO;
    }

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

    // initalize record to 0 bytes
    memset(&record, 0, sizeof(record));

    // update record with new values if applicable
    if (strlen(key) >= KEY_SIZE) // validate key
    {
        fclose(fptr);
        return CASK_ERR_KEY_TOO_LARGE;
    }

    if (strlen(value) >= VALUE_SIZE) // validate value
    {
        fclose(fptr);
        return CASK_ERR_VALUE_TOO_LARGE;
    }

    strcpy(record.key, key);
    strcpy(record.value, value);
    record.in_use = 1; // update flag to tell db that the record is in use

    fwrite(&record, header.record_size, 1, fptr); // write the updated record into the database
    fclose(fptr);
    
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
    long offset = header_size + (index * record_size);

    return offset;
}
