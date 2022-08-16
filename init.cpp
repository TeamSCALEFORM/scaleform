#include <filesystem>
#include "init.hpp"
#include "sdk.hpp"

#include "config.hpp"
#include "scaleform/scaleform.hpp"

#ifdef WIN32
#include <minhook.h>
#else
#include "funchook/include/funchook.h"
#endif

// hooks
#define prot_hook(name, type)                     \
struct name {                                 \
using fn_t = std::remove_pointer_t<type>; \
static fn_t fn;                           \
static inline fn_t* og;                   \
WIN32_LINUX_LITERAL(private:, static inline funchook_t* fh;)                    \
};                          

// decl hooks
prot_hook(level_init_pre_entity, void(FASTCALL *)(FASTCALL_ARGS, const char *));
prot_hook(level_shutdown, void(FASTCALL *)(FASTCALL_ARGS));
prot_hook(create_move, bool(FASTCALL *)(FASTCALL_ARGS, float, tsf::user_cmd_t *));
prot_hook(fire_event_intern, bool(FASTCALL *)(FASTCALL_ARGS, tsf::event_t *, bool, bool));
prot_hook(set_image_data_r8g8b8a8, bool(FASTCALL *)(FASTCALL_ARGS, const uint8_t *, uint32_t, const char *, int, int, void*, int));

// impl hooks
void level_init_pre_entity::fn(FASTCALL_ARGS, const char *map)
{
    DEBUG("LevelInitPreEntity\n");
    og(FASTCALL_CALL, map);
    return scaleform_install();
}

void level_shutdown::fn(FASTCALL_ARGS)
{
    // maybe get the retaddr of only one call. eh, this is very inexpensive so it doesn't matter
    DEBUG("LevelShutdown\n");
    og(FASTCALL_CALL);
    return scaleform_init();
}

bool create_move::fn(FASTCALL_ARGS, float input_sample_time, tsf::user_cmd_t *cmd)
{
    if (!self || !cmd || cmd->command_number == 0 || cmd->tick_count == 0 || input_sample_time == 0.F)
        return og(FASTCALL_CALL, input_sample_time, cmd);
    
    // TODO: This is not the ideal place for this...
    scaleform_tick((tsf::player_t*)self);
    
    og(FASTCALL_CALL, input_sample_time, cmd);
    return true;
}

#define DEBUG_EVENTS 0
bool fire_event_intern::fn(FASTCALL_ARGS, tsf::event_t *event, bool client, bool server)
{
    if (!event)
        return og(FASTCALL_CALL, event, client, server);
    
    const char *name = event->get_name();
#if (DEBUG_EVENTS == 1)
    DEBUG("%s\n", event->get_name());
#endif
    
    scaleform_on_event(event);
    
    bool ret = og(FASTCALL_CALL, event, client, server);
    
    // event is invalid after og
    scaleform_after_event(name);
    return ret;
}

// false - vsvg
// true - svg
#define VSVG_OR_SVG true
#define VSVG_EXT ((VSVG_OR_SVG) ? ".svg" : ".vsvg")
static const char *get_extension(const char *filename)
{
    if (ctx.f.compare_extension(filename, ".png"))
        return ".png";
    else if (ctx.f.compare_extension(filename, ".svg"))
        return ".svg";
    else if (ctx.f.compare_extension(filename, ".vsvg"))
        return VSVG_EXT;
    return nullptr; // we don't care abt. the rest
}

#define DUMP_ICONS 0
#define DUMP_FILENAMES 1
bool set_image_data_r8g8b8a8::fn(FASTCALL_ARGS, const uint8_t *data, uint32_t len, const char *filename, int w, int h, void* arg1, int arg2)
{
    if (!ctx.g.scf_on || !filename)
        return og(FASTCALL_CALL, data, len, filename, w, h, arg1, arg2);
    
#if (DUMP_FILENAMES == 1)
    DEBUG("File: %s\n", filename);
#endif
    
    const char *extension = get_extension(filename);
    // Data is actually the file itself, it's not first turned into RGBA
    // data.
    if (!data || !len || !extension)
        return og(FASTCALL_CALL, data, len, filename, w, h, arg1, arg2);
    
    //DEBUG("extension: %s arg1: %d arg2: %d\n", extension, arg1, arg2);
    constexpr const char eq_prefix[] = WIN32_LINUX_LITERAL("materials\\panorama\\images\\icons\\equipment\\", "materials/panorama/images/icons/equipment/");
    bool equipment = (strstr(filename, eq_prefix) == filename) && !strcmp(extension, VSVG_EXT);
    
    const uint8_t *replacement_data;
    size_t replacement_size;
    int replacement_w, replacement_h;
    if (scaleform_try_votepanel_replacement_icons(filename, replacement_data, replacement_size, replacement_w, replacement_h)) 
    {
        arg2 = 6;
        return og(FASTCALL_CALL, replacement_data, replacement_size, filename, replacement_w, replacement_h, arg1, arg2);
    } else if (equipment)
    {
        // name
        char copy[256];
        const char *start_ptr = &filename[sizeof(eq_prefix) - 1];
        const char *end_ptr = strstr(start_ptr, ".vsvg");
        size_t size = (size_t)end_ptr - (size_t)start_ptr;
        DEBUG("%d\n", size);
        strncpy(copy, start_ptr, size); 
        copy[size] = 0;
        DEBUG("%s\n", copy);
        
#if (DUMP_ICONS == 1)
        scaleform_dump_icons(copy, data, len, extension);
#endif
        
        if (scaleform_get_replacement_icon(copy, replacement_data, replacement_size, replacement_w, replacement_h))
        {
            arg2 = 6;
            DEBUG("!! replaced %s\n", copy);
            return og(FASTCALL_CALL, replacement_data, replacement_size, filename, replacement_w, replacement_h, arg1, arg2);
        } else
            DEBUG("!! didn't replace %s\n", copy);
    }
    
    return og(FASTCALL_CALL, data, len, filename, w, h, arg1, arg2);
}

// setup hooks
template <typename T>
static void hook_impl(std::optional<void *> &&target) 
{
#ifdef WIN32
    if (target.has_value() &&
        (MH_CreateHook(target.value(), (void*)(&T::fn), (void**)(&T::og)) == MH_OK))
        LOG("Succesful hook at %p\n", target.value());
#else
    if (target.has_value()) 
    {
        T::fh = funchook_create();
        
        T::og = (decltype(T::og))(target.value());
        
        if (T::fh && (funchook_prepare(T::fh, (void**)(&T::og), (void*)(T::fn)) == 0) && (funchook_install(T::fh, 0) == 0)) 
            LOG("Succesful hook at %p\n", target.value());
    }
#endif
    else (void)(LOG("Failed hooking (address nil)\n"), exit(0));
}
#define hook(a, ...) hook_impl<a>(__VA_ARGS__)

static void hooks_init()
{
#ifdef WIN32
    MH_Initialize();
    
    hook(level_init_pre_entity, ctx.client.find_string<void *, false>("(mapname)", MEMSCAN_FIRST_MATCH, {0x55, 0x8b, 0xec}, MEMSCAN_FIRST_MATCH, MS_FOLLOW_DIRECTION_BACKWARDS));
    hook(level_shutdown, ctx.client.find_string<void *, false>("(mapname)", MEMSCAN_FIRST_MATCH, {0x55, 0x8b, 0xec}, 1, MS_FOLLOW_DIRECTION_FORWARDS));
    hook(create_move, ctx.client.find_pattern<void *>("55 8B EC 56 8B F1 57 8B 7D 0C 8B 8E", MEMSCAN_FIRST_MATCH));
    hook(fire_event_intern, ctx.engine.find_string<void *, false>("FireEvent: event '%s' not registered.\n", MEMSCAN_FIRST_MATCH, {0x55, 0x8b, 0xec}, MEMSCAN_FIRST_MATCH, MS_FOLLOW_DIRECTION_BACKWARDS));
    hook(set_image_data_r8g8b8a8, ctx.panorama.find_string<void *, false>("CImageData::SetImageDataR8G8B8A8", MEMSCAN_FIRST_MATCH, {0x55, 0x8b, 0xec}, MEMSCAN_FIRST_MATCH, MS_FOLLOW_DIRECTION_BACKWARDS));
    
    MH_EnableHook(MH_ALL_HOOKS);
#else
    hook(level_init_pre_entity, ctx.client.find_pattern<void *>("55 48 89 E5 53 48 89 F3 48 83 EC 08 C6 05 CC CC CC CC CC", MEMSCAN_FIRST_MATCH));
    hook(level_shutdown, ctx.client.find_pattern<void *>("55 48 89 E5 41 54 49 89 FC 53 48 8B 1D CC CC CC CC 48 89 DF", MEMSCAN_FIRST_MATCH));
    hook(create_move, ctx.client.find_pattern<void *>("55 0F 28 C8 48 89 E5 41 54 49 89 F4", MEMSCAN_FIRST_MATCH));
    hook(fire_event_intern, rel_to_abs<void*>(ctx.engine.find_pattern<uintptr_t>("E9 CC CC CC CC 90 66 66 66 2E 0F 1F 84 CC CC CC CC CC 55 B9 CC CC CC CC", MEMSCAN_FIRST_MATCH).value() + 1));
    hook(set_image_data_r8g8b8a8, rel_to_abs<void*>(ctx.panorama.find_pattern<uintptr_t>("E8 CC CC CC CC 84 C0 41 88 44 24 CC", MEMSCAN_FIRST_MATCH).value() + 1));
#endif
}

// setup ctx
static void ctx_init()
{
#ifdef __linux__
    void* panorama_vk = dlopen("panorama_client.so", RTLD_LAZY | RTLD_NOLOAD);
    if (panorama_vk) 
    {
        ctx.g.is_vulkan = true;
        dlclose(panorama_vk);
    }
#endif
    
    using namespace memscan;
    ctx.client   = mapped_region_t(GET_MODULE_HANDLE(CLIENT_DLL));
    LOG("client:   %x %x\n", ctx.client.get_start(), ctx.client.get_end());
    ctx.engine   = mapped_region_t(GET_MODULE_HANDLE(ENGINE_DLL));
    LOG("engine:   %x %x\n", ctx.engine.get_start(), ctx.engine.get_end());
    ctx.panorama = mapped_region_t(GET_MODULE_HANDLE(PANORAMA_DLL));
    LOG("panorama: %x %x\n", ctx.panorama.get_start(), ctx.panorama.get_end());
    
#ifdef WIN32
    auto panorama = ctx.panorama.find_pattern<uintptr_t>("B9 CC CC CC CC 56 FF 50 40 8B", MEMSCAN_FIRST_MATCH);
    if (panorama.has_value())
        ctx.i.panorama = *(tsf::panorama_t **)(panorama.value() + 1);
#else
    // there is a different panorama lib for vulkan
    auto panorama_gl = ctx.panorama.find_pattern<uintptr_t>("48 8B 05 CC CC CC CC 48 8D 1D CC CC CC CC", MEMSCAN_FIRST_MATCH);
    
    if (panorama_gl.has_value())
        ctx.i.panorama = **rel_to_abs<tsf::panorama_t ***>(panorama_gl.value() + 3);
#endif
    else (void)(LOG("Failed init (panorama interface nil)\n"), exit(0));
    
#ifdef WIN32
    auto cvars = ctx.engine.find_string<uintptr_t, false>("sv_skyname", 3, {0x8b, 0x0d}, MEMSCAN_FIRST_MATCH, MS_FOLLOW_DIRECTION_BACKWARDS);
    if (cvars.has_value())
        ctx.i.cvars = **(tsf::cvars_t ***)(cvars.value() + 2);
#else
    auto cvars = ctx.engine.find_pattern<uintptr_t>("48 8B 05 CC CC CC CC C6 05 CC CC CC CC CC 48 8D 35 CC CC CC CC", MEMSCAN_FIRST_MATCH);
    if (cvars.has_value())
        ctx.i.cvars = **rel_to_abs<tsf::cvars_t ***>(cvars.value() + 3);
#endif
    else (void)(LOG("Failed init (cvars interface nil)\n"), exit(0));
    
#ifdef WIN32
    auto compare_extension = ctx.panorama.find_pattern<decltype(ctx.f.compare_extension)>("55 8B EC 53 57 8B 7D 08 85", MEMSCAN_FIRST_MATCH);
    if (compare_extension.has_value())
        ctx.f.compare_extension = compare_extension.value();
#else
    auto compare_extension_gl = ctx.panorama.find_pattern<uintptr_t>("E8 CC CC CC CC 80 78 03 7B", MEMSCAN_FIRST_MATCH);
    
    if (compare_extension_gl.has_value())
        ctx.f.compare_extension = rel_to_abs<decltype(ctx.f.compare_extension)>(compare_extension_gl.value() + 1);
#endif
    else (void)(LOG("Failed init (compare_extension function nil)\n"), exit(0));
    
    ctx.c.cl_hud_color            = ctx.i.cvars->get_var("cl_hud_color");
    ctx.c.cl_hud_background_alpha = ctx.i.cvars->get_var("cl_hud_background_alpha");
    ctx.c.cl_hud_healthammo_style = ctx.i.cvars->get_var("cl_hud_healthammo_style");
    
    ctx.g.scf_on      = SCALEFORM_DEFAULT;
    ctx.g.old_wp      = SCALEFORM_WINPANEL_DEFAULT;
    ctx.g.show_rarity = SCALEFORM_WEAPON_SELECTION_RARITY_DEFAULT;
    
#if (DUMP_ICONS == 1)
    std::filesystem::path folder_path = std::filesystem::current_path() / "pano_icos";
    if (!std::filesystem::exists(folder_path))
        std::filesystem::create_directory(folder_path);
#endif
}

void init()
{
    ctx_init();
    scaleform_init();
    hooks_init();
}