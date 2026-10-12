// TObjKey::SearchCage (the PS2 build's name), out of line: while the key's
// placement has no work block, it looks through the task list its
// communication number names for an object of class 0x24 closer than
// keyObjectCageRange, and for the first one gives the placement a KeyCage
// marked 0x12345678 with the key's position. The constructor inlines it
// (key_object_class.inc); this copy has no caller and is kept with
// force_active.

#define KEY_OBJECT_CTOR inline
#define KEY_SEARCH_CAGE_INLINE

#include "src/rel/key_object_class.inc"
