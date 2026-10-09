// EFLensPtcl's destructor and constructor, out of line. The original defines
// them in the lens flare's file, in this order, and inlines them into the lens
// code after them; lens_flare_class.inc carries them with LENS_FLARE_PTCL,
// inline by default and empty here. Out of line, both list walks test the
// head through the owner and then copy it into the walk's pointer (`mr r3,
// r0`, `mr r4, r0`), which is how they are written; inlined, the copy goes
// away.

#define LENS_FLARE_CTOR     inline
#define LENS_FLARE_SET_CTOR inline
#define LENS_FLARE_DTOR     inline
#define LENS_FLARE_PTCL
#include "src/rel/lens_flare_class.inc"
