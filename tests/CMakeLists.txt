add_executable(test_storage
    test_storage.c
    ../src/storage.c
    ../src/error.c
    ../src/helper.c
)

target_include_directories(test_storage PRIVATE ../include)

add_test(NAME storage_test COMMAND test_storage)
