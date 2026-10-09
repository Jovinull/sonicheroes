// TObjS06Chip, shared by rel/s06_chip_create.cpp, which defines S06_CHIP_CTOR
// as inline so its factory inlines the constructor, and rel/s06_chip_ctor.cpp,
// which defines it empty to emit the out-of-line copy the module also keeps.

#include "game/effect/eff_bomb.h"
#include "game/material.h"
#include "game/setObj.h"

// The record a key-like object leaves on its placement once it has found a
// cage.
struct KeyCage {
	u32 magic;      // 0x00
	RwV3d position; // 0x04
	u32 unk10;      // 0x10
};

struct SetObjLists {
	u8 pad000[0x30];
	SETOBJ_PARAM* lists[1]; // 0x30
};

struct GameMode {
	u8 pad00[0x24];
	s8 mode; // 0x24
};

extern "C" char* CL_TObjS06Chip;
extern "C" CCL_INFO s06ChipCclInfo;
extern "C" void* s06ChipModel;
extern "C" const f32 s06ChipZero[1];
extern "C" const f32 s06ChipOne[1];
extern "C" const f32 s06ChipCageRange[1];
extern "C" SetObjLists* lbl_8042C298;
extern "C" GameMode* lbl_8042C180;
extern "C" TObject* lbl_8042C110;
extern "C" RpClump* fn_80150588(void* model);
extern "C" void fn_8003BF04(C_COLLI* colli, CCL_INFO* info, int count, u8 kind);
void objRpClumpForAllAtomicsToSetRenderCallbackToUseLight(RpClump*, u32);
f32 Distance2P2P(const RwV3d*, const RwV3d*);

// C_COLLI::InitShare, still fn_8003BF04 in main's symbols. Taking the
// collision base by reference adjusts `this` to it without the null test a
// pointer conversion would add, which is what calling the member does.
inline void InitShare(C_COLLI& colli, CCL_INFO* info, int count, u8 kind)
{
	fn_8003BF04(&colli, info, count, kind);
}

class TObjS06Chip : public TObject, public TObjSetObj, public C_COLLI
{
public:
	RwV3d pos;              // 0xB8
	u8 unkC4[8];            // 0xC4
	f32 unkCC;              // 0xCC
	f32 unkD0;              // 0xD0
	s32 unkD4;              // 0xD4
	RpClump* clump;         // 0xD8
	DealMaterial* material; // 0xDC

	TObjS06Chip(TObject* parent);

	void SearchCage()
	{
		if (ObjParam->originalWork == NULL) {
			SETOBJ_PARAM* node = lbl_8042C298->lists[ObjParam->setData.communicateId];
			f32 range          = s06ChipCageRange[0];
			for (; node != NULL; node = node->next) {
				if (node->setData.uniqueId == 0x24
				    && Distance2P2P(&ObjParam->setData.pos, &node->setData.pos) < range) {
					ObjParam->originalWork                       = new KeyCage;
					((KeyCage*)ObjParam->originalWork)->magic    = 0x12345678;
					((KeyCage*)ObjParam->originalWork)->position = ObjParam->setData.pos;
					return;
				}
			}
		}
	}

	virtual void Exec();
	virtual ~TObjS06Chip();
	virtual void EditOnChange(SETDATA_PARAM*);
};

S06_CHIP_CTOR TObjS06Chip::TObjS06Chip(TObject* parent)
    : TObject(parent)
{
	ClassName = CL_TObjS06Chip;
	DispTime  = 0xE0;

	pos      = ObjParam->setData.pos;
	unkD4    = 0;
	unkCC    = s06ChipZero[0];
	unkD0    = s06ChipOne[0];
	material = NULL;

	clump = fn_80150588(s06ChipModel);
	if (clump != NULL) {
		objRpClumpForAllAtomicsToSetRenderCallbackToUseLight(
		    clump, ((ObjParam->setData.condition.Flag & 0x1C0000) >> 18) + 4);
		material = new DealMaterial(clump);
	}

	if (!OnEdit()) {
		InitShare(*this, &s06ChipCclInfo, 1, 4);
		SearchCage();
	}

	if (lbl_8042C180->mode == 8) {
		ObjParam->setData.condition.Flag |= 0x10000000;
	}
}
