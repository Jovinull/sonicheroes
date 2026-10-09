// TObjKey, shared by rel/key_object_create.cpp, which defines KEY_OBJECT_CTOR
// as inline so its factory inlines the constructor, and rel/key_object_ctor.cpp,
// which defines it empty to emit the out-of-line copy the module also keeps.

#include "game/effect/eff_bomb.h"
#include "game/setObj.h"

// The record a key leaves on its placement once it has found a cage.
struct KeyCage {
	u32 magic;      // 0x00: 0x12345678
	RwV3d position; // 0x04
	u32 unk10;      // 0x10
};

struct ObjectManager {
	u8 pad000[0x30];
	SETOBJ_PARAM* lists[1]; // 0x30: one list per group
};

extern "C" char* CL_TObjKey;
extern "C" CCL_INFO keyObjectCclInfo;
extern "C" void* keyObjectResource;
extern "C" const f32 keyObjectCageRange[1];
extern "C" ObjectManager* lbl_8042C298;
extern "C" u8* lbl_8042C1D0;
extern "C" TObject* lbl_8042C110;
extern "C" RpClump* fn_80150588(void* model);
extern "C" void fn_8015BB08(void* world, RpClump* clump);
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

class TObjKey : public TObject, public TObjSetObj, public C_COLLI
{
public:
	RwV3d pos;      // 0xB8
	s32 unkC4;      // 0xC4
	s32 unkC8;      // 0xC8
	s32 unkCC;      // 0xCC
	s32 unkD0;      // 0xD0
	RpClump* clump; // 0xD4
	s32 unkD8;      // 0xD8

	TObjKey(TObject* parent);

	void SearchCage()
	{
		if (ObjParam->originalWork == NULL) {
			SETOBJ_PARAM* node = lbl_8042C298->lists[ObjParam->setData.communicateId];
			f32 range          = keyObjectCageRange[0];
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
	virtual ~TObjKey();
};

KEY_OBJECT_CTOR TObjKey::TObjKey(TObject* parent)
    : TObject(parent)
{
	ClassName = CL_TObjKey;
	DispTime  = 0xDC;

	pos = ObjParam->setData.pos;

	unkD8 = unkD0 = unkC4 = unkC8 = unkCC = 0;

	clump = fn_80150588(keyObjectResource);
	fn_8015BB08(*(void**)(lbl_8042C1D0 + 0x725C), clump);

	u32 flag = *(volatile u32*)&ObjParam->setData.condition.Flag;
	objRpClumpForAllAtomicsToSetRenderCallbackToUseLight(clump, ((flag & 0x1C0000) >> 18) + 4);

	InitShare(*this, &keyObjectCclInfo, 1, 4);
	SearchCage();
}
