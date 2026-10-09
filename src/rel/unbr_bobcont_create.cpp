#include "game/obj_container.h"

// unbrBobcontObjectCreate, the factory the editor record for
// TObjBobcontUnbreakable points at.
//
// It is the same 78 instructions in the thirteen stage modules that share the
// engine core, at their own address in each, so each module's splits.txt names
// its own range.
//
// It is rel/wood_container_create.cpp on the bobsleigh crate base: material 2,
// the module's own model and debris, light set 0x10 in stages 0x1A to 0x1C and
// the placement's light everywhere else. The stage is named three times in the
// test for the reason written up there, and the light bits are read through a
// volatile access for the reason written up in rel/itembaloon_create.cpp.

extern "C" char* CL_TObjBobcontUnbreakable;
extern "C" void* unbrBobcontResource;
extern "C" void* unbrBobcontPieces[3];
extern "C" void* unbrBobcontPieceTable[6];

// The game's global state block; the word at 0x2C is the stage being played.
struct GameState {
	u8 pad00[0x2C];
	s32 stage; // 0x2C
};

extern "C" GameState lbl_8029C310;
extern "C" u8* lbl_8042C1D0;
extern "C" TObject* lbl_8042C110;
extern "C" RpClump* fn_80150588(void* model);
extern "C" void fn_8015BB08(void* world, RpClump* clump);
void objRpClumpForAllAtomicsToSetRenderCallbackToUseLight(RpClump*, u32);

class TObjBobcontUnbreakable : public TObjBobcontainer
{
public:
	TObjBobcontUnbreakable(TObject* parent)
	    : TObjBobcontainer(parent)
	{
		ClassName = CL_TObjBobcontUnbreakable;
		DispTime  = 0xF8;

		material = 2;
		clump    = fn_80150588(unbrBobcontResource);
		fn_8015BB08(*(void**)(lbl_8042C1D0 + 0x725C), clump);
		SetPosition();

		if (lbl_8029C310.stage == 0x1A || lbl_8029C310.stage == 0x1B
		    || lbl_8029C310.stage == 0x1C) {
			objRpClumpForAllAtomicsToSetRenderCallbackToUseLight(clump, 0x10);
		} else {
			u32 flag = *(volatile u32*)&ObjParam->setData.condition.Flag;
			objRpClumpForAllAtomicsToSetRenderCallbackToUseLight(
			    clump, ((flag & 0x1C0000) >> 18) + 4);
		}

		pieces     = unbrBobcontPieces;
		unkEC      = 0;
		pieceTable = unbrBobcontPieceTable;
		pieceKinds = 3;
	}
	virtual ~TObjBobcontUnbreakable();
};

extern "C" void unbrBobcontObjectCreate(void)
{
	new TObjBobcontUnbreakable(lbl_8042C110);
}
