// TObjEFLensSet::Exec. Out of range or due to be killed, the set raises the
// kill bit of its signal; otherwise it asks OnEdit and returns early when it
// is placed in the editor, with nothing after that in either case. The early
// return is what keeps the original's `cmpwi r3, 0` with no branch after it:
// an empty if body is dropped together with its test. The classes are in
// lens_flare_class.inc.

#define LENS_FLARE_CTOR     inline
#define LENS_FLARE_SET_CTOR inline
#define LENS_FLARE_DTOR     inline
#include "src/rel/lens_flare_class.inc"

void TObjEFLensSet::Exec()
{
	if (CheckRangeOut() || CheckMustKill()) {
		Signal |= 1;
	} else if (OnEdit()) {
		return;
	}
}
