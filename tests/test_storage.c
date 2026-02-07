// TEST HARNESS

#include "cask.h"
#include "error.h"
#include "helper.h"
#include "storage.h"
#include <stdio.h>
#include <string.h>

#define TEST_DB_FILE "test_db.cask"

void print_result(const char *test_name, cask_error_t res)
{
  if (res == CASK_OK)
    printf("[PASS] %s\n", test_name);
  else
    printf("[FAIL] %s (error code: %d)\n", test_name, res);
}

int main()
{
  cask_error_t res;
  char value_buffer[VALUE_SIZE];

  printf("=== CASK STORAGE TEST SUITE ===\n\n");

  // ---------------- INIT ----------------
  res = cask_storage_init(TEST_DB_FILE);
  print_result("Storage Initialization", res);

  // ---------------- PUT ----------------
  res = cask_record_put("username", "dev");
  print_result("Put Record: username", res);

  res = cask_record_put("project", "binary_kv_store");
  print_result("Put Record: project", res);

  // ---------------- GET ----------------
  memset(value_buffer, 0, sizeof(value_buffer));
  res = cask_record_get("username", value_buffer);
  print_result("Get Record: username", res);

  if (res == CASK_OK) printf("  Retrieved Value: %s\n", value_buffer);

  // ---------------- UPDATE TEST ----------------
  res = cask_record_put("username", "embedded_engineer");
  print_result("Update Record: username", res);

  memset(value_buffer, 0, sizeof(value_buffer));
  res = cask_record_get("username", value_buffer);
  print_result("Get Updated Record", res);

  if (res == CASK_OK) printf("  Updated Value: %s\n", value_buffer);

  // ---------------- DELETE ----------------
  res = cask_record_delete("project");
  print_result("Delete Record: project", res);

  // Try getting deleted key
  memset(value_buffer, 0, sizeof(value_buffer));
  res = cask_record_get("project", value_buffer);
  print_result("Get Deleted Record (should fail)", res);

  // ---------------- DUPLICATE KEY TEST ----------------
  res = cask_record_put("username", "systems_dev");
  print_result("Overwrite Existing Key", res);

  // ---------------- INVALID KEY TEST ----------------
  res = cask_record_get("nonexistent_key", value_buffer);
  print_result("Get Nonexistent Key (should fail)", res);

  // ---------------- CLOSE ----------------
  res = cask_storage_close();
  print_result("Storage Close", res);

  printf("\n=== TESTING COMPLETE ===\n");
  return 0;
}
