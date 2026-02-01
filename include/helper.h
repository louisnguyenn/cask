#ifndef HELPER_H
#define HELPER_H

#include "error.h"
#include <stdint.h>
#include <ctype.h>

/**
 * HELPER FUNCTION: returns position/offset of a record
 * parameters: current index
 */
long cask_record_offset(uint32_t index, uint32_t header_size, uint32_t record_size);

/**
 * HELPER FUNCTION: returns a truthy value to validate user input
 */
cask_error_t validate_input(int input);

#endif // HELPER_H
