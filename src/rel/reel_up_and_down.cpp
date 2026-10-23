#include "types.h"

// TObjReel::ReelUpAndDown (the PS2 build's name, by its place in the PS2
// order; reelUpAndDown here). Winding in (state 4) the speed eases towards
// -2.5 with the winch sound playing until the reel is in, then the reel
// bounces (state 5: the speed reversed and damped); letting out (state 2) the
// speed eases towards 2.5 until the reel reaches its length, then it bounces
// (state 3). A bouncing reel goes back to winding when it moves too far, and
// once the speed has died it rests at its end (state 1 when nothing holds it).

#include "MSL_C/math.h"

typedef struct Reel {
	u8 unk00[0xB8];
	s32 state;   // 0xB8
	u8 unkBC;    // 0xBC
	s8 holder;   // 0xBD
	u8 unkBE[2]; // 0xBE
	f32 current; // 0xC0
	u8 unkC4[4]; // 0xC4
	f32 length;  // 0xC8
	f32 speed;   // 0xCC
} Reel;

extern "C" void* lbl_8042C388;
extern "C" const f32 reelZero[1];
extern "C" const f32 reelHeightScale[1];
extern "C" const f32 reelWindSpeed[1];
extern "C" const f32 reelEase[1];
extern "C" const f32 reelBounce[1];
extern "C" const f32 reelUnwindSpeed[1];

extern "C" void fn_800B4A38(void* sound, s32 id, void* pos, void* owner, s32 a, s32 b, s32 c);
extern "C" void fn_800B52E8(void* sound, s32 id, s32 a, s32 b);
f32 AdjustFloat(f32 value, f32 target, f32 rate);

extern "C" void reelUpAndDown(Reel* object)
{
	switch (object->state) {
		case 4:
			if (object->current > reelZero[0]) {
				if (lbl_8042C388 != NULL) {
					fn_800B4A38(lbl_8042C388, 0x1041, NULL, object, 2, 0, 2);
				}
				object->speed = AdjustFloat(object->speed, reelWindSpeed[0], reelEase[0]);
			} else {
				if (lbl_8042C388 != NULL) {
					fn_800B52E8(lbl_8042C388, 0x1042, 0x60, 0);
				}
				object->state = 5;
				object->speed = reelBounce[0] * -object->speed;
			}
			object->current = object->current + object->speed;
			break;
		case 5: {
			if (object->current > reelUnwindSpeed[0]) {
				object->state = 4;
				break;
			}
			if (reelZero[0] == object->speed) {
				object->current = reelZero[0];
				if (object->holder == -1) {
					object->state = 1;
				}
				break;
			}
			double magnitude = __fabs(object->speed);
			object->speed    = reelBounce[0] * (f32)magnitude;
			if (object->speed < reelHeightScale[0]) {
				object->speed = reelZero[0];
			}
			if (object->current > reelZero[0]) {
				object->speed = -object->speed;
			}
			object->current = object->current + object->speed;
			break;
		}
		case 2:
			if (object->current < object->length) {
				if (lbl_8042C388 != NULL) {
					fn_800B4A38(lbl_8042C388, 0x1041, NULL, object, 2, 0, 2);
				}
				object->speed = AdjustFloat(object->speed, reelUnwindSpeed[0], reelEase[0]);
			} else {
				if (lbl_8042C388 != NULL) {
					fn_800B52E8(lbl_8042C388, 0x1042, 0x60, 0);
				}
				object->state = 3;
				object->speed = reelBounce[0] * -object->speed;
			}
			object->current = object->current + object->speed;
			break;
		case 3: {
			if (object->current < object->length - reelUnwindSpeed[0]) {
				object->state = 2;
				break;
			}
			if (reelZero[0] == object->speed) {
				object->current = object->length;
				if (object->holder == -1) {
					object->state = 1;
				}
				break;
			}
			double magnitude = __fabs(object->speed);
			object->speed    = reelBounce[0] * (f32)magnitude;
			if (object->speed < reelHeightScale[0]) {
				object->speed = reelZero[0];
			}
			if (object->current > object->length) {
				object->speed = -object->speed;
			}
			object->current = object->current + object->speed;
			break;
		}
	}
}
