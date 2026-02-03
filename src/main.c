#include "cask.h"
#include "error.h"
#include "helper.h"
#include "storage.h"
#include <stdlib.h>

/**
 * TODO:
 * 1.
 */
int main() {
    cask_error_t err;
    uint32_t max_records;
    int input = 0;
    int init_storage_flag = 0;
    char buffer[100];
    FILE* fptr;

    do {
        printf("Welcome to Cask (C-based Atomic Storage Kernel)!\n");
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
        if (err != CASK_OK) // validate input
        {
            printf("Error: %s\n", cask_strerror(err));
        } else {
            input = atoi(buffer);       // convert to integer
            if (input > 6 || input < 1) // check if input is in the range
            {
                printf("Error: %s\n\n",
                       cask_strerror(7)); // return invalid input err
            }
        }

        switch (input) {
        case 1:
            if (init_storage_flag ==
                1) // check if storage has already been initialized
            {
                printf("Error: Storage already initialized\n\n");
                break;
            }

            fptr = fopen("../data/store.bin", "rb+");
            if (fptr != NULL) // check if storage already exists
            {
                printf("Error: Storage already exists\n\n");
                init_storage_flag = 1;
                fclose(fptr);
                break;
            }

            printf("Enter the number of max records: ");
            fgets(buffer, sizeof(buffer), stdin);

            err = validate_input(buffer);
            if (err != CASK_OK) {
                printf("Error: %s\n", cask_strerror(err));
            }

            max_records = atoi(buffer); // convert to an integer
            err = cask_storage_init("../data/store.bin",
                                    max_records); // initialize storage

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
                printf("Error: %s\n", cask_strerror(8));
            }

            printf("\n");
            break;
        case 4:
            if (init_storage_flag != 1) {
                printf("Error: %s\n", cask_strerror(8));
            }

            printf("\n");
            break;
        case 5:
            if (init_storage_flag != 1) {
                printf("Error: %s\n", cask_strerror(8));
            }

            printf("\n");
            break;
        case 6:
            printf("Exiting...\n");
        }
    } while (input != 6);

    return 0;
}
