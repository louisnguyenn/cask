#include "cask.h"
#include "error.h"
#include "helper.h"
#include "storage.h"
#include <stdlib.h>

/**
 * TODO:
 * 1. check if the database exists before the do while loop
 */
int main() {
    cask_error_t err;
    uint32_t max_records;
    int input = 0;
    int init_storage_flag = -1;
    char buffer[100];

    g_cask.fptr = fopen("../data/store.bin", "rb+");
    // check if storage already exists
    if (g_cask.fptr != NULL) {
        init_storage_flag = 1;
    }

    printf("Welcome to Cask (C-based Atomic Storage Kernel)!\n");
    do {
        printf("Here are the options:\n");
        printf("1. Initialize database\n");
        printf("2. Create a record\n");
        printf("3. Get a record\n");
        printf("4. Delete a record\n");
        printf("5. Close the database\n");
        printf("6. Exit\n\n");
        printf("Enter your choice: ");

        fgets(buffer, sizeof(buffer), stdin);

        err = validate_input(buffer);
        // validate input
        if (err != CASK_OK) {
            printf("Error: %s\n", cask_strerror(err));
        } else {
            input = atoi(buffer); // convert to integer
            // check if input is in the range
            if (input > 6 || input < 1) {
                // return invalid input err
                printf("Error: %s\n\n", cask_strerror(7));
            }
        }

        switch (input) {
        case 1:
            // check if storage has already been initialized
            if (init_storage_flag == 1) {
                printf("Error: Storage already initialized\n\n");
                break;
            }

            printf("Enter the number of max records: ");
            fgets(buffer, sizeof(buffer), stdin);

            err = validate_input(buffer);
            if (err != CASK_OK) {
                printf("Error: %s\n", cask_strerror(err));
            }

            max_records = atoi(buffer); // convert to an integer
            // initialize storage
            err = cask_storage_init("../data/store.bin", max_records);

            if (err != CASK_OK) {
                printf("Error: Initialization failed, %s\n",
                       cask_strerror(err));
            } else {
                printf("Storage initialized successfully\n");
                init_storage_flag = 1;
            }

            printf("\n");
            break;
        case 2:
            if (init_storage_flag != 1) {
                printf("Error: %s\n\n", cask_strerror(8));
                break;
            }

            printf("Enter key (max 31 chars): ");
            fgets(buffer, sizeof(buffer), stdin);

            char key[KEY_SIZE];
            strcpy(key, buffer);
            key[strlen(key) - 1] = '\0';

            printf("Enter value (max 127 chars): ");
            fgets(buffer, sizeof(buffer), stdin);

            char value[VALUE_SIZE];
            strcpy(value, buffer);
            value[strlen(value) - 1] = '\0';

            err = cask_record_put(key, value);
            if (err != CASK_OK) {
                printf("Error: %s\n", cask_strerror(err));
                break;
            }

            printf("Record created successfully\n");

            printf("\n");
            break;
        case 3:
            if (init_storage_flag != 1) {
                printf("Error: %s\n\n", cask_strerror(8));
                break;
            }

            char search_key[KEY_SIZE];
            char out_value[VALUE_SIZE];

            printf("Enter key: ");
            fgets(buffer, sizeof(buffer), stdin);
            strcpy(search_key, buffer);
            search_key[strlen(search_key) - 1] = '\0';

            err = cask_record_get(search_key, out_value); // call function

            // error checking
            if (err != CASK_OK) {
                printf("Error: %s\n\n", cask_strerror(err));
            }

            printf("\n");
            break;
        case 4:
            if (init_storage_flag != 1) {
                printf("Error: %s\n", cask_strerror(8));
                break;
            }

            printf("Enter key: ");
            fgets(buffer, sizeof(buffer), stdin);
            buffer[strlen(buffer) - 1] = '\0';

            char search_key[KEY_SIZE];
            strcpy(search_key, buffer);

            err = cask_record_delete(search_key);
            if (err != CASK_OK) {
                printf("Error: %s\n", cask_strerror(err));
            } else {
                printf("Record deleted successfully\n");
            }

            printf("\n");
            break;
        case 5:
            if (init_storage_flag != 1) {
                printf("Error: %s\n", cask_strerror(8));
                break;
            }

            err = cask_storage_close();
            if (err != CASK_OK) {
                printf("Error: %s\n", strerror(err));
            } else {
                printf("Storage closed successfully\n");
            }

            printf("\n");
            break;
        case 6:
            if (g_cask.is_open != 0) {
                printf("Error: "); // TODO: create error 
            }
            printf("Exiting...\n");
        }
    } while (input != 6);

    return 0;
}
