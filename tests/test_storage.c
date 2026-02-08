#include "cask.h"
#include "error.h"
#include "storage.h"
#include <assert.h>
#include <stdio.h>

int main() {
  cask_error_t res;

  res = cask_storage_init("test.db", 10);
  assert(res == CASK_OK);

  res = cask_storage_close();
  assert(res == CASK_OK);

  printf("All storage tests passed\n");
  return 0;
}
