// Built by Cristei Gabriel-Marian (cristeigabriel)
// (cristei <dot> g772 <at> gmail <dot> com)
// 
// ~TeamSCALEFORM~

#include "init.hpp"

BOOL APIENTRY DllMain(HMODULE module, DWORD reason, LPVOID reserved)
{
    if (reason != DLL_PROCESS_ATTACH)
        return FALSE;
    (void)(reserved);
    
    AllocConsole();
    freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);
    
    LOG("Created by cristeigabriel, with the help of:\n");
    LOG("isak, jo and other public contributors\n");
    LOG("cristeigabriel: reverse engineering, boilerplate, original JS,\n");
    LOG("making TeamSCALEFORM its own project\n");
    LOG("isak: new JS, design\n");
    LOG("jo: 2013 winpanel\n");
    LOG("~~~~~~~~~~~~\n");
    init();
    
    return TRUE;
}