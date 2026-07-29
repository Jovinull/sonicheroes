#include "types.h"

// Scalar pool used by adv_draw.cpp. Keeping these named values in a data-only
// object preserves the original ordering while allowing the drawing code to
// treat them as opaque externs, as MWCC did at each load site.
extern "C" const f32 lbl_1_rodata_1CD8 = 1.0f;
extern "C" const f32 lbl_1_rodata_1CDC = 0.5f;
extern "C" const f32 lbl_1_rodata_1CE0 = 0.03125f;
extern "C" const f32 lbl_1_rodata_1CE4 = 32.0f;
extern "C" const f32 lbl_1_rodata_1CE8 = 2.0f;
extern "C" const f32 lbl_1_rodata_1CEC = 16.0f;
extern "C" const f32 lbl_1_rodata_1CF0 = 3.0f;
extern "C" const f32 lbl_1_rodata_1CF4 = 8.0f;
extern "C" const f32 lbl_1_rodata_1CF8 = 0.0f;
