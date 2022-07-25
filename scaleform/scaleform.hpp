#pragma once

#include <cstdint>

namespace tsf
{
    struct ui_panel_t;
    struct player_t;
    struct event_t;
}

struct scaleform_t
{
    // game panel
    tsf::ui_panel_t *root;
    // root's weap sel panel
    tsf::ui_panel_t *weap_sel;
    // reset on shutdown, whether scaleform was initialized
    // (for toggle)
    bool inited;
    // old color cvar value
    int old_color;
    // old alpha cvar value
    float old_alpha;
    // old healthammo style cvar value
    int old_healthammo_style;
    // old in buyzone value
    int old_in_buyzone;
    // verify if we received mvp event
    bool pending_mvp;
} inline scf;

void scaleform_init();
void scaleform_install();
void scaleform_tick(tsf::player_t *);
void scaleform_on_event(tsf::event_t *);
void scaleform_after_event(const char *);
// special event
void scaleform_on_death();
void scaleform_on_weapon_event();
void scaleform_dump_icons(const uint8_t *, size_t, const char *);