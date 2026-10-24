#include "types.h"

// TObjSwitchPushPull::CheckCollision (the PS2 build's name, by its place in the
// PS2 order; pushPullSwitchCheckCollision here). Something solid against the
// switch (a touch of kind 1) turns both shapes off. Otherwise the shapes are a
// push wall (kinds 4 and 6) and, while a player pushes or pulls it, the
// switch moves by the player's push along its direction, within its travel;
// a stuck push turns the shapes off. Each passing of a notch plays a click
// (0x1008 going in, 0x1009 coming out). A push switch (kind 1) pushed all the
// way in, or a pull switch (kind 0) pulled all the way out, is done (state
// 3, sound 0x100A): its shapes go off and its set object learns it.

typedef struct RwV3d {
	f32 x, y, z;
} RwV3d;

typedef struct PushPullShapes {
	u8 kind0; // 0x00
	u8 unk01[0x2F];
	u8 kind1; // 0x30
	u8 unk31[0x3];
	u32 flags1; // 0x34
} PushPullShapes;

typedef struct PushPullHitLink {
	u8 unk0[0x4];
	void* colli; // 0x04
} PushPullHitLink;

struct PushPullBodyData {
	u8 unk00[0x2C];
};

// the pushing player's body; its vtable pointer sits at 0x2C
struct PushPullBody : public PushPullBodyData {
	virtual void vslot0();
	virtual void vslot1();
	virtual void vslot2();
	virtual void vslot3();
	virtual void Stop();
	virtual void vslot5();
	virtual void GetPush(RwV3d* push, s32 arg);
};

struct PushPullPusherData {
	PushPullBody* body; // 0x00
};

// the player pushing; its vtable pointer sits at 0x04
struct PushPullPusher : public PushPullPusherData {
	virtual void vslot0();
	virtual void vslot1();
	virtual void vslot2();
	virtual f32 Along(RwV3d* push);
};

typedef struct PushPullSetData {
	u8 unk00[0x10];
	s32 done; // 0x10
} PushPullSetData;

typedef struct PushPullFrame {
	u8 unk00[0x30];
	PushPullSetData* data; // 0x30
} PushPullFrame;

typedef struct PushPullSwitch {
	u8 unk00[0x28];
	PushPullFrame* frame;   // 0x28, the set object's
	u8 unk2C[0x4];          // 0x2C
	u8 colli[0x10];         // 0x30
	PushPullShapes* shapes; // 0x40
	u8 unk44[0x74];         // 0x44
	s32 state;              // 0xB8
	u8 unkBC[0x4];          // 0xBC
	s8 kind;                // 0xC0
	u8 unkC1[0x1B];         // 0xC1
	f32 travel;             // 0xDC
	u8 unkE0[0x18];         // 0xE0
	PushPullPusher* pusher; // 0xF8
} PushPullSwitch;

extern "C" u8 lbl_8042C1A4[];
extern "C" void* lbl_8042C388;
extern "C" const f32 pushPullSwitchZero[1];
extern "C" const f32 pushPullSwitchDepth[1];

extern "C" void fn_80021824(void* collision);
extern "C" PushPullHitLink* fn_80020BD8(void* colli, s32 kind);
extern "C" f32 fn_801991B4(RwV3d* v);
extern "C" void fn_800B52E8(void* sound, s32 id, s32 a, s32 b);

// whether something touched the switch with the given kind
static inline void* pushPullTouch(PushPullSwitch* object, s32 kind)
{
	PushPullHitLink* link = fn_80020BD8(object->colli, kind);

	return link != NULL ? link->colli : NULL;
}

#pragma opt_common_subs off
extern "C" void pushPullSwitchCheckCollision(PushPullSwitch* object)
{
	fn_80021824(lbl_8042C1A4);
	if (pushPullTouch(object, 1) != NULL) {
		object->shapes->kind0 = 0;
		object->shapes->kind1 = 0;
		return;
	}
	if (object->shapes != NULL) {
		object->shapes->kind0 = 4;
		object->shapes->kind1 = 6;
	}
	if (object->pusher == NULL) {
		return;
	}
	RwV3d push;

	object->pusher->body->GetPush(&push, 0);
	if (fn_801991B4(&push) <= pushPullSwitchZero[0]) {
		return;
	}
	f32 along = object->pusher->Along(&push);
	f32 old   = object->travel;
	object->pusher->body->Stop();
	object->travel += along;
	if (object->travel < pushPullSwitchZero[0]) {
		object->travel = pushPullSwitchZero[0];
	}
	// the depth read again for the store (a volatile read through the same
	// address)
	const f32* depth;
	if (object->travel > *(depth = pushPullSwitchDepth)) {
		object->travel = *(const volatile f32*)depth;
	}
	if (old == object->travel && object->shapes != NULL && pushPullSwitchZero[0] != along) {
		object->shapes->kind0 = 0;
		object->shapes->kind1 = 0;
	}
	if (along > pushPullSwitchZero[0] && (s32)old % 4 < 2 && (s32)object->travel % 4 >= 2) {
		if (lbl_8042C388 != NULL) {
			fn_800B52E8(lbl_8042C388, 0x1008, 0, 0);
		}
	} else if (along < pushPullSwitchZero[0] && (s32)old % 4 >= 2 && (s32)object->travel % 4 < 2) {
		if (lbl_8042C388 != NULL) {
			fn_800B52E8(lbl_8042C388, 0x1009, 0, 0);
		}
	}
	s8 kind = object->kind;
	if (kind == 1 && object->travel >= pushPullSwitchDepth[0]) {
		object->state = 3;
		if (lbl_8042C388 != NULL) {
			fn_800B52E8(lbl_8042C388, 0x100A, 0x20, 0);
		}
	} else if (kind == 0 && object->travel <= pushPullSwitchZero[0]) {
		object->state = 3;
		if (lbl_8042C388 != NULL) {
			fn_800B52E8(lbl_8042C388, 0x100A, 0x20, 0);
		}
	}
	if (object->state == 3) {
		object->shapes->flags1 |= 0x10;
		object->shapes->kind0 = 0;
		object->shapes->kind1 = 0;
		if (object->frame->data != NULL) {
			object->frame->data->done = 2;
		}
	}
}
#pragma opt_common_subs reset
