#include "types.h"

// TObjSwitchPushPull::SetPosition (pushPullSwitchSetPosition here). It turns
// the switch model by the placement's angles (Y, X, Z) and moves it to the
// switch. The handle's point (its travel along the model's Z) goes through the
// model's matrix into the switch's handle position, and the grandchild frame
// (the handle) is set there. The collision volume's points follow: the handle
// raised by the first offset, the reach worked out from that height, the handle
// one unit higher still, then its range is recomputed, the volume's direction is
// the model's Z axis and its depth what is left of the travel.
//
// Every turn works the frame's matrix address out again, as common
// subexpression elimination off gives.

typedef struct RwV3d {
	f32 x, y, z;
} RwV3d;

// The collision volume's shape object: a real virtual call (the slot is loaded
// into r12 through the object in r3). Its vtable pointer follows 0x2C bytes of
// data and the direction setter is the eighth virtual.
class PushPullVolume
{
public:
	u8 unk00[0x2C];
	virtual void vslot0();
	virtual void vslot1();
	virtual void vslot2();
	virtual void vslot3();
	virtual void vslot4();
	virtual void vslot5();
	virtual void vslot6();
	virtual void SetDirection(RwV3d* direction);
};

typedef struct PushPullColliInfo {
	u8 unk00[0x8];
	RwV3d top; // 0x08
	u8 unk14[0x8];
	f32 depth;              // 0x1C
	PushPullVolume* volume; // 0x20
	u8 unk24[0x14];
	RwV3d handle; // 0x38
	u8 unk44[0x2C];
	f32 reach2; // 0x70
	u8 unk74[0x4];
	f32 reach; // 0x78
	u8 unk7C[0x1C];
	RwV3d base; // 0x98
} PushPullColliInfo;

typedef struct PushPullModel {
	u8 unk00[0x4];
	void* frame; // 0x04
} PushPullModel;

typedef struct PushPullSwitch {
	u8 unk00[0x30];
	u8 colli[0x10];          // 0x30
	PushPullColliInfo* info; // 0x40
	u8 unk44[0x80];
	RwV3d pos;            // 0xC4
	RwV3d handlePos;      // 0xD0
	f32 travel;           // 0xDC
	s32 angX;             // 0xE0
	s32 angY;             // 0xE4
	s32 angZ;             // 0xE8
	PushPullModel* model; // 0xEC
} PushPullSwitch;

extern "C" const RwV3d AxisX;
extern "C" const RwV3d AxisY;
extern "C" const RwV3d AxisZ;
extern "C" const f32 pushPullSwitchZero[1];
extern "C" const f32 pushPullSwitchDepth[1];
extern "C" const f32 pushPullSwitchOne[1];
extern "C" const f32 pushPullSwitchTopOffset[1];
extern "C" const f32 pushPullSwitchReachScale[1];
extern "C" const f32 pushPullSwitchReachBias[1];

extern "C" f32 fn_800D7B00(s32 angle);
extern "C" f32 fn_800D7AE4(s32 angle);
extern "C" void fn_80195790(void* matrix, const RwV3d* axis, f32 oneMinusCos, f32 sin, s32 combine);
extern "C" void fn_8019EB94(void* frame, RwV3d* translation, s32 combine);
extern "C" void fn_8019941C(RwV3d* out, RwV3d* in, s32 count, void* matrix);
extern "C" void fn_8019947C(RwV3d* out, RwV3d* in, s32 count, void* matrix);
extern "C" void CalcRange__7C_COLLIFv(void* colli);
void* objRwFrameGetChildFrame(struct RwFrame* frame, struct RwFrame* after);

#pragma opt_common_subs off
extern "C" void pushPullSwitchSetPosition(PushPullSwitch* object)
{
	RwV3d point;
	RwV3d axis;
	void* frame = object->model->frame;
	f32 sin;
	f32 reach;

	sin = fn_800D7B00(object->angY);
	fn_80195790(
	    (u8*)frame + 0x10, &AxisY, pushPullSwitchOne[0] - fn_800D7AE4(object->angY), sin, 0);
	sin = fn_800D7B00(object->angX);
	fn_80195790(
	    (u8*)frame + 0x10, &AxisX, pushPullSwitchOne[0] - fn_800D7AE4(object->angX), sin, 2);
	sin = fn_800D7B00(object->angZ);
	fn_80195790(
	    (u8*)frame + 0x10, &AxisZ, pushPullSwitchOne[0] - fn_800D7AE4(object->angZ), sin, 2);
	fn_8019EB94(frame, &object->pos, 2);

	point.x = point.y = pushPullSwitchZero[0];
	point.z           = object->travel;
	fn_8019941C(&object->handlePos, &point, 1, (u8*)frame + 0x10);
	fn_8019EB94(objRwFrameGetChildFrame(
	                (struct RwFrame*)objRwFrameGetChildFrame((struct RwFrame*)frame, NULL), NULL),
	    &point, 0);

	point.z += pushPullSwitchTopOffset[0];
	object->info->top    = point;
	object->info->base   = point;
	reach                = pushPullSwitchReachScale[0] * point.z - pushPullSwitchReachBias[0];
	object->info->reach  = reach;
	object->info->reach2 = reach;
	point.z += pushPullSwitchOne[0];
	object->info->handle = point;
	CalcRange__7C_COLLIFv(object->colli);

	axis.y = axis.x = pushPullSwitchZero[0];
	axis.z          = pushPullSwitchOne[0];
	fn_8019947C(&axis, &axis, 1, (u8*)frame + 0x10);
	object->info->volume->SetDirection(&axis);
	object->info->depth = pushPullSwitchDepth[0] - object->travel;
}
#pragma opt_common_subs reset
