#include "helper.h"
#include "error.h"

/**
 * validate user input
 */
cask_error_t validate_input(int input)
{
    if (!isdigit(input))
    {
        return CASK_ERR_INVALID_FORMAT;
    }

    return CASK_OK; // success
}

/**
 * calculate record offsets
 */
long cask_record_offset(uint32_t index, uint32_t header_size, uint32_t record_size)
{
    long offset = header_size + (index * record_size);

    return offset;
}
