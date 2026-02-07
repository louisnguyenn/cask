#include "helper.h"
#include "error.h"

/**
 * validate user input
 */
cask_error_t validate_input(char *input)
{
  int i = 0;

  input[strlen(input) - 1] = '\0';// remove newline character
  while (!(input[i] == '\0')) {
    // printf("input: %c", input[i]);
    if (!isdigit(input[i])) { return CASK_ERR_INVALID_INPUT; }

    i += 1;
  }

  return CASK_OK;// success
}

/**
 * calculate record offsets
 */
long cask_record_offset(uint32_t index, uint32_t header_size, uint32_t record_size)
{
  long offset = header_size + (index * record_size);

  return offset;
}
