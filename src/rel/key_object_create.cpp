#include "game/effect/eff_bomb.h"
#include "game/setObj.h"

// keyObjectCreate, the factory the editor record for TObjKey points at.
//
// It is the same 124 instructions in the thirteen stage modules that share the
// engine core, at their own address in each, so each module's splits.txt names
// its own range.
//
// The allocation is a real new-expression of the C++ class, which is what
// gives the original's `mr r0, r3` and then `mr r31, r0`; rel/sample1_create.cpp
// has the long form. C_COLLI is the third base, as in rel/warp_create.cpp, and
// it takes its shape through InitShare, the PS2 name of fn_8003BF04; see the
// helper below.
//
// The constructor ends with SearchCage, which rel/e_s11_key_stage11.cpp already
// writes for stage 11's key: unless the placement already carries one, walk
// the placements of the key's group for a cage (type 0x24) closer than the
// module's range constant, and leave a tagged record with the key's position
// on the placement. Here the range is the module's own float, read once before
// the walk.
//
// The light bits are read through a volatile access for the reason written up
// in rel/itembaloon_create.cpp.

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

	TObjKey(TObject* parent)
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

	virtual ~TObjKey();
	virtual void Exec();
};

extern "C" void keyObjectCreate(void)
{
	new TObjKey(lbl_8042C110);
}
