#include "error.h"
#include "storage.h"

int main()
{
    cask_error_t err;
    uint32_t max_records;
    int input = 0;
    int init_storage_flag = 0;

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

        scanf("%d", &input);
        if (!isdigit(input)) // validate input
        {
            printf("Error: enter an integer\n");
        }

        switch (input)
        {
        case 1:
            printf("Enter the number of max records: ");
            scanf("%d", &max_records);

            if (!isdigit(max_records))
            {
                printf("Error: enter an integer\n");
            }

            err = cask_storage_init("../data/store.bin", max_records); // initialize storage
            if (err != CASK_OK)
            {
                printf("Initialization failed: %s\n", cask_strerror(err));
                return -1;
            }

            printf("Storage initialized successfully\n");
            init_storage_flag = 1;
            break;
        case 2:
            if (init_storage_flag != 1)
            {
                printf("Error: initalize database first\n");
            }

            break;
        case 3:
            if (init_storage_flag != 1)
            {
                printf("Error: initalize database first\n");
            }

            break;
        case 4:
            if (init_storage_flag != 1)
            {
                printf("Error: initalize database first\n");
            }

            break;
        case 5:
            if (init_storage_flag != 1)
            {
                printf("Error: initalize database first\n");
            }

            break;
        }
    } while (input != 6);

    return 0;
}
