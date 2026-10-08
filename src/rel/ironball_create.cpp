#include "game/effect/eff_bomb.h"
#include "game/setObj.h"

// ironballCreate, the factory rel/ironball_register.cpp puts in the editor
// record for TObjIronball.
//
// It is the same 164 instructions in the thirteen stage modules that share the
// engine core, at their own address in each, so each module's splits.txt names
// its own range.
//
// The allocation is a real new-expression of the C++ class, which is what
// gives the original's `mr r0, r3` and then `mr r31, r0`; rel/sample1_create.cpp
// has the long form. C_COLLI is the third base, as in rel/warp_create.cpp.
//
// The placement's parameter block picks a single ball (0) or a chain, and gives
// two sizes. A single ball clones the module's first model; a chain clones the
// second once, the third twice and the fourth twice, and lights and places all
// five; the PS2 build names that step CloneClump. Outside the editor the
// collision takes one shape of the module's table for a ball and four for a
// chain.
//
// The light bits are read through a volatile access for the reason written up
// in rel/itembaloon_create.cpp; the zero is the module's own float, read as an
// external.

struct IronballParam {
	s32 chain; // 0x00
	f32 a;     // 0x04
	f32 b;     // 0x08
};

extern "C" char* CL_TObjIronball;
extern "C" void* ironballModels[4];
extern "C" CCL_INFO ironballCclInfo[4];
extern "C" const f32 ironballZero[1];
extern "C" u8* lbl_8042C1D0;
extern "C" TObject* lbl_8042C110;
extern "C" RpClump* fn_80150588(void* model);
extern "C" void fn_8015BB08(void* world, RpClump* clump);
void objRpClumpForAllAtomicsToSetRenderCallbackToUseLight(RpClump*, u32);

class TObjIronball : public TObject, public TObjSetObj, public C_COLLI
{
public:
	s32 kind;           // 0xB8: 1 a ball, 2 a chain
	RwV3d pos;          // 0xBC
	sAngle ang;         // 0xC8
	f32 a;              // 0xD4
	f32 unkD8;          // 0xD8
	f32 b;              // 0xDC
	RpClump* clumps[5]; // 0xE0

	TObjIronball(TObject* parent)
	    : TObject(parent)
	{
		IronballParam* param = (IronballParam*)ObjParam->setData.setBuffer;

		ClassName = CL_TObjIronball;
		DispTime  = 0xF4;

		pos = ObjParam->setData.pos;
		ang = ObjParam->setData.ang;

		a     = param->a;
		b     = param->b;
		unkD8 = ironballZero[0];

		if (param->chain == 0) {
			kind = 1;
		} else {
			kind = 2;
		}

		CloneClump();

		if (!OnEdit()) {
			if (kind == 1) {
				Init(ironballCclInfo, 1, 4);
			} else {
				Init(ironballCclInfo, 4, 4);
			}
		}
	}

	void CloneClump()
	{
		if (kind == 1) {
			clumps[0] = fn_80150588(ironballModels[0]);
			u32 flag  = *(volatile u32*)&ObjParam->setData.condition.Flag;
			objRpClumpForAllAtomicsToSetRenderCallbackToUseLight(
			    clumps[0], ((flag & 0x1C0000) >> 18) + 4);
			fn_8015BB08(*(void**)(lbl_8042C1D0 + 0x725C), clumps[0]);
			clumps[1] = NULL;
			clumps[2] = NULL;
			clumps[3] = NULL;
			clumps[4] = NULL;
		} else {
			clumps[0] = fn_80150588(ironballModels[1]);
			clumps[1] = fn_80150588(ironballModels[2]);
			clumps[2] = fn_80150588(ironballModels[2]);
			clumps[3] = fn_80150588(ironballModels[3]);
			clumps[4] = fn_80150588(ironballModels[3]);
			for (int i = 0; i < 5; i++) {
				u32 flag = *(volatile u32*)&ObjParam->setData.condition.Flag;
				objRpClumpForAllAtomicsToSetRenderCallbackToUseLight(
				    clumps[i], ((flag & 0x1C0000) >> 18) + 4);
				fn_8015BB08(*(void**)(lbl_8042C1D0 + 0x725C), clumps[i]);
			}
		}
	}

	virtual ~TObjIronball();
	virtual void Exec();
	virtual void EditOnChange(SETDATA_PARAM*);
};

extern "C" void ironballCreate(void)
{
	new TObjIronball(lbl_8042C110);
}
