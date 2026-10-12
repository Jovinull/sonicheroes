// TObjBobcontUnbreakable, shared by rel/unbr_bobcont_create.cpp and the units
// that define its out-of-line members. The constructor is inline (the factory
// inlines it); rel/unbr_bobcont_ctor.cpp defines UNBR_BOBCONT_CTOR empty to
// emit the out-of-line copy each module also keeps.

#include "game/obj_container.h"

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

#ifndef UNBR_BOBCONT_CTOR
#define UNBR_BOBCONT_CTOR inline
#endif

class TObjBobcontUnbreakable : public TObjBobcontainer
{
public:
	UNBR_BOBCONT_CTOR TObjBobcontUnbreakable(TObject* parent);
	// The first virtual declared is the key function, and the unit that defines
	// it emits the vtable. These are all overrides, whose order does not move
	// their slots: rel/unbr_bobcont_exec.cpp (Disp and Exec) declares the destructor
	// first, the others Exec.
#ifdef UNBR_BOBCONT_DTOR_FIRST
	virtual ~TObjBobcontUnbreakable();
#endif
	virtual void Exec();
	virtual void Disp();
	virtual s32 CheckBreak();
	virtual void BrokenSE();
#ifndef UNBR_BOBCONT_DTOR_FIRST
	virtual ~TObjBobcontUnbreakable();
#endif
};

UNBR_BOBCONT_CTOR TObjBobcontUnbreakable::TObjBobcontUnbreakable(TObject* parent)
    : TObjBobcontainer(parent)
{
	ClassName = CL_TObjBobcontUnbreakable;
	DispTime  = 0xF8;

	material = 2;
	clump    = fn_80150588(unbrBobcontResource);
	fn_8015BB08(*(void**)(lbl_8042C1D0 + 0x725C), clump);
	SetPosition();

	if (lbl_8029C310.stage == 0x1A || lbl_8029C310.stage == 0x1B || lbl_8029C310.stage == 0x1C) {
		objRpClumpForAllAtomicsToSetRenderCallbackToUseLight(clump, 0x10);
	} else {
		u32 flag = *(volatile u32*)&ObjParam->setData.condition.Flag;
		objRpClumpForAllAtomicsToSetRenderCallbackToUseLight(clump, ((flag & 0x1C0000) >> 18) + 4);
	}

	pieces     = unbrBobcontPieces;
	unkEC      = 0;
	pieceTable = unbrBobcontPieceTable;
	pieceKinds = 3;
}
