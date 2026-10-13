#include "types.h"

// The checkpoint's Disp (checkpointDisp here). With the game not paused and
// the post's model loaded, it lights the post by the placement's light bits,
// turns the model's frame by the post's angles (Y, then X, then Z) and moves it
// to the post, draws it, and then draws the star once it is fully shown
// (checkpointStarDispOpaque, rel/checkpoint_star_disp_opaque.cpp, inlined).

typedef struct RpClump RpClump;
typedef struct RpAtomic RpAtomic;

typedef struct RwV3d {
	f32 x, y, z;
} RwV3d;

typedef struct RwFrame {
	u8 unk00[0x10];
	u8 modelling[0x40]; // 0x10
} RwFrame;

typedef struct CheckpointModel {
	u8 unk00[0x4];
	RwFrame* frame; // 0x04
} CheckpointModel;

typedef struct CheckpointStar {
	s32 state;      // 0x00
	u8 unk04[0x2C]; // 0x04
	RpClump* clump; // 0x30
	u8 unk34[0x44]; // 0x34
	f32 alpha;      // 0x78
} CheckpointStar;

typedef struct CheckpointPlacement {
	u8 unk00[0x18];
	u32 flag; // 0x18
} CheckpointPlacement;

typedef struct Checkpoint {
	u8 unk00[0x28];
	CheckpointPlacement* placement; // 0x28
	u8 unk2C[0xC];
	RwV3d pos;            // 0x38
	s32 angX;             // 0x44
	s32 angY;             // 0x48
	s32 angZ;             // 0x4C
	CheckpointStar* star; // 0x50
} Checkpoint;

class CLIGHT
{
public:
	u8 unk000[0x4BE];
	s8 regular; // 0x4BE

	void SetCurrentNum(s8 num);
	void SetLightRegular(s8 num);
};

extern "C" CLIGHT lbl_802D5E80;
extern "C" u8* lbl_8042C180;
extern "C" CheckpointModel* checkpointModel;
extern "C" const RwV3d AxisX;
extern "C" const RwV3d AxisY;
extern "C" const RwV3d AxisZ;
extern "C" const f32 checkpointOne[1];

extern "C" RpAtomic* checkpointBind(RpAtomic* atomic, void* data);
extern "C" f32 fn_800D7B00(s32 angle);
extern "C" f32 fn_800D7AE4(s32 angle);
extern "C" void fn_80195790(void* matrix, const RwV3d* axis, f32 oneMinusCos, f32 sin, s32 combine);
extern "C" void fn_8019EB94(RwFrame* frame, RwV3d* translation, s32 combine);
extern "C" void fn_8014FFBC(void* clump, RpAtomic* (*callback)(RpAtomic*, void*), void* data);
extern "C" void fn_8014FF2C(void* clump);

static inline void checkpointStarDispOpaque(CheckpointStar* star)
{
	if ((s8)lbl_8042C180[0x20] == 0) {
		if (star->alpha >= checkpointOne[0]) {
			lbl_802D5E80.SetCurrentNum(0x10);
			lbl_802D5E80.SetLightRegular(lbl_802D5E80.regular);
			u8 alpha = 0xFF;
			fn_8014FFBC(star->clump, checkpointBind, &alpha);
			fn_8014FF2C(star->clump);
		}
	}
}

extern "C" void checkpointDisp(Checkpoint* object)
{
	if ((s8)lbl_8042C180[0x20] == 0 && checkpointModel != NULL) {
		RwFrame* frame;
		f32 sin;

		lbl_802D5E80.SetCurrentNum(((object->placement->flag & 0x1C0000) >> 18) + 4);
		CLIGHT* light = &lbl_802D5E80;
		light->SetLightRegular(light->regular);
		frame = checkpointModel->frame;
		sin   = fn_800D7B00(object->angY);
		fn_80195790(frame->modelling, &AxisY, checkpointOne[0] - fn_800D7AE4(object->angY), sin, 0);
		sin = fn_800D7B00(object->angX);
		fn_80195790(frame->modelling, &AxisX, checkpointOne[0] - fn_800D7AE4(object->angX), sin, 2);
		sin = fn_800D7B00(object->angZ);
		fn_80195790(frame->modelling, &AxisZ, checkpointOne[0] - fn_800D7AE4(object->angZ), sin, 2);
		fn_8019EB94(frame, &object->pos, 2);
		fn_8014FF2C(checkpointModel);
		lbl_802D5E80.SetCurrentNum(0x10);
		lbl_802D5E80.SetLightRegular(light->regular);
		checkpointStarDispOpaque(object->star);
	}
}
