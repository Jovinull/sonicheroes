// TObjEFLens's destructor, out of line, in each of the 13 stage modules that
// carry the lens flare. Its body is in lens_flare_class.inc, which says why
// the chain walk is written there directly; this unit defines LENS_FLARE_DTOR
// empty to emit it. The destructor is declared after the class's first other
// virtual so this unit does not emit the vtable.

#define LENS_FLARE_CTOR     inline
#define LENS_FLARE_SET_CTOR inline
#define LENS_FLARE_DTOR
#include "src/rel/lens_flare_class.inc"
