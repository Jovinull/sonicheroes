// TObjContUnbreakable, shared by rel/unbreakable_container_create.cpp and the units
// that define its out-of-line members. The constructor stays inline in the
// class: the factory inlines it.

#include "game/obj_container.h"

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
	// The first virtual declared is the key function, and the unit that defines
	// it emits the vtable. These are all overrides, whose order does not move
	// their slots: rel/unbreakable_container_exec.cpp (Disp and Exec) declares the destructor
	// first, the others Exec.
#ifdef UNBREAKABLE_CONTAINER_DTOR_FIRST
	virtual ~TObjContUnbreakable();
#endif
	virtual void Exec();
	virtual void Disp();
	virtual s32 CheckBreak();
#ifndef UNBREAKABLE_CONTAINER_DTOR_FIRST
	virtual ~TObjContUnbreakable();
#endif
};
