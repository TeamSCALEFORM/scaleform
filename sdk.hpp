#pragma once

#include <cstdint>

namespace tsf
{
    struct ui_panel_t
    {
        const char *get_id()
        {
            return ((const char *(__thiscall*)(ui_panel_t *))((*(uintptr_t**)(this))[9]))(this);
        }
        
        ui_panel_t* get_parent()
        {
            return ((ui_panel_t *(__thiscall*)(ui_panel_t *))((*(uintptr_t**)(this))[25]))(this);
        }
        
        void set_visible(bool to)
        {
            return ((void(__thiscall*)(ui_panel_t *, bool))((*(uintptr_t**)(this))[27]))(this, to);
        }
        
        ui_panel_t *find_child_traverse(const char *name)
        {
            return ((ui_panel_t *(__thiscall*)(ui_panel_t *, const char *))((*(uintptr_t**)(this))[40]))(this, name);
        }
    };
    
    struct ui_engine_t {
        bool is_valid_panel_pointer(ui_panel_t const *panel)
        {
            return ((bool(__thiscall*)(ui_engine_t *, ui_panel_t const *))((*(uintptr_t**)(this))[36]))(this, panel);
        }
        
        ui_panel_t *get_last_dispatched_event_target_panel()
        {
            return ((ui_panel_t *(__thiscall*)(ui_engine_t *))((*(uintptr_t**)(this))[56]))(this);
        }
        
        
        void run_script(ui_panel_t *panel, const char *js, const char *schema_path, int a5 = 8, int a6 = 10, bool a7 = false, bool a8 = false)
        {
            return ((void(__thiscall*)(ui_engine_t *, ui_panel_t *, const char *, const char *, int, int, bool, bool))((*(uintptr_t**)(this))[113]))(this, panel, js, schema_path, a5, a6, a7, a8);
        }
    };
    
    struct panorama_t {
        ui_engine_t *access_ui_engine() 
        {
            return ((ui_engine_t *(__thiscall*)(panorama_t *))((*(uintptr_t**)(this))[11]))(this);
        }
    };
    
    struct user_cmd_t {
        int get_command_number() {
            return *(int*)((uintptr_t)this + 0x4);
        }
    };
}