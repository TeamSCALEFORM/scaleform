// Built by Cristei Gabriel-Marian (cristeigabriel)
// (cristei <dot> g772 <at> gmail <dot> com)
// 
// ~TeamSCALEFORM~

#include <thread>
#include <filesystem>
#include "init.hpp"

static void run_init()
{
    LOG("Created by cristeigabriel, with the help of:\n"
        "isak, jo and other public contributors\n"
        "cristeigabriel: reverse engineering, boilerplate, original JS,\n"
        "making TeamSCALEFORM its own project\n"
        "isak: new JS, design\n"
        "jo: 2013 winpanel\n"
        "bruhmoment21: Linux port\n"
        "~~~~~~~~~~~~\n"
        "Refer to config.hpp for help\n"
        "NOTE: TeamSCALEFORM currently requires you disconnect\n"
        "for Scaleform Toggle Off to take effect\n"
        "(Toggle On will immediately take effect.)\n"
        "JavaScript to load on bind must be located at %s\\base.js\n"
        "~~~~~~~~~~~~\n"
        "This software is licensed under AGPL-3.0, if it\n"
        "wasn't shipped with the source code, you can download it at\n"
        "https://github.com/TeamSCALEFORM/scaleform\n"
        "~~~~~~~~~~~~\n",
        std::filesystem::current_path().string().c_str());
    
    ::init();
}

#ifdef WIN32
BOOL APIENTRY DllMain(HMODULE module, DWORD reason, LPVOID reserved)
{
    if (reason != DLL_PROCESS_ATTACH)
        return FALSE;
    (void)(reserved);
    
    AllocConsole();
    freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);
    
    run_init();
    return TRUE;
}
#else
static void __attribute__((constructor)) attach() 
{
    std::thread _{run_init};
    _.detach();
}
#endif