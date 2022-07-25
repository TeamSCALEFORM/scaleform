#include <fstream>
#include <filesystem>
#include <string>
#include <minmax.h>
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

// ${showRarity} - whether to show rarity
#define SHOW_RARITY "${showRarity}"
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

void ::scaleform_init()
{
    scf.root = scf.weap_sel = nullptr;
    scf.inited = false;
    scf.old_color = scf.old_healthammo_style = -1;
    scf.old_alpha = -1.f;
    scf.old_in_buyzone = -1;
    scf.pending_mvp = false;
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
    std::string js = weapon_select;
    replace_str(js, SHOW_RARITY, ctx.g.show_rarity ? "true" : "false");
    engine->run_script(scf.root, js.c_str(), CSGO_HUD_SCHEMA);
}

void ::scaleform_install()
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
        if (scf.weap_sel = parent->find_child_traverse("WeaponPanelBottomBG"); !scf.weap_sel)
        {
            return LOG("Failed Scaleform install (weapsel panel)\n");
        }
    } else return LOG("Failed Scaleform install (weapsel parent)\n");
    
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
    
    scf.inited = true;
    LOG("Scaleform installed!\n");
}

void ::scaleform_tick(tsf::player_t *local)
{
    // listen to user commands
    if (GetAsyncKeyState(SCALEFORM_TOGGLE_KEY) & 1)
    {
        ctx.g.scf_on = !ctx.g.scf_on;
        LOG("Toggled Scaleform %s\n", (ctx.g.scf_on ? "on" : "off"));
    } else if (GetAsyncKeyState(SCALEFORM_WINPANEL_TOGGLE_KEY) & 1)
    {
        ctx.g.old_wp = !ctx.g.old_wp;
        LOG("Toggled Scaleform winpanel to %s\n", (ctx.g.old_wp ? "old" : "new"));
    } else if (GetAsyncKeyState(SCALEFORM_WEAPON_SELECTION_RARITY_TOGGLE_KEY) & 1)
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
    
    if (GetAsyncKeyState(SCALEFORM_JAVASCRIPT_LOADER_KEY) & 1)
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
    
    if (scf.weap_sel) {
        // make always visible (needs to be done in C++ for performance)
        scf.weap_sel->set_visible(true);
    }
    
    UPDATING_VAR(scf.old_color, n, min(std::size(colors) - 1, ctx.c.cl_hud_color->get_int()),
                 {
                     DEBUG("Changed hud color!\n");
                     std::string js = std::string(color);
                     replace_str(js, RADAR_COLOR, get_color(n, kRadarColor));
                     replace_str(js, DASHBOARD_LABEL_COLOR, get_color(n, kDashColor));
                     engine->run_script(scf.root, js.c_str(), CSGO_HUD_SCHEMA);
                 });
    
    UPDATING_VAR(scf.old_alpha, n, min(MAX_ALPHA, ctx.c.cl_hud_background_alpha->get_float()),
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

void ::scaleform_on_event(tsf::event_t *event)
{
    if (!scf.inited)
        return;
    
    if (!strcmp(event->get_name(), "round_mvp"))
        scf.pending_mvp = true; // flag mvp
    else if (!strcmp(event->get_name(), "round_end"))
        scaleform_winpanel(event->get_int("winner"));
}

void ::scaleform_after_event(const char *name)
{
    if (!scf.inited)
        return;
    
    if (!strcmp(name, "bot_takeover") || !strcmp(name, "switch_team") ||
        !strcmp(name, "round_start")) 
    {
        scaleform_teamcount_avatar();
        scaleform_weapon_selection();
    } else if (!strcmp(name, "spec_target_updated") || !strcmp(name, "spec_mode_updated"))
        scaleform_weapon_selection();
}

void ::scaleform_on_death()
{
    if (!scf.inited)
        return;
    
    tsf::ui_engine_t *engine = ctx.i.panorama->access_ui_engine();
    if (!engine)
        return LOG("Failed Scaleform Death Notice event (ui engine)\n");
    
    DEBUG("Deathnotices being edited!\n");
    engine->run_script(scf.root, deathnotices, CSGO_HUD_SCHEMA);
}

void ::scaleform_on_weapon_event()
{
    if (!scf.inited)
        return;
    
    scaleform_weapon_selection();
}

static uint64_t hash_data(const uint8_t *data, size_t len) 
{
    uint64_t hash = 0x543C730D;
    
    for (size_t i = 0; i < len; ++i) {
        hash ^= data[i];
        hash *= 0x1000931;
    }
    
    return hash;
}

void ::scaleform_dump_icons(const uint8_t *data, size_t len, const char *extension)
{
    std::filesystem::path folder_path = std::filesystem::current_path() / "pano_icos";
    
    uint64_t hash = hash_data(data, len);
    std::string name = "icon_" + std::to_string(hash) + extension;
    
    std::filesystem::path rgba_path = folder_path / name;
    
    std::ofstream stream(rgba_path, std::ios::binary | std::ios::out);
    stream.write((const char *)data, len);
    stream.close();
    DEBUG("Dumped icon %s!\n", name.c_str());
}