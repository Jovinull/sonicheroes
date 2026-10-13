#include "types.h"

// Two TObjBobsleigh helpers right after its Exec, both with no caller left:
// - bobsleighS08ColliFlag (the name is ours): in stage 9 it finds the
//   S08BOB COLLI_OBJECT task (class 0x743) and returns the first word of its
//   work, 0 without one.
// - TObjBobsleigh::SetPositionLauncher (the PS2 build's name): with the
//   launcher model (0x314, flag 0x364) it moves the model's frame to the
//   launcher's position and turns it by its Z, X and Y angles.

typedef struct RwV3d {
	f32 x, y, z;
} RwV3d;

struct RwMatrixTag {
	u8 data[0x40];
};

typedef struct RwFrame {
	u8 unk00[0x10];
	RwMatrixTag modelling; // 0x10
} RwFrame;

typedef struct RpClump {
	u8 unk00[0x4];
	RwFrame* frame; // 0x04
} RpClump;

typedef struct GameState {
	u8 unk00[0x2C];
	s32 stage; // 0x2C
} GameState;

typedef struct RinoColTask RinoColTask;
struct RinoColTask {
	u8 unk00[0x28];
	u16 classId; // 0x28
	u8 unk2A[0x6];
	s32* work; // 0x30
	u8 unk34[0x4];
	RinoColTask* next; // 0x38
};

typedef struct RinoColTaskLists {
	u8 unk00[0x30];
	RinoColTask* lists[1]; // 0x30
} RinoColTaskLists;

typedef struct Bobsleigh {
	u8 unk000[0x138];
	RwV3d launcherPos; // 0x138
	s32 launcherAngX;  // 0x144
	s32 launcherAngY;  // 0x148
	s32 launcherAngZ;  // 0x14C
	u8 unk150[0x1C4];
	RpClump* launcher; // 0x314
	u8 unk318[0x4C];
	s32 hasLauncher; // 0x364
} Bobsleigh;

extern "C" GameState lbl_8029C310;
extern "C" RinoColTaskLists* lbl_8042C298;
extern "C" const f32 bobsleighOne[1];
extern "C" const RwV3d AxisX;
extern "C" const RwV3d AxisY;
extern "C" const RwV3d AxisZ;

extern "C" f32 fn_800D7B00(s32 angle);
extern "C" f32 fn_800D7AE4(s32 angle);
extern "C" void fn_80195790(
    RwMatrixTag* matrix, const RwV3d* axis, f32 oneMinusCos, f32 sin, s32 combine);
extern "C" void fn_8019EB94(RwFrame* frame, RwV3d* translation, s32 combine);

extern "C" s32 bobsleighS08ColliFlag(void)
{
	RinoColTask* task;

	if (lbl_8029C310.stage != 9) {
		return 0;
	}
	for (task = lbl_8042C298->lists[0]; task != NULL; task = task->next) {
		if (task->classId == 0x743) {
			if (task->work == NULL) {
				return 0;
			}
			return *task->work;
		}
	}
	return 0;
}

extern "C" void SetPositionLauncher__13TObjBobsleighFv(Bobsleigh* object)
{
	if (object->hasLauncher != 0) {
		RwFrame* frame = object->launcher->frame;

		fn_8019EB94(frame, &object->launcherPos, 0);
		fn_80195790(&frame->modelling, &AxisZ, bobsleighOne[0] - fn_800D7AE4(object->launcherAngZ),
		    fn_800D7B00(object->launcherAngZ), 1);
		fn_80195790(&frame->modelling, &AxisX, bobsleighOne[0] - fn_800D7AE4(object->launcherAngX),
		    fn_800D7B00(object->launcherAngX), 1);
		fn_80195790(&frame->modelling, &AxisY, bobsleighOne[0] - fn_800D7AE4(object->launcherAngY),
		    fn_800D7B00(object->launcherAngY), 1);
	}
}
