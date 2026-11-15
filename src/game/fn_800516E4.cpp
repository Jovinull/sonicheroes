#include "game/misc.h"

// Updates the scripted camera rig lbl_802C218C by its mode (+0x0): mode 0 measures the offset
// (+0x28) from the target (+0x10) to the eye (+0x34), keeps its length (+0x40) and derives its
// angles (+0x1C/+0x20, fn_80051FF0); modes 1 and 3 rebuild the offset from the angles
// (fn_80051F68) scaled by the length and place the eye at target + offset (1) or the target at
// eye - offset (3); modes 2 and 4 keep the given offset, derive its angles and length and place
// the eye (2) or the target (4). lbl_8042B088 is passed through. HYPOTHESIS: the mode roles
// (look-at, orbit) are UNKNOWN.

struct Angle800516E4 {
	s32 pitch; // 0x0
	s32 yaw;   // 0x4
};

struct Rig800516E4 {
	s32 mode; // 0x0
	u8 pad4[0x10 - 0x4];
	RwV3d target;        // 0x10
	Angle800516E4 angle; // 0x1C
	u8 pad24[0x28 - 0x24];
	RwV3d offset; // 0x28
	RwV3d eye;    // 0x34
	f32 length;   // 0x40
	u8 pad44[0x54 - 0x44];
};

extern "C" {
extern Rig800516E4 lbl_802C218C;
extern void* lbl_8042B088;
f32 fn_801991B4(const RwV3d* v);
void fn_80051FF0(void* unused, RwV3d* v, s32* pitch, s32* yaw);
void fn_80051F68(void* self, Angle800516E4* angle, RwV3d* out);
}

extern "C" void fn_800516E4(void)
{
	switch (lbl_802C218C.mode) {
		case 0:
			SubVectorReturnToVector(&lbl_802C218C.eye, &lbl_802C218C.target, &lbl_802C218C.offset);
			lbl_802C218C.length = fn_801991B4(&lbl_802C218C.offset);
			fn_80051FF0(lbl_8042B088, &lbl_802C218C.offset, &lbl_802C218C.angle.pitch,
			    &lbl_802C218C.angle.yaw);
			break;
		case 1:
			fn_80051F68(lbl_8042B088, &lbl_802C218C.angle, &lbl_802C218C.offset);
			lbl_802C218C.offset.x *= lbl_802C218C.length;
			lbl_802C218C.offset.y *= lbl_802C218C.length;
			lbl_802C218C.offset.z *= lbl_802C218C.length;
			AddVectorReturnToVector(&lbl_802C218C.target, &lbl_802C218C.offset, &lbl_802C218C.eye);
			break;
		case 2:
			fn_80051FF0(lbl_8042B088, &lbl_802C218C.offset, &lbl_802C218C.angle.pitch,
			    &lbl_802C218C.angle.yaw);
			lbl_802C218C.length = fn_801991B4(&lbl_802C218C.offset);
			AddVectorReturnToVector(&lbl_802C218C.target, &lbl_802C218C.offset, &lbl_802C218C.eye);
			break;
		case 3:
			fn_80051F68(lbl_8042B088, &lbl_802C218C.angle, &lbl_802C218C.offset);
			lbl_802C218C.offset.x *= lbl_802C218C.length;
			lbl_802C218C.offset.y *= lbl_802C218C.length;
			lbl_802C218C.offset.z *= lbl_802C218C.length;
			SubVectorReturnToVector(&lbl_802C218C.eye, &lbl_802C218C.offset, &lbl_802C218C.target);
			break;
		case 4:
			fn_80051FF0(lbl_8042B088, &lbl_802C218C.offset, &lbl_802C218C.angle.pitch,
			    &lbl_802C218C.angle.yaw);
			lbl_802C218C.length = fn_801991B4(&lbl_802C218C.offset);
			SubVectorReturnToVector(&lbl_802C218C.eye, &lbl_802C218C.offset, &lbl_802C218C.target);
			break;
	}
}
