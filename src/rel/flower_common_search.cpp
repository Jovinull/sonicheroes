#include "game/effect/eff_bomb.h"
#include "game/object.h"

// TObjFlowerCommon's IsNowFading, ChangeFlowerColli_Open and
// SearchNodeFrameFromNodeID (the PS2 build's names, in its order).
// IsNowFading asks the main fade screen whether its two fade values still
// differ; ChangeFlowerColli_Open sets the push of the collision's second and
// third shapes; SearchNodeFrameFromNodeID is TObjBobsleigh's
// (rel/bobsleigh_search.cpp): the frame of the hierarchy node with the bone id.

// The fade screen as the flower sees it: only the two virtuals it calls, at
// vtable slots 0x38 and 0x3C (their names are not known).
class FADESCREEN : public TObject
{
public:
	virtual void Slot2C();
	virtual void Slot30();
	virtual void Slot34();
	virtual f32 Slot38();
	virtual f32 Slot3C();

	static FADESCREEN* GetMainFadeScreenPointer();
};

extern "C" FADESCREEN* lbl_8042C170;

inline FADESCREEN* FADESCREEN::GetMainFadeScreenPointer()
{
	return lbl_8042C170;
}

typedef struct FlowerCommon {
	u8 unk00[0x40];
	CCL_INFO* info; // 0x40, the collision's (at 0x30)
} FlowerCommon;

int objRpHAnimHierarchyFindFrameFromBoneID(RpHAnimHierarchy* hierarchy, int id);

extern "C" u8 IsNowFading__16TObjFlowerCommonFv(FlowerCommon* flower)
{
	FADESCREEN* fade = FADESCREEN::GetMainFadeScreenPointer();

	return fade->Slot38() != fade->Slot3C();
}

extern "C" void ChangeFlowerColli_Open__16TObjFlowerCommonFv(FlowerCommon* flower)
{
	flower->info[1].push = 0xF0;
	flower->info[2].push = 0xFF;
}

extern "C" RwFrame* SearchNodeFrameFromNodeID__16TObjFlowerCommonFP16RpHAnimHierarchyi(
    FlowerCommon* flower, RpHAnimHierarchy* hierarchy, int id)
{
	int index = objRpHAnimHierarchyFindFrameFromBoneID(hierarchy, id);

	return hierarchy->pNodeInfo[index].pFrame;
}
