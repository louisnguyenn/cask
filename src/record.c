#include "error.h"
#include "helper.h"
#include "storage.h"

cask_error_t cask_record_put(const char* key, const char* value) {
    FILE* fptr;
    cask_record_t record;
    cask_header_t header;
    int empty_index = -1;
    long offset = 0;
    uint32_t header_size;
    uint32_t record_size;

    fptr = fopen("../data/store.bin", "rb+"); // open in write binary mode
    if (fptr == NULL) {
        return CASK_ERR_IO;
    }

    if (fread(&header, sizeof(cask_header_t), 1, fptr) != 1) // read the header
    {
        fclose(fptr);
        return CASK_ERR_IO;
    }

    // read the record
    for (uint32_t i = 0; i < header.max_records; i += 1) {
        fread(&record, header.record_size, 1, fptr);
        if (record.in_use == 0) // look for an empty slot to define a new record
                                // with inputted values
        {
            empty_index = i;
            break;
        }
    }

    // check if no records are found
    if (empty_index == -1) {
        fclose(fptr);
        return CASK_ERR_FULL; // return error: db is full
    }

    header_size = sizeof(header);
    record_size = header.record_size;
    offset = cask_record_offset(empty_index, header_size,
                                record_size); // calculate offset
    fseek(fptr, offset, SEEK_SET);            // seek to the empty record

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

    fwrite(&record, header.record_size, 1,
           fptr); // write the updated record into the database
    fclose(fptr);

    return CASK_OK;
}

/**
 * TODO:
 * 1. create error for record not found
 * 2. move all the print record information to the main file
 * 3. test
 */
cask_error_t cask_record_get(const char* key, char* out_value) {
    FILE* fptr;
    cask_header_t header;
    cask_record_t record;
    char input;
    int record_index = -1;

    fptr = fopen("../data/store.bin", "rb+");
    if (fptr == NULL) {
        return CASK_ERR_IO;
    }

    if (fread(&header, sizeof(cask_header_t), 1, fptr) !=
        1) // read header information
    {
        fclose(fptr);
        return CASK_ERR_IO;
    }

    // loop through the file to find the record
    for (uint32_t i = 0; i < header.max_records; i += 1) {
        fread(&record, header.record_size, 1, fptr);
        if (strcmp(record.key, key) == 0) {
            record_index = i;
            break;
        }
    }

    if (record_index == -1) {
        printf("Record not found\n\n");
        return CASK_OK;
    }

    do {
        printf("Record found! Would you like to see its contents? [Y/n]: ");
        scanf(" %c", &input);

        if (input == 'Y') {
            fseek(fptr, sizeof(header) + (record_index * header.record_size),
                  SEEK_SET); // seek to the record

            printf("\n");
            printf("Record Information:\n");
            printf("Key: %s\n", record.key);
            strcpy(out_value, record.value);

            return out_value;
        } else if (input == 'n') {
            return CASK_OK;
        } else {
            printf("Error: %s\n\n", cask_strerror(7)); // invalid input error
        }
    } while (input != 'n');

    return CASK_OK;
}

cask_error_t cask_record_delete(const char* key) {
    return CASK_OK;
}

cask_error_t cask_storage_close() {
    return CASK_OK;
}
