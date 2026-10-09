// GetNearestLens, out of line: the module keeps this copy beside the one
// inlined into TObjEFLensSet::TDisp, though nothing calls it (force_active).
// Out of line, the original tests efLensTop through the global and only then
// copies it into `nearest` (`mr r30, r3` after the branch), which is how
// lens_flare_class.inc writes it; inlined, both forms come out the same. This
// unit defines LENS_FLARE_NEAREST empty to emit it.

#define LENS_FLARE_CTOR     inline
#define LENS_FLARE_SET_CTOR inline
#define LENS_FLARE_DTOR     inline
#define LENS_FLARE_NEAREST
#include "src/rel/lens_flare_class.inc"
