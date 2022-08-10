#include <fstream>
#include <filesystem>
#include <string>

#ifdef WIN32
#include <minmax.h>
#else
#include <algorithm>
#endif

#include "scaleform.hpp"
#include "../init.hpp"
#include "../sdk.hpp"
#include "../config.hpp"

#include "sanitary_macros.hpp"

JAVASCRIPT base =
#include "base.js"
;

JAVASCRIPT alerts =
#include "alerts.js"
;

JAVASCRIPT teamcount_avatar =
#include "teamcount_avatar.js"
;

// ${buyZone} - percentage
#define BUYZONE "${buyZone}"
JAVASCRIPT buyzone =
#include "buyzone.js"
;

// ${isShort} - is healthammo style short
#define HEALTHAMMO_STYLE "${isShort}"
JAVASCRIPT healthammo =
#include "healthammo.js"
;

JAVASCRIPT deathnotices =
#include "deathnotices.js"
;

JAVASCRIPT spectating =
#include "spectating.js"
;

JAVASCRIPT weapon_select =
#include "weapon_select.js"
;

// ${isCt} - whether winner team is CT
// ${isT} - whether winner team is T
// ${pendingMvp} - there's a mvp for the round
// ${is2013} - is 2013 winpanel or post 2013
#define IS_CT "${isCt}"
#define IS_T "${isT}"
#define PENDING_MVP "${pendingMvp}"
#define IS_2013 "${is2013}"
JAVASCRIPT winpanel =
#include "winpanel.js"
;

// ${radarColor} - radar hex
// ${dashboardLabelColor} - dashboard label hex
#define RADAR_COLOR "${radarColor}"
#define DASHBOARD_LABEL_COLOR "${dashboardLabelColor}"
JAVASCRIPT color = 
#include "color.js"
;

// ${alpha} - alpha float
#define ALPHA "${alpha}"
JAVASCRIPT alpha =
#include "alpha.js"
;
#define MAX_ALPHA 1.F

// Old colors
// Note: for dashboard label we just append 'B2' (70% opac)
// for radar elements we just add '19' (25% opac)
HEX_COLOR colors[11] = 
{
    "#F5FFC0", // Classic
    "#FFFFFF", // White
    "#C4ECFE", // Light Blue
    "#6E9CFB", // Dark Blue
    "#F294FF", // Purple
    "#FF6057", // Red
    "#FFA557", // Orange
    "#FEFD55", // Yellow
    "#78FF51", // Green
    "#57FFBD", // Pale Green/Aqua
    "#FFADC4"  // Pink
};

#define kRadarColor 0
#define kDashColor 1
static std::string get_color(int n, int color_type)
{
    if (color_type == kRadarColor)
        return std::string(colors[n]) + "19";
    else if (color_type == kDashColor)
        return std::string(colors[n]) + "B2";
    else return std::string(colors[n]);
};

// utilities

static void replace_str(std::string &s, const std::string& search, const std::string &replace ) {
	for (size_t pos = 0;;pos += replace.length()) {
		// Locate the substring to replace
		pos = s.find(search, pos);
		if (pos == std::string::npos)
			break;
		// Replace by erasing and inserting
		s.erase(pos, search.length());
		s.insert(pos, replace);
	}
}

static tsf::ui_panel_t *get_panel(const char *id)
{
    tsf::ui_engine_t *engine = ctx.i.panorama->access_ui_engine();
    if (!engine)
        return nullptr;
    
    tsf::ui_panel_t *parent = engine->get_last_dispatched_event_target_panel();
    if (!parent)
        return nullptr;
    
    tsf::ui_panel_t *itr = parent;
    while (itr && engine->is_valid_panel_pointer(itr)) {
        if (!strcmp(itr->get_id(), id))
            return itr;
        
        itr = itr->get_parent();
    }
    
    return nullptr;
}

// internal

void scaleform_init()
{
    scf.root = scf.weap_sel = scf.weap_pan_bg = nullptr;
    scf.inited = false;
    scf.old_color = scf.old_healthammo_style = -1;
    scf.old_alpha = -1.f;
    scf.old_in_buyzone = -1;
    scf.pending_mvp = false;
    scf.old_weap_rows_count = 0;
}

static void scaleform_teamcount_avatar()
{
    tsf::ui_engine_t *engine = ctx.i.panorama->access_ui_engine();
    if (!engine)
        return LOG("Failed Scaleform Team Count event (ui engine)\n");
    
    DEBUG("Teamcount being edited!\n");
    engine->run_script(scf.root, teamcount_avatar, CSGO_HUD_SCHEMA);
}

static void scaleform_weapon_selection()
{
    tsf::ui_engine_t *engine = ctx.i.panorama->access_ui_engine();
    if (!engine)
        return LOG("Failed Scaleform Weapon Selection event (ui engine)\n");
    
    DEBUG("Weapon selection being edited!\n");
    engine->run_script(scf.root, weapon_select, CSGO_HUD_SCHEMA);
}

static void scaleform_spec()
{
    tsf::ui_engine_t *engine = ctx.i.panorama->access_ui_engine();
    if (!engine)
        return LOG("Failed Scaleform Spec event (ui engine)\n");
    
    DEBUG("Spec being edited!\n");
    engine->run_script(scf.root, spectating, CSGO_HUD_SCHEMA);
}

void scaleform_install()
{
    if (!ctx.g.scf_on || scf.inited)
        return;
    
    if (scf.root = get_panel("CSGOHud"); !scf.root) {
        // cannot gracefully recover
        LOG("Failed Scaleform install (root panel)\n");
        return;
    }
    
    DEBUG("scf.root = %p\n", scf.root);
    
    if (tsf::ui_panel_t *parent = scf.root->find_child_traverse("HudWeaponPanel"); parent)
    {
        if (scf.weap_pan_bg = parent->find_child_traverse("WeaponPanelBottomBG"); !scf.weap_pan_bg)
        {
            return LOG("Failed Scaleform install (weap panel bg)\n");
        }
    } else return LOG("Failed Scaleform install (weap panel)\n");
    
    
    if (scf.weap_sel = scf.root->find_child_traverse("HudWeaponSelection"); !scf.weap_sel)
    {
        return LOG("Failed Scaleform install (weap sel)\n");
    }
    
    DEBUG("scf.weap_pan_bg = %p\n", scf.weap_pan_bg);
    DEBUG("scf.weap_sel = %p\n", scf.weap_sel);
    
    tsf::ui_engine_t *engine = ctx.i.panorama->access_ui_engine();
    if (!engine)
        return LOG("Failed Scaleform install (ui engine)\n");
    
    // install base modifications
    engine->run_script(scf.root, base, CSGO_HUD_SCHEMA);
    
    // alerts
    engine->run_script(scf.root, alerts, CSGO_HUD_SCHEMA);
    
    // anticipate events
    scaleform_teamcount_avatar();
    scaleform_weapon_selection();
    scaleform_spec();
    
    scf.inited = true;
    LOG("Scaleform installed!\n");
}

void scaleform_tick(tsf::player_t *local)
{
    static const Uint8 *state = SDL_GetKeyboardState(NULL);

    // listen to user commands
    if (GETASYNCKEYSTATE(SCALEFORM_TOGGLE_KEY) & 1)
    {
        ctx.g.scf_on = !ctx.g.scf_on;
        LOG("Toggled Scaleform %s\n", (ctx.g.scf_on ? "on" : "off"));
    } else if (GETASYNCKEYSTATE(SCALEFORM_WINPANEL_TOGGLE_KEY) & 1)
    {
        ctx.g.old_wp = !ctx.g.old_wp;
        LOG("Toggled Scaleform winpanel to %s\n", (ctx.g.old_wp ? "old" : "new"));
    } else if (GETASYNCKEYSTATE(SCALEFORM_WEAPON_SELECTION_RARITY_TOGGLE_KEY) & 1)
    {
        ctx.g.show_rarity = !ctx.g.show_rarity;
        LOG("Toggled Scaleform Weapon Selection Rarity to %s\n", (ctx.g.show_rarity ? "on" : "off"));
    }
    
    tsf::ui_engine_t *engine = ctx.i.panorama->access_ui_engine();
    if (!engine)
        return;
    
    // could also be potential recovery from (very unlikely to impossible)
    // fail in levelinit
    if (!scf.inited && ctx.g.scf_on)
    {
        scaleform_install();
        return;
    } else if (!scf.inited || !ctx.g.scf_on) 
        return;
    
    if (GETASYNCKEYSTATE(SCALEFORM_JAVASCRIPT_LOADER_KEY) & 1)
    {
        std::filesystem::path js_path = std::filesystem::current_path() / "base.js";
        if (std::filesystem::exists(js_path))
        {
            std::ifstream read(js_path);
            std::string js((std::istreambuf_iterator<char>(read)), std::istreambuf_iterator<char>());
            engine->run_script(scf.root, js.c_str(), CSGO_HUD_SCHEMA);
            LOG("Loaded JavaScript!\n");
        }
        else 
        {
            LOG("Cannot find %s!\n", js_path.string().c_str());
        }
    }
    
    // TODO: other way around, fully reinitialzie schema on toggle off
    
    // tick events
    
    if (scf.weap_pan_bg) {
        // make always visible (needs to be done in C++ for performance)
        scf.weap_pan_bg->set_visible(true);
    }
    
    UPDATING_VAR(scf.old_color, n, std::min((int)(std::size(colors) - 1), ctx.c.cl_hud_color->get_int()),
                 {
                     DEBUG("Changed hud color!\n");
                     std::string js = std::string(color);
                     replace_str(js, RADAR_COLOR, get_color(n, kRadarColor));
                     replace_str(js, DASHBOARD_LABEL_COLOR, get_color(n, kDashColor));
                     engine->run_script(scf.root, js.c_str(), CSGO_HUD_SCHEMA);
                 });
    
    UPDATING_VAR(scf.old_alpha, n, std::min(MAX_ALPHA, ctx.c.cl_hud_background_alpha->get_float()),
                 {
                     DEBUG("Changed hud alpha!\n");
                     std::string js = std::string(alpha);
                     char buf[16];
                     sprintf(buf, "%.2f", n);
                     replace_str(js, ALPHA, buf);
                     engine->run_script(scf.root, js.c_str(), CSGO_HUD_SCHEMA);
                 });
    
    UPDATING_VAR(scf.old_healthammo_style, n, ctx.c.cl_hud_healthammo_style->get_int(),
                 {
                     DEBUG("Changed hud healthammo style!\n");
                     std::string js = std::string(healthammo);
                     replace_str(js, HEALTHAMMO_STYLE, (n == 0 ? "true" : "false"));
                     engine->run_script(scf.root, js.c_str(), CSGO_HUD_SCHEMA);
                 });
    
    UPDATING_VAR(scf.old_in_buyzone, n, local->in_buyzone(),
                 {
                     DEBUG("Changed buyzone state!\n");
                     std::string js = std::string(buyzone);
                     replace_str(js, BUYZONE, n == 1 ? "100%" : "0%");
                     engine->run_script(scf.root, js.c_str(), CSGO_HUD_SCHEMA);
                 });
    
    // sorry for the very bad code
    // NOTE(para): it's so bad that i felt the need to clarify
    // for some reason valve really doesn't like this being stored on the
    // stack.
    // see here too 55 8B EC 83 3D ? ? ? ? ? 8B 15 ? ? ? ? 56 8B F1 C7 05
    auto vec = (tsf::utl_vector_t<tsf::ui_panel_t *> *)malloc(24); 
    memset(vec, 0, 24);
    scf.weap_sel->find_children_with_class_traverse("weapon-row", vec);
    int count = vec->size;
    free(vec);
    
    UPDATING_VAR(scf.old_weap_rows_count, n, count, 
                 {
                     scaleform_weapon_selection();
                 });
}

static void scaleform_winpanel(int team)
{
    tsf::ui_engine_t *engine = ctx.i.panorama->access_ui_engine();
    if (!engine)
        return LOG("Failed Scaleform Win Panel event (ui engine)\n");
    
    DEBUG("Winpanel being edited!\n");
    std::string js = std::string(winpanel);
    replace_str(js, IS_CT, (team == 3) ? "true" : "false");
    replace_str(js, IS_T, (team == 2) ? "true" : "false");
    replace_str(js, PENDING_MVP, scf.pending_mvp ? "true" : "false");
    replace_str(js, IS_2013, ctx.g.old_wp ? "true" : "false");
    engine->run_script(scf.root, js.c_str(), CSGO_HUD_SCHEMA);
    
    scf.pending_mvp = false;
}

void scaleform_on_event(tsf::event_t *event)
{
    if (!scf.inited)
        return;
    
    if (!strcmp(event->get_name(), "round_mvp"))
        scf.pending_mvp = true; // flag mvp
    // NOTE(para): relying on item_equip for certainty isn't great but it's
    // not going to be the downfall of anything.
    else if (!strcmp(event->get_name(), "round_start") || !strcmp(event->get_name(), "item_equip"))
        scaleform_weapon_selection();
    else if (!strcmp(event->get_name(), "round_end"))
        scaleform_winpanel(event->get_int("winner"));
}

void scaleform_after_event(const char *name)
{
    if (!scf.inited)
        return;
    
    if (!strcmp(name, "bot_takeover") || !strcmp(name, "switch_team") ||
        !strcmp(name, "round_start")) 
    {
        scaleform_teamcount_avatar();
        scaleform_weapon_selection();
    } else if (!strcmp(name, "spec_target_updated") || !strcmp(name, "spec_mode_updated") || !strcmp(name, "item_equip"))
        scaleform_spec();
}

void scaleform_on_death()
{
    if (!scf.inited)
        return;
    
    tsf::ui_engine_t *engine = ctx.i.panorama->access_ui_engine();
    if (!engine)
        return LOG("Failed Scaleform Death Notice event (ui engine)\n");
    
    DEBUG("Deathnotices being edited!\n");
    engine->run_script(scf.root, deathnotices, CSGO_HUD_SCHEMA);
}

constexpr static uint64_t hash_data(const char *data, size_t len) 
{
    uint64_t hash = 0x543C730D;
    
    for (size_t i = 0; i < len; ++i) {
        hash ^= data[i];
        hash *= 0x1000931;
    }
    
    return hash;
}

template<auto V>
struct ct_data
{
    constexpr static auto value = V;
};

void scaleform_dump_icons(const char *imgname, const uint8_t *data, size_t len, const char *extension)
{
    std::filesystem::path folder_path = std::filesystem::current_path() / "pano_icos";
    
    std::string name = std::string("icon_") + imgname + extension;
    
    std::filesystem::path rgba_path = folder_path / name;
    
    std::ofstream stream(rgba_path, std::ios::binary | std::ios::out);
    stream.write((const char *)data, len);
    stream.close();
    DEBUG("Dumped icon %s!\n", name.c_str());
}


// warning: A LOT OF DATA!
#include "data.hpp"
bool scaleform_get_replacement_icon(const char *name, const uint8_t *&data, size_t &len, int &w, int &h)
{
    uint64_t hash = hash_data(name, strlen(name));
    switch (hash) {
        case ct_data<hash_data(icon_m4a1_silencer_name, sizeof(icon_m4a1_silencer_name) - 1)>::value: data = icon_m4a1_silencer; len = sizeof(icon_m4a1_silencer); w = icon_m4a1_silencer_w; h = icon_m4a1_silencer_h; return true; break;
        case ct_data<hash_data(icon_m4a1_name, sizeof(icon_m4a1_name) - 1)>::value: data = icon_m4a1; len = sizeof(icon_m4a1); w = icon_m4a1_w; h = icon_m4a1_h; return true; break;
        case ct_data<hash_data(icon_knife_tactical_name, sizeof(icon_knife_tactical_name) - 1)>::value: data = icon_knife_tactical; len = sizeof(icon_knife_tactical); w = icon_knife_tactical_w; h = icon_knife_tactical_h; return true; break;
        case ct_data<hash_data(icon_knife_t_name, sizeof(icon_knife_t_name) - 1)>::value: data = icon_knife_t; len = sizeof(icon_knife_t); w = icon_knife_t_w; h = icon_knife_t_h; return true; break;
        case ct_data<hash_data(icon_knife_survival_bowie_name, sizeof(icon_knife_survival_bowie_name) - 1)>::value: data = icon_knife_survival_bowie; len = sizeof(icon_knife_survival_bowie); w = icon_knife_survival_bowie_w; h = icon_knife_survival_bowie_h; return true; break;
        case ct_data<hash_data(icon_knife_push_name, sizeof(icon_knife_push_name) - 1)>::value: data = icon_knife_push; len = sizeof(icon_knife_push); w = icon_knife_push_w; h = icon_knife_push_h; return true; break;
        case ct_data<hash_data(icon_knife_m9_bayonet_name, sizeof(icon_knife_m9_bayonet_name) - 1)>::value: data = icon_knife_m9_bayonet; len = sizeof(icon_knife_m9_bayonet); w = icon_knife_m9_bayonet_w; h = icon_knife_m9_bayonet_h; return true; break;
        case ct_data<hash_data(icon_knife_karambit_name, sizeof(icon_knife_karambit_name) - 1)>::value: data = icon_knife_karambit; len = sizeof(icon_knife_karambit); w = icon_knife_karambit_w; h = icon_knife_karambit_h; return true; break;
        case ct_data<hash_data(icon_knife_gut_name, sizeof(icon_knife_gut_name) - 1)>::value: data = icon_knife_gut; len = sizeof(icon_knife_gut); w = icon_knife_gut_w; h = icon_knife_gut_h; return true; break;
        case ct_data<hash_data(icon_knife_flip_name, sizeof(icon_knife_flip_name) - 1)>::value: data = icon_knife_flip; len = sizeof(icon_knife_flip); w = icon_knife_flip_w; h = icon_knife_flip_h; return true; break;
        case ct_data<hash_data(icon_knife_name, sizeof(icon_knife_name) - 1)>::value: data = icon_knife; len = sizeof(icon_knife); w = icon_knife_w; h = icon_knife_h; return true; break;
        case ct_data<hash_data(icon_knife_butterfly_name, sizeof(icon_knife_butterfly_name) - 1)>::value: data = icon_knife_butterfly; len = sizeof(icon_knife_butterfly); w = icon_knife_butterfly_w; h = icon_knife_butterfly_h; return true; break;
        case ct_data<hash_data(icon_bayonet_name, sizeof(icon_bayonet_name) - 1)>::value: data = icon_bayonet; len = sizeof(icon_bayonet); w = icon_bayonet_w; h = icon_bayonet_h; return true; break;
        case ct_data<hash_data(icon_incgrenade_name, sizeof(icon_incgrenade_name) - 1)>::value: data = icon_incgrenade; len = sizeof(icon_incgrenade); w = icon_incgrenade_w; h = icon_incgrenade_h; return true; break;
        case ct_data<hash_data(icon_hkp2000_name, sizeof(icon_hkp2000_name) - 1)>::value: data = icon_hkp2000; len = sizeof(icon_hkp2000); w = icon_hkp2000_w; h = icon_hkp2000_h; return true; break;
        case ct_data<hash_data(icon_hegrenade_name, sizeof(icon_hegrenade_name) - 1)>::value: data = icon_hegrenade; len = sizeof(icon_hegrenade); w = icon_hegrenade_w; h = icon_hegrenade_h; return true; break;
        case ct_data<hash_data(icon_flashbang_name, sizeof(icon_flashbang_name) - 1)>::value: data = icon_flashbang; len = sizeof(icon_flashbang); w = icon_flashbang_w; h = icon_flashbang_h; return true; break;
        case ct_data<hash_data(icon_elite_name, sizeof(icon_elite_name) - 1)>::value: data = icon_elite; len = sizeof(icon_elite); w = icon_elite_w; h = icon_elite_h; return true; break;
        case ct_data<hash_data(icon_decoy_name, sizeof(icon_decoy_name) - 1)>::value: data = icon_decoy; len = sizeof(icon_decoy); w = icon_decoy_w; h = icon_decoy_h; return true; break;
        case ct_data<hash_data(icon_deagle_name, sizeof(icon_deagle_name) - 1)>::value: data = icon_deagle; len = sizeof(icon_deagle); w = icon_deagle_w; h = icon_deagle_h; return true; break;
        case ct_data<hash_data(icon_awp_name, sizeof(icon_awp_name) - 1)>::value: data = icon_awp; len = sizeof(icon_awp); w = icon_awp_w; h = icon_awp_h; return true; break;
        case ct_data<hash_data(icon_ak47_name, sizeof(icon_ak47_name) - 1)>::value: data = icon_ak47; len = sizeof(icon_ak47); w = icon_ak47_w; h = icon_ak47_h; return true; break;
        case ct_data<hash_data(icon_ssg08_name, sizeof(icon_ssg08_name) - 1)>::value: data = icon_ssg08; len = sizeof(icon_ssg08); w = icon_ssg08_w; h = icon_ssg08_h; return true; break;
        case ct_data<hash_data(icon_smokegrenade_name, sizeof(icon_smokegrenade_name) - 1)>::value: data = icon_smokegrenade; len = sizeof(icon_smokegrenade); w = icon_smokegrenade_w; h = icon_smokegrenade_h; return true; break;
        case ct_data<hash_data(icon_molotov_name, sizeof(icon_molotov_name) - 1)>::value: data = icon_molotov; len = sizeof(icon_molotov); w = icon_molotov_w; h = icon_molotov_h; return true; break;
        case ct_data<hash_data(icon_mag7_name, sizeof(icon_mag7_name) - 1)>::value: data = icon_mag7; len = sizeof(icon_mag7); w = icon_mag7_w; h = icon_mag7_h; return true; break;
        case ct_data<hash_data(icon_m4a1_silencer_off_name, sizeof(icon_m4a1_silencer_off_name) - 1)>::value: data = icon_m4a1_silencer_off; len = sizeof(icon_m4a1_silencer_off); w = icon_m4a1_silencer_off_w; h = icon_m4a1_silencer_off_h; return true; break;
    }
    
    return false;
}