#include "game/effect/eff_bomb.h"
#include "game/setObj.h"

// TObjTriSpring's constructor (the PS2 build's TObjTriSpring::__ct). It takes the
// placement (position, angles, the two springs' sizes, the launch value and the
// power picked from triSpringChoices), starts at rest (amplitude and scales 1,
// timers clear, state 1), makes the three spring models (lit by the placement's
// light bits, the node's material drawn with mode 0x10) and registers them, and
// three shadows of the fourth model. Then it gives the collision its two shapes
// with flag 0x40 and takes its saved byte from the placement's work block,
// making the block the first time.
//
// A real constructor over bases with destructors: the model arrays are indexed
// from `this` in both loops (an offset register), as the retail does. The light
// bits are read before the clump, as the volatile read keeps them (as in
// rel/chao_ctor.cpp).

struct TriSpringParams {
	f32 sizeA;  // 0x00
	f32 sizeB;  // 0x04
	s16 launch; // 0x08
	s8 power;   // 0x0A
};

struct TriSpringChoice {
	const char* label; // 0x00
	s32 value;         // 0x04
};

struct RpAtomic;

class TObjTriSpring : public TObject, public TObjSetObj, public C_COLLI
{
public:
	s32 state;           // 0xB8
	s8 timers[8];        // 0xBC
	u8 saved;            // 0xC4
	s8 power;            // 0xC5
	s16 launch;          // 0xC6
	RwV3d pos;           // 0xC8
	sAngle ang;          // 0xD4
	s32 phase;           // 0xE0
	f32 amplitude;       // 0xE4
	f32 scaleA;          // 0xE8
	f32 scaleB;          // 0xEC
	f32 sizeA;           // 0xF0
	f32 sizeB;           // 0xF4
	RpClump* models[3];  // 0xF8
	RpClump* shadows[3]; // 0x104

	TObjTriSpring(TObject* parent);
	virtual ~TObjTriSpring();
};

extern "C" u8* lbl_8042C1D0;
extern "C" char* CL_TObjTriSpring;
extern "C" void* triSpringModels[4];
extern "C" char triSpringNodeName[];
extern "C" TriSpringChoice triSpringChoices[];
extern "C" CCL_INFO triSpringCclInfo;
extern "C" const f32 triSpringOne[1];

extern "C" RpClump* fn_80150588(void* model);
extern "C" void fn_8015BB08(void* world, RpClump* clump);
extern "C" void fn_8003C640(RpClump* clump);
extern "C" void fn_801491A8(RpAtomic* atomic);
extern "C" s32* RpAtomicMCCGetCustomRenderCallBack(RpAtomic* atomic);
void objRpClumpForAllAtomicsToSetRenderCallbackToUseLight(RpClump* clump, u32 light);
RpAtomic* objRpClumpGetAtomicWithTexture(RpClump* clump, RpAtomic* after, char* texture);
RpAtomic* objRpClumpGetAtomic(RpClump* clump, RpAtomic* after);

TObjTriSpring::TObjTriSpring(TObject* parent)
    : TObject(parent)
{
	TriSpringParams* params;
	int i;

	ClassName = CL_TObjTriSpring;
	DispTime  = 0x110;
	pos       = ObjParam->setData.pos;
	ang       = ObjParam->setData.ang;
	params    = (TriSpringParams*)ObjParam->setData.setBuffer;
	sizeA     = params->sizeA;
	sizeB     = triSpringOne[0] + params->sizeB;
	launch    = params->launch;
	power     = triSpringChoices[params->power].value;
	phase     = 0;
	amplitude = triSpringOne[0];
	scaleA    = triSpringOne[0];
	scaleB    = triSpringOne[0];
	timers[0] = 0;
	timers[1] = 0;
	timers[2] = 0;
	timers[3] = 0;
	timers[4] = 0;
	timers[5] = 0;
	timers[6] = 0;
	timers[7] = 0;
	state     = 1;

	for (i = 0; i < 3; i++) {
		models[i] = fn_80150588(triSpringModels[i]);
		u32 flag  = *(volatile u32*)&ObjParam->setData.condition.Flag;
		objRpClumpForAllAtomicsToSetRenderCallbackToUseLight(
		    models[i], ((flag & 0x1C0000) >> 18) + 4);
		s32* mode = RpAtomicMCCGetCustomRenderCallBack(
		    objRpClumpGetAtomicWithTexture(models[i], NULL, triSpringNodeName));
		*mode = 0x10;
		fn_8015BB08(*(void**)(lbl_8042C1D0 + 0x725C), models[i]);
	}
	for (i = 0; i < 3; i++) {
		shadows[i] = fn_80150588(triSpringModels[3]);
		fn_8003C640(shadows[i]);
		fn_801491A8(objRpClumpGetAtomic(shadows[i], NULL));
		objRpClumpForAllAtomicsToSetRenderCallbackToUseLight(shadows[i], 0x10);
	}

	Init(&triSpringCclInfo, 2, 4);
	flag |= 0x40;
	if (ObjParam->originalWork != NULL) {
		saved = *(u8*)ObjParam->originalWork;
	} else {
		u8* work               = new u8;
		ObjParam->originalWork = work;
		saved                  = 0;
		*work                  = 0;
	}
}
