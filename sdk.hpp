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
    
    struct ui_engine_t 
    {
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
    
    struct panorama_t
    {
        ui_engine_t *access_ui_engine() 
        {
            return ((ui_engine_t *(__thiscall*)(panorama_t *))((*(uintptr_t**)(this))[11]))(this);
        }
    };
    
    struct player_t
    {
        bool in_buyzone()
        {
            return *(bool*)((uintptr_t)this + 0x99B5);
        }
    };
    
    struct user_cmd_t 
    {
        int get_command_number() 
        {
            return *(int*)((uintptr_t)this + 0x4);
        }
    };
    
    struct cvar_t
    {
        float get_float() 
        {
            return ((float(__thiscall*)(cvar_t *))((*(uintptr_t**)(this))[12]))(this);
        }
        
        int get_int() 
        {
            return ((int(__thiscall*)(cvar_t *))((*(uintptr_t**)(this))[13]))(this);
        }
    };
    
    struct cvars_t
    {
        cvar_t *get_var(const char *name) 
        {
            return ((cvar_t *(__thiscall*)(cvars_t *, const char *))((*(uintptr_t**)(this))[16]))(this, name);
        }
    };
    
    struct event_t
    {
        const char *get_name() 
        {
            return ((const char *(__thiscall*)(event_t *))((*(uintptr_t**)(this))[1]))(this);
        }
        
        int get_int(const char *key, int def = 0) 
        {
            return ((int(__thiscall*)(event_t *, const char *, int))((*(uintptr_t**)(this))[6]))(this, key, def);
        }
    };
}