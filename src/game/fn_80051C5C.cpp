// Loads the camera frame's matrix into a pushed matrix slot, inverts it and projects the vector through it (fn_8019947C), then pops the slot.
#include "game/matrix.h"

struct Frame80051C5C {
	u8 pad0[0x10];
	RwMatrixTag m;
};
struct Link80051C5C {
	u8 pad0[4];
	Frame80051C5C* f4;
};
struct Task80051C5C {
	u8 pad0[0x28];
	Link80051C5C* f28;
};

extern "C" {
extern Task80051C5C* lbl_8042C1F8;
RwV3d* fn_8019947C(RwV3d*, const RwV3d*, s32, const RwMatrixTag*);
}

extern "C" void fn_80051C5C(s32 unused, RwV3d* a, const RwV3d* b)
{
	Frame80051C5C* f;
	PushMatrixEx();
	f = lbl_8042C1F8->f28->f4;
	{
		RwMatrixTag* src = &f->m;
		*pCurrentMatrix  = *src;
	}
	njInvertMatrix(0);
	fn_8019947C(a, b, 1, pCurrentMatrix);
	PopMatrixEx();
}
