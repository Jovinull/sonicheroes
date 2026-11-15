// Refreshes an object's cached frame matrix: copies the frame's world matrix (fn_8019E8EC on the
// frame at +0x8; HYPOTHESIS: RwFrameGetLTM) to +0xC, and keeps its position at +0x4C and its "at"
// row at +0x58. The object's role is UNKNOWN.
#include "types.h"

struct RwV3d {
	f32 x;
	f32 y;
	f32 z;
};

struct RwMatrix8003C8F8 {
	RwV3d right; // 0x0
	u32 flags;   // 0xC
	RwV3d up;    // 0x10
	u32 pad1;    // 0x1C
	RwV3d at;    // 0x20
	u32 pad2;    // 0x2C
	RwV3d pos;   // 0x30
	u32 pad3;    // 0x3C
};

struct Obj8003C8F8 {
	u8 pad0[8];
	void* frame;             // 0x8
	RwMatrix8003C8F8 matrix; // 0xC
	RwV3d position;          // 0x4C
	RwV3d at;                // 0x58
};

extern "C" {
RwMatrix8003C8F8* fn_8019E8EC(void* frame);

void fn_8003C8F8(Obj8003C8F8* o)
{
	o->matrix   = *fn_8019E8EC(o->frame);
	o->position = o->matrix.pos;
	o->at       = o->matrix.at;
}
}
