#include "helper.h"
#include "error.h"
#include <ctype.h>
#include <string.h>
#include <stdint.h>

/**
 * validate user input
 */
cask_error_t validate_input(char *input)
{
  int chr = 0;

  input[strlen(input) - 1] = '\0';// remove newline character
  while (!(input[chr] == '\0')) {
    // printf("input: %c", input[i]);
    if (!isdigit(input[chr])) { return CASK_ERR_INVALID_INPUT; }

    chr += 1;
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
