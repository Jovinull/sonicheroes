#include "game/effect/eff_bomb.h"
#include "game/setObj.h"

// itembaloonObjectCreate, the factory rel/itembaloon_register.cpp puts in the
// editor record for TObjItembaloon.
//
// It is the same 99 instructions in the thirteen stage modules that share the
// engine core, at their own address in each, so each module's splits.txt names
// its own range.
//
// The allocation is a real new-expression of the C++ class, which is what
// gives the original's `mr r0, r3` and then `mr r31, r0`; rel/sample1_create.cpp
// has the long form. C_COLLI is the third base, as in rel/warp_create.cpp.
//
// The placement's parameter block holds the item in its first byte and a size
// offset at 4. The balloon clones the module's model, lights it from the
// placement's light bits, and scales the module's collision shape by its size.
//
// The light bits are read through a volatile access. The original loads them
// into a register before it loads the clone for the call, which is what an
// ordinary local gives before copy propagation folds it back into the
// argument; the volatile keeps the load where it is written. It is a
// reconstruction aid, not a claim about the original source.
//
// The two floats are the module's constants 1 and 0, shared with the rest of
// the class's code, so they are read as externals.

struct ItembaloonParam {
	u8 item;  // 0x00
	f32 size; // 0x04
};

extern "C" char* CL_TObjItembaloon;
extern "C" CCL_INFO itembaloonCclInfo;
extern "C" void* itembaloonResource;
extern "C" const f32 itembaloonOne[1];
extern "C" const f32 itembaloonZero[1];
extern "C" TObject* lbl_8042C110;
extern "C" RpClump* fn_80150588(void* model);
void objRpClumpForAllAtomicsToSetRenderCallbackToUseLight(RpClump*, u32);

class TObjItembaloon : public TObject, public TObjSetObj, public C_COLLI
{
public:
	u8 item;        // 0xB8
	s32 unkBC;      // 0xBC
	RwV3d pos;      // 0xC0
	sAngle ang;     // 0xCC
	f32 size;       // 0xD8
	f32 unkDC;      // 0xDC
	RwV3d scale;    // 0xE0
	s32 unkEC;      // 0xEC
	RpClump* clump; // 0xF0

	TObjItembaloon(TObject* parent)
	    : TObject(parent)
	{
		ClassName = CL_TObjItembaloon;
		DispTime  = 0xF4;

		pos = ObjParam->setData.pos;
		ang = ObjParam->setData.ang;

		ItembaloonParam* param = (ItembaloonParam*)ObjParam->setData.setBuffer;

		item    = param->item;
		size    = itembaloonOne[0] + param->size;
		unkEC   = 0;
		unkDC   = itembaloonZero[0];
		scale.x = itembaloonOne[0];
		scale.y = itembaloonOne[0];
		scale.z = itembaloonOne[0];
		unkBC   = 1;

		clump    = fn_80150588(itembaloonResource);
		u32 flag = *(volatile u32*)&ObjParam->setData.condition.Flag;
		objRpClumpForAllAtomicsToSetRenderCallbackToUseLight(clump, ((flag & 0x1C0000) >> 18) + 4);

		Init(&itembaloonCclInfo, 1, 4);
		info->a = itembaloonCclInfo.a * size;
		CalcRange();
	}
	virtual ~TObjItembaloon();
	virtual void Exec();
	virtual void Disp();
	virtual void TDisp();
	virtual void EditOnChange(SETDATA_PARAM*);
};

extern "C" void itembaloonObjectCreate(void)
{
	new TObjItembaloon(lbl_8042C110);
}
