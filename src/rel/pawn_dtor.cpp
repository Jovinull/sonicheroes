#include "types.h"

// TObjPawn's destructor. It restores both vtable pointers, releases every
// resource the object can be holding — a buffer, a collision flag, two more
// buffers, a virtual object, three counted resources, four meshes — runs the
// embedded animation class down and then the object base, and hands the
// object back to the heap when the caller asks for it.
//
// The claim is .text 0x32CFC to 0x32ED4 and nothing else. The vtable stays in
// each module's data and is renamed to the shared name below; it reads no
// constant, so it owns no rodata.
//
// The name is read from the layout: the run ends exactly where pawnCtor
// begins.
//
// The run is the same in nine of the twelve stage modules that share the
// engine core; stage26D, stage27D and stage28D carry a different revision
// here and are left out. pawnReleaseBuffer itself lives at a different
// address in stage31D/32D/33D than in the other six, since that trio's copy
// of the surrounding unclaimed code is laid out differently even though
// pawnDtor's own bytes are identical everywhere; each module's symbols.txt
// points the name at its own address.
//
// Unlike the ring family, TObjPawn does not embed a Motion base and its
// destructor never calls dtor_8005BD3C or __dt__7TObjectFv: the embedded
// animation class at +0x240 and fn_800A7088 are its own base chain instead.
// Every other field below is addressed by raw offset rather than through a
// full struct, since only these offsets are known so far.
//
// The virtual call at +0x240 dispatches through slot 2 of the pointee's own
// vtable, guarded by two separate null checks on the same field rather than
// one — the second is dead by dataflow but survives because these objects
// build with -opt nopeephole, which is also why it was not folded away here
// either.
//
// The delete flag is a short. It is sign extended before the test, so a plain
// s32 parameter does not reproduce the compare.

typedef struct Collidable {
	u8 unk0[4]; // 0x00
	u16 flags;  // 0x04
} Collidable;

class VBase
{
public:
	virtual void release(s32 flags);
};

extern "C" void* lbl_8042C148;

extern "C" void pawnReleaseBuffer(void* buffer);
extern "C" void fn_8010AFE4(void* object);
extern "C" void dtor_800FE334(void* object, s32 flags);
extern "C" void fn_80150958(void* mesh);
extern "C" void __dt__10HAnimClassFv(void* hAnim, s32 flags);
extern "C" void fn_800A7088(void* object, s32 flags);
extern "C" void fn_800189A4(void* heap, void* object);

// Defined by each module, renamed to this name in its own symbols.txt.
extern "C" void* pawnVtable[];

extern "C" void* pawnDtor(void* object, s16 flags)
{
	u8* base = (u8*)object;

	if (object != NULL) {
		*(void**)(base + 0x18) = pawnVtable;
		*(void**)(base + 0xB4) = pawnVtable + 0xB;

		if (*(void**)(base + 0x314) != NULL) {
			pawnReleaseBuffer(*(void**)(base + 0x314));
			*(void**)(base + 0x314) = NULL;
		}

		if (*(Collidable**)(base + 0x244) != NULL) {
			(*(Collidable**)(base + 0x244))->flags |= 1;
			*(Collidable**)(base + 0x244) = NULL;
		}

		if (*(void**)(base + 0x2DC) != NULL) {
			fn_8010AFE4(*(void**)(base + 0x2DC));
			*(void**)(base + 0x2DC) = NULL;
		}

		if (*(void**)(base + 0x2D8) != NULL) {
			fn_8010AFE4(*(void**)(base + 0x2D8));
			*(void**)(base + 0x2D8) = NULL;
		}

		if (*(VBase**)(base + 0x240) != NULL) {
			if (*(VBase**)(base + 0x240) != NULL) {
				(*(VBase**)(base + 0x240))->release(1);
			}
			*(VBase**)(base + 0x240) = NULL;
		}

		if (*(void**)(base + 0x280) != NULL) {
			dtor_800FE334(*(void**)(base + 0x280), 1);
			*(void**)(base + 0x280) = NULL;
		}

		if (*(void**)(base + 0x278) != NULL) {
			dtor_800FE334(*(void**)(base + 0x278), 1);
			*(void**)(base + 0x278) = NULL;
		}

		if (*(void**)(base + 0x270) != NULL) {
			dtor_800FE334(*(void**)(base + 0x270), 1);
			*(void**)(base + 0x270) = NULL;
		}

		if (*(void**)(base + 0x284) != NULL) {
			fn_80150958(*(void**)(base + 0x284));
			*(void**)(base + 0x284) = NULL;
		}

		if (*(void**)(base + 0x36C) != NULL) {
			fn_80150958(*(void**)(base + 0x36C));
			*(void**)(base + 0x36C) = NULL;
		}

		if (*(void**)(base + 0x368) != NULL) {
			fn_80150958(*(void**)(base + 0x368));
			*(void**)(base + 0x368) = NULL;
		}

		if (*(void**)(base + 0xE8) != NULL) {
			fn_80150958(*(void**)(base + 0xE8));
			*(void**)(base + 0xE8) = NULL;
		}

		__dt__10HAnimClassFv(base + 0x240, 0);
		fn_800A7088(object, 0);

		if (flags > 0) {
			fn_800189A4(lbl_8042C148, object);
		}
	}
	return object;
}
