#include "error.h"
#include "storage.h"
#include "helper.h"

/**
 * TODO:
 * 1. create a "isdigit" function to check if the user input is an integer
 * if not then return -1 if not successful, then check if the return type is equal to CASK_OK
 * if it return 0, then it is validated because CASK_OK is equal to 0
 * if not then inform the user of the error
 * 
 * 2. create a new error message in the error and c file to inform the user to initialize the database first before choosing the other options
 */
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
        err = isdigit(input);
        if (!err) // validate input
        {
            printf("Error: %s", cask_strerror(err));
        }

        switch (input)
        {
        case 1:
            printf("Enter the number of max records: ");
            scanf("%d", &max_records);

            err = isdigit(max_records);
            if (!err)
            {
                printf("Error: %s\n", cask_strerror(err));
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
