#include "error.h"

int main(int argc, char *argv[])
{
    int err = 0;
    uint32_t max_records = 100;

    err = cask_storage_init("store.bin", max_records);  // initalize storage
    printf("Storage initaialized");
    return 0;
}
