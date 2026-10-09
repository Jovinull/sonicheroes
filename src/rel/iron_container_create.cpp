#include "game/obj_container.h"

// ironContainerCreate, the factory rel/iron_container_register.cpp puts in the
// editor record for TObjContIron.
//
// It is the same 65 instructions in the thirteen stage modules that share the
// engine core, at their own address in each, so each module's splits.txt names
// its own range.
//
// The allocation is a real new-expression of the C++ class, which is what
// gives the original's `mr r0, r3` and then `mr r31, r0`; rel/sample1_create.cpp
// has the long form. The class adds nothing to TObjContainer: its constructor
// names the class, marks the material, clones the module's model into the
// world, places it, lights it and hands it the iron debris.
//
// The light bits are read through a volatile access for the reason written up
// in rel/itembaloon_create.cpp.

extern "C" char* CL_TObjContIron;
extern "C" void* ironContainerResource;
extern "C" void* ironContainerPieces[3];
extern "C" void* ironContainerPieceTable[6];
extern "C" u8* lbl_8042C1D0;
extern "C" TObject* lbl_8042C110;
extern "C" RpClump* fn_80150588(void* model);
extern "C" void fn_8015BB08(void* world, RpClump* clump);
void objRpClumpForAllAtomicsToSetRenderCallbackToUseLight(RpClump*, u32);

class TObjContIron : public TObjContainer
{
public:
	TObjContIron(TObject* parent)
	    : TObjContainer(parent)
	{
		ClassName = CL_TObjContIron;
		DispTime  = 0xF8;

		material = 1;
		clump    = fn_80150588(ironContainerResource);
		fn_8015BB08(*(void**)(lbl_8042C1D0 + 0x725C), clump);
		SetPosition();

		u32 flag = *(volatile u32*)&ObjParam->setData.condition.Flag;
		objRpClumpForAllAtomicsToSetRenderCallbackToUseLight(clump, ((flag & 0x1C0000) >> 18) + 4);

		pieces     = ironContainerPieces;
		unkEC      = 0;
		pieceTable = ironContainerPieceTable;
		pieceKinds = 3;
	}
	virtual ~TObjContIron();
};

extern "C" void ironContainerCreate(void)
{
	new TObjContIron(lbl_8042C110);
}
