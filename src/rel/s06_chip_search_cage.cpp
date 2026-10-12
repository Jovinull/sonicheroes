// TObjS06Chip::SearchCage (the PS2 build's name), out of line: while the chip's
// placement has no work block, it looks through the task list its
// communication number names for an object of class 0x24 within range, and
// for the first one gives the placement a KeyCage marked 0x12345678 with its
// position (rel/key_search_cage.cpp has TObjKey's). The constructor inlines
// it (s06_chip_class.inc); this copy has no caller and is kept with force_active.

#define S06_CHIP_CTOR inline
#define S06_CHIP_SEARCH_CAGE_INLINE

#include "src/rel/s06_chip_class.inc"
