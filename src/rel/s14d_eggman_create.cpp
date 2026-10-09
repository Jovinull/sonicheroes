// s14dEggmanCreate, the factory rel/s14d_eggman_register.cpp puts in the editor
// record for TObjS14Eggman, in stage13D.
//
// The allocation is a real new-expression of the C++ class, which is what
// gives the original's `mr r0, r3` and then `mr r31, r0`; rel/sample1_create.cpp
// has the long form.
//
// The module's loader (fn_9_75A80) builds the clump from the class's model
// description; when there is one, every atomic gets the class's render
// callback and the placement's light. The first object of a placement leaves a
// one-word record on it. The clump's frame is then turned about Y by the
// placement's angle, as one minus the cosine and the sine the matrix call
// takes, and moved to the placement. The 1 is the module's constant, read as
// an external.

#define S14D_EGGMAN_CTOR inline
#include "src/rel/s14d_eggman_class.inc"

extern "C" void s14dEggmanCreate(void)
{
	new TObjS14Eggman(lbl_8042C110);
}
