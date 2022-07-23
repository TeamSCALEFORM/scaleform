#include "memscan/memscan.h"
#include <assert.h>
#include <cstdio>
#include <time.h>

#undef NDEBUG
#define NDEBUG 0

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
    freopen_s(reinterpret_cast<FILE**>(stdout), "CONOUT$", "w", stdout);

    clock_t begin = clock();

    /* create range */

    /* can also take start and end in numeric form */

    memscan::mapped_region_t client(GetModuleHandleA("client.dll"));

    /* the following are just injections into the context, you can also access
     * the functions by doing memscan::mapped_region_t::* but that'll require
     * bounds */

    auto test_1 = client.find_pattern<ms_uptr_t>({0x55, 0x8B, 0xEC});

    if (test_1.has_value()) {
        printf("test1: %x\n", test_1.value());

        /* the fact that we're here implies that the following is be guaranteed
         * to work */

        auto test_2 = client.find_pattern<ms_uptr_t>("55 8B EC");

        if (test_2.has_value()) {
            printf("test2: %x\n", test_2.value());

            /* assert that the second test variable has a status of found and
             * that it equals the first test variable's status as they're
             * equivalent */

            assert(test_1.value() == test_2.value());
        }
    }

    auto test_3 = memscan::mapped_region_t::find_pattern<ms_uptr_t>(
        test_1.value(), test_1.value() + 0x3000, "8B 4D");

    if (test_3.has_value()) {
        printf("test3: %x\n", test_3.value());

        auto test_4 = client.find_pattern<ms_uptr_t, false>(
            "55 8B EC", MEMSCAN_FIRST_MATCH, "8B 4D", MEMSCAN_FIRST_MATCH,
            MS_FOLLOW_DIRECTION_FORWARDS);

        printf("test4: %x\n", test_4.value());

        assert(test_3.value() == test_4.value());

        auto test_5 = memscan::mapped_region_t::find_xref_at<ms_uptr_t>(
            test_1.value(), test_1.value() + 0x3000, test_3.value() + 2,
            MEMSCAN_FIRST_MATCH, true);

        printf("test5: %x\n", test_5.value());

        assert(test_5.value() == (test_3.value() + 2) &&
               (*reinterpret_cast<ms_uptr_t*>(test_5.value()) ==
                *reinterpret_cast<ms_uptr_t*>(test_3.value() + 2)));

        printf("test5 2: %x %x\n",
               *reinterpret_cast<ms_uptr_t*>(test_5.value()),
               *reinterpret_cast<ms_uptr_t*>(test_3.value() + 2));
    }

    /* find NulLRNG string */

    auto test_6 = client.find_string<ms_uptr_t>("NullRNG", MEMSCAN_FIRST_MATCH);

    if (test_6.has_value())
        printf("test6: %x %s\n", test_6.value(),
               *reinterpret_cast<const char**>(test_6.value()));

    printf("time: %lf\n",
           static_cast<double>(clock() - begin) / CLOCKS_PER_SEC);

    return TRUE; // Successful DLL_PROCESS_ATTACH.
}
