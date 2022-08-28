#define JAVASCRIPT constexpr const char *
#define HEX_COLOR constexpr const char *
#define CSGO_HUD_SCHEMA "panorama/layout/hud/hud.xml"

#define UPDATING_VAR(old, goal_name, goal, on_update) \
{                                                 \
decltype(old) goal_name = goal;               \
if (old != goal_name)                         \
{                                             \
on_update;                                \
old = goal_name;                          \
}                                             \
}                                                 
