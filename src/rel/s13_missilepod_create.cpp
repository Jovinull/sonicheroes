#include "game/effect/eff_bomb.h"
#include "game/setObj.h"

// s13MissilepodCreate, the editor record factory for TObjS13MissilePod (the
// class name its constructor stores) in stage13D. It is a real new-expression
// of the class; rel/sample1_create.cpp has the long form of the allocation.
//
// The constructor builds its clump through the module's loader (fn_9_75A80,
// as rel/s13_partition_class.inc does) and takes the module's shape for its
// collision block (its third base). When the shape is there it gives it a
// moving-and-turning reactor (Construct_CCL_REACTOR_TRANSROTS) and sets the
// reactor's parameter to no move and the placement's angles plus the shape's.
// Then, with a clump, it turns the frame by the placement's Y and Z angles and
// moves it to the placement's position.

struct RwFrame;

// The part of a RenderWare frame used here: its modelling matrix.
struct MissilepodFrame {
	u8 unk00[0x10];
	u8 modelling[0x40]; // 0x10
};

// the collision reactor (game/c_colli_react.h, whose CCL_INFO clashes with
// eff_bomb.h's): only the virtuals up to SetParameter are called here
class CCL_REACTOR
{
public:
	s32 countReffered;
	s32 react;
	RwV3d vecParam;
	sAngle angParam;
	RwV3d vecDirection;

	virtual ~CCL_REACTOR();
	virtual s32 React(RwV3d*, sAngle*);
	virtual f32 GetDotProductOfDirection(RwV3d*);
	virtual void SetParameter(RwV3d*, sAngle*);
};

extern "C" char* CL_TObjS13MissilePod;
extern "C" u32 s13MissilepodModels[];
extern "C" CCL_INFO s13MissilepodCclInfo;
extern "C" const RwV3d s13MissilepodNoMove;
extern "C" const f32 s13MissilepodOne[1];
extern "C" const RwV3d AxisY;
extern "C" const RwV3d AxisZ;
extern "C" TObject* lbl_8042C110;
extern "C" void fn_9_75A80(void* info, s32 index, RpClump** clump, s32 flags);
extern "C" f32 fn_800D7B00(s32 angle);
extern "C" f32 fn_800D7AE4(s32 angle);
extern "C" void fn_80195790(void* matrix, const RwV3d* axis, f32 oneMinusCos, f32 sin, s32 combine);
extern "C" void fn_8019E880(void* frame);
extern "C" void fn_8019EB94(void* frame, RwV3d* translation, s32 combine);
s32 Construct_CCL_REACTOR_TRANSROTS(CCL_INFO* info);

class TObjS13MissilePod : public TObject, public TObjSetObj, public C_COLLI
{
public:
	RpClump* clump; // 0xB8

	TObjS13MissilePod(TObject* parent)
	    : TObject(parent)
	{
		ClassName = CL_TObjS13MissilePod;
		DispTime  = 0xBC;

		fn_9_75A80(s13MissilepodModels, 0, &clump, 0);
		Init(&s13MissilepodCclInfo, 1, 4);
		if (info != NULL) {
			Construct_CCL_REACTOR_TRANSROTS(info);
			if (info->pReactor != NULL) {
				RwV3d move = s13MissilepodNoMove;
				sAngle ang = ObjParam->setData.ang;

				ang.x += info->angx;
				ang.y += info->angy;
				ang.z += info->angz;
				info->pReactor->SetParameter(&move, &ang);
			}
		}
		if (clump != NULL) {
			MissilepodFrame* frame = *(MissilepodFrame**)((u8*)clump + 4);
			f32 sine;

			sine = fn_800D7B00(ObjParam->setData.ang.y);
			fn_80195790(frame->modelling, &AxisY,
			    s13MissilepodOne[0] - fn_800D7AE4(ObjParam->setData.ang.y), sine, 0);
			fn_8019E880(frame);
			sine = fn_800D7B00(ObjParam->setData.ang.z);
			fn_80195790(frame->modelling, &AxisZ,
			    s13MissilepodOne[0] - fn_800D7AE4(ObjParam->setData.ang.z), sine, 2);
			fn_8019E880(frame);
			fn_8019EB94(frame, &ObjParam->setData.pos, 2);
		}
	}
	virtual ~TObjS13MissilePod();
};

extern "C" void s13MissilepodCreate(void)
{
	new TObjS13MissilePod(lbl_8042C110);
}
