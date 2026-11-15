// Starts the free camera (HYPOTHESIS; names inferred): takes its position from the player object
// lbl_8042C248 (0x1C4), clears its counters and, while the camera button (0x1000) of the current
// player's pad is held, offsets its angles by the stick (dead zone of 5000 in 8.8 fixed point,
// scaled by 1/64) from the camera context lbl_8042C208 and moves its distance (0x40) by the
// zoom buttons, by 10 with button 0x400 held or 2 otherwise; the distance stays at least 5.
// Then enters mode 3 and resets the current camera slot's value.
#include "game/matrix.h"

struct Pad80131168 {
	u32 held; // 0x0
	u8 pad4[0x14 - 0x4];
	s16 stickX; // 0x14
	s16 stickY; // 0x16
	u8 pad18[0x4C - 0x18];
};

// Pad state; the per-pad rows start at 0x48.
struct PadSystem80131168 {
	u8 pad0[0x48];
	Pad80131168 pads[4]; // 0x48
};

struct CameraContext80131168 {
	u8 pad0[0xC];
	s32 angleX; // 0xC
	s32 angleY; // 0x10
	u8 pad14[0x3C - 0x14];
	f32 distance; // 0x3C
};

struct Player80131168 {
	u8 pad0[0x1C4];
	RwV3d position; // 0x1C4
};

struct FreeCamera80131168 {
	s32 mode; // 0x0
	s32 unk4; // 0x4
	s32 unk8; // 0x8
	s32 unkC; // 0xC
	u8 pad10[0x1C - 0x10];
	s32 angleX; // 0x1C
	s32 angleY; // 0x20
	s32 unk24;  // 0x24
	u8 pad28[0x34 - 0x28];
	RwV3d position; // 0x34
	f32 distance;   // 0x40
};

extern "C" {
extern s32 lbl_8042C1FC;
extern Player80131168* lbl_8042C248;
extern CameraContext80131168* lbl_8042C208;
extern void* lbl_8042C1F8;
extern PadSystem80131168 lbl_8029BBD0;
extern s32 lbl_802408F8[];
s32 fn_8004E608(void* heap);
s32 fn_8004E564(void* heap, s32 slot);
void fn_8004DEC0(void* heap, s32 slot, s32 value);

void fn_80131168(FreeCamera80131168* camera)
{
	s32 player = lbl_8042C1FC;

	camera->position = lbl_8042C248->position;
	camera->unk24    = 0;
	camera->unk4     = 0;
	camera->unk8     = 0;
	camera->unkC     = 0;
	if (lbl_8029BBD0.pads[lbl_802408F8[player]].held & 0x1000) {
		s32 x = lbl_8029BBD0.pads[lbl_802408F8[player]].stickX << 8;
		s32 y = lbl_8029BBD0.pads[lbl_802408F8[player]].stickY << 8;
		u32 held;

		if (x > -5000 && x < 5000) {
			x = 0;
		}
		if (y > -5000 && y < 5000) {
			y = 0;
		}
		camera->angleY = x / 64 + lbl_8042C208->angleY;
		camera->angleX = y / 64 + lbl_8042C208->angleX;
		held           = lbl_8029BBD0.pads[lbl_802408F8[player]].held;
		if (held & 0x400) {
			if (held & 0x40) {
				camera->distance = 10.0f + lbl_8042C208->distance;
			} else if (held & 0x20) {
				camera->distance = lbl_8042C208->distance - 10.0f;
			}
		} else {
			if (held & 0x40) {
				camera->distance = 2.0f + lbl_8042C208->distance;
			} else if (held & 0x20) {
				camera->distance = lbl_8042C208->distance - 2.0f;
			}
		}
	}
	if (camera->distance < 5.0f) {
		camera->distance = 5.0f;
	}
	camera->mode = 3;
	if (fn_8004E564(lbl_8042C1F8, fn_8004E608(lbl_8042C1F8)) != 0) {
		fn_8004DEC0(lbl_8042C1F8, fn_8004E608(lbl_8042C1F8), 0);
	}
}
}
