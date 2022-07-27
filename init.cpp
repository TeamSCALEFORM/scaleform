#include <filesystem>
#include "init.hpp"
#include "sdk.hpp"

#include "config.hpp"
#include "scaleform/scaleform.hpp"

#include <minhook.h>

// hooks
#define prot_hook(name, type)                     \
struct name {                                 \
using fn_t = std::remove_pointer_t<type>; \
static fn_t fn;                           \
static inline fn_t* og;                   \
};                          

// decl hooks
prot_hook(level_init_pre_entity, void(__stdcall *)(const char *));
prot_hook(level_shutdown, void(__fastcall *)(void *, void *));
prot_hook(create_move, bool(__fastcall *)(tsf::player_t *, void *, float, tsf::user_cmd_t *));
prot_hook(fire_event_intern, bool(__fastcall *)(void *, void *, tsf::event_t *, bool, bool));
prot_hook(killfeed_update, void(__fastcall *)(void *,void *, tsf::event_t *));
prot_hook(weapon_selection_update, void(__fastcall *)(void *,void *, tsf::event_t *));
prot_hook(set_image_data_r8g8b8a8, bool(__fastcall *)(void *, void *, const uint8_t *, size_t, const char *, int, int, int, int));

// impl hooks
void level_init_pre_entity::fn(const char *map)
{
    DEBUG("LevelInitPreEntity\n");
    og(map);
    return scaleform_install();
}

void level_shutdown::fn(void *self, void *edx)
{
    // maybe get the retaddr of only one call. eh, this is very inexpensive so it doesn't matter
    DEBUG("LevelShutdown\n");
    og(self, edx);
    return scaleform_init();
}

bool create_move::fn(tsf::player_t *self, void *edx, float input_sample_time, tsf::user_cmd_t *cmd)
{
    if (!self || !cmd || cmd->get_command_number() == 0 || cmd->get_tick_count() == 0 || input_sample_time == 0.F)
        return og(self, edx, input_sample_time, cmd);
    
    // TODO: This is not the ideal place for this...
    scaleform_tick(self);
    
    og(self, edx, input_sample_time, cmd);
    return true;
}

#define DEBUG_EVENTS 0
bool fire_event_intern::fn(void *self, void *edx, tsf::event_t *event, bool client, bool server)
{
    if (!event)
        return og(self, edx, event, client, server);
    
    const char *name = event->get_name();
#if (DEBUG_EVENTS == 1)
    DEBUG("%s\n", event->get_name());
#endif
    
    scaleform_on_event(event);
    
    bool ret = og(self, edx, event, client, server);
    
    // event is invalid after og
    scaleform_after_event(name);
    return ret;
}

// NOTE: can probably be done in scaleform_on_event
// I wrote this a while ago and I don't want to test as of now
// so I'll either get back to this part later or maybe a nice
// contributor can do the testing :)
void killfeed_update::fn(void *self, void *edx, tsf::event_t *event)
{
    if (!event)
        return og(self, edx, event);
    
    og(self, edx, event);
    
    return scaleform_on_death();
}

// NOTE: ditto (weaponhud_selection)
void weapon_selection_update::fn(void *self, void *edx, tsf::event_t *event)
{
    if (!event)
        return og(self, edx, event);
    
    og(self, edx, event);
    
    return scaleform_on_weapon_event();
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
#define DUMP_FILENAMES 0
bool set_image_data_r8g8b8a8::fn(void *self, void *edx, const uint8_t *data, size_t len, const char *filename, int w, int h, int arg1, int arg2)
{
    if (!filename)
        return og(self, edx, data, len, filename, w, h, arg1, arg2);
    
    
#if (DUMP_FILENAMES == 1)
    DEBUG("File: %s\n", filename);
#endif
    
    const char *extension = get_extension(filename);
    // Data is actually the file itself, it's not first turned into RGBA
    // data.
    if (!data || !len || !extension)
        return og(self, edx, data, len, filename, w, h, arg1, arg2);
    
    //DEBUG("extension: %s arg1: %d arg2: %d\n", extension, arg1, arg2);
    constexpr const char eq_prefix[] = "materials\\panorama\\images\\icons\\equipment\\";
    bool equipment = (strstr(filename, eq_prefix) == filename) && !strcmp(extension, VSVG_EXT);
    
    if (equipment)
    {
        // gonna be written to by reference
        const uint8_t *replacement_data;
        size_t replacement_size;
        int replacement_w, replacement_h;
        
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
            arg2 = 2;
            DEBUG("!! replaced %s\n", copy);
            return og(self, edx, replacement_data, replacement_size, filename, replacement_w, replacement_h, arg1, arg2);
        } else {
            DEBUG("!! didn't replace %s\n", copy);
        }
    }
    
    return og(self, edx, data, len, filename, w, h, arg1, arg2);
}

// setup hooks
template <typename T>
static void hook_impl(std::optional<void *> &&target) {
    if (target.has_value() &&
        (MH_CreateHook(target.value(), (void*)(&T::fn), (void**)(&T::og)) == MH_OK))
        LOG("Succesful hook at %p\n", target.value());
    else (void)(LOG("Failed hooking (address nil)\n"), exit(0));
}
#define hook(a, ...) hook_impl<a>(__VA_ARGS__)

static void hooks_init()
{
    MH_Initialize();
    hook(level_init_pre_entity, ctx.client.find_string<void *, false>("(mapname)", MEMSCAN_FIRST_MATCH, {0x55, 0x8b, 0xec}, MEMSCAN_FIRST_MATCH, MS_FOLLOW_DIRECTION_BACKWARDS));
    hook(level_shutdown, ctx.client.find_string<void *, false>("(mapname)", MEMSCAN_FIRST_MATCH, {0x55, 0x8b, 0xec}, 1, MS_FOLLOW_DIRECTION_FORWARDS));
    hook(create_move, ctx.client.find_pattern<void *>("55 8B EC 56 8B F1 57 8B 7D 0C 8B 8E", MEMSCAN_FIRST_MATCH));
    hook(fire_event_intern, ctx.engine.find_string<void *, false>("FireEvent: event '%s' not registered.\n", MEMSCAN_FIRST_MATCH, {0x55, 0x8b, 0xec}, MEMSCAN_FIRST_MATCH, MS_FOLLOW_DIRECTION_BACKWARDS));
    hook(killfeed_update, ctx.client.find_string<void *, false>("realtime_passthrough", MEMSCAN_FIRST_MATCH, {0x55, 0x8b, 0xec}, MEMSCAN_FIRST_MATCH, MS_FOLLOW_DIRECTION_BACKWARDS));
    hook(weapon_selection_update, ctx.client.find_string<void *, false>("ggprogressive_player_levelup", 3, {0x55, 0x8b, 0xec}, MEMSCAN_FIRST_MATCH, MS_FOLLOW_DIRECTION_BACKWARDS));
    hook(set_image_data_r8g8b8a8, ctx.panorama.find_string<void *, false>("CImageData::SetImageDataR8G8B8A8", MEMSCAN_FIRST_MATCH, {0x55, 0x8b, 0xec}, MEMSCAN_FIRST_MATCH, MS_FOLLOW_DIRECTION_BACKWARDS));
    MH_EnableHook(MH_ALL_HOOKS);
}

// setup ctx
static void ctx_init()
{
    using namespace memscan;
    ctx.client   = mapped_region_t(GetModuleHandleA("client.dll"));
    LOG("client:   %x %x\n", ctx.client.get_start(), ctx.client.get_end());
    ctx.engine   = mapped_region_t(GetModuleHandleA("engine.dll"));
    LOG("engine:   %x %x\n", ctx.engine.get_start(), ctx.engine.get_end());
    ctx.panorama = mapped_region_t(GetModuleHandleA("panorama.dll"));
    LOG("panorama: %x %x\n", ctx.panorama.get_start(), ctx.panorama.get_end());
    
    auto panorama = ctx.panorama.find_pattern<uintptr_t>("B9 CC CC CC CC 56 FF 50 40 8B", MEMSCAN_FIRST_MATCH);
    if (panorama.has_value())
        ctx.i.panorama = *(tsf::panorama_t **)(panorama.value() + 1);
    else (void)(LOG("Failed init (panorama interface nil)\n"), exit(0));
    
    auto cvars = ctx.engine.find_string<uintptr_t, false>("sv_skyname", 3, {0x8b, 0x0d}, MEMSCAN_FIRST_MATCH, MS_FOLLOW_DIRECTION_BACKWARDS);
    if (cvars.has_value())
        ctx.i.cvars = **(tsf::cvars_t ***)(cvars.value() + 2);
    else (void)(LOG("Failed init (cvars interface nil)\n"), exit(0));
    
    auto compare_extension =  ctx.panorama.find_pattern<decltype(ctx.f.compare_extension)>("55 8B EC 53 57 8B 7D 08 85", MEMSCAN_FIRST_MATCH);
    if (compare_extension.has_value())
        ctx.f.compare_extension = compare_extension.value();
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

void ::init()
{
    ctx_init();
    scaleform_init();
    hooks_init();
}