// Refreshes the instanced data of an atomic before rendering (HYPOTHESIS: the GameCube atomic
// re-instance step). When the geometry was locked since it was instanced (+0xC), waits for the GPU
// to pass the instance's draw-sync token, re-instances the geometry (fn_8015CD70) and clears the
// lock; when a morphing geometry (more than one morph target) has a dirty interpolator (atomic
// +0x4C bit 0), waits again and re-instances the morph (fn_8015DF00), clearing the bit. Returns the
// atomic. Names are inferred from this function and fn_8015C004.
#include "types.h"

struct Geometry8015CFDC {
	u8 pad0[0xC];
	u16 lockedSinceInstance; // 0xC
	u8 padE[0x18 - 0xE];
	s32 numMorphTargets; // 0x18
};

// Instance data placed after the 0x18-byte resource entry header; starts with the draw-sync token.
struct Instance8015CFDC {
	u16 drawSyncToken; // 0x0
};

struct Atomic8015CFDC {
	u8 pad0[0x18];
	Geometry8015CFDC* geometry; // 0x18
	u8 pad1C[0x4C - 0x1C];
	u32 interpolatorFlags; // 0x4C: bit 0 dirty
};

struct Pipeline8015CFDC {
	u8* resEntry; // 0x0: instance data follows the 0x18-byte header
	u8 pad4[0x28 - 0x4];
	s32 flags28; // 0x28
};

extern "C" {
extern volatile u16 lbl_8042BE88; // next draw-sync token to issue
void GXSetDrawSync(u16 token);
s32 fn_801B2894(u16 token);
void fn_8015CD70(Geometry8015CFDC* geometry, Instance8015CFDC* instance, s32 flags);
void fn_8015DF00(Geometry8015CFDC* geometry, Instance8015CFDC* instance, u32* interpolatorFlags);
}

// Waits until the GPU has passed the token, issuing it first when it is the pending one.
static inline void WaitDrawSync8015CFDC(Instance8015CFDC* instance)
{
	if (instance->drawSyncToken == lbl_8042BE88) {
		GXSetDrawSync(lbl_8042BE88);
		lbl_8042BE88 = (lbl_8042BE88 + 1) % 0xE000;
	}
	while (!fn_801B2894(instance->drawSyncToken)) {
	}
}

extern "C" {
Atomic8015CFDC* fn_8015CFDC(Atomic8015CFDC* atomic, Pipeline8015CFDC* pipeline)
{
	Geometry8015CFDC* geometry = atomic->geometry;
	Instance8015CFDC* instance = (Instance8015CFDC*)(pipeline->resEntry + 0x18);

	if (geometry->lockedSinceInstance != 0) {
		WaitDrawSync8015CFDC(instance);
		fn_8015CD70(geometry, instance, pipeline->flags28);
		geometry->lockedSinceInstance = 0;
	}
	if (geometry->numMorphTargets != 1 && (atomic->interpolatorFlags & 1)) {
		WaitDrawSync8015CFDC(instance);
		fn_8015DF00(geometry, instance, &atomic->interpolatorFlags);
		atomic->interpolatorFlags &= ~1;
	}
	return atomic;
}
}
