#include "game/effect/eff_bomb.h"
#include "game/setObj.h"

// s14WallSideCreate, the editor record factory for TObjS14WallSide (the
// class name its constructor stores) in stage13D. It is a real new-expression
// of the class; rel/sample1_create.cpp has the long form of the allocation.
//
// The constructor takes the two walls through fn_9_75908 with the light set
// the placement's flags pick, as rel/s14_railend_sign_create.cpp does. With
// the first wall (and then with the second too), each frame is first set to
// the wall's offset, the set data's size to the left for the first and to the
// right for the second, then turned by the placement's Y, X and Z angles and
// moved to the placement's position.

// The part of a RenderWare frame used here: its modelling matrix.
struct WallSideFrame {
	u8 unk00[0x10];
	u8 modelling[0x40]; // 0x10
};

// the set data's parameters (rel/s14_wall_side_edit.cpp)
struct S14WallSideParams {
	f32 size; // 0x00
};

extern "C" char* CL_TObjS14WallSide;
extern "C" const RwV3d s14WallSideOffsetL;
extern "C" const RwV3d s14WallSideOffsetR;
extern "C" u8 s14WallSideModels[];
extern "C" const f32 s14WallSideOne[1];
extern "C" const RwV3d AxisX;
extern "C" const RwV3d AxisY;
extern "C" const RwV3d AxisZ;
extern "C" TObject* lbl_8042C110;
extern "C" void fn_9_75908(void* table, s16 index, s8 lightSet, RpClump** clump, void* frame);
extern "C" f32 fn_800D7B00(s32 angle);
extern "C" f32 fn_800D7AE4(s32 angle);
extern "C" void fn_80195790(void* matrix, const RwV3d* axis, f32 oneMinusCos, f32 sin, s32 combine);
extern "C" void fn_8019E880(void* frame);
extern "C" void fn_8019EB94(void* frame, RwV3d* translation, s32 combine);

class TObjS14WallSide : public TObject, public TObjSetObj
{
public:
	RpClump* clump;  // 0x30
	RpClump* clump2; // 0x34

	TObjS14WallSide(TObject* parent)
	    : TObject(parent)
	{
		ClassName = CL_TObjS14WallSide;
		DispTime  = 0x38;

		f32 sine;

		u32 flag = *(volatile u32*)&ObjParam->setData.condition.Flag;
		fn_9_75908(s14WallSideModels, 0, ((flag & 0x1C0000) >> 18) + 4, &clump, NULL);
		flag = *(volatile u32*)&ObjParam->setData.condition.Flag;
		fn_9_75908(s14WallSideModels, 1, ((flag & 0x1C0000) >> 18) + 4, &clump2, NULL);
		S14WallSideParams* params = (S14WallSideParams*)ObjParam->setData.setBuffer;

		if (clump != NULL) {
			WallSideFrame* frame = *(WallSideFrame**)((u8*)clump + 4);

			RwV3d left = s14WallSideOffsetL;

			left.x = -params->size;
			fn_8019EB94(frame, &left, 0);
			sine = fn_800D7B00(ObjParam->setData.ang.y);
			fn_80195790(frame->modelling, &AxisY,
			    s14WallSideOne[0] - fn_800D7AE4(ObjParam->setData.ang.y), sine, 2);
			fn_8019E880(frame);
			sine = fn_800D7B00(ObjParam->setData.ang.x);
			fn_80195790(frame->modelling, &AxisX,
			    s14WallSideOne[0] - fn_800D7AE4(ObjParam->setData.ang.x), sine, 2);
			fn_8019E880(frame);
			sine = fn_800D7B00(ObjParam->setData.ang.z);
			fn_80195790(frame->modelling, &AxisZ,
			    s14WallSideOne[0] - fn_800D7AE4(ObjParam->setData.ang.z), sine, 2);
			fn_8019E880(frame);
			fn_8019EB94(frame, &ObjParam->setData.pos, 2);
			if (clump2 != NULL) {
				frame = *(WallSideFrame**)((u8*)clump2 + 4);

				RwV3d right = s14WallSideOffsetR;

				right.x = params->size;
				fn_8019EB94(frame, &right, 0);
				sine = fn_800D7B00(ObjParam->setData.ang.y);
				fn_80195790(frame->modelling, &AxisY,
				    s14WallSideOne[0] - fn_800D7AE4(ObjParam->setData.ang.y), sine, 2);
				fn_8019E880(frame);
				sine = fn_800D7B00(ObjParam->setData.ang.x);
				fn_80195790(frame->modelling, &AxisX,
				    s14WallSideOne[0] - fn_800D7AE4(ObjParam->setData.ang.x), sine, 2);
				fn_8019E880(frame);
				sine = fn_800D7B00(ObjParam->setData.ang.z);
				fn_80195790(frame->modelling, &AxisZ,
				    s14WallSideOne[0] - fn_800D7AE4(ObjParam->setData.ang.z), sine, 2);
				fn_8019E880(frame);
				fn_8019EB94(frame, &ObjParam->setData.pos, 2);
			}
		}
	}
	virtual ~TObjS14WallSide();
};

extern "C" void s14WallSideCreate(void)
{
	new TObjS14WallSide(lbl_8042C110);
}
