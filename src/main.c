#include "error.h"
#include "storage.h"
#include "helper.h"
#include "cask.h"
#include <stdlib.h>

int main()
{
    cask_error_t err;
    uint32_t max_records;
    int input = 0;
    int init_storage_flag = 0;
    char buffer[100];

    do
    {
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
            printf("Error: %s", cask_strerror(err));
        }

        input = atoi(buffer); // convert to integer

        switch (input)
        {
        case 1:
            printf("Enter the number of max records: ");
            fgets(buffer, sizeof(buffer), stdin);

            err = validate_input(buffer);
            if (err != CASK_OK)
            {
                printf("Error: %s\n", cask_strerror(err));
            }

            max_records = atoi(buffer);                                // convert to an integer
            err = cask_storage_init("../data/store.bin", max_records); // initialize storage

            if (err != CASK_OK)
            {
                printf("Initialization failed: %s\n", cask_strerror(err));
            }
            else
            {
                printf("Storage initialized successfully\n");
                init_storage_flag = 1;
            }
            break;
        case 2:
            if (init_storage_flag != 1)
            {
                printf("Error: %s\n", cask_strerror(8));
            }

            break;
        case 3:
            if (init_storage_flag != 1)
            {
                printf("Error: %s\n", cask_strerror(8));
            }

            break;
        case 4:
            if (init_storage_flag != 1)
            {
                printf("Error: %s\n", cask_strerror(8));
            }

            break;
        case 5:
            if (init_storage_flag != 1)
            {
                printf("Error: %s\n", cask_strerror(8));
            }

            break;
        case 6:
            printf("Exiting...\n");
        }
    } while (input != 6);

    return 0;
}
