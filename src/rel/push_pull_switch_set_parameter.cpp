#include "types.h"

// TObjSwitchPushPull::SetParameter (pushPullSwitchSetParameter here), the
// out-of-line copy nothing calls. It takes the placement's position, angles and
// kind, then the switch's state from the placement's work block, making the
// block (zeroed state) the first time. The handle starts pulled out or pushed in
// by kind and state: kind 0 is out while the state is 0, kind 1 the other way.

typedef struct RwV3d {
	f32 x, y, z;
} RwV3d;

typedef struct PushPullWork {
	u8 unk00[0x10];
	s32 state;  // 0x10
} PushPullWork; // 0x14

typedef struct PushPullSetData {
	RwV3d pos;          // 0x00
	s32 angX;           // 0x0C
	s32 angY;           // 0x10
	s32 angZ;           // 0x14
	u8 unk18[0x14];     // 0x18
	s8* params;         // 0x2C
	PushPullWork* work; // 0x30
} PushPullSetData;

typedef struct PushPullSwitch {
	u8 unk00[0x28];
	PushPullSetData* setdata; // 0x28
	u8 unk2C[0x90];
	s32 state; // 0xBC
	s8 kind;   // 0xC0
	u8 padC1[0x3];
	RwV3d pos; // 0xC4
	u8 unkD0[0xC];
	f32 travel; // 0xDC
	s32 angX;   // 0xE0
	s32 angY;   // 0xE4
	s32 angZ;   // 0xE8
} PushPullSwitch;

extern "C" const f32 pushPullSwitchZero[1];
extern "C" const f32 pushPullSwitchDepth[1];

extern "C" void pushPullSwitchSetParameter(PushPullSwitch* object)
{
	PushPullSetData* setdata = object->setdata;
	s8* params               = setdata->params;
	PushPullWork* work;

	object->pos.x = setdata->pos.x;
	object->pos.y = setdata->pos.y;
	object->pos.z = setdata->pos.z;
	setdata       = object->setdata;
	object->angX  = setdata->angX;
	object->angY  = setdata->angY;
	object->angZ  = setdata->angZ;
	object->kind  = params[0];

	work = object->setdata->work;
	if (work != NULL) {
		object->state = work->state;
	} else {
		work                  = new PushPullWork;
		object->setdata->work = work;
		work->state = object->state = 0;
	}

	switch (object->kind) {
		case 0:
			if (object->state == 0) {
				object->travel = pushPullSwitchDepth[0];
			} else {
				object->travel = pushPullSwitchZero[0];
			}
			break;
		case 1:
			if (object->state == 0) {
				object->travel = pushPullSwitchZero[0];
			} else {
				object->travel = pushPullSwitchDepth[0];
			}
			break;
	}
}
