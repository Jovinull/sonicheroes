// TObjEFLensTmp's constructor, out of line; nothing calls it, so each module
// keeps it through force_active. TObjEFLens's constructor is inlined into it
// and the lens then zeroes its position, z first (one chained assignment).
// The class is shared through lens_flare_class.inc; this unit defines
// LENS_FLARE_TMP_CTOR empty to emit the constructor.

#define LENS_FLARE_CTOR     inline
#define LENS_FLARE_SET_CTOR inline
#define LENS_FLARE_TMP_CTOR
#define LENS_FLARE_DTOR inline
#include "src/rel/lens_flare_class.inc"
