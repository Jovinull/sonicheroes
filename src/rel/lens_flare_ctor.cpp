// TObjEFLensSet's constructor, out of line, with TObjEFLens's constructor
// inlined into it: the copy each module keeps beside the one inlined into
// lensFlareCreate. The classes are shared through lens_flare_class.inc.

#define LENS_FLARE_CTOR inline
#define LENS_FLARE_SET_CTOR
#include "src/rel/lens_flare_class.inc"
