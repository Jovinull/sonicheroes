// TObjChao::SearchCage (the PS2 build's name): while the chao's placement has
// no work block, the chao looks through the task list its communication number
// names for an object of class 0x24 within 100 of its position; for the first
// one it finds, it gives the placement a 0x14-byte work block, marked
// 0x12345678 and holding the chao's position. Exec inlines it; this copy has no
// caller and is kept with force_active. The class is in chao_class.inc.

#define CHAO_SEARCH_CAGE_INLINE

#include "src/rel/chao_class.inc"
#include "src/rel/chao_methods.inc"
