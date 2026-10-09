// TObjEFLensTmp's destructor, out of line. Its own body is empty and
// TObjEFLens's destructor is inlined into it (lens_flare_class.inc, defined
// inline here). The destructor is declared after the class's first other
// virtual so this unit does not emit the vtable.

#define LENS_FLARE_CTOR     inline
#define LENS_FLARE_SET_CTOR inline
#define LENS_FLARE_DTOR     inline
#include "src/rel/lens_flare_class.inc"

TObjEFLensTmp::~TObjEFLensTmp() { }
