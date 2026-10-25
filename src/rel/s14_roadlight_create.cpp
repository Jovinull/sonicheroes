#include "game/effect/eff_bomb.h"
#include "game/setObj.h"

// s14RoadlightCreate, the editor record factory for TObjS14RoadLight (the
// class name its constructor stores) in stage13D. It is a real new-expression
// of the class; rel/sample1_create.cpp has the long form of the allocation.
//
// While the editor is on, a set data with no width or no depth gets 1. The
// constructor takes its model through fn_9_75908 with the light set the
// placement's flags pick, as rel/s14_koware_create.cpp does; with it, the
// frame is scaled by the width (X) and depth (Z), turned by the placement's
// Y, X and Z angles and moved to the placement's position. The light then
// shows unless the game's frame count is a multiple of 12.

// The part of a RenderWare frame used here: its modelling matrix.
struct RoadLightFrame {
	u8 unk00[0x10];
	u8 modelling[0x40]; // 0x10
};

// the set data's parameters
struct S14RoadlightParams {
	f32 width; // 0x00
	f32 depth; // 0x04
};

// the game: only its frame count is read here
struct S14RoadlightGame {
	u8 unk00[0x30];
	s32 frame; // 0x30
};

extern "C" char* CL_TObjS14RoadLight;
extern "C" u8 s14RoadlightModels[];
extern "C" const RwV3d s14RoadlightUnitScale;
extern "C" const f32 s14RoadlightEditMin[1];
extern "C" const f32 s14RoadlightOne[1];
extern "C" const RwV3d AxisX;
extern "C" const RwV3d AxisY;
extern "C" const RwV3d AxisZ;
extern "C" S14RoadlightGame* lbl_8042C180;
extern "C" TObject* lbl_8042C110;
extern "C" void fn_9_75908(void* table, s16 index, s8 lightSet, RpClump** clump, void* frame);
extern "C" f32 fn_800D7B00(s32 angle);
extern "C" f32 fn_800D7AE4(s32 angle);
extern "C" void fn_80195790(void* matrix, const RwV3d* axis, f32 oneMinusCos, f32 sin, s32 combine);
extern "C" void fn_8019E880(void* frame);
extern "C" void fn_8019EB94(void* frame, RwV3d* translation, s32 combine);
extern "C" void fn_8019EC30(void* frame, RwV3d* scale, s32 combine);
void objRpClumpForAllAtomicsToRender(RpClump* clump);
void objRpClumpForAllAtomicsToHide(RpClump* clump);

class TObjS14RoadLight : public TObject, public TObjSetObj
{
public:
	RpClump* clump; // 0x30

	TObjS14RoadLight(TObject* parent)
	    : TObject(parent)
	{
		ClassName = CL_TObjS14RoadLight;
		DispTime  = 0x34;

		S14RoadlightParams* params = (S14RoadlightParams*)ObjParam->setData.setBuffer;

		if (OnEdit()) {
			if (s14RoadlightEditMin[0] == params->width) {
				params->width = s14RoadlightOne[0];
			}
			if (s14RoadlightEditMin[0] == params->depth) {
				params->depth = s14RoadlightOne[0];
			}
		}

		u32 flag = *(volatile u32*)&ObjParam->setData.condition.Flag;
		fn_9_75908(s14RoadlightModels, 0, ((flag & 0x1C0000) >> 18) + 4, &clump, NULL);

		S14RoadlightParams* scaleParams = (S14RoadlightParams*)ObjParam->setData.setBuffer;

		if (clump != NULL) {
			RoadLightFrame* frame = *(RoadLightFrame**)((u8*)clump + 4);
			RwV3d scale           = s14RoadlightUnitScale;
			f32 sine;

			scale.x = scaleParams->width;
			scale.z = scaleParams->depth;
			fn_8019EC30(frame, &scale, 0);
			sine = fn_800D7B00(ObjParam->setData.ang.y);
			fn_80195790(frame->modelling, &AxisY,
			    s14RoadlightOne[0] - fn_800D7AE4(ObjParam->setData.ang.y), sine, 2);
			fn_8019E880(frame);
			sine = fn_800D7B00(ObjParam->setData.ang.x);
			fn_80195790(frame->modelling, &AxisX,
			    s14RoadlightOne[0] - fn_800D7AE4(ObjParam->setData.ang.x), sine, 2);
			fn_8019E880(frame);
			sine = fn_800D7B00(ObjParam->setData.ang.z);
			fn_80195790(frame->modelling, &AxisZ,
			    s14RoadlightOne[0] - fn_800D7AE4(ObjParam->setData.ang.z), sine, 2);
			fn_8019E880(frame);
			fn_8019EB94(frame, &ObjParam->setData.pos, 2);
		}
		if (lbl_8042C180->frame % 12 > 0) {
			objRpClumpForAllAtomicsToRender(clump);
		} else {
			objRpClumpForAllAtomicsToHide(clump);
		}
	}
	virtual ~TObjS14RoadLight();
};

extern "C" void s14RoadlightCreate(void)
{
	new TObjS14RoadLight(lbl_8042C110);
}
