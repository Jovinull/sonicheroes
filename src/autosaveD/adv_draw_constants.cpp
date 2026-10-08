#include "types.h"

// autosaveD carries its own copy of this unit: the same source as
// advertiseD/adv_draw_constants.cpp, linked here at .rodata 0x328-0x350. Functions and data are
// byte-identical to the advertiseD objects once relocations are masked; only
// module-local names differ (fn_1_/lbl_1_ there, fn_2_/lbl_2_ here), mapped by
// pairing every relocation at the same offset in both retail objects. Taken
// over from the abandoned PR #116 (ThePlayerRolo), which first identified these
// AutoSaveD classes from PS2 symbols; the reconstruction is CYPRESS's advertiseD
// work. Keep the two copies in sync.
//
// Scalar pool used by adv_draw.cpp. Keeping these named values in a data-only
// object preserves the original ordering while allowing the drawing code to
// treat them as opaque externs, as MWCC did at each load site.
extern "C" const f32 lbl_2_rodata_328 = 1.0f;
extern "C" const f32 lbl_2_rodata_32C = 0.5f;
extern "C" const f32 lbl_2_rodata_330 = 0.03125f;
extern "C" const f32 lbl_2_rodata_334 = 32.0f;
extern "C" const f32 lbl_2_rodata_338 = 2.0f;
extern "C" const f32 lbl_2_rodata_33C = 16.0f;
extern "C" const f32 lbl_2_rodata_340 = 3.0f;
extern "C" const f32 lbl_2_rodata_344 = 8.0f;
extern "C" const f32 lbl_2_rodata_348 = 0.0f;
