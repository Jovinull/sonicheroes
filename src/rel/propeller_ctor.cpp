#include "game/effect/eff_bomb.h"
#include "game/setObj.h"

// TObjPropeller's constructor, called by the factory in rel/propeller_create.cpp.
// It takes the placement's position and angle and, when the stage has loaded the
// propeller's three models, makes a clump of each and registers it with the world
// (otherwise it stops there). Then it gives its collision block its shape with
// flag 0x40 set, sets its other fields and sets the placement's communicate id to
// 0x78.
//
// It is a real constructor over bases with destructors: that is what makes MWCC
// index the model array from `this` in the loop (an offset register stepping by
// 4) instead of walking a pointer.

class TObjPropeller : public TObject, public TObjSetObj, public C_COLLI
{
public:
	s32 unkB8;          // 0xB8
	s8 unkBC;           // 0xBC
	RwV3d pos;          // 0xC0
	sAngle ang;         // 0xCC
	f32 unkD8;          // 0xD8
	s32 unkDC;          // 0xDC
	s32 unkE0;          // 0xE0
	u8 unkE4[0x24];     // 0xE4
	sAngle unk108;      // 0x108
	u8 unk114[0xC];     // 0x114
	sAngle unk120;      // 0x120
	u8 unk12C[0xC];     // 0x12C
	f32 unk138;         // 0x138
	u8 unk13C[0x8];     // 0x13C
	f32 unk144;         // 0x144
	u8 unk148[0x8];     // 0x148
	RpClump* models[3]; // 0x150
	s32 unk15C;         // 0x15C

	TObjPropeller(TObject* parent);
	virtual ~TObjPropeller();
};

extern "C" u8* lbl_8042C1D0;
extern "C" char* CL_TObjPropeller;
extern "C" s32 propellerLoaded;
extern "C" void* propellerResources[3];
extern "C" CCL_INFO propellerCclInfo;
extern "C" const f32 propellerPitchStart[1];
extern "C" const f32 propellerZeroSpin[1];
extern "C" const f32 propellerOne[1];

extern "C" RpClump* fn_80150588(void* model);
extern "C" void fn_8015BB08(void* world, RpClump* clump);

TObjPropeller::TObjPropeller(TObject* parent)
    : TObject(parent)
{
	ClassName = CL_TObjPropeller;
	DispTime  = 0x164;
	pos       = ObjParam->setData.pos;
	ang       = ObjParam->setData.ang;
	models[0] = NULL;
	models[1] = NULL;
	models[2] = NULL;
	if (propellerLoaded == 0) {
		return;
	}
	for (int i = 0; i < 3; i++) {
		models[i] = fn_80150588(propellerResources[i]);
		fn_8015BB08(*(void**)(lbl_8042C1D0 + 0x7260), models[i]);
	}
	Init(&propellerCclInfo, 1, 4);
	flag |= 0x40;
	unk138   = propellerPitchStart[0];
	unk144   = propellerZeroSpin[0];
	unkB8    = 0;
	unkD8    = propellerOne[0];
	unkDC    = 0;
	unkBC    = -1;
	unk120.x = unk120.y = unk120.z = 0;
	unk108.x = unk108.y = unk108.z  = 0;
	unkE0                           = 0;
	unk15C                          = 0;
	ObjParam->setData.communicateId = 0x78;
}
