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
    // weap sel
    tsf::ui_panel_t *weap_sel;
    // weap pan bg
    tsf::ui_panel_t *weap_pan_bg;
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
    // old weapon selection rows count
    int old_weap_rows_count;
} inline scf;

void scaleform_init();
void scaleform_install();
void scaleform_tick(tsf::player_t *);
void scaleform_on_event(tsf::event_t *);
void scaleform_after_event(const char *);
void scaleform_dump_icons(const char *, const uint8_t *, size_t, const char *);
bool scaleform_get_replacement_icon(const char *, const uint8_t *&, size_t &, int &, int &);