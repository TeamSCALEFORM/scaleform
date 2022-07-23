#include <string>
#include "scaleform.hpp"
#include "../init.hpp"
#include "../sdk.hpp"

#include "sanitary_macros.hpp"

#define CSGO_HUD_SCHEMA "panorama/layout/hud/hud.xml"

JAVASCRIPT base =
#include "base.js"
;

// TODO: set to default value
SCALEFORM_JS_STATE winpanel;

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

void ::scaleform_install()
{
    if (scf.inited)
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
    
    scf.inited = true;
}

void ::scaleform_tick()
{
    bool on = true;
    
    // could also be potential recovery from (very unlikely to impossible)
    // fail in levelinit
    if (!scf.inited && on)
    {
        scaleform_install();
        return;
    } else if (!scf.inited || !on) 
        return;
    
    // TODO: other way around, fully reinitialzie schema on toggle off
    
    if (scf.weap_sel) {
        // make always visible (needs to be done in C++ for performance)
        scf.weap_sel->set_visible(true);
    }
    
    // verify state vars and update
}