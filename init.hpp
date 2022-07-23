#pragma once

#define WIN32_LEAN_AND_MEAN
#include "memscan/src/memscan/memscan.h"
#include <windows.h>
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
    
    struct interfaces_t {
        tsf::panorama_t *panorama;
        tsf::cvars_t *cvars;
    } i;
    struct cvars_t {
        tsf::cvar_t *cl_hud_color;
        tsf::cvar_t *cl_hud_background_alpha;
        tsf::cvar_t *cl_hud_healthammo_style;
    } c;
    struct globals_t {
        bool scf_on;
        bool old_wp;
    } g;
} inline ctx;

void init();