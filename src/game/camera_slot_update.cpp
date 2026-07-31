#include "types.h"

// The other half of the file game/camera_slot_create.cpp carves: the per-frame
// update that walks the camera toward its slot's target and writes the result
// out for the caller.
//
// The claim is .text 0x80139FC4 to 0x8013A49C, extab 0x8000BA80 to 0x8000BA88,
// extabindex 0x80011AA0 to 0x80011AAC and .sdata2 0x8042F168 to 0x8042F190.
// That .sdata2 run is the unit's own constant pool. 0x8042F184 is the padding
// the double at 0x8042F188 needs for eight byte alignment, and that double is
// the compiler's int-to-float constant rather than one the source writes.
//
// Four things the match turns on, each settled by compiling rather than by
// argument:
//
//   1. -fp_contract off. Every lerp here emits fmuls and fadds as a pair where
//      the default contracts them into fmadds. configure.py already carries
//      cflags_rel_nofma for units built this way.
//   2. The slot index is unsigned. Signed, MWCC keeps the index itself in the
//      callee-saved register and rebuilds the scaled offset after every call;
//      unsigned, it keeps idx * 4, which is what the original does.
//   3. Order of the six leading locals. The anchor's three components take
//      f31 to f29 and the preserved position takes f28 to f26, which follows
//      from reading the anchor first, and eye has to be three floats declared
//      after them rather than a Vec declared before, or it takes f31 to f29
//      itself.
//   4. A value read once and used twice needs a local. The delta block, the
//      pull block's z component and the tail's two writes through unk3C all
//      reload or reorder without one. look, on the other hand, must stay a Vec:
//      splitting it into three floats costs fourteen points.
//
// The pull factor is assigned inside the expression that first uses it, which
// is what puts the anchor read and its subtraction ahead of the division. Its
// two later uses need their subtraction in a local as well, or the multiply
// takes its operands in the other order.

typedef struct Vec {
	f32 x; // 0x00
	f32 y; // 0x04
	f32 z; // 0x08
} Vec;     // 0x0C

typedef struct Out {
	s32 unk00; // 0x00
	s32 unk04; // 0x04
	s32 unk08; // 0x08
	u8 unk0C[0x4];
	Vec unk10; // 0x10
	u8 unk1C[0x8];
	s32 unk24; // 0x24
	u8 unk28[0xC];
	Vec unk34; // 0x34
} Out;         // 0x40

typedef struct Cam {
	u8 unk00[0x8];
	s32 unk08; // 0x08
	u8 unk0C[0x8];
	s32 unk14;  // 0x14
	Vec unk18;  // 0x18
	Vec unk24;  // 0x24
	Vec unk30;  // 0x30
	Vec* unk3C; // 0x3C
	f32 unk40;  // 0x40
	f32 unk44;  // 0x44
	u8 unk48[0x4];
	u8 unk4C; // 0x4C
	u8 unk4D; // 0x4D
	u8 unk4E[0x2];
	f32 unk50; // 0x50
	f32 unk54; // 0x54
	s32 unk58; // 0x58
	f32 unk5C; // 0x5C
	f32 unk60; // 0x60
	f32 unk64; // 0x64
} Cam;         // 0x68

typedef struct Anchor {
	u8 unk00[0x40];
	Vec unk40; // 0x40
} Anchor;

typedef struct Slot {
	u8 unk00[0x44];
	s32 unk44; // 0x44
	u8 unk48[0xC];
	s32 unk54; // 0x54
} Slot;

typedef struct Focus {
	Vec unk00; // 0x00
	u8 unk0C[0x18];
	Vec unk24; // 0x24
} Focus;

extern "C" s32 lbl_8042C1FC;
extern "C" Focus* lbl_8042C208;
extern "C" Anchor* lbl_80303DC8[];
extern "C" Slot* lbl_803EC350[];

extern "C" void fn_801990E0(Vec* dst, Vec* src);
extern "C" f32 fn_801991B4(Vec* v);

extern "C" void cameraSlotUpdate(Out* out, Cam* cam)
{
	u32 idx        = lbl_8042C1FC;
	Anchor* anchor = lbl_80303DC8[idx];
	f32 targetX    = anchor->unk40.x;
	f32 targetY    = anchor->unk40.y;
	f32 targetZ    = anchor->unk40.z;
	f32 keepX      = cam->unk3C->x;
	f32 keepY      = cam->unk3C->y;
	f32 keepZ      = cam->unk3C->z;
	f32 eyeX;
	f32 eyeY;
	f32 eyeZ;
	f32 rate = 0.1f;
	s32 frames;
	Vec delta;
	Vec away;
	Vec look;

	cam->unk44 = cam->unk44 + rate * (cam->unk5C - cam->unk44);
	cam->unk40 = cam->unk40 + rate * (cam->unk60 - cam->unk40);
	cam->unk50 = cam->unk50 + rate * (cam->unk64 - cam->unk50);

	{
		Vec* at = cam->unk3C;
		f32 aty;
		f32 atz;

		delta.x = targetX - (aty = at->y, atz = at->z, at->x);
		delta.y = targetY - aty;
		delta.z = targetZ - atz;
	}

	if (delta.x * delta.x + delta.y * delta.y + delta.z * delta.z > 0.01f) {
		fn_801990E0(&delta, &delta);
	}

	eyeX = targetX + cam->unk40 * delta.x;
	eyeY = targetY + cam->unk40 * delta.y;
	eyeZ = targetZ + cam->unk40 * delta.z;

	if (cam->unk58 == 0) {
		eyeY = eyeY + cam->unk44;
	}

	cam->unk18.x = eyeX - targetX;
	cam->unk18.y = eyeY - targetY;
	cam->unk18.z = eyeZ - targetZ;

	frames     = cam->unk14 - 1;
	cam->unk14 = frames;

	if (cam->unk14 < 0) {
		cam->unk14 = 0;
	} else {
		eyeX = eyeX + 0.016666668f * ((f32)cam->unk14 * (lbl_8042C208->unk00.x - eyeX));
		eyeY = eyeY + 0.016666668f * ((f32)cam->unk14 * (lbl_8042C208->unk00.y - eyeY));
		eyeZ = eyeZ + 0.016666668f * ((f32)cam->unk14 * (lbl_8042C208->unk00.z - eyeZ));
	}

	away.x = cam->unk3C->x - targetX;
	away.y = cam->unk3C->y - targetY;
	away.z = cam->unk3C->z - targetZ;

	if (fn_801991B4(&away) < 10.0f) {
		look.x = targetX + cam->unk24.x;
		look.y = targetY + cam->unk24.y;
		look.z = targetZ + cam->unk24.z;
	} else {
		f32 pull;
		Vec* at = cam->unk3C;

		look.x = at->x
		    + (targetX - at->x)
		        * (pull = 1.0f - (cam->unk50 * (f32)lbl_803EC350[idx]->unk54) / 30.0f);
		{
			f32 aty = at->y;
			f32 dy  = targetY - aty;

			look.y = aty + dy * pull;
		}
		{
			f32 atz = at->z;

			f32 dz = targetZ - atz;

			look.z = atz + dz * pull;
		}

		look.y = look.y + cam->unk54 * (1.0f - (f32)lbl_803EC350[idx]->unk54 / 30.0f);

		cam->unk24.x = cam->unk3C->x - targetX;
		cam->unk24.y = cam->unk3C->y - targetY;
		cam->unk24.z = cam->unk3C->z - targetZ;
	}

	if (lbl_803EC350[idx]->unk44 != 0) {
		lbl_803EC350[idx]->unk54 = lbl_803EC350[idx]->unk54 - 1;

		if (lbl_803EC350[idx]->unk54 <= 0) {
			lbl_803EC350[idx]->unk54 = 0;
		}
	} else {
		lbl_803EC350[idx]->unk54 = lbl_803EC350[idx]->unk54 + 1;

		if (lbl_803EC350[idx]->unk54 >= 30) {
			lbl_803EC350[idx]->unk54 = 30;
		}
	}

	if (cam->unk08 > 10) {
		out->unk34.x = lbl_8042C208->unk24.x + 0.2f * (look.x - lbl_8042C208->unk24.x);
		out->unk34.y = lbl_8042C208->unk24.y + 0.2f * (look.y - lbl_8042C208->unk24.y);
		out->unk34.z = lbl_8042C208->unk24.z + 0.2f * (look.z - lbl_8042C208->unk24.z);
	} else {
		out->unk34.x = look.x;
		out->unk34.y = look.y;
		out->unk34.z = look.z;
	}

	out->unk10.x = eyeX;
	out->unk10.y = eyeY;
	out->unk10.z = eyeZ;

	{
		Vec* at = cam->unk3C;

		at->x = keepX;
		at->y = keepY;
		at->z = keepZ;
	}

	{
		Vec* at = cam->unk3C;

		cam->unk30.x = at->x;
		cam->unk30.y = at->y;
		cam->unk30.z = at->z;
	}

	out->unk00 = 0;
	out->unk24 = 0;
	out->unk04 = (s8)cam->unk4C;
	out->unk08 = (s8)cam->unk4D;
}
