#include "types.h"

// TObjBobsleigh::SetArrowPosition (the PS2 build's name), the same in the
// twelve stage modules that carry the bobsleigh: for each other team's sled
// marker model, the marker of the sled's own team is put where the sled
// (lifted by bobsleighArrowLift) lies in the camera's space, and both of its
// frames take the camera's rotation, so the arrow faces the viewer.

typedef struct RpClump RpClump;

typedef struct RwV3d {
	f32 x;
	f32 y;
	f32 z;
} RwV3d;

typedef struct RwMatrixTag {
	RwV3d right; // 0x00
	u32 flags;   // 0x0C
	RwV3d up;    // 0x10
	u32 pad1C;   // 0x1C
	RwV3d at;    // 0x20
	u32 pad2C;   // 0x2C
	RwV3d pos;   // 0x30
	u32 pad3C;   // 0x3C
} RwMatrixTag;

typedef struct RwFrame {
	u8 unk00[0x98];
	struct RwFrame* child; // 0x98
} RwFrame;

typedef struct BobsleighArrowModel {
	u8 unk0[0x4];
	RwFrame* frame; // 0x04
} BobsleighArrowModel;

typedef struct BobsleighCamera {
	RwV3d pos; // 0x00
	s32 angX;  // 0x0C
	s32 angY;  // 0x10
	s32 angZ;  // 0x14
} BobsleighCamera;

typedef struct Bobsleigh {
	u8 unk000[0x104];
	RwV3d pos; // 0x104
	u8 unk110[0x8C];
	s32 team; // 0x19C
} Bobsleigh;

extern "C" s32 lbl_8042C1FC;
extern "C" BobsleighCamera* lbl_8042C208;
extern "C" BobsleighArrowModel* s31bobDummyModels[2];
extern "C" const f32 bobsleighOne[1];
extern "C" f32 bobsleighArrowLift;
extern "C" const RwV3d AxisX;
extern "C" const RwV3d AxisY;
extern "C" const RwV3d AxisZ;

extern "C" f32 fn_800D7B00(s32 angle);
extern "C" f32 fn_800D7AE4(s32 angle);
extern "C" void fn_80195790(
    RwMatrixTag* matrix, const RwV3d* axis, f32 oneMinusCos, f32 sin, s32 combine);
extern "C" void fn_80196050(RwMatrixTag* matrix, const RwV3d* translation, s32 combine);
extern "C" void fn_80195B5C(RwMatrixTag* out, const RwMatrixTag* in);
extern "C" RwMatrixTag* fn_8019E8EC(RwFrame* frame);
extern "C" void fn_8019941C(RwV3d* out, const RwV3d* in, s32 count, const RwMatrixTag* matrix);
void CalcPoint(const RwMatrixTag* matrix, const RwV3d* in, RwV3d* out);

extern "C" void SetArrowPosition__13TObjBobsleighFv(Bobsleigh* object)
{
	s32 i;

	for (i = 0; i < 2; i++) {
		if (s31bobDummyModels[i] != NULL && i != lbl_8042C1FC && object->team == i) {
			BobsleighCamera* camera = lbl_8042C208;
			RwMatrixTag inverse;
			RwMatrixTag view;
			RwV3d local;
			RwV3d target;
			RwFrame* frame;
			RwMatrixTag* matrix;

			fn_80196050(&view, &camera->pos, 0);
			fn_80195790(&view, &AxisY, bobsleighOne[0] - fn_800D7AE4(camera->angY),
			    fn_800D7B00(camera->angY), 1);
			fn_80195790(&view, &AxisX, bobsleighOne[0] - fn_800D7AE4(camera->angX),
			    fn_800D7B00(camera->angX), 1);
			fn_80195790(&view, &AxisZ, bobsleighOne[0] - fn_800D7AE4(camera->angZ),
			    fn_800D7B00(camera->angZ), 1);
			fn_80195B5C(&inverse, &view);
			target.x = object->pos.x;
			target.y = object->pos.y;
			target.z = object->pos.z;
			target.y += bobsleighArrowLift;
			CalcPoint(&inverse, &target, &local);

			frame         = s31bobDummyModels[i]->frame->child;
			matrix        = fn_8019E8EC(frame);
			matrix->right = view.right;
			matrix->up    = view.up;
			matrix->at    = view.at;
			fn_8019941C(&matrix->pos, &local, 1, &view);

			matrix        = fn_8019E8EC(frame->child);
			matrix->right = view.right;
			matrix->up    = view.up;
			matrix->at    = view.at;
			fn_8019941C(&matrix->pos, &local, 1, &view);
		}
	}
}
