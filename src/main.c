#include "error.h"
#include "storage.h"

int main()
{
    cask_error_t err;
    uint32_t max_records = 100;
    int input = 0;

    do
    {
        printf("Welcome to Cask (C-based Atomic Storage Kernel)\n");
        printf("Here are the options:\n");
        printf("1. Initialize database\n");
        printf("2. Create a record\n");
        printf("3. Get a record\n");
        printf("4. Delete a record\n");
        printf("5. Close the database\n");
        printf("6. Exit");

        scanf("%d", &input);
        if (!isdigit(input))
        {
            printf("Error: enter a valid input");
        }
    } while (input != 6);
    
    err = cask_storage_init("../data/store.bin", max_records); // initialize storage

    if (err != CASK_OK)
    {
        printf("Initialization failed: %s\n", cask_strerror(err));
        return -1;
    }

    printf("Storage initialized successfully");
    return 0;
}
