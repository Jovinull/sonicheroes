#include "game/obj_container.h"

// unbreakableContainerCreate, the factory the editor record for
// TObjContUnbreakable points at.
//
// It is the same 71 instructions in the thirteen stage modules that share the
// engine core, at their own address in each, so each module's splits.txt names
// its own range.
//
// It is rel/iron_container_create.cpp with material 2, its own model and
// debris, and one step more: once the collision base has a shape, bit 0x4000 of
// the shape's attributes is cleared, which is what keeps this one from
// breaking.
//
// The light bits are read through a volatile access for the reason written up
// in rel/itembaloon_create.cpp.

extern "C" char* CL_TObjContUnbreakable;
extern "C" void* unbreakableContainerResource;
extern "C" void* unbreakableContainerPieces[3];
extern "C" void* unbreakableContainerPieceTable[6];
extern "C" u8* lbl_8042C1D0;
extern "C" TObject* lbl_8042C110;
extern "C" RpClump* fn_80150588(void* model);
extern "C" void fn_8015BB08(void* world, RpClump* clump);
void objRpClumpForAllAtomicsToSetRenderCallbackToUseLight(RpClump*, u32);

class TObjContUnbreakable : public TObjContainer
{
public:
	TObjContUnbreakable(TObject* parent)
	    : TObjContainer(parent)
	{
		ClassName = CL_TObjContUnbreakable;
		DispTime  = 0xF8;

		material = 2;
		clump    = fn_80150588(unbreakableContainerResource);
		fn_8015BB08(*(void**)(lbl_8042C1D0 + 0x725C), clump);
		SetPosition();

		u32 flag = *(volatile u32*)&ObjParam->setData.condition.Flag;
		objRpClumpForAllAtomicsToSetRenderCallbackToUseLight(clump, ((flag & 0x1C0000) >> 18) + 4);

		pieces     = unbreakableContainerPieces;
		unkEC      = 0;
		pieceTable = unbreakableContainerPieceTable;
		pieceKinds = 3;

		if (info != NULL) {
			info->attr &= ~0x4000;
		}
	}
	virtual ~TObjContUnbreakable();
};

extern "C" void unbreakableContainerCreate(void)
{
	new TObjContUnbreakable(lbl_8042C110);
}
