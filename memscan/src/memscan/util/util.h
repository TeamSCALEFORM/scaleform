#pragma once

/* Includes */

#include <limits.h>
#include <stdbool.h>
#include <stdint.h>

/* Types */

typedef uint8_t   ms_ubyte_t;
typedef uintptr_t ms_uptr_t;
typedef uint32_t  ms_usize_t;

/* Extern */

#if __cplusplus
#define MEMSCAN_EXTERN extern "C"
#else
#define MEMSCAN_EXTERN extern
#endif

typedef enum {
    /* nothing to free, or there's a condition preventing the process */
    MS_FREE_NO = 0,

    /* the data was found present and then freed */
    MS_FREE_YES
} ms_free_t;

typedef enum {
    /* won't be reached unless UTIL_UNSAFE_OPTIMIZATIONS is off */

    /* passed data was NULL */
    MS_BUILD_STATUS_NO_DATA = 0,

    /* data len was 0 */
    MS_BUILD_STATUS_SHORT_DATA,

    /* */

    /* generation has succeeded, status was set to OK */
    MS_BUILD_STATUS_OK
} ms_build_status_t;

typedef struct {
    ms_ubyte_t*       m_data;
    ms_usize_t        m_size;
    ms_build_status_t m_status;
} ms_pattern_t;

/* Methods */

/**
 * @brief Generate byte code array from byte-code style string
 *
 * @param data Example: "AA BB CC DD EE FF", equivalent to
 * (ms_ubyte_t*)"\xAA\xBB\xCC\xDD\xEE\xFF"
 * @param data_size Size of 'data'
 * @return Refer to ms_pattern_t for documentation
 */
MEMSCAN_EXTERN ms_pattern_t
util_build_pattern(const char* data, const ms_usize_t data_size);

/**
 * @brief Deallocate pattern array after usage
 *
 * @param pattern Reference to the pattern construct
 * @return Refer to ms_free_t for documentation
 */
MEMSCAN_EXTERN ms_free_t
util_free_pattern(ms_pattern_t* pattern);

/**
 * @brief Convert pointer in numerical form to byteset of MEMSCAN_BYTESET_SIZE
 * bytes
 *
 * @param num Value to convert
 * @param swap_endianness Whether to swap endianness or not
 * @return Value as a MEMSCAN_BYTESET_SIZE bytes array
 */
MEMSCAN_EXTERN ms_ubyte_t*
               util_ptr_to_byteset(const ms_uptr_t num, bool swap_endianness);

/* Constants */

#define MEMSCAN_BYTESET_SIZE (sizeof(ms_uptr_t) / sizeof(ms_ubyte_t))
#define MEMSCAN_POINTER_BITS (sizeof(ms_uptr_t) * CHAR_BIT)