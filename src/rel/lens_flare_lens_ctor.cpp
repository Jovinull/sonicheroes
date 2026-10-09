// TObjEFLens's constructor, out of line: the copy each module keeps beside
// the ones inlined into the factory and into TObjEFLensSet's constructor. Its
// body is in lens_flare_class.inc, which says why the chain walk is written
// in it directly; this unit defines LENS_FLARE_CTOR empty to emit it.

#define LENS_FLARE_CTOR
#define LENS_FLARE_SET_CTOR inline
#define LENS_FLARE_DTOR     inline
#include "src/rel/lens_flare_class.inc"
