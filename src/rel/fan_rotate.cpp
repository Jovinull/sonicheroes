#include "types.h"

// TObjFan::Rotate (the PS2 build's name; fanRotate here), the out-of-line copy
// nothing calls. While the game runs
// and nothing of collision kind 0x13 is touching it, a fan of kind 0 or 1 eases
// its spin towards its strength (or to a stop when it does not spin) and turns
// its blades by it, wrapping the angle.

typedef struct ColliHit {
	u8 unk0[0x4];
	u32 touching; // 0x4
} ColliHit;

typedef struct Fan {
	u8 unk00[0x30];
	u8 colli[0x88]; // 0x30, a C_COLLI
	s32 spin;       // 0xB8
	s8 kind;        // 0xBC
	u8 unkBD[0x1B];
	f32 angle; // 0xD8
	f32 speed; // 0xDC
	u8 unkE0[0x8];
	f32 strength; // 0xE8
} Fan;

extern "C" u8* lbl_8042C180;
extern "C" const f32 fanSpinRate;
extern "C" const f32 fanSpinStep;
extern "C" const f32 fanFullTurn;
extern "C" const f32 fanStopSpeed;

extern "C" void fn_80021824(void* colli);
extern "C" ColliHit* fn_80020BD8(void* colli, s32 kind);
f32 AdjustFloat(f32 value, f32 target, f32 step);

extern "C" void fanRotate(Fan* fan)
{
	ColliHit* hit;

	if ((s8)lbl_8042C180[0x1F] != 0) {
		return;
	}
	fn_80021824(fan->colli);
	hit = fn_80020BD8(fan->colli, 0x13);
	if ((hit != NULL ? hit->touching : 0) != 0) {
		return;
	}
	if (fan->kind != 0 && fan->kind != 1) {
		return;
	}
	switch (fan->spin) {
		case 1:
			fan->speed = AdjustFloat(fan->speed, fanSpinRate * fan->strength, fanSpinStep);
			fan->angle += fan->speed;
			while (fan->angle >= fanFullTurn) {
				fan->angle -= fanFullTurn;
			}
			break;
		default:
			fan->speed = AdjustFloat(fan->speed, fanStopSpeed, fanSpinStep);
			fan->angle += fan->speed;
			while (fan->angle >= fanFullTurn) {
				fan->angle -= fanFullTurn;
			}
			break;
	}
}
