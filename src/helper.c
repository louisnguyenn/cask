#include "helper.h"

/**
 * validate user input
 */
int validate_input(int input)
{

}

/**
 * calculate record offsets
 */
long cask_record_offset(uint32_t index, uint32_t header_size, uint32_t record_size)
{
    long offset = header_size + (index * record_size);

    return offset;
}
