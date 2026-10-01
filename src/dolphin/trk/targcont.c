#include "TRK_MINNOW_DOLPHIN/Os/dolphin/targcont.h"
#include "TRK_MINNOW_DOLPHIN/Os/dolphin/dolphin_trk_glue.h"
#include "TRK_MINNOW_DOLPHIN/ppc/Generic/targimpl.h"

// MetroTRK targcont.c: the continue entry point, 0x801CFF18 to 0x801CFF4C.
// Boundaries: every function matched by instruction shape against the
// reference compiled with the MetroTRK flags, in link order.
// Reference: mariopartyrd/marioparty4 src/TRK_MINNOW_DOLPHIN/targcont.c (public
// decompilation of the same MetroTRK build). Built with GC/1.3; see the
// TRK_MINNOW_DOLPHIN entry in configure.py.

DSError TRKTargetContinue(void)
{
	TRKTargetSetStopped(0);
	UnreserveEXI2Port();
	TRKSwapAndGo();
	ReserveEXI2Port();
	return 0;
}
