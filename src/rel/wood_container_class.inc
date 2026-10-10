// TObjContWood, shared by rel/wood_container_create.cpp and the units that
// define its out-of-line members. The constructor is inline (the factory
// inlines it); rel/wood_container_ctor.cpp defines WOOD_CONTAINER_CTOR empty to
// emit the out-of-line copy each module also keeps.

#include "game/obj_container.h"

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

#ifndef WOOD_CONTAINER_CTOR
#define WOOD_CONTAINER_CTOR inline
#endif

class TObjContWood : public TObjContainer
{
public:
	WOOD_CONTAINER_CTOR TObjContWood(TObject* parent);
	// The first virtual declared is the key function, and the unit that defines
	// it emits the vtable. These are all overrides, whose order does not move
	// their slots: rel/wood_container_exec.cpp (Disp and Exec) declares the
	// destructor first, the others Exec.
#ifdef WOOD_CONTAINER_DTOR_FIRST
	virtual ~TObjContWood();
#endif
	virtual void Exec();
	virtual void Disp();
#ifndef WOOD_CONTAINER_DTOR_FIRST
	virtual ~TObjContWood();
#endif
};

WOOD_CONTAINER_CTOR TObjContWood::TObjContWood(TObject* parent)
    : TObjContainer(parent)
{
	ClassName = CL_TObjContWood;
	DispTime  = 0xF8;

	material = 0;
	clump    = fn_80150588(woodContainerResource);
	fn_8015BB08(*(void**)(lbl_8042C1D0 + 0x725C), clump);
	SetPosition();

	if (lbl_8029C310.stage == 0x1A || lbl_8029C310.stage == 0x1B || lbl_8029C310.stage == 0x1C) {
		objRpClumpForAllAtomicsToSetRenderCallbackToUseLight(clump, 0x10);
	} else {
		u32 flag = *(volatile u32*)&ObjParam->setData.condition.Flag;
		objRpClumpForAllAtomicsToSetRenderCallbackToUseLight(clump, ((flag & 0x1C0000) >> 18) + 4);
	}

	pieces     = woodContainerPieces;
	unkEC      = woodContainerUnkEC;
	pieceTable = woodContainerPieceTable;
	pieceKinds = 3;
}
