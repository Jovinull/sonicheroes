#include "types.h"

// gokurakuchoAtomicCallback, which the bird's constructor
// (rel/gokuracho_ctor.cpp) runs over each atomic of its stage model: the
// atomic is kept in the object, and its render callback set to the bird's own
// (fn_3_7D9A0), the default one (fn_8014F1B0) standing in should that be
// missing.

typedef struct RpAtomic RpAtomic;

struct RpAtomic {
	u8 unk00[0x48];
	RpAtomic* (*renderCallBack)(RpAtomic* atomic); // 0x48
};

extern "C" RpAtomic* fn_3_7D9A0(RpAtomic* atomic);
extern "C" RpAtomic* fn_8014F1B0(RpAtomic* atomic);

extern "C" RpAtomic* gokurakuchoAtomicCallback(RpAtomic* atomic, void* data)
{
	*(RpAtomic**)data      = atomic;
	atomic->renderCallBack = fn_3_7D9A0;
	if (atomic->renderCallBack == NULL) {
		atomic->renderCallBack = fn_8014F1B0;
	}
	return NULL;
}
