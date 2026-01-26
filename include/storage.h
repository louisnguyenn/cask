#include <stdint.h>
#include "error.h"

/**
 * define storage file layout 
 */
struct cask_header_t {
    char magic_number[4];
    uint32_t version;
    uint32_t max_records;
    uint32_t record_size;
};

/**
 * each record contains the following
 */
struct cask_record_t {
    char key[32];
    char value[128];
    bool flag;
};

// function prototypes

/**
 * initialize storage function
 */
cask_error_t cask_storage_init(const char *filename, uint32_t max_records);
