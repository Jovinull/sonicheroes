#include "types.h"

// TObjBobsleigh::SetCameraPosition (the PS2 build's name): finds the sled's
// place on the merged path at its blended speed and keeps the path's angles;
// builds the path frame there and sets the team's camera record: its base (the
// module's camera offset through the frame in a race or in stage 13, the path
// point itself otherwise), its angles (after tilting the frame by the race or
// normal pitch) and its distance.

typedef struct RwV3d {
	f32 x, y, z;
} RwV3d;

struct RwMatrixTag {
	u8 data[0x40];
};

typedef struct sAngle {
	s32 x, y, z;
} sAngle;

typedef struct GameState {
	u8 unk00[0x2C];
	s32 stage; // 0x2C
} GameState;

typedef struct BobsleighPlayerWork {
	u8 unk00[0x1C];
	sAngle angle; // 0x1C
	u8 unk28[0xC];
	RwV3d base;        // 0x34
	f32 distance;      // 0x40
} BobsleighPlayerWork; // 0x44

typedef struct Bobsleigh {
	u8 unk000[0x168];
	s32 pathPoint; // 0x168
	f32 pathRate;  // 0x16C
	f32 pathSpeed; // 0x170
	u8 unk174[0x28];
	s32 team; // 0x19C
	u8 unk1A0[0x6C];
	sAngle pathAngle; // 0x20C
	u8 unk218[0x148];
	s32 race; // 0x360
	u8 unk364[0x10];
	u8 merge[0x4]; // 0x374 (MergeRoadData)
} Bobsleigh;

extern "C" GameState lbl_8029C310;
extern "C" BobsleighPlayerWork lbl_803EA4E8[];
extern "C" f32 bobsleighSpeedBlend;
extern "C" f32 bobsleighCameraHeight;
extern "C" f32 bobsleighCameraBack;
extern "C" s32 bobsleighCameraRacePitch;
extern "C" s32 bobsleighCameraPitch;
extern "C" f32 bobsleighCameraRaceDistance;
extern "C" f32 bobsleighCameraDistance;
extern "C" const f32 bobsleighBaseSpeed[1];
extern "C" const f32 bobsleighZero[1];
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
void GetRotZXY(RwMatrixTag* matrix, s32* x, s32* y, s32* z);
extern "C" void CalcDoubleMergePathPos__13TObjBobsleighFP13MergeRoadDataPiPfPfffR5RwV3dR6sAngle(
    Bobsleigh* object, void* merge, s32* point, f32* rate, f32* speed, f32 a, f32 b, RwV3d* pos,
    sAngle* angle);

extern "C" void SetCameraPosition__13TObjBobsleighFv(Bobsleigh* object)
{
	RwMatrixTag matrix;
	RwV3d pos;
	sAngle pathAngle;
	RwV3d offset;
	sAngle angle;
	f32 speed;
	f32 base;
	f32 diff;

	base     = bobsleighBaseSpeed[0];
	diff     = object->pathSpeed - base;
	speed    = base + diff * bobsleighSpeedBlend;
	offset.x = bobsleighZero[0];
	offset.y = bobsleighCameraHeight;
	offset.z = bobsleighCameraBack;
	CalcDoubleMergePathPos__13TObjBobsleighFP13MergeRoadDataPiPfPfffR5RwV3dR6sAngle(object,
	    object->merge, &object->pathPoint, &object->pathRate, &speed, bobsleighZero[0],
	    bobsleighZero[0], &pos, &pathAngle);
	object->pathAngle = pathAngle;
	fn_80196050(&matrix, &pos, 0);
	fn_80195790(&matrix, &AxisZ, bobsleighOne[0] - fn_800D7AE4(object->pathAngle.z),
	    fn_800D7B00(object->pathAngle.z), 1);
	fn_80195790(&matrix, &AxisX, bobsleighOne[0] - fn_800D7AE4(object->pathAngle.x),
	    fn_800D7B00(object->pathAngle.x), 1);
	fn_80195790(&matrix, &AxisY, bobsleighOne[0] - fn_800D7AE4(object->pathAngle.y),
	    fn_800D7B00(object->pathAngle.y), 1);
	if (object->race != 0 || lbl_8029C310.stage == 13) {
		CalcPoint(&matrix, &offset, &lbl_803EA4E8[object->team].base);
	} else {
		lbl_803EA4E8[object->team].base = pos;
	}
	if (object->race != 0 || lbl_8029C310.stage == 13) {
		fn_80195790(&matrix, &AxisX, bobsleighOne[0] - fn_800D7AE4(bobsleighCameraRacePitch),
		    fn_800D7B00(bobsleighCameraRacePitch), 1);
	} else {
		fn_80195790(&matrix, &AxisX, bobsleighOne[0] - fn_800D7AE4(bobsleighCameraPitch),
		    fn_800D7B00(bobsleighCameraPitch), 1);
	}
	GetRotZXY(&matrix, &angle.x, &angle.y, &angle.z);
	lbl_803EA4E8[object->team].angle = angle;
	if (object->race != 0 || lbl_8029C310.stage == 13) {
		lbl_803EA4E8[object->team].distance = bobsleighCameraRaceDistance;
	} else {
		lbl_803EA4E8[object->team].distance = bobsleighCameraDistance;
	}
}
