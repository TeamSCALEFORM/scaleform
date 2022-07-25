
<a href="https://discord.gg/FDkMfgZDnz"><img width="245" src="https://discord.com/api/guilds/1000835399364661420/widget.png?style=banner3" alt="discord"></a>
Join us on Discord!

# scaleform
A hackable and future-proof reimplementation of In-Game Scaleform HUD in CS:GO using Panorama. Written using C, C++ and JS.

# Disclaimer
We're not responsible for any potential VAC bans from using our project. Do not use this on any account you care about, unless you use `-insecure`, or respectively `sv_lan 1` on local servers.

# Features
- JavaScript loader (load changes at run-time, on bind);
- Toggle Scaleform at run-time, without restarting game (on keybind - you're currently required to disconnect after toggling off, not when toggling on);
- Hot-swappable Win Panels (on keybind);
- Toggle Weapon Selection "show rarity" on/off (on keybind);
- Fully supports (almost) every HUD command (including `cl_hud_color`, `cl_hud_background_alpha`, `cl_hud_healthammo_style`, etc...); 
- `-insecure` is not enforced;
- No performance drawbacks (unlike with HLAE+MIGI);
- Fully standalone (you only have to inject one DLL);
- Future proof (does not require to be updated for code.pbin updates - unless it breaks any of the JavaScript itself);
- Customizable (you can modify the CSS to your desires, and you can change keybinds and default states in `config.hpp`).

# Issues
The current known issues are:
- Weapon Selection boilerplate does not support weapon switches when spectating someone (this includes POV demos);
- Win Panels do not have the background white flash;
- Win Panels have not been tested with music kits;
- Team Counter does not support the bottom option;
- Team Counter Avatars white outline is hackily implemented, thus has delays;
- Weapon Selection boilerplate is also somewhat hackily implemented, therefore it may also have delays (not noticeable when you have rarity off);
- Local Death Notices (local kill/death) background does not have transition properties, therefore we shorten the animation before they kick in (to 5 seconds, from originally 8).

# TODO
- Old Spectator HUD;
- Support more gamemodes (eg. Deathmatch - currently you'll have a mix of new and old UI);
- Fix Issues;
- Prettify JS;
- And more.

# Main Menu
If there's interest, and support, we're willing to kickstart progress towards replicating the Scaleform main-menu(s). Anyhow, before we divert any attention to that, there's much work left on the In-Game HUD.

# Contributing
Even if you don't know C++, you can write your changes in JavaScript (relating to the schema itself), and we will help implement the necessary boiler-plate for your change. If you're interested in doing such things, please join our Discord and see the `#contributing` channel. Thank you for your interest!

NOTE: Once you open your game, you'll be told where your custom JavaScript file is expected. If it is not found, and you press the Load JavaScript keybind, you'll be announced in the console.

# Building
To build this project, you must install `CMake (>=3.21)`, `Ninja` and `Visual Studio 2022 Developer Tools`, then, open up `Developer Command Prompt for Visual Studio 2022`, go to the respective directory where your clone of this project is located (quick-tip: if your clone is located on a disk other than your start disk, you can modify the Developer Command Prompt 'Start In' flag, in properties), then write:

`./build_release.bat` for release builds, or;

`./build_debug.bat` for debug builds (includes Debug logs).

Then, a build should start, and when it's done, your command prompt will be moved to the output directory, which should contain a `TeamSCALEFORM.dll` binary.

# Ports
We support ports of the boilerplate to software's APIs. If you developed a port of the scaleform boilerplate, open a pull request that links your repository under this comment.
<!-- Here! Remember to use [name](url) -->

# Alternatives
If you're a movie-maker, and you want something better suited for that purpose, please refer [to this](https://www.youtube.com/watch?v=FVtBAll3xjw).

# Licensing
This project is licensed under the [AGPL-3.0 license](https://github.com/TeamSCALEFORM/scaleform/blob/main/LICENSE). For a TLDR, refer to [this](https://tldrlegal.com/license/gnu-affero-general-public-license-v3-(agpl-3.0)). Please respect this.

# Scams
If some are blind to the "Licensing" section, they're going to be 'advertised' here, so you know who to avoid. We encourage people to make pull requests, if they ever notice a project using this against our firm licensing terms, which name and link said project.
<!-- If you know any project which uses this against the licensing terms, please link them [in this format](link) -->
