#include "types.h"

struct FrameVec {
	f32 x;
	f32 y;
	f32 z;
};

struct Frame801734F4 {
	u8 pad0[8];
	u32 flags;       // 0x8
	u8 matrix[0x30]; // 0xC (RwMatrix)
};

extern "C" {
extern volatile f32 lbl_8042F49C;
void* fn_80196050(void* matrix, const FrameVec* translation, s32 combine);

void* fn_801734F4(void* arg0, f32 x, f32 y)
{
	Frame801734F4* frame = (Frame801734F4*)arg0;
	volatile FrameVec translation;

	translation.x = x;
	translation.y = y;
	translation.z = lbl_8042F49C;
	fn_80196050(frame->matrix, (const FrameVec*)&translation, 1);
	frame->flags |= 2;
	return frame;
}
}
