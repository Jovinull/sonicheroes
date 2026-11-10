# Documentation

Start with [getting_started.md](getting_started.md). The project's public site
(source in [`site/`](../site)) is at <https://jovinull.github.io/sonicheroes/>.

## Working on the decompilation

* [Getting started](getting_started.md): build, verify, find work, match in
  objdiff, open a pull request.
* [Codex engineering baseline](codex-engineering-baseline.md): commit-scoped
  engineering risks, verification state and semantic audit candidates.
* [Source language and compiler evidence](language-policy.md): which units are
  C and which are C++, and how that is decided.
* [Source-language migration audit](language-audit.md): reviewed decisions.
* [Object post-processors](object-post-processors.md): the few objects that
  are patched after compiling, and why each one is allowed.
* [Units returned to NonMatching](units-returned-to-nonmatching.md).
* [Decompilation work tracking](decomp-work-tracking.md): who is working on
  what, so work does not overlap.

## Completed areas

* [advertiseD REL — completed decompilation](advertiseD-decomp.md)
* [CRI completed-unit integration, 2026-09-25](cri-integration-20260925.md)
* [Native LSC reconstruction audit](cri-lsc-native-audit.md)

## Toolchain reference

From the upstream [dtk-template](https://github.com/encounter/dtk-template):

* [splits.txt](splits.md) and [symbols.txt](symbols.md) formats
* [CodeWarrior `.comment` section](comment_section.md)
* [Common BSS](common_bss.md)
* [dtk-template setup guide](dtk-template-guide.md), for starting a new project

## Unit evidence

Notes recording why a translation unit's boundaries, names and code are what
they are, kept for review. Source files link to the note that covers them.

* [Stage13 antenna native matching evidence](antenna-unit-evidence.md)
* [Stage13 blink-light native matching evidence](blinklight-unit-evidence.md)
* [Collision reactor translation unit evidence](c-colli-react-unit-evidence.md)
* [Collision compiler constant order](calc-colli-constant-order.md)
* [Calc native compiler matching](calc-register-evidence.md)
* [Enemy communication translation unit evidence](e-communication-unit-evidence.md)
* [Enemy database translation unit evidence](e-database-unit-evidence.md)
* [Enemy gadget base translation unit evidence](e-gadget-unit-evidence.md)
* [Complete enemy icon-manager translation unit evidence](e-iconman-unit-evidence.md)
* [Complete enemy-link translation unit evidence](e-link-unit-evidence.md)
* [Enemy material-texture translation unit evidence](e-material-unit-evidence.md)
* [Complete enemy motion-controller translation unit evidence](e-motion-unit-evidence.md)
* [Enemy motion-path translation unit evidence](e-mtnpath-unit-evidence.md)
* [Complete enemy power-core translation unit evidence](e-powercore-unit-evidence.md)
* [Complete enemy ring-laser translation unit evidence](e-ringlaser-unit-evidence.md)
* [Complete enemy score-manager translation unit evidence](e-scoreman-unit-evidence.md)
* [Complete enemy shock-wave translation unit evidence](e-shockwave-unit-evidence.md)
* [Complete enemy summoning translation unit evidence](e-summon-unit-evidence.md)
* [Enemy hierarchy utility translation unit evidence](e-utility-hierarchy-unit-evidence.md)
* [Enemy render utility translation unit evidence](e-utility-render-unit-evidence.md)
* [Enemy RenderWare frame-search utility evidence](e-utility-rw-unit-evidence.md)
* [Complete enemy player-search utility evidence](e-utility-search-unit-evidence.md)
* [Enemy timer utility translation unit evidence](e-utility-system-unit-evidence.md)
* [Complete ball effect translation unit evidence](eff-ball-unit-evidence.md)
* [Complete bomb-effect translation unit evidence](eff-bomb-unit-evidence.md)
* [Complete brim and fly-jump effect translation unit evidence](eff-brim-unit-evidence.md)
* [Complete crash effect translation unit evidence](eff-crash3d-unit-evidence.md)
* [Complete dash-effect translation unit evidence](eff-dush-unit-evidence.md)
* [Complete footprint-effect translation unit evidence](eff-footprints-unit-evidence.md)
* [Complete rocket effect translation unit evidence](eff-rocketaxel-unit-evidence.md)
* [Complete thunder-bomb effect translation unit evidence](eff-thunderbomb-unit-evidence.md)
* [Enemy voice controller unit evidence](enemy-voice-unit-evidence.md)
* [Two-player game table translation unit evidence](game2ptable-unit-evidence.md)
* [Sky Egg laser collision unit](laser-collision-unit-evidence.md)
* [Native light unit evidence](light-register-evidence.md)
* [locateTable.cpp unit evidence](locate-table-unit-evidence.md)
* [Complete material.cpp unit](material-unit-evidence.md)
* [Material color change plugin translation unit](materialcolorchange-unit-evidence.md)
* [Memory.cpp native matching evidence](memory-unit-evidence.md)
* [miscs.cpp compiler constant ordering](miscs-constant-order.md)
* [Complete object.cpp reconstruction](object-unit-evidence.md)
* [object.cpp semantic audit](object-semantic-audit.md): grouped review of all
  79 symbols, source structure, port risks and the remaining register gap.
* [ONEFILE translation unit evidence](one-unit-evidence.md)
* [Path-control compiler constant order](pathctrl-constant-order.md)
* [Path control translation unit evidence](pathctrl-unit-evidence.md)
* [Complete player barrier translation unit evidence](player-barrier-unit-evidence.md)
* [Complete player search translation unit evidence](player-search-unit-evidence.md)
* [rankTable.cpp unit evidence](rank-table-unit-evidence.md)
* [Scanpath translation unit evidence](scanpath-unit-evidence.md)
* [Set-object base translation unit evidence](setobj-unit-evidence.md)
* [Sparkle whole-unit evidence](sparkle-unit-evidence.md)
* [storyTable.cpp complete-unit evidence](story-table-unit-evidence.md)
* [Vertical collision translation unit evidence](vertical-colli-unit-evidence.md)
