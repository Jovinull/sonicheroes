#include "types.h"

// TObjTarget::Rotate (the PS2 build's name, by its place in the PS2 order;
// targetRotate here). A target of kind 0 or 1 spins: running away (state 3)
// it speeds up to its full speed; hit (states 5 and 7) it does too while its
// glow fades and, once it has been hit long enough, sparks every 15 frames.
// Otherwise a fast spin slows to its rest speed, and a slow one turns on to
// the next whole turn and stops there. The spin stays within a turn.

typedef struct RwV3d {
	f32 x, y, z;
} RwV3d;

typedef struct sAngle {
	s32 x, y, z;
} sAngle;

typedef struct Target {
	u8 unk00[0xB8];
	s32 state;     // 0xB8
	s8 kind;       // 0xBC
	u8 unkBD[0x1]; // 0xBD
	s16 time;      // 0xBE
	u8 unkC0[0x8]; // 0xC0
	RwV3d pos;     // 0xC8
	s32 angX;      // 0xD4
	s32 angY;      // 0xD8
	s32 angZ;      // 0xDC
	f32 spin;      // 0xE0
	f32 speed;     // 0xE4
	f32 glow;      // 0xE8
} Target;

extern "C" u8* lbl_8042C180;
extern "C" const f32 targetOne[1];
extern "C" const f32 targetZero[1];
extern "C" const f32 targetFullSpeed[1];
extern "C" const f32 targetFullTurn[1];
extern "C" const f32 targetGlowFade[1];
extern "C" const f32 targetRestSpeed[1];

f32 AdjustFloat(f32 value, f32 target, f32 rate);
extern "C" void fn_8006298C(s32 kind, RwV3d* pos, sAngle* ang);

extern "C" void targetRotate(Target* object)
{
	if (object->kind == 0 || object->kind == 1) {
		switch (object->state) {
			case 3:
				object->speed = AdjustFloat(object->speed, targetFullSpeed[0], targetOne[0]);
				object->spin += object->speed;
				while (object->spin >= targetFullTurn[0]) {
					object->spin -= targetFullTurn[0];
				}
				break;
			case 5:
			case 7:
				object->speed = AdjustFloat(object->speed, targetFullSpeed[0], targetOne[0]);
				object->spin += object->speed;
				while (object->spin >= targetFullTurn[0]) {
					object->spin -= targetFullTurn[0];
				}
				object->glow -= targetGlowFade[0];
				// the zero read through a pointer taken inside the comparison loads
				// after the glow and is the register stored
				const f32* zero;
				if (object->glow < *(zero = targetZero)) {
					object->glow = *zero;
				}
				if (object->time > 30 && *(s32*)(lbl_8042C180 + 0x30) % 15 == 0) {
					sAngle ang;

					ang.x = ang.z = 0;
					ang.y         = object->angY;
					fn_8006298C(0, &object->pos, &ang);
				}
				break;
			default:
				if (object->speed <= targetRestSpeed[0]) {
					if (targetZero[0] != object->spin) {
						object->spin
						    = AdjustFloat(object->spin, targetFullTurn[0], targetRestSpeed[0]);
						if (targetFullTurn[0] == object->spin) {
							object->speed = object->spin = targetZero[0];
						}
					}
				} else {
					object->speed = AdjustFloat(object->speed, targetRestSpeed[0], targetOne[0]);
					object->spin += object->speed;
				}
				while (object->spin >= targetFullTurn[0]) {
					object->spin -= targetFullTurn[0];
				}
				break;
		}
	}
}
