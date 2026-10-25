#include "types.h"

// The unload and load hooks rel/s02_break_ruin_s_register.cpp puts in S02
// BREAKRUIN S's editor record: they release and load the resources the
// stage's breakable objects share (s02BreakReleaseResources and
// s02BreakLoadResources, still assembly), the load then keeping the lengths
// of the three shared animations the ruin plays.

// an RtAnimAnimation: only its duration is read here
typedef struct Anim {
	u8 unk00[0xC]; // 0x00
	f32 duration;  // 0x0C
} Anim;

extern "C" Anim** s02BreakruinSAnims[3];
extern "C" f32 s02BreakruinSAnimDurations[3];

extern "C" void s02BreakReleaseResources(void);
extern "C" void s02BreakLoadResources(void);

extern "C" void s02BreakruinSUnload(void)
{
	s02BreakReleaseResources();
}

extern "C" void s02BreakruinSLoad(void)
{
	s02BreakLoadResources();
	s02BreakruinSAnimDurations[0] = (*s02BreakruinSAnims[0])->duration;
	s02BreakruinSAnimDurations[1] = (*s02BreakruinSAnims[1])->duration;
	s02BreakruinSAnimDurations[2] = (*s02BreakruinSAnims[2])->duration;
}
