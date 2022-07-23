#include "util.h"
#include <stdlib.h>
#include <string.h>

ms_pattern_t
util_build_pattern(const char* data, const ms_usize_t data_size)
{
    ms_pattern_t result = {0};

    result.m_data = NULL;
    result.m_size = 0;

#if !UTIL_UNSAFE_OPTIMIZATIONS
    if (data == NULL) {
        result.m_status = MS_BUILD_STATUS_NO_DATA;

        goto leave;
    }
#endif

    size_t len = data_size;

#if !UTIL_UNSAFE_OPTIMIZATIONS
    if (len == 0) {
        result.m_status = MS_BUILD_STATUS_SHORT_DATA;
        goto leave;
    }
#endif

    /* data */

    char* start = (char*)data;
    char* end   = (char*)(data + len);

    /* precompute allocation size */

    ms_usize_t size = 0;

    for (char* current = start; current < end; ++current)
        ++size;

    ms_ubyte_t* bytes = (ms_ubyte_t*)malloc(size * sizeof *bytes);

    /* prefetched */

    ms_usize_t indice = 0;

    for (char* current = start; current < end; ++current) {
        /* hex substring conversion */

        bytes[indice++] = (ms_ubyte_t)strtoul(current, &current, 16);
    }

    result.m_data   = bytes;
    result.m_size   = indice;
    result.m_status = MS_BUILD_STATUS_OK;

leave:
    return result;
}

/* */

ms_free_t
util_free_pattern(ms_pattern_t* pattern)
{
#if !UTIL_UNSAFE_OPTIMIZATIONS
    if (pattern == NULL) {
        return MS_FREE_NO;
    }
#endif

    ms_free_t result = MS_FREE_NO;

    if (pattern->m_status == MS_BUILD_STATUS_OK) {
        free(pattern->m_data);
        pattern->m_data = NULL;

        result = MS_FREE_YES;
    }

    pattern->m_size = 0;

    return result;
}

ms_ubyte_t*
util_ptr_to_byteset(const ms_uptr_t num, bool swap_endianness)
{
    /* data */

    static ms_ubyte_t bytes[MEMSCAN_BYTESET_SIZE] = {0};

    for (ms_usize_t i = 0; i < MEMSCAN_BYTESET_SIZE; ++i) {
        /* shift formation to get current indice */

        bytes[swap_endianness ? i : MEMSCAN_BYTESET_SIZE - i - 1] =
            (ms_ubyte_t)(num >> (i * CHAR_BIT));
    }

    return bytes;
}