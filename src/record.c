#include "storage.h"

cask_error_t cask_record_put(const char *key, const char *value)
{

}

cask_error_t cask_record_get(const char *key, char *out_value)
{

}

cask_error_t cask_record_delete(const char *key)
{

}

cask_error_t cask_storage_close()
{

}

long cask_record_offset(uint32_t index)
{
    const offset = sizeof(cask_record_t) + index;
    return offset;
}
