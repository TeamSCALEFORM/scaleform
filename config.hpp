#include "sdk.hpp"

#ifdef __linux__
#include <SDL2/SDL.h>
#include <SDL2/SDL_keyboard.h>
#endif

#define ON true
#define OFF false

#define OLD true
#define NEW false

// refer to https://docs.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes
// for keybinds

#define SCALEFORM_TOGGLE_KEY                         WIN32_LINUX_LITERAL(VK_F11, SDL_SCANCODE_F11)
#define SCALEFORM_DEFAULT                            ON
#define SCALEFORM_WINPANEL_TOGGLE_KEY                WIN32_LINUX_LITERAL(VK_F10, SDL_SCANCODE_F10)
#define SCALEFORM_WINPANEL_DEFAULT                   OLD
#define SCALEFORM_JAVASCRIPT_LOADER_KEY              WIN32_LINUX_LITERAL(VK_F7, SDL_SCANCODE_F7)
#define SCALEFORM_WEAPON_SELECTION_RARITY_DEFAULT    OFF
#define SCALEFORM_WEAPON_SELECTION_RARITY_TOGGLE_KEY WIN32_LINUX_LITERAL(VK_F6, SDL_SCANCODE_F6)

#ifdef WIN32
#define GET_ASYNC_KEY_STATE(x) GetAsyncKeyState(x)
#else
#define GET_ASYNC_KEY_STATE(x) state ? state[x] : 0
#endif