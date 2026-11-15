// Camera events of the players (HYPOTHESIS; names inferred): lbl_803EB3F8 holds the active event of
// each player, with a value at 0x0, flags, an end callback, a camera pose and distance and the
// camera it drives.
#include "game/matrix.h"

struct CameraPose80132958 {
	RwV3d eye;    // 0x0
	RwV3d unkC;   // 0xC
	RwV3d unk18;  // 0x18
	RwV3d target; // 0x24
	RwV3d unk30;  // 0x30
};

struct CameraContext80132958 {
	CameraPose80132958 pose; // 0x0
	f32 distance;            // 0x3C
};

struct Camera80132958 {
	u8 pad0[0x10];
	RwV3d eye; // 0x10
	u8 pad1C[0x34 - 0x1C];
	RwV3d target; // 0x34
};

struct CameraEvent80132958 {
	f32 value; // 0x0
	u8 pad4[0x20 - 0x4];
	u32 flags;               // 0x20
	void (*onEnd)(void);     // 0x24
	CameraPose80132958 pose; // 0x28
	f32 distance;            // 0x64
	Camera80132958* camera;  // 0x68
};

extern "C" {
extern s32 lbl_8042C1FC;
extern void* lbl_8042C1F8;
extern CameraContext80132958* lbl_8042C208;
extern CameraEvent80132958* lbl_803EB3F8[];
extern f32 lbl_8042EF38;
s32 fn_8004E608(void* heap);
void fn_8004DE10(void* heap, s32 slot);
void fn_8004DEC0(void* heap, s32 slot, s32 value);
void fn_8004D99C(void* heap);
void fn_8004CDBC(void* heap, s32 value);

// Returns the value of the player's event, or lbl_8042EF38 without one.
f32 fn_80132958(s32 player)
{
	CameraEvent80132958* event = lbl_803EB3F8[player];

	if (event == 0) {
		return lbl_8042EF38;
	}
	return event->value;
}

// Sets the value of the player's event; returns whether there is one.
s32 fn_80132980(s32 player, f32 value)
{
	CameraEvent80132958* event = lbl_803EB3F8[player];

	if (event == 0) {
		return 0;
	}
	event->value = value;
	return 1;
}

// Ends the current player's event once the camera slot is in mode 13: runs its end callback (flag
// 0x20), leaves mode 13 and either sets the slot's value to 8 (flag 0x8) or, with flag 0x80, resets
// it and hands the event's pose and distance to its camera and the camera context lbl_8042C208;
// then drops the event. Always updates the slots (fn_8004D99C), and for player 0 runs fn_8004CDBC.
void fn_801329AC(void)
{
	CameraEvent80132958* event = lbl_803EB3F8[lbl_8042C1FC];
	Camera80132958* camera;

	if (event == 0) {
		return;
	}
	camera = event->camera;
	if (camera == 0) {
		return;
	}
	if (fn_8004E608(lbl_8042C1F8) == 13) {
		if ((event->flags & 0x20) && event->onEnd != 0) {
			event->onEnd();
		}
		fn_8004DE10(lbl_8042C1F8, 13);
		if (event->flags & 0x8) {
			fn_8004DEC0(lbl_8042C1F8, fn_8004E608(lbl_8042C1F8), 8);
		} else if (event->flags & 0x80) {
			fn_8004DEC0(lbl_8042C1F8, fn_8004E608(lbl_8042C1F8), 0);
			camera->eye    = event->pose.eye;
			camera->target = event->pose.target;
			{
				CameraContext80132958* context = lbl_8042C208;
				context->pose                  = event->pose;
				context->distance              = event->distance;
			}
		}
		lbl_803EB3F8[lbl_8042C1FC] = 0;
	}
	fn_8004D99C(lbl_8042C1F8);
	if (lbl_8042C1FC == 0) {
		fn_8004CDBC(lbl_8042C1F8, 0);
	}
}
}
