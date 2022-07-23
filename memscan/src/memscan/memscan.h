#pragma once

/* Includes */

#include <stdint.h>

/* Utility */

#include "util/util.h"

/* Types */

typedef enum {
    /* the search goes backwards (substracts from current address) */
    MS_FOLLOW_DIRECTION_BACKWARDS = 0,
    
    /* the search goes forwards (adds to current address) */
    MS_FOLLOW_DIRECTION_FORWARDS
} ms_follow_direction_t;

typedef enum {
    /* won't be reached if MEMSCAN_UNSAFE_OPTIMIZATIONS are on */
    
    MS_RESULT_NO_VALID_BYTES_INFO = 0,
    
    /* finish <= start */
    MS_RESULT_NO_VALID_SPAN,
    
    /* */
    
    /* generic response if not found */
    MS_RESULT_STATUS_NOT_FOUND,
    
    /* follow led to address being < start and thus was not applied */
    MS_RESULT_STATUS_FOUND_FOLLOW_FAIL_LHS,
    
    /* follow led to address being > end and thus was not applied */
    MS_RESULT_STATUS_FOUND_FOLLOW_FAIL_RHS,
    
    /* broke before reaching a match in memory, the former 2 are pioritized */
    MS_RESULT_STATUS_FOUND_FOLLOW_FAIL_INCOMPLETE,
    
    /* pattern was found, follow has succeeded, status set to FOUND */
    MS_RESULT_STATUS_FOUND
} ms_result_status_t;

typedef struct {
    ms_uptr_t          m_address;
    ms_result_status_t m_status;
} ms_result_t;

/* Methods */

/* Patterns */

/**
 * @brief Bytes, Bytes pattern-scanning function
 *
 * @param start Position to start scanning from in global address space
 * @param end Position to stop scanning at in global address space (expected to
 * be, at the very least, start + pattern_size, failure to meet this condition
 * will be evidenciated in the return)
 * @param pattern Array of ubytes to match in memory, may contain
 * [k_memscan_wildcard], which allows a mismatch at the opcode's position
 * @param pattern_size Size of pattern
 * @param pattern_nth_match N-th pattern repetition to select, starts at
 * MEMSCAN_FIRST_MATCH
 * @param follow_pattern Array of ubytes to look for, from pattern scan
 * address, in a specified direction. Spanned from start to end (failures to
 * meet conditions will be evidentiated in the return)
 * @param follow_pattern_size Size of follow_pattern
 * @param follow_nth_match Same as pattern_nth_match, but with the
 * follow_pattern
 * @param follow_direction refer to ms_follow_direction_t for documentation
 * @return Refer to ms_result_t for documentation
 */
MEMSCAN_EXTERN ms_result_t
memscan_find_pattern_bb(const ms_uptr_t start, const ms_uptr_t end,
                        const ms_ubyte_t*           pattern,
                        const ms_usize_t            pattern_size,
                        const ms_usize_t            pattern_nth_match,
                        const ms_ubyte_t*           follow_pattern,
                        const ms_usize_t            follow_pattern_size,
                        const ms_usize_t            follow_nth_match,
                        const ms_follow_direction_t follow_direction);

/**
 * @brief Bytes, String pattern-scanning function
 *
 * @param start Position to start scanning from in global address space
 * @param end Position to stop scanning at in global address space (expected to
 * be, at the very least, start + pattern_size, failure to meet this condition
 * will be evidenciated in the return)
 * @param pattern Array of ubytes to match in memory, may contain
 * [k_memscan_wildcard], which allows a mismatch at the opcode's position
 * @param pattern_size Size of pattern
 * @param pattern_nth_match N-th pattern repetition to select, starts at
 * MEMSCAN_FIRST_MATCH
 * @param follow_pattern Byte-code style string that will be turned into a
 * ms_ubyte_t array for evaluation, example: "8B 4D"
 * @param follow_nth_match Same as pattern_nth_match, but with the
 * follow_pattern
 * @param follow_direction refer to ms_follow_direction_t for documentation
 * @return Refer to ms_result_t for documentation
 */
MEMSCAN_EXTERN ms_result_t
memscan_find_pattern_bs(const ms_uptr_t start, const ms_uptr_t end,
                        const ms_ubyte_t*           pattern,
                        const ms_usize_t            pattern_size,
                        const ms_usize_t            pattern_nth_match,
                        const char*                 follow_pattern,
                        const ms_usize_t            follow_nth_match,
                        const ms_follow_direction_t follow_direction);

/**
 * @brief String, Bytes pattern-scanning function
 *
 * @param start Position to start scanning from in global address space
 * @param end Position to stop scanning at in global address space (expected to
 * be, at the very least, start + pattern_size, failure to meet this condition
 * will be evidenciated in the return)
 * @param pattern Byte-code style string that will be turned into a ms_ubyte_t
 * array for evaluation, may contain [k_memscan_wildcard], which allows a
 * mismatch at the opcode's position. example: "55 8B EC CC CC CC CC"
 * @param pattern_nth_match N-th pattern repetition to select, starts at
 * MEMSCAN_FIRST_MATCH
 * @param follow_pattern Array of ubytes to look for, from pattern scan
 * address, in a specified direction. Spanned from start to end (failures to
 * meet conditions will be evidentiated in the return)
 * @param follow_pattern_size Size of follow_pattern
 * @param follow_nth_match Same as pattern_nth_match, but with the
 * follow_pattern
 * @param follow_direction refer to ms_follow_direction_t for documentation
 * @return Refer to ms_result_t for documentation
 */
MEMSCAN_EXTERN ms_result_t
memscan_find_pattern_sb(const ms_uptr_t start, const ms_uptr_t end,
                        const char* pattern, const ms_usize_t pattern_nth_match,
                        const ms_ubyte_t*           follow_pattern,
                        const ms_usize_t            follow_pattern_size,
                        const ms_usize_t            follow_nth_match,
                        const ms_follow_direction_t follow_direction);

/**
 * @brief String, String pattern-scanning function
 *
 * @param start Position to start scanning from in global address space
 * @param end Position to stop scanning at in global address space (expected to
 * be, at the very least, start + pattern_size, failure to meet this condition
 * will be evidenciated in the return)
 * @param pattern Byte-code style string that will be turned into a ms_ubyte_t
 * array for evaluation, may contain [k_memscan_wildcard], which allows a
 * mismatch at the opcode's position. example: "55 8B EC CC CC CC CC"
 * @param pattern_nth_match N-th pattern repetition to select, starts at
 * MEMSCAN_FIRST_MATCH
 * @param follow_pattern Byte-code style string that will be turned into a
 * ms_ubyte_t array for evaluation, example: "8B 4D"
 * @param follow_nth_match Same as pattern_nth_match, but with the
 * follow_pattern
 * @param follow_direction refer to ms_follow_direction_t for documentation
 * @return Refer to ms_result_t for documentation
 */
MEMSCAN_EXTERN ms_result_t
memscan_find_pattern_ss(const ms_uptr_t start, const ms_uptr_t end,
                        const char* pattern, const ms_usize_t pattern_nth_match,
                        const char*                 follow_pattern,
                        const ms_usize_t            follow_nth_match,
                        const ms_follow_direction_t follow_direction);

/**
 * @brief No follow, Bytes pattern-scanning function
 *
 * @param start Position to start scanning from in global address space
 * @param end Position to stop scanning at in global address space (expected to
 * be, at the very least, start + pattern_size, failure to meet this condition
 * will be evidenciated in the return)
 * @param pattern Array of ubytes to match in memory, may contain
 * [k_memscan_wildcard], which allows a mismatch at the opcode's position
 * @param pattern_size Size of pattern
 * @param pattern_nth_match N-th pattern repetition to select, starts at
 * MEMSCAN_FIRST_MATCH
 * @return Refer to ms_result_t for documentation
 */
MEMSCAN_EXTERN ms_result_t
memscan_find_pattern_nfb(const ms_uptr_t start, const ms_uptr_t end,
                         const ms_ubyte_t* pattern,
                         const ms_usize_t  pattern_size,
                         const ms_usize_t  pattern_nth_match);

/**
 * @brief No follow, String pattern-scanning function
 *
 * @param start Position to start scanning from in global address space
 * @param end Position to stop scanning at in global address space (expected to
 * be, at the very least, start + pattern_size, failure to meet this condition
 * will be evidenciated in the return)
 * @param pattern Byte-code style string that will be turned into a ms_ubyte_t
 * array for evaluation, may contain [k_memscan_wildcard], which allows a
 * mismatch at the opcode's position. example: "55 8B EC CC CC CC CC"
 * @param pattern_nth_match N-th pattern repetition to select, starts at
 * MEMSCAN_FIRST_MATCH
 * @return Refer to ms_result_t for documentation
 */
MEMSCAN_EXTERN ms_result_t
memscan_find_pattern_nfs(const ms_uptr_t start, const ms_uptr_t end,
                         const char*      pattern,
                         const ms_usize_t pattern_nth_match);

/**
 * @brief Xref Bytes Follow finder from a sequence
 *
 * @param start Position to start scanning from in global address space
 * @param end Position to stop scanning at in global address space (expected to
 * be, at the very least, start + MEMSCAN_BYTESET_SIZE, failure to meet this
 * condition will be evidenciated in the return)
 * @param content Content to find  in global address space
 * @param nth_match N-th repetition of content, starts at  MEMSCAN_FIRST_MATCH
 * @param swap_endianness Whether the content should have it's endianness
 * swapped
 * @param follow_pattern Array of ms_ubyte_t to look for, from xref address, in
 * a specified direction. Spanned from start to end (failures to meet conditions
 * will be evidentiated in the return)
 * @param follow_pattern_size Size of follow_pattern
 * @param follow_nth_match Same as nth_match, but with the follow_pattern
 * @param follow_direction refer to ms_follow_direction_t for documentation
 * @return Refer to ms_result_t for documentation
 */
MEMSCAN_EXTERN ms_result_t
memscan_find_xref_b(const ms_uptr_t start, const ms_uptr_t end,
                    const ms_uptr_t content, const ms_usize_t content_nth_match,
                    bool swap_endianness, const ms_ubyte_t* follow_pattern,
                    const ms_usize_t            follow_pattern_size,
                    const ms_usize_t            follow_nth_match,
                    const ms_follow_direction_t follow_direction);

/**
 * @brief Xref Bytes Follow finder from a reference to pointer
 *
 * @param start Position to start scanning from in global address space
 * @param end Position to stop scanning at in global address space (expected to
 * be, at the very least, start + MEMSCAN_BYTESET_SIZE, failure to meet this
 * condition will be evidenciated in the return)
 * @param address Reference to address to find references to in global address
 * space
 * @param nth_match N-th repetition of reference to select, starts at
 * MEMSCAN_FIRST_MATCH, for clarification, matches are looked for from start,
 * not from address
 * @param swap_endianness Whether the contents at address to have their
 * endianness swapped
 * @param follow_pattern Array of ubytes to look for, from xref address, in
 * a specified direction. Spanned from start to end (failures to meet conditions
 * will be evidentiated in the return)
 * @param follow_pattern_size Size of follow_pattern
 * @param follow_nth_match Same as nth_match, but with the follow_pattern
 * @param follow_direction refer to ms_follow_direction_t for documentation
 * @return Refer to ms_result_t for documentation
 */
MEMSCAN_EXTERN ms_result_t
memscan_find_xref_at_b(const ms_uptr_t start, const ms_uptr_t end,
                       const ms_uptr_t address, const ms_usize_t nth_match,
                       bool swap_endianness, const ms_ubyte_t* follow_pattern,
                       const ms_usize_t            follow_pattern_size,
                       const ms_usize_t            follow_nth_match,
                       const ms_follow_direction_t follow_direction);

/**
 * @brief Xref String Follow finder from a sequence
 *
 * @param start Position to start scanning from in global address space
 * @param end Position to stop scanning at in global address space (expected to
 * be, at the very least, start + MEMSCAN_BYTESET_SIZE, failure to meet this
 * condition will be evidenciated in the return)
 * @param content Content to find  in global address space
 * @param nth_match N-th repetition of content, starts at  MEMSCAN_FIRST_MATCH
 * @param swap_endianness Whether the content should have it's endianness
 * swapped
 * @param follow_pattern Byte-code style string that will be turned into a
 * ms_ubyte_t array for evaluation, example: "8B 4D"
 * @param follow_nth_match Same as nth_match, but with the follow_pattern
 * @param follow_direction refer to ms_follow_direction_t for documentation
 * @return Refer to ms_result_t for documentation
 */
MEMSCAN_EXTERN ms_result_t
memscan_find_xref_s(const ms_uptr_t start, const ms_uptr_t end,
                    const ms_uptr_t content, const ms_usize_t content_nth_match,
                    bool swap_endianness, const char* follow_pattern,
                    const ms_usize_t            follow_nth_match,
                    const ms_follow_direction_t follow_direction);

/**
 * @brief Xref String Follow finder from a reference to pointer
 *
 * @param start Position to start scanning from in global address space
 * @param end Position to stop scanning at in global address space (expected to
 * be, at the very least, start + MEMSCAN_BYTESET_SIZE, failure to meet this
 * condition will be evidenciated in the return)
 * @param address Reference to address to find references to in global address
 * space
 * @param nth_match N-th repetition of reference to select, starts at
 * MEMSCAN_FIRST_MATCH, for clarification, matches are looked for from start,
 * not from address
 * @param swap_endianness Whether the contents at address to have their
 * endianness swapped
 * @param follow_pattern Byte-code style string that will be turned into a
 * ms_ubyte_t array for evaluation, example: "8B 4D"
 * @param follow_nth_match Same as nth_match, but with the follow_pattern
 * @param follow_direction refer to ms_follow_direction_t for documentation
 * @return Refer to ms_result_t for documentation
 */
MEMSCAN_EXTERN ms_result_t
memscan_find_xref_at_s(const ms_uptr_t start, const ms_uptr_t end,
                       const ms_uptr_t address, const ms_usize_t nth_match,
                       bool swap_endianness, const char* follow_pattern,
                       const ms_usize_t            follow_nth_match,
                       const ms_follow_direction_t follow_direction);

/**
 * @brief Xref No follow finder from a sequence
 *
 * @param start Position to start scanning from in global address space
 * @param end Position to stop scanning at in global address space (expected to
 * be, at the very least, start + MEMSCAN_BYTESET_SIZE, failure to meet this
 * condition will be evidenciated in the return)
 * @param content Content to find  in global address space
 * @param nth_match N-th repetition of content, starts at  MEMSCAN_FIRST_MATCH
 * @param swap_endianness Whether the content should have it's endianness
 * swapped
 * @return Refer to ms_result_t for documentation
 */
MEMSCAN_EXTERN ms_result_t
memscan_find_xref_nf(const ms_uptr_t start, const ms_uptr_t end,
                     const ms_uptr_t  content,
                     const ms_usize_t content_nth_match, bool swap_endianness);

/**
 * @brief Xref No follow finder from a reference to pointer
 *
 * @param start Position to start scanning from in global address space
 * @param end Position to stop scanning at in global address space (expected to
 * be, at the very least, start + MEMSCAN_BYTESET_SIZE, failure to meet this
 * condition will be evidenciated in the return)
 * @param address Reference to address to find references to in global address
 * space
 * @param nth_match N-th repetition of reference to select, starts at
 * MEMSCAN_FIRST_MATCH, for clarification, matches are looked for from start,
 * not from address
 * @param swap_endianness Whether the contents at address to have their
 * endianness swapped
 * @return Refer to ms_result_t for documentation
 */
MEMSCAN_EXTERN ms_result_t
memscan_find_xref_at_nf(const ms_uptr_t start, const ms_uptr_t end,
                        const ms_uptr_t address, const ms_usize_t nth_match,
                        bool swap_endianness);

/**
 * @brief String, Bytes follow finder from string start pointer to reversed
 * endianness address scan
 *
 * @param start Position to start scanning from in global address space
 * @param end Position to stop scanning at in global address space (expected to
 * be, at the very least, start + MEMSCAN_BYTESET_SIZE, failure to meet this
 * condition will be evidenciated in the return)
 * @param text Compile-time string to find (should be found in '.rdata'/it's
 * variations for Windows, or maybe batched in '.text', etc...)
 * @param text_size Size of the 'text'
 * @param nth_match N-th reference to the address of the first character of the
 * string with reversed endianness in memory
 * @param follow_pattern Array of ubytes to look for, from string xref
 * address, in a specified direction. Spanned from start to end (failures to
 * meet conditions will be evidentiated in the return)
 * @param follow_pattern_size Size of follow_pattern
 * @param follow_nth_match Same as nth_match, but with the follow_pattern
 * @param follow_direction refer to ms_follow_direction_t for documentation
 * @return Refer to ms_result_t for documentation
 */
MEMSCAN_EXTERN ms_result_t
memscan_find_string_b(const ms_uptr_t start, const ms_uptr_t end,
                      const char* text, const ms_usize_t text_size,
                      const ms_usize_t            nth_match,
                      const ms_ubyte_t*           follow_pattern,
                      const ms_usize_t            follow_pattern_size,
                      const ms_usize_t            follow_nth_match,
                      const ms_follow_direction_t follow_direction);

/**
 * @brief String, String follow finder from string start pointer to reversed
 * endianness address scan
 *
 * @param start Position to start scanning from in global address space
 * @param end Position to stop scanning at in global address space (expected to
 * be, at the very least, start + MEMSCAN_BYTESET_SIZE, failure to meet this
 * condition will be evidenciated in the return)
 * @param text Compile-time string to find (should be found in '.rdata'/it's
 * variations for Windows, or maybe batched in '.text', etc...)
 * @param text_size Size of the 'text'
 * @param nth_match N-th reference to the address of the first character of the
 * string with reversed endianness in memory
 * @param follow_pattern Byte-code style string that will be turned into a
 * ms_ubyte_t array for evaluation, example: "8B 4D"
 * @param follow_nth_match Same as nth_match, but with the follow_pattern
 * @param follow_direction refer to ms_follow_direction_t for documentation
 * @return Refer to ms_result_t for documentation
 */
MEMSCAN_EXTERN ms_result_t
memscan_find_string_s(const ms_uptr_t start, const ms_uptr_t end,
                      const char* text, const ms_usize_t text_size,
                      const ms_usize_t nth_match, const char* follow_pattern,
                      const ms_usize_t            follow_nth_match,
                      const ms_follow_direction_t follow_direction);

/**
 * @brief String No Follow finder from string start pointer to reversed
 * endianness address scan
 *
 * @param start Position to start scanning from in global address space
 * @param end Position to stop scanning at in global address space (expected to
 * be, at the very least, start + MEMSCAN_BYTESET_SIZE, failure to meet this
 * condition will be evidenciated in the return)
 * @param text Compile-time string to find (should be found in '.rdata'/it's
 * variations for Windows, or maybe batched in '.text', etc...)
 * @param text_size Size of the 'text'
 * @param nth_match N-th reference to the address of the first character of the
 * string with reversed endianness in memory
 * @return Refer to ms_result_t for documentation
 */
MEMSCAN_EXTERN ms_result_t
memscan_find_string_nf(const ms_uptr_t start, const ms_uptr_t end,
                       const char* text, const ms_usize_t text_size,
                       const ms_usize_t nth_match);

/* Detail */

static const ms_ubyte_t k_memscan_wildcard = 0xCC;

/* Constants */

#define MEMSCAN_FIRST_MATCH (0)

/* Wrapper */

#if __cplusplus
#include <optional>
#include <string>
#include <windows.h>

namespace memscan
{
    struct mapped_region_t {
        /* constructors */
        
        mapped_region_t() = default;
        
        [[nodiscard]] mapped_region_t(const ms_uptr_t start,
                                      const ms_uptr_t end) noexcept
            : m_start(start),
        m_end(end)
        {
        }
        
        [[nodiscard]] mapped_region_t(const HMODULE& module)
            : m_start(reinterpret_cast<ms_uptr_t>(module))
        {
            const auto* const dos_header =
                reinterpret_cast<PIMAGE_DOS_HEADER>(m_start);
            
#if MEMSCAN_UNSAFE_OPTIMIZATIONS
            if (dos_header == nullptr) {
                return;
            }
#endif
            
            const auto* const nt_headers = reinterpret_cast<PIMAGE_NT_HEADERS>(
                                                                               m_start + static_cast<ms_uptr_t>(dos_header->e_lfanew));
            
#if MEMSCAN_UNSAFE_OPTIMIZATIONS
            if (nt_headers == nullptr) {
                return;
            }
#endif
            
            m_end = m_start +
                static_cast<ms_uptr_t>(nt_headers->OptionalHeader.SizeOfImage);
        }
        
        /* implementations */
        
        /* C-style casts are used for automatic cast deduction */
        
        template <typename T, bool AcceptFailedFollow, ms_usize_t N, ms_usize_t N2>
            static std::optional<T>
            find_pattern(const ms_uptr_t start, const ms_uptr_t           end,
                         const ms_ubyte_t (&pattern)[N], const ms_usize_t nth_match,
                         const ms_ubyte_t (&follow)[N2],
                         const ms_usize_t            follow_nth_match,
                         const ms_follow_direction_t follow_direction) noexcept
        {
            auto&& result =
                memscan_find_pattern_bb(start, end, pattern, N, nth_match, follow,
                                        N2, follow_nth_match, follow_direction);
            
            constexpr auto status = AcceptFailedFollow
                ? MS_RESULT_STATUS_FOUND_FOLLOW_FAIL_LHS
                : MS_RESULT_STATUS_FOUND;
            if (result.m_status >= status)
                return (T)result.m_address;
            
            return std::nullopt;
        }
        
        template <typename T, bool AcceptFailedFollow, ms_usize_t N>
            static std::optional<T>
            find_pattern(const ms_uptr_t start, const ms_uptr_t end,
                         const std::string_view pattern, const ms_usize_t nth_match,
                         const ms_ubyte_t (&follow)[N],
                         const ms_usize_t            follow_nth_match,
                         const ms_follow_direction_t follow_direction) noexcept
        {
            auto&& result = memscan_find_pattern_sb(
                                                    start, end, pattern.data(), nth_match, follow, N, follow_nth_match,
                                                    follow_direction);
            
            constexpr auto status = AcceptFailedFollow
                ? MS_RESULT_STATUS_FOUND_FOLLOW_FAIL_LHS
                : MS_RESULT_STATUS_FOUND;
            if (result.m_status >= status)
                return (T)result.m_address;
            
            return std::nullopt;
        }
        
        template <typename T, bool AcceptFailedFollow, ms_usize_t N>
            static std::optional<T>
            find_pattern(const ms_uptr_t start, const ms_uptr_t           end,
                         const ms_ubyte_t (&pattern)[N], const ms_usize_t nth_match,
                         const std::string_view      follow,
                         const ms_usize_t            follow_nth_match,
                         const ms_follow_direction_t follow_direction) noexcept
        {
            auto&& result = memscan_find_pattern_bs(
                                                    start, end, pattern, N, nth_match, follow.data(), follow_nth_match,
                                                    follow_direction);
            
            constexpr auto status = AcceptFailedFollow
                ? MS_RESULT_STATUS_FOUND_FOLLOW_FAIL_LHS
                : MS_RESULT_STATUS_FOUND;
            if (result.m_status >= status)
                return (T)result.m_address;
            
            return std::nullopt;
        }
        
        template <typename T, bool AcceptFailedFollow>
            static std::optional<T>
            find_pattern(const ms_uptr_t start, const ms_uptr_t end,
                         const std::string_view pattern, const ms_usize_t nth_match,
                         const std::string_view      follow,
                         const ms_usize_t            follow_nth_match,
                         const ms_follow_direction_t follow_direction) noexcept
        {
            auto&& result = memscan_find_pattern_ss(
                                                    start, end, pattern.data(), nth_match, follow.data(),
                                                    follow_nth_match, follow_direction);
            
            constexpr auto status = AcceptFailedFollow
                ? MS_RESULT_STATUS_FOUND_FOLLOW_FAIL_LHS
                : MS_RESULT_STATUS_FOUND;
            if (result.m_status >= status)
                return (T)result.m_address;
            
            return std::nullopt;
        }
        
        template <typename T, ms_usize_t N>
            static std::optional<T>
            find_pattern(const ms_uptr_t start, const ms_uptr_t end,
                         const ms_ubyte_t (&pattern)[N],
                         const ms_usize_t nth_match = MEMSCAN_FIRST_MATCH) noexcept
        {
            auto&& result =
                memscan_find_pattern_nfb(start, end, pattern, N, nth_match);
            
            if (result.m_status == MS_RESULT_STATUS_FOUND)
                return (T)result.m_address;
            
            return std::nullopt;
        }
        
        template <typename T>
            static std::optional<T>
            find_pattern(const ms_uptr_t start, const ms_uptr_t end,
                         const std::string_view pattern,
                         const ms_usize_t nth_match = MEMSCAN_FIRST_MATCH) noexcept
        {
            auto&& result =
                memscan_find_pattern_nfs(start, end, pattern.data(), nth_match);
            
            if (result.m_status == MS_RESULT_STATUS_FOUND)
                return (T)result.m_address;
            
            return std::nullopt;
        }
        
        template <typename T, bool AcceptFailedFollow, ms_usize_t N>
            static std::optional<T>
            find_xref(const ms_uptr_t start, const ms_uptr_t end,
                      const ms_uptr_t content, const ms_usize_t content_nth_match,
                      bool             swap_endianness, const ms_ubyte_t (&follow)[N],
                      const ms_usize_t follow_nth_match,
                      const ms_follow_direction_t follow_direction) noexcept
            
        {
            auto&& result = memscan_find_xref_b(
                                                start, end, content, content_nth_match, swap_endianness, follow, N,
                                                follow_nth_match, follow_direction);
            
            constexpr auto status = AcceptFailedFollow
                ? MS_RESULT_STATUS_FOUND_FOLLOW_FAIL_LHS
                : MS_RESULT_STATUS_FOUND;
            if (result.m_status >= status)
                return (T)result.m_address;
            
            return std::nullopt;
        }
        
        template <typename T, bool AcceptFailedFollow>
            static std::optional<T>
            find_xref(const ms_uptr_t start, const ms_uptr_t end,
                      const ms_uptr_t content, const ms_usize_t content_nth_match,
                      bool swap_endianness, const std::string_view follow,
                      const ms_usize_t            follow_nth_match,
                      const ms_follow_direction_t follow_direction) noexcept
            
        {
            auto&& result = memscan_find_xref_s(
                                                start, end, content, content_nth_match, swap_endianness,
                                                follow.data(), follow_nth_match, follow_direction);
            
            constexpr auto status = AcceptFailedFollow
                ? MS_RESULT_STATUS_FOUND_FOLLOW_FAIL_LHS
                : MS_RESULT_STATUS_FOUND;
            if (result.m_status >= status)
                return (T)result.m_address;
            
            return std::nullopt;
        }
        
        template <typename T>
            static std::optional<T>
            find_xref(const ms_uptr_t start, const ms_uptr_t end,
                      const ms_uptr_t content, const ms_usize_t content_nth_match,
                      bool swap_endianness) noexcept
        {
            auto&& result = memscan_find_xref_nf(
                                                 start, end, content, content_nth_match, swap_endianness);
            
            if (result.m_status == MS_RESULT_STATUS_FOUND)
                return (T)result.m_address;
            
            return std::nullopt;
        }
        
        template <typename T, bool AcceptFailedFollow, ms_usize_t N>
            static std::optional<T>
            find_xref_at(const ms_uptr_t start, const ms_uptr_t end,
                         const ms_uptr_t address, const ms_usize_t nth_match,
                         bool swap_endianness, const ms_ubyte_t (&follow)[N],
                         const ms_usize_t            follow_nth_match,
                         const ms_follow_direction_t follow_direction) noexcept
            
        {
            auto&& result = memscan_find_xref_at_b(
                                                   start, end, address, nth_match, swap_endianness, follow, N,
                                                   follow_nth_match, follow_direction);
            
            constexpr auto status = AcceptFailedFollow
                ? MS_RESULT_STATUS_FOUND_FOLLOW_FAIL_LHS
                : MS_RESULT_STATUS_FOUND;
            if (result.m_status >= status)
                return (T)result.m_address;
            
            return std::nullopt;
        }
        
        template <typename T, bool AcceptFailedFollow>
            static std::optional<T>
            find_xref_at(const ms_uptr_t start, const ms_uptr_t end,
                         const ms_uptr_t address, const ms_usize_t nth_match,
                         bool swap_endianness, const std::string_view follow,
                         const ms_usize_t            follow_nth_match,
                         const ms_follow_direction_t follow_direction) noexcept
            
        {
            auto&& result = memscan_find_xref_at_s(
                                                   start, end, address, nth_match, swap_endianness, follow.data(),
                                                   follow_nth_match, follow_direction);
            
            constexpr auto status = AcceptFailedFollow
                ? MS_RESULT_STATUS_FOUND_FOLLOW_FAIL_LHS
                : MS_RESULT_STATUS_FOUND;
            if (result.m_status >= status)
                return (T)result.m_address;
            
            return std::nullopt;
        }
        
        template <typename T>
            static std::optional<T>
            find_xref_at(const ms_uptr_t start, const ms_uptr_t end,
                         const ms_uptr_t address, const ms_usize_t nth_match,
                         bool swap_endianness) noexcept
        {
            auto&& result = memscan_find_xref_at_nf(start, end, address, nth_match,
                                                    swap_endianness);
            
            if (result.m_status == MS_RESULT_STATUS_FOUND)
                return (T)result.m_address;
            
            return std::nullopt;
        }
        
        template <typename T, bool AcceptFailedFollow, ms_usize_t N>
            static std::optional<T>
            find_string(const ms_uptr_t start, const ms_uptr_t end,
                        const std::string_view string, const ms_usize_t nth_match,
                        const ms_ubyte_t (&follow)[N],
                        const ms_usize_t            follow_nth_match,
                        const ms_follow_direction_t follow_direction) noexcept
        {
            auto&& result = memscan_find_string_b(
                                                  start, end, string.data(), string.size(), nth_match, follow, N,
                                                  follow_nth_match, follow_direction);
            
            constexpr auto status = AcceptFailedFollow
                ? MS_RESULT_STATUS_FOUND_FOLLOW_FAIL_LHS
                : MS_RESULT_STATUS_FOUND;
            if (result.m_status >= status)
                return (T)result.m_address;
            
            return std::nullopt;
        }
        
        template <typename T, bool AcceptFailedFollow>
            static std::optional<T>
            find_string(const ms_uptr_t start, const ms_uptr_t end,
                        const std::string_view string, const ms_usize_t nth_match,
                        const std::string_view      follow,
                        const ms_usize_t            follow_nth_match,
                        const ms_follow_direction_t follow_direction) noexcept
        {
            auto&& result = memscan_find_string_s(
                                                  start, end, string.data(), string.size(), nth_match, follow.data(),
                                                  follow_nth_match, follow_direction);
            
            constexpr auto status = AcceptFailedFollow
                ? MS_RESULT_STATUS_FOUND_FOLLOW_FAIL_LHS
                : MS_RESULT_STATUS_FOUND;
            if (result.m_status >= status)
                return (T)result.m_address;
            
            return std::nullopt;
        }
        
        template <typename T>
            static std::optional<T>
            find_string(const ms_uptr_t start, const ms_uptr_t end,
                        const std::string_view string,
                        const ms_usize_t       nth_match = MEMSCAN_FIRST_MATCH) noexcept
        {
            auto&& result = memscan_find_string_nf(start, end, string.data(),
                                                   string.size(), nth_match);
            
            if (result.m_status >= MS_RESULT_STATUS_FOUND)
                return (T)result.m_address;
            
            return std::nullopt;
        }
        
        /* injections */
        
        template <typename T, bool AcceptFailedFollow, ms_usize_t N, ms_usize_t N2>
            std::optional<T>
            find_pattern(const ms_ubyte_t (&pattern)[N], const ms_usize_t nth_match,
                         const ms_ubyte_t (&follow)[N2],
                         const ms_usize_t            follow_nth_match,
                         const ms_follow_direction_t follow_direction) const noexcept
        {
            return find_pattern<T, AcceptFailedFollow, N, N2>(
                                                              m_start, m_end, pattern, nth_match, follow, follow_nth_match,
                                                              follow_direction);
        }
        
        template <typename T, bool AcceptFailedFollow, ms_usize_t N>
            std::optional<T>
            find_pattern(const std::string_view pattern, const ms_usize_t nth_match,
                         const ms_ubyte_t (&follow)[N],
                         const ms_usize_t            follow_nth_match,
                         const ms_follow_direction_t follow_direction) const noexcept
        {
            return find_pattern<T, AcceptFailedFollow, N>(
                                                          m_start, m_end, pattern, nth_match, follow, follow_nth_match,
                                                          follow_direction);
        }
        
        template <typename T, bool AcceptFailedFollow, ms_usize_t N>
            std::optional<T>
            find_pattern(const ms_ubyte_t (&pattern)[N], const ms_usize_t nth_match,
                         const std::string_view      follow,
                         const ms_usize_t            follow_nth_match,
                         const ms_follow_direction_t follow_direction) const noexcept
        {
            return find_pattern<T, AcceptFailedFollow, N>(
                                                          m_start, m_end, pattern, nth_match, follow, follow_nth_match,
                                                          follow_direction);
        }
        
        template <typename T, bool AcceptFailedFollow>
            std::optional<T>
            find_pattern(const std::string_view pattern, const ms_usize_t nth_match,
                         const std::string_view      follow,
                         const ms_usize_t            follow_nth_match,
                         const ms_follow_direction_t follow_direction) const noexcept
        {
            return find_pattern<T, AcceptFailedFollow>(
                                                       m_start, m_end, pattern, nth_match, follow, follow_nth_match,
                                                       follow_direction);
        }
        
        template <typename T, ms_usize_t N>
            std::optional<T>
            find_pattern(const ms_ubyte_t (&pattern)[N],
                         const ms_usize_t match = MEMSCAN_FIRST_MATCH) const noexcept
        {
            return find_pattern<T, N>(m_start, m_end, pattern, match);
        }
        
        template <typename T>
            std::optional<T> find_pattern(
                                          const std::string_view pattern,
                                          const ms_usize_t       nth_match = MEMSCAN_FIRST_MATCH) const noexcept
        {
            return find_pattern<T>(m_start, m_end, pattern, nth_match);
        }
        
        template <typename T, bool AcceptFailedFollow, ms_usize_t N>
            std::optional<T>
            find_xref(const ms_uptr_t content, const ms_usize_t content_nth_match,
                      bool             swap_endianness, const ms_ubyte_t (&follow)[N],
                      const ms_usize_t follow_nth_match,
                      const ms_follow_direction_t follow_direction) const noexcept
            
        {
            return find_xref<T, AcceptFailedFollow, N>(
                                                       content, content_nth_match, swap_endianness, follow,
                                                       follow_nth_match, follow_direction);
        }
        
        template <typename T, bool AcceptFailedFollow>
            std::optional<T>
            find_xref(const ms_uptr_t content, const ms_usize_t content_nth_match,
                      bool swap_endianness, const std::string_view follow,
                      const ms_usize_t            follow_nth_match,
                      const ms_follow_direction_t follow_direction) const noexcept
            
        {
            return find_xref<T, AcceptFailedFollow>(
                                                    m_start, m_end, content, content_nth_match, swap_endianness, follow,
                                                    follow_nth_match, follow_direction);
        }
        
        template <typename T>
            std::optional<T> find_xref(const ms_uptr_t  content,
                                       const ms_usize_t content_nth_match,
                                       bool             swap_endianness) const noexcept
        {
            return find_xref<T>(m_start, m_end, content, content_nth_match,
                                swap_endianness);
        }
        
        template <typename T, bool AcceptFailedFollow, ms_usize_t N>
            std::optional<T>
            find_xref_at(const ms_uptr_t address, const ms_usize_t nth_match,
                         bool swap_endianness, const ms_ubyte_t (&follow)[N],
                         const ms_usize_t            follow_nth_match,
                         const ms_follow_direction_t follow_direction) const noexcept
            
        {
            return find_xref_at<T, AcceptFailedFollow, N>(
                                                          m_start, m_end, address, nth_match, swap_endianness, follow,
                                                          follow_nth_match, follow_direction);
        }
        
        template <typename T, bool AcceptFailedFollow>
            std::optional<T>
            find_xref_at(const ms_uptr_t address, const ms_usize_t nth_match,
                         bool swap_endianness, const std::string_view follow,
                         const ms_usize_t            follow_nth_match,
                         const ms_follow_direction_t follow_direction) const noexcept
            
        {
            return find_xref_at<T, AcceptFailedFollow>(
                                                       m_start, m_end, address, nth_match, swap_endianness, follow,
                                                       follow_nth_match, follow_direction);
        }
        
        template <typename T>
            std::optional<T> find_xref_at(const ms_uptr_t  address,
                                          const ms_usize_t nth_match,
                                          bool swap_endianness) const noexcept
        {
            return find_xref_at<T>(m_start, m_end, address, nth_match,
                                   swap_endianness);
        }
        
        template <typename T, bool AcceptFailedFollow, ms_usize_t N>
            std::optional<T>
            find_string(const std::string_view string, const ms_usize_t nth_match,
                        const ms_ubyte_t (&follow)[N],
                        const ms_usize_t            follow_nth_match,
                        const ms_follow_direction_t follow_direction) const noexcept
        {
            return find_string<T, AcceptFailedFollow, N>(
                                                         m_start, m_end, string, nth_match, follow, follow_nth_match,
                                                         follow_direction);
        }
        
        template <typename T, bool AcceptFailedFollow>
            std::optional<T>
            find_string(const std::string_view string, const ms_usize_t nth_match,
                        const std::string_view      follow,
                        const ms_usize_t            follow_nth_match,
                        const ms_follow_direction_t follow_direction) const noexcept
        {
            return find_string<T, AcceptFailedFollow>(
                                                      m_start, m_end, string, nth_match, follow, follow_nth_match,
                                                      follow_direction);
        }
        
        template <typename T>
            std::optional<T>
            find_string(const std::string_view string,
                        const ms_usize_t nth_match = MEMSCAN_FIRST_MATCH) const noexcept
        {
            return find_string<T>(m_start, m_end, string, nth_match);
        }
        
        /* helpers */
        
        const auto get_start() const noexcept { return m_start; }
        const auto get_end() const noexcept { return m_end; }
        
        private:
        ms_uptr_t m_start;
        ms_uptr_t m_end;
    };
} // namespace memscan
#endif