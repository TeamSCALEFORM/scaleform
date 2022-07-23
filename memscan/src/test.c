#include "memscan/memscan.h"
#include <assert.h>
#include <stdio.h>
#include <time.h>
#include <windows.h>

BOOL WINAPI
DllMain(HINSTANCE hinstDLL,  // handle to DLL module
        DWORD     fdwReason, // reason for calling function
        LPVOID    lpReserved)   // reserved
{
    (void)hinstDLL;
    (void)lpReserved;

    if (fdwReason != DLL_PROCESS_ATTACH)
        return FALSE;

    /* open IO and console */

    AllocConsole();
    freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);

    clock_t begin = clock();

    /* current tests are temporary and not guaranteed to work outside of the
     * repository owner's machine */

    /* get guaranteed module in csgo.exe */

    ms_uptr_t client = (ms_uptr_t)GetModuleHandleA("client.dll");

    /* pattern finding */

#define MAGIC_VALUE 0x40000000
#define GLOBAL_RANGE client, client + MAGIC_VALUE

    const ms_ubyte_t* address = (const ms_ubyte_t*)"\x55\x8B\xEC";
    ms_result_t       test_1 =
        memscan_find_pattern_nfb(GLOBAL_RANGE, address, 3, MEMSCAN_FIRST_MATCH);

    if (test_1.m_status == MS_RESULT_STATUS_FOUND) {
        printf("test1: %x\n", test_1.m_address);

        /* the fact that we're here implies that the following is be guaranteed
         * to work */

        ms_result_t test_2 = memscan_find_pattern_nfs(GLOBAL_RANGE, "55 8B EC",
                                                      MEMSCAN_FIRST_MATCH);

        printf("test2: %d %x\n", test_2.m_status, test_2.m_address);

        /* assert that the second test variable has a status of found and that
         * it equals the first test variable's status as they're equivalent */

        assert(test_2.m_status == MS_RESULT_STATUS_FOUND &&
               test_1.m_address == test_2.m_address);
    }

    /* find first occurence of "8B 4D" from the first occurence of "55 8B EC"
     * without using a standard follow routine */

    ms_result_t test_3 =
        memscan_find_pattern_nfs(test_1.m_address, test_1.m_address + 0x3000,
                                 "8B 4D", MEMSCAN_FIRST_MATCH);

    if (test_3.m_status == MS_RESULT_STATUS_FOUND) {
        printf("test3: %x\n", test_3.m_address);

        ms_result_t test_4 = memscan_find_pattern_ss(
            GLOBAL_RANGE, "55 8B EC", MEMSCAN_FIRST_MATCH, "8B 4D",
            MEMSCAN_FIRST_MATCH, MS_FOLLOW_DIRECTION_FORWARDS);

        printf("test4: %d %x\n", test_4.m_status, test_4.m_address);

        assert(test_4.m_status == MS_RESULT_STATUS_FOUND &&
               test_3.m_address == test_4.m_address);

        ms_result_t test_5 = memscan_find_xref_at_nf(
            test_1.m_address, test_1.m_address + 0x3000, test_3.m_address + 2,
            MEMSCAN_FIRST_MATCH, true);

        printf("test5: %d %x\n", test_5.m_status, test_5.m_address);

        assert(test_5.m_status == MS_RESULT_STATUS_FOUND &&
               test_5.m_address == (test_3.m_address + 2) &&
               (*(ms_uptr_t*)test_5.m_address ==
                *(ms_uptr_t*)(test_3.m_address + 2)));

        printf("test5 2: %x %x\n", *(ms_uptr_t*)test_5.m_address,
               *(ms_uptr_t*)(test_3.m_address + 2));
    }

    /* resolve first reference of "NullRNG" string */

    const char NullRNG[] = "NullRNG";

    ms_result_t test_6 = memscan_find_string_nf(
        GLOBAL_RANGE, NullRNG, sizeof(NullRNG), MEMSCAN_FIRST_MATCH);

    if (test_6.m_status == MS_RESULT_STATUS_FOUND)
        printf("test6: %x %s\n", test_6.m_address,
               *(const char**)test_6.m_address);

    printf("time: %lf\n", (double)(clock() - begin) / CLOCKS_PER_SEC);

    return TRUE; // Successful DLL_PROCESS_ATTACH.
}