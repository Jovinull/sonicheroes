#include "types.h"

// The unload and load hooks rel/s02_break_ruin_l_register.cpp puts in S02
// BREAKRUIN L's editor record: they release and load the resources the
// stage's breakable objects share (s02BreakReleaseResources and
// s02BreakLoadResources, still assembly), the load then keeping the length
// of the shared animation the ruin plays.

// an RtAnimAnimation: only its duration is read here
typedef struct Anim {
	u8 unk00[0xC]; // 0x00
	f32 duration;  // 0x0C
} Anim;

extern "C" Anim* lbl_3_bss_1958;
extern "C" f32 s02BreakruinLAnimDuration;

extern "C" void s02BreakReleaseResources(void);
extern "C" void s02BreakLoadResources(void);

extern "C" void s02BreakruinLUnload(void)
{
	s02BreakReleaseResources();
}

extern "C" void s02BreakruinLLoad(void)
{
	s02BreakLoadResources();
	s02BreakruinLAnimDuration = lbl_3_bss_1958->duration;
}
