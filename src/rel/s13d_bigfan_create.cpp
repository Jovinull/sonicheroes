#include "game/effect/eff_bomb.h"
#include "game/setObj.h"

// s13dBigfanCreate, the editor record factory for TObjS13BigFan (the class
// name its constructor stores) in stage13D. It is a real new-expression of the
// class; rel/sample1_create.cpp has the long form of the allocation.
//
// The constructor takes the fan from the module's table through fn_9_75D2C
// and, with it, the animation after it (+0x14) through fn_9_757C4, starting
// the time at zero (the edit minimum), then the fan's base as its second clump
// and the module's shape for its collision block (its third base). While the
// editor is on, a set data with no size gets 1. Each clump's frame is turned
// by the placement's Y angle and moved to the placement's position, as
// rel/s13_design_pipe_create.cpp does.

// The part of a RenderWare frame used here: its modelling matrix.
struct BigFanFrame {
	u8 unk00[0x10];
	u8 modelling[0x40]; // 0x10
};

// the set data's parameters (rel/s13d_bigfan_edit.cpp)
struct S13dBigfanParams {
	f32 size; // 0x00
};

extern "C" char* CL_TObjS13BigFan;
extern "C" u8 s13dBigfanModels[];
extern "C" CCL_INFO s13dBigfanCclInfo;
extern "C" const f32 s13dBigfanEditMin[1];
extern "C" const f32 s13dBigfanOne[1];
extern "C" const RwV3d AxisY;
extern "C" TObject* lbl_8042C110;
extern "C" void fn_9_75D2C(void* table, s16 index, RpClump** clump, void* frame);
extern "C" void fn_9_757C4(RpClump* clump, void* animation, void* state);
extern "C" void fn_8003BF04(C_COLLI* colli, CCL_INFO* info, int count, u8 kind);
extern "C" f32 fn_800D7B00(s32 angle);
extern "C" f32 fn_800D7AE4(s32 angle);
extern "C" void fn_80195790(void* matrix, const RwV3d* axis, f32 oneMinusCos, f32 sin, s32 combine);
extern "C" void fn_8019E880(void* frame);
extern "C" void fn_8019EB94(void* frame, RwV3d* translation, s32 combine);

// C_COLLI::InitShare (fn_8003BF04), as rel/yajirusi_class.inc has it
inline void InitShare(C_COLLI& colli, CCL_INFO* info, int count, u8 kind)
{
	fn_8003BF04(&colli, info, count, kind);
}

class TObjS13BigFan : public TObject, public TObjSetObj, public C_COLLI
{
public:
	RpClump* clump; // 0xB8
	RpClump* base;  // 0xBC
	f32 time;       // 0xC0
	u8 state[4];    // 0xC4

	TObjS13BigFan(TObject* parent)
	    : TObject(parent)
	{
		S13dBigfanParams* params = (S13dBigfanParams*)ObjParam->setData.setBuffer;

		ClassName = CL_TObjS13BigFan;
		DispTime  = 0xC8;

		fn_9_75D2C(s13dBigfanModels, 0, &clump, NULL);
		if (clump != NULL) {
			fn_9_757C4(clump, s13dBigfanModels + 0x14, state);
			time = s13dBigfanEditMin[0];
		}
		fn_9_75D2C(s13dBigfanModels, 1, &base, NULL);
		InitShare(*this, &s13dBigfanCclInfo, 1, 4);
		if (OnEdit()) {
			if (s13dBigfanEditMin[0] == params->size) {
				params->size = s13dBigfanOne[0];
			}
		}
		if (clump != NULL) {
			BigFanFrame* frame = *(BigFanFrame**)((u8*)clump + 4);
			f32 sine;

			sine = fn_800D7B00(ObjParam->setData.ang.y);
			fn_80195790(frame->modelling, &AxisY,
			    s13dBigfanOne[0] - fn_800D7AE4(ObjParam->setData.ang.y), sine, 0);
			fn_8019E880(frame);
			fn_8019EB94(frame, &ObjParam->setData.pos, 2);
		}
		if (base != NULL) {
			BigFanFrame* frame = *(BigFanFrame**)((u8*)base + 4);
			f32 sine;

			sine = fn_800D7B00(ObjParam->setData.ang.y);
			fn_80195790(frame->modelling, &AxisY,
			    s13dBigfanOne[0] - fn_800D7AE4(ObjParam->setData.ang.y), sine, 0);
			fn_8019E880(frame);
			fn_8019EB94(frame, &ObjParam->setData.pos, 2);
		}
	}
	virtual ~TObjS13BigFan();
};

extern "C" void s13dBigfanCreate(void)
{
	new TObjS13BigFan(lbl_8042C110);
}
