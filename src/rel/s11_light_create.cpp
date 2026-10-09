#include "game/effect/eff_bomb.h"
#include "game/material.h"
#include "game/setObj.h"

// s11lightObjectCreate, the factory the editor record for TObjS11Light points
// at, in stage11D.
//
// The allocation is a real new-expression of the C++ class, which is what
// gives the original's `mr r0, r3` and then `mr r31, r0`; rel/sample1_create.cpp
// has the long form. C_COLLI is the third base, as in rel/warp_create.cpp.
//
// The parameter block picks one of the module's four models and raises the
// light by its height plus the module's constant 1. The light clones that
// model, lights it with set 0x10 and wraps it in a DealMaterial; the first two
// kinds clone it six more times the same way. Each DealMaterial is a real
// new-expression too.

struct S11LightParam {
	s32 kind;   // 0x00
	f32 height; // 0x04
};

extern "C" char* CL_TObjS11Light;
extern "C" void* s11LightModels[4];
extern "C" const f32 s11LightOne[1];
extern "C" TObject* lbl_8042C110;
extern "C" RpClump* fn_80150588(void* model);
void objRpClumpForAllAtomicsToSetRenderCallbackToUseLight(RpClump*, u32);

class TObjS11Light : public TObject, public TObjSetObj, public C_COLLI
{
public:
	RwV3d pos;                  // 0xB8
	sAngle ang;                 // 0xC4
	s32 kind;                   // 0xD0
	f32 height;                 // 0xD4
	s32 unkD8;                  // 0xD8
	u8 unkDC[4];                // 0xDC
	f32 unkE0;                  // 0xE0
	RpClump* clump;             // 0xE4
	DealMaterial* material;     // 0xE8
	RpClump* clumps[6];         // 0xEC
	DealMaterial* materials[6]; // 0x104
	s32 unk11C[6];              // 0x11C
	u8 unk134[0x1E0 - 0x134];   // 0x134

	TObjS11Light(TObject* parent)
	    : TObject(parent)
	{
		ClassName = CL_TObjS11Light;
		DispTime  = 0x1E0;

		S11LightParam* param = (S11LightParam*)ObjParam->setData.setBuffer;

		pos = ObjParam->setData.pos;
		ang = ObjParam->setData.ang;

		kind   = param->kind;
		height = s11LightOne[0] + param->height;

		clump     = NULL;
		clumps[0] = NULL;
		clumps[1] = NULL;
		clumps[2] = NULL;
		clumps[3] = NULL;
		clumps[4] = NULL;
		clumps[5] = NULL;
		unkD8     = 0;
		unkE0     = s11LightOne[0];

		void* model = s11LightModels[kind];
		if (model != NULL) {
			if (clump == NULL) {
				clump = fn_80150588(model);
				objRpClumpForAllAtomicsToSetRenderCallbackToUseLight(clump, 0x10);
				material = new DealMaterial(clump);
			}
			if (kind == 0 || kind == 1) {
				for (int i = 0; i < 6; i++) {
					if (clumps[i] == NULL) {
						clumps[i] = fn_80150588(model);
						objRpClumpForAllAtomicsToSetRenderCallbackToUseLight(clumps[i], 0x10);
						materials[i] = new DealMaterial(clumps[i]);
					}
				}
			}
		}

		unk11C[0] = 0;
		unk11C[1] = 0;
		unk11C[2] = 0;
		unk11C[3] = 0;
		unk11C[4] = 0;
		unk11C[5] = 0;
	}
	virtual ~TObjS11Light();
	virtual void Exec();
	virtual void EditOnChange(SETDATA_PARAM*);
};

extern "C" void s11lightObjectCreate(void)
{
	new TObjS11Light(lbl_8042C110);
}
