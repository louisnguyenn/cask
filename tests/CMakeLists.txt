enable_testing()

add_executable(test_storage tests/test_storage.c src/storage.c)

target_include_directories(test_storage PRIVATE include)

add_test(NAME storage_test COMMAND test_storage)
