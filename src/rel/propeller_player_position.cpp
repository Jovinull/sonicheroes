#include "types.h"

// TObjPropeller::setPlayerPosition (the PS2 build's name, by its place in the
// PS2 order; propellerSetPlayerPosition here). While carrying (state 2), once
// the propeller has risen all the way, or the team's pad lets go (buttons 0x100
// or 0x200), or the leader is hurt or falling (states 10 and 0x2C), the
// player drops (state 3, 120 frames) with no speed and is let go; otherwise
// the player holding on is kept under the handle, facing it, and the
// collision is made solid for the player.

typedef struct RwV3d {
	f32 x, y, z;
} RwV3d;

typedef struct sAngle {
	s32 x, y, z;
} sAngle;

typedef struct PropellerShape {
	u8 unk0[0x4];
	u32 flags; // 0x04
} PropellerShape;

typedef struct PropellerPad {
	u8 unk00[0x48];
	u32 buttons; // 0x48
} PropellerPad;  // 0x4C

typedef struct PropellerPads {
	u8 unk00[0x8];
	PropellerPad pads[4]; // 0x08
} PropellerPads;

typedef struct PropellerTeam {
	u8 unk000[0x3B];
	s8 leader; // 0x3B
} PropellerTeam;

typedef struct PropellerPlayerState {
	s16 state; // 0x0
} PropellerPlayerState;

typedef struct Propeller {
	u8 unk00[0x40];
	PropellerShape* shape; // 0x40, the collision's
	u8 unk44[0x74];        // 0x44
	union {                // 0xB8
		u8 replace;        // the OBJ_ReplacePlayer part, which has no fields
		s32 state;
	};
	s8 holder;        // 0xBC
	u8 unkBD[0x4B];   // 0xBD
	sAngle handleAng; // 0x108
	u8 unk114[0x18];  // 0x114
	RwV3d handlePos;  // 0x12C
	u8 unk138[0x4];   // 0x138
	f32 rise;         // 0x13C
	u8 unk140[0x8];   // 0x140
	s32 wait;         // 0x148
	u8 unk14C[0x14];  // 0x14C
	s32 team;         // 0x160
} Propeller;

extern "C" PropellerPads lbl_8029BBD0;
extern "C" s32 lbl_802408F8[];
extern "C" PropellerTeam* lbl_80303DC8[];
extern "C" PropellerPlayerState* lbl_802AD090[];
extern "C" s32 propellerDropTime;
extern "C" const f32 propellerOne[1];
extern "C" const f32 propellerZeroSpin[1];

extern "C" void fn_800E0E98(s32 player, f32 x, f32 y, f32 z);
extern "C" void objSetPlayerHandlingPosition__17OBJ_ReplacePlayerFiUcP5RwV3dP6sAngle(
    void* replace, s32 player, u8 flags, RwV3d* pos, sAngle* ang);

extern "C" void propellerSetPlayerPosition(Propeller* object)
{
	object->shape->flags &= ~0x10;
	switch (object->state) {
		case 0:
		case 1:
			break;
		case 2:
			if (object->rise >= propellerOne[0]
			    || (lbl_8029BBD0.pads[lbl_802408F8[object->team]].buttons & 0x200)
			    || (lbl_8029BBD0.pads[lbl_802408F8[object->team]].buttons & 0x100)
			    || lbl_802AD090[lbl_80303DC8[object->team]->leader]->state == 10
			    || lbl_802AD090[lbl_80303DC8[object->team]->leader]->state == 0x2C) {
				// the one read again through a pointer taken inside the comparison
				const f32* one;
				if (object->rise >= *(one = propellerOne)) {
					object->rise = *one;
				}
				object->state = 3;
				object->wait  = propellerDropTime;
				if (object->holder != -1) {
					fn_800E0E98(object->holder, propellerZeroSpin[0], propellerZeroSpin[0],
					    propellerZeroSpin[0]);
				}
				object->holder = -1;
			} else if (object->holder != -1) {
				sAngle ang;

				ang.x = object->handleAng.x;
				ang.y = 0x4000 - object->handleAng.y;
				ang.z = object->handleAng.z;
				objSetPlayerHandlingPosition__17OBJ_ReplacePlayerFiUcP5RwV3dP6sAngle(
				    &object->replace, object->holder, 0, &object->handlePos, &ang);
				object->shape->flags |= 0x10;
			}
			break;
		case 3:
			break;
	}
}
