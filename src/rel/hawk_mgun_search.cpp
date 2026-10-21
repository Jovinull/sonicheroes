#include "types.h"

// SearchClumpAtomic and its callback, and HAWK_MGUN::SetBulletClump (the PS2
// build's names; the two search functions are local there).
// SearchClumpAtomic lists the clump's atomics into the array (Init inlines
// it); SetBulletClump keeps the clump the bullets are drawn with.

#include "src/rel/hawk_mgun.inc"

typedef struct RpAtomic RpAtomic;

// the number of atomics listed so far
extern "C" s8 hawkMGunAtomicCount;

extern "C" void fn_8014FFBC(RpClump* clump, RpAtomic* (*callback)(RpAtomic*, void*), void* data);

RpAtomic* callbackSearchClumpAtomic(RpAtomic* atomic, void* data);

void SearchClumpAtomic(RpClump* clump, RpAtomic** atomics)
{
	hawkMGunAtomicCount = 0;
	fn_8014FFBC(clump, callbackSearchClumpAtomic, atomics);
}

RpAtomic* callbackSearchClumpAtomic(RpAtomic* atomic, void* data)
{
	((RpAtomic**)data)[hawkMGunAtomicCount] = atomic;
	hawkMGunAtomicCount++;
	return atomic;
}

void HAWK_MGUN::SetBulletClump(RpClump* clump)
{
	pSrcClumpBullet = clump;
}
