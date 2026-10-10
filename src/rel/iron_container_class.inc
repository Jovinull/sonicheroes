// TObjContIron, shared by rel/iron_container_create.cpp and the units
// that define its out-of-line members. The constructor stays inline in the
// class: the factory inlines it.

#include "game/obj_container.h"

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
	// The first virtual declared is the key function, and the unit that defines
	// it emits the vtable. These are all overrides, whose order does not move
	// their slots: rel/iron_container_exec.cpp (Disp and Exec) declares the destructor
	// first, the others Exec.
#ifdef IRON_CONTAINER_DTOR_FIRST
	virtual ~TObjContIron();
#endif
	virtual void Exec();
	virtual void Disp();
#ifndef IRON_CONTAINER_DTOR_FIRST
	virtual ~TObjContIron();
#endif
};
