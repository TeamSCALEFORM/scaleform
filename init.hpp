#pragma once

#define WIN32_LEAN_AND_MEAN
#include "memscan/src/memscan/memscan.h"

#include "sdk.hpp"

#ifdef WIN32
#include <windows.h>
#endif

#include <iomanip>
#include <cstdlib>
#include <type_traits>

#define LOG(...) (void)(printf("TeamScaleform/ "), printf(__VA_ARGS__))

#ifdef _DEBUG
#define DEBUG(...) (void)(printf("TeamScaleform/ DEBUG: "), printf(__VA_ARGS__))
#else
#define DEBUG(...)
#endif

namespace tsf 
{
    struct panorama_t;
    struct cvar_t;
    struct cvars_t;
}

struct context_t {
    context_t() = default;
    
    memscan::mapped_region_t client;
    memscan::mapped_region_t engine;
    memscan::mapped_region_t panorama;
    
    struct interfaces_t 
    {
        tsf::panorama_t *panorama;
        tsf::cvars_t *cvars;
    } i;
    struct functions_t
    {
        char *(CDECL* compare_extension)(const char *lhs, const char *rhs);
    } f;
    struct cvars_t 
    {
        tsf::cvar_t *cl_hud_color;
        tsf::cvar_t *cl_hud_background_alpha;
        tsf::cvar_t *cl_hud_healthammo_style;
    } c;
    struct globals_t
    {
        bool scf_on;
        bool old_wp;
        bool show_rarity;
    } g;
} inline ctx;

void init();