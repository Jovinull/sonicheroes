#include "game/obj_container.h"

// woodContainerCreate, the factory rel/wood_container_register.cpp puts in the
// editor record for TObjContWood.
//
// It is the same 80 instructions in twelve of the stage modules that share the
// engine core, at their own address in each, so each module's splits.txt names
// its own range.
//
// It is rel/iron_container_create.cpp with material 0, its own model and
// debris, a word from the module for the field at 0xEC, and one difference in
// the lighting: in stages 0x1A to 0x1C the crate takes light set 0x10 instead
// of the one its placement asks for. The test names the stage three times, as
// three equality tests; a local, or a switch, lets the compiler fold them into
// one range check, which the original does not have.
//
// The light bits are read through a volatile access for the reason written up
// in rel/itembaloon_create.cpp.

extern "C" char* CL_TObjContWood;
extern "C" void* woodContainerResource;
extern "C" void* woodContainerPieces[3];
extern "C" s32 woodContainerUnkEC;
extern "C" void* woodContainerPieceTable[6];

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

class TObjContWood : public TObjContainer
{
public:
	TObjContWood(TObject* parent)
	    : TObjContainer(parent)
	{
		ClassName = CL_TObjContWood;
		DispTime  = 0xF8;

		material = 0;
		clump    = fn_80150588(woodContainerResource);
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

		pieces     = woodContainerPieces;
		unkEC      = woodContainerUnkEC;
		pieceTable = woodContainerPieceTable;
		pieceKinds = 3;
	}
	virtual ~TObjContWood();
};

extern "C" void woodContainerCreate(void)
{
	new TObjContWood(lbl_8042C110);
}
