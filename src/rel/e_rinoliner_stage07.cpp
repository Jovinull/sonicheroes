// stage07D's copy of the rinoliner (rel/e_rinoliner_stage11.cpp): like
// stage05D's (rel/e_rinoliner_stage05.cpp), and its vtable's DispShadow slot
// takes fn_8_B49E0, and the empty slot before it takes the module's own copy,
// fn_6_E70BC.

#define E_RINOLINER_SHARED_STRATEGY
#define E_RINOLINER_DISP_SHADOW fn_8_B49E0
#define E_RINOLINER_EMPTY_SLOT  fn_6_E70BC
#include "src/rel/e_rinoliner_stage11.cpp"
