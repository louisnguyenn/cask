#include "error.h"
#include "storage.h"

int main(int argc, char *argv[])
{
    cask_error_t err;
    uint32_t max_records = 100;

    err = cask_storage_init("store.bin", max_records); // initialize storage

    if (err != CASK_OK)
    {
        printf("Initialization failed: %s\n", cask_strerror(err));
        return -1;
    }

    printf("Storage initialized successfully");
    return 0;
}
