#include "types.h"

// The constructor of the object each searcher builds into its +0x2F0 field
// (searcherGroundCtor here; the destructor is rel/searcher_ground_dtor.cpp),
// the same in the thirteen stage modules that share the engine core: a TObject
// that moves on the ground, with one collision volume of kind 3 whose 0x40 flag
// is cleared.
//
// stage27D, stage28D and stage31D to stage33D carry it without a caller, so
// it is kept there with force_active.

typedef struct TObject {
	u8 unk00[0x18];
	void** vtable; // 0x18
	u8 unk1C[0xC];
} TObject;

typedef struct SearcherGround {
	TObject base;          // 0x00
	u8 moveOnGround[0x38]; // 0x28
	u8 volume[0x8];        // 0x60
	u16 volumeFlags;       // 0x68
	u8 pad6A[0x2];
	f32 volumeRadius; // 0x6C
	u8 unk70[0x78];
	f32 unkE8; // 0xE8
	f32 unkEC; // 0xEC
	s32 unkF0; // 0xF0
	f32 unkF4; // 0xF4
} SearcherGround;

extern "C" void* searcherGroundVtable[];
extern "C" u8 searcherGroundVolumeInfo[];
extern "C" const f32 searcherGroundUnkE8;
extern "C" const f32 searcherGroundUnkF4;
extern "C" const f32 searcherGroundRadius;

extern "C" void __ct__7TObjectFP7TObject(TObject* object, TObject* parent);
extern "C" void __ct__16OBJ_MoveOnGroundFv(void* move);
extern "C" void __ct__7C_COLLIFv(void* volume);
extern "C" void Init__7C_COLLIFP8CCL_INFOiUc(void* volume, void* info, s32 count, u8 kind);

extern "C" SearcherGround* searcherGroundCtor(SearcherGround* object, TObject* parent)
{
	__ct__7TObjectFP7TObject(&object->base, parent);
	__ct__16OBJ_MoveOnGroundFv(object->moveOnGround);
	__ct__7C_COLLIFv(object->volume);
	object->base.vtable = searcherGroundVtable;
	object->unkE8       = searcherGroundUnkE8;
	object->unkEC       = searcherGroundUnkE8;
	object->unkF4       = searcherGroundUnkF4;
	Init__7C_COLLIFP8CCL_INFOiUc(object->volume, searcherGroundVolumeInfo, 1, 3);
	object->volumeFlags &= ~0x40;
	object->volumeRadius = searcherGroundRadius;
	object->unkF0        = 0;
	return object;
}
