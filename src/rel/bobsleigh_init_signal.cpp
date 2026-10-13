#include "types.h"

// TObjBobsleigh::InitStartSignal and InitGoalSignal (the PS2 build's names):
// each turns a matrix at the launcher (start) or at the goal by its angles,
// takes the module's signal offset through it and creates the signal there
// (texture set 0 for the start, 1 for the goal), keeping it in the sled.

typedef struct RwV3d {
	f32 x, y, z;
} RwV3d;

struct RwMatrixTag {
	u8 data[0x40];
};

typedef struct sAngle {
	s32 x, y, z;
} sAngle;

struct TObjectBase {
	char* ClassName; // 0x00
	u8 unk04[0x14];
};

extern "C" void* lbl_8042C148;
extern "C" void* Malloc__9THeapCtrlFUi(void* heap, u32 size);

class TObject : public TObjectBase
{
public:
	TObject(TObject* parent);
	virtual ~TObject();
	u8 unk1C[0xC];

	static void* operator new(unsigned long size)
	{
		return Malloc__9THeapCtrlFUi(lbl_8042C148, size);
	}
}; // 0x28

enum ENUM_BOB_SIGNAL_TEX { BOB_SIGNAL_TEX_START, BOB_SIGNAL_TEX_GOAL };

class TObjBobsleighSignal : public TObject
{
public:
	TObjBobsleighSignal(TObject* parent, RwV3d* pos, sAngle* ang, ENUM_BOB_SIGNAL_TEX tex);
	u8 unk28[0xD0];
}; // 0xF8

typedef struct Bobsleigh {
	u8 unk000[0x138];
	RwV3d launcherPos;  // 0x138
	sAngle launcherAng; // 0x144
	u8 unk150[0x158];
	RwV3d goalPos;  // 0x2A8
	sAngle goalAng; // 0x2B4
	u8 unk2C0[0x94];
	TObjBobsleighSignal* startSignal; // 0x354
	TObjBobsleighSignal* goalSignal;  // 0x358
} Bobsleigh;

extern "C" const RwV3d bobsleighStartSignalOffset;
extern "C" const RwV3d bobsleighGoalSignalOffset;
extern "C" const f32 bobsleighOne[1];
extern "C" const RwV3d AxisX;
extern "C" const RwV3d AxisY;
extern "C" const RwV3d AxisZ;

extern "C" f32 fn_800D7B00(s32 angle);
extern "C" f32 fn_800D7AE4(s32 angle);
extern "C" void fn_80195790(
    RwMatrixTag* matrix, const RwV3d* axis, f32 oneMinusCos, f32 sin, s32 combine);
extern "C" void fn_80196050(RwMatrixTag* matrix, RwV3d* translation, s32 combine);
void CalcPoint(const RwMatrixTag* matrix, const RwV3d* point, RwV3d* out);

extern "C" void InitStartSignal__13TObjBobsleighFv(Bobsleigh* object)
{
	RwMatrixTag matrix;
	RwV3d pos;

	fn_80196050(&matrix, &object->launcherPos, 0);
	fn_80195790(&matrix, &AxisZ, bobsleighOne[0] - fn_800D7AE4(object->launcherAng.z),
	    fn_800D7B00(object->launcherAng.z), 1);
	fn_80195790(&matrix, &AxisX, bobsleighOne[0] - fn_800D7AE4(object->launcherAng.x),
	    fn_800D7B00(object->launcherAng.x), 1);
	fn_80195790(&matrix, &AxisY, bobsleighOne[0] - fn_800D7AE4(object->launcherAng.y),
	    fn_800D7B00(object->launcherAng.y), 1);
	RwV3d offset = bobsleighStartSignalOffset;
	CalcPoint(&matrix, &offset, &pos);
	object->startSignal = new TObjBobsleighSignal(
	    (TObject*)object, &pos, &object->launcherAng, BOB_SIGNAL_TEX_START);
}

extern "C" void InitGoalSignal__13TObjBobsleighFv(Bobsleigh* object)
{
	RwMatrixTag matrix;
	RwV3d pos;

	fn_80196050(&matrix, &object->goalPos, 0);
	fn_80195790(&matrix, &AxisY, bobsleighOne[0] - fn_800D7AE4(object->goalAng.y),
	    fn_800D7B00(object->goalAng.y), 1);
	fn_80195790(&matrix, &AxisX, bobsleighOne[0] - fn_800D7AE4(object->goalAng.x),
	    fn_800D7B00(object->goalAng.x), 1);
	fn_80195790(&matrix, &AxisZ, bobsleighOne[0] - fn_800D7AE4(object->goalAng.z),
	    fn_800D7B00(object->goalAng.z), 1);
	RwV3d offset = bobsleighGoalSignalOffset;
	CalcPoint(&matrix, &offset, &pos);
	object->goalSignal
	    = new TObjBobsleighSignal((TObject*)object, &pos, &object->goalAng, BOB_SIGNAL_TEX_GOAL);
}
