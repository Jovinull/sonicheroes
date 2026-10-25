#include "game/effect/eff_bomb.h"
#include "game/setObj.h"

// s14dUfoCreate, the editor record factory for TObjS14UFO (the class name its
// constructor stores) in stage13D. It is a real new-expression of the class;
// rel/sample1_create.cpp has the long form of the allocation.
//
// It is rel/s13d_ufo_create.cpp's body, with the models taken through
// fn_9_75BB4 with the light set the placement's flags pick (as
// rel/s14_koware_create.cpp does with fn_9_75908). The constructor clears its
// time and takes its body and its second part from the module's table,
// starting each one's animation through fn_9_757C4 when the table has one.
// With the body (and then with the second part too), the frame is turned by
// the placement's Y, X and Z angles and moved to the placement's position;
// the second part is first turned about Z by the set data's angle. The
// module's shape goes to its collision block (its third base) last.
//
// The constructor is over MWCC's default inline size, and the retail has it
// inlined into the factory, so the unit raises the limit.

#pragma inline_max_size(2048)

// The part of a RenderWare frame used here: its modelling matrix.
struct UfoFrame {
	u8 unk00[0x10];
	u8 modelling[0x40]; // 0x10
};

// an animation entry of the module's table: its type (0 for none) first
struct UfoAnimation {
	s8 type; // 0x00
	u8 unk01[0x17];
}; // 0x18

// the module's table: two models, each followed by its animation
struct S14dUfoTable {
	u8 model0[0x14];         // 0x00
	UfoAnimation animation0; // 0x14
	u8 model1[0x14];         // 0x2C
	UfoAnimation animation1; // 0x40
};

// the set data's parameters
struct S14dUfoParams {
	s32 roll; // 0x00: the second part's angle about Z
};

extern "C" char* CL_TObjS14UFO;
extern "C" S14dUfoTable s14dUfoModels;
extern "C" CCL_INFO s14dUfoCclInfo;
extern "C" const f32 s14dUfoZero[1];
extern "C" const f32 s14dUfoOne[1];
extern "C" const RwV3d AxisX;
extern "C" const RwV3d AxisY;
extern "C" const RwV3d AxisZ;
extern "C" TObject* lbl_8042C110;
extern "C" void fn_9_75BB4(void* table, s16 index, s8 lightSet, RpClump** clump, void* frame);
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

class TObjS14UFO : public TObject, public TObjSetObj, public C_COLLI
{
public:
	f32 time;        // 0xB8
	RpClump* clump;  // 0xBC
	RpClump* clump2; // 0xC0

	TObjS14UFO(TObject* parent)
	    : TObject(parent)
	{
		ClassName = CL_TObjS14UFO;
		DispTime  = 0xC4;
		time      = s14dUfoZero[0];
		u32 flag  = *(volatile u32*)&ObjParam->setData.condition.Flag;
		fn_9_75BB4(&s14dUfoModels, 0, ((flag & 0x1C0000) >> 18) + 4, &clump, NULL);
		S14dUfoTable* table = &s14dUfoModels;
		if (table->animation0.type != 0) {
			fn_9_757C4(clump, &table->animation0, NULL);
		}
		flag = *(volatile u32*)&ObjParam->setData.condition.Flag;
		fn_9_75BB4(&s14dUfoModels, 1, ((flag & 0x1C0000) >> 18) + 4, &clump2, NULL);
		table = &s14dUfoModels;
		if (table->animation1.type != 0) {
			fn_9_757C4(clump2, &table->animation1, NULL);
		}

		S14dUfoParams* params = (S14dUfoParams*)ObjParam->setData.setBuffer;

		if (clump != NULL) {
			UfoFrame* frame = *(UfoFrame**)((u8*)clump + 4);
			f32 sine;

			sine = fn_800D7B00(ObjParam->setData.ang.y);
			fn_80195790(frame->modelling, &AxisY,
			    s14dUfoOne[0] - fn_800D7AE4(ObjParam->setData.ang.y), sine, 0);
			fn_8019E880(frame);
			sine = fn_800D7B00(ObjParam->setData.ang.x);
			fn_80195790(frame->modelling, &AxisX,
			    s14dUfoOne[0] - fn_800D7AE4(ObjParam->setData.ang.x), sine, 2);
			fn_8019E880(frame);
			sine = fn_800D7B00(ObjParam->setData.ang.z);
			fn_80195790(frame->modelling, &AxisZ,
			    s14dUfoOne[0] - fn_800D7AE4(ObjParam->setData.ang.z), sine, 2);
			fn_8019E880(frame);
			fn_8019EB94(frame, &ObjParam->setData.pos, 2);
			if (clump2 != NULL) {
				frame = *(UfoFrame**)((u8*)clump2 + 4);
				sine  = fn_800D7B00(params->roll);
				fn_80195790(
				    frame->modelling, &AxisZ, s14dUfoOne[0] - fn_800D7AE4(params->roll), sine, 0);
				fn_8019E880(frame);
				sine = fn_800D7B00(ObjParam->setData.ang.y);
				fn_80195790(frame->modelling, &AxisY,
				    s14dUfoOne[0] - fn_800D7AE4(ObjParam->setData.ang.y), sine, 2);
				fn_8019E880(frame);
				sine = fn_800D7B00(ObjParam->setData.ang.x);
				fn_80195790(frame->modelling, &AxisX,
				    s14dUfoOne[0] - fn_800D7AE4(ObjParam->setData.ang.x), sine, 2);
				fn_8019E880(frame);
				sine = fn_800D7B00(ObjParam->setData.ang.z);
				fn_80195790(frame->modelling, &AxisZ,
				    s14dUfoOne[0] - fn_800D7AE4(ObjParam->setData.ang.z), sine, 2);
				fn_8019E880(frame);
				fn_8019EB94(frame, &ObjParam->setData.pos, 2);
			}
		}
		InitShare(*this, &s14dUfoCclInfo, 1, 4);
	}
	virtual ~TObjS14UFO();
};

extern "C" void s14dUfoCreate(void)
{
	new TObjS14UFO(lbl_8042C110);
}
