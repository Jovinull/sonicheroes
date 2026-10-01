#include "types.h"
#include <dolphin/ax.h>

#include "__ax.h"

// AXProf.c of the Dolphin SDK AX audio library, 0x801E4F94 to 0x801E4FDC.
// Boundaries: every function was matched by instruction shape against the
// reference compiled with GC/1.2.5n, in the library's link order.
// Reference: doldecomp/dolsdk2004 src/ax/AXProf.c (public reconstruction of the
// Dolphin SDK); this DOL carries the 2003 release build "<< Dolphin SDK - AX ... Jul 29 2003 16:15:36 >>".
// Compiled with GC/1.2.5n like the other SDK units. The original linker
// smart-stripped the functions nothing in the game calls; they are still
// defined here, as in the SDK source, and the linker drops them again.

static AXPROFILE* __AXProfile;
static u32 __AXMaxProfiles;
static u32 __AXCurrentProfile;
static u32 __AXProfileInitialized;

AXPROFILE* __AXGetCurrentProfile(void)
{
	AXPROFILE* profile;

	if (__AXProfileInitialized != 0) {
		profile = &__AXProfile[__AXCurrentProfile];
		__AXCurrentProfile += 1;
		__AXCurrentProfile %= __AXMaxProfiles;
		return profile;
	}

	return 0;
}

void AXInitProfile(AXPROFILE* profile, u32 maxProfiles)
{

	__AXProfile            = profile;
	__AXMaxProfiles        = maxProfiles;
	__AXCurrentProfile     = 0;
	__AXProfileInitialized = 1;
}

u32 AXGetProfile(void)
{
	BOOL old;
	u32 n;

	old = OSDisableInterrupts();
	n   = __AXCurrentProfile;
	if (n != 0) {
		n -= 1;
	}

	__AXCurrentProfile = 0;
	OSRestoreInterrupts(old);
	return n;
}
