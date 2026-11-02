#include "types.h"

// The searcher sound limiter of the bonus stages (31D-33D; their searcher is
// the other kind, see rel/searcher_sound_limit.cpp): its constructor
// (searcherSoundLimitCtor here), which clears its fields (2.5 at 0x40) and
// becomes the instance, the kill request for the instance
// (searcherSoundLimitKill) and the create (searcherSoundLimitCreate), which
// makes the instance once (the constructor inlined) and returns it.

typedef struct TObject {
	char* name; // 0x00
	u16 flags;  // 0x04
	u8 unk06[0x12];
	void** vtable; // 0x18
	u8 unk1C[0x2];
	u16 size; // 0x1E
	u8 unk20[0x8];
} TObject;

typedef struct SearcherSoundLimit {
	TObject base; // 0x00
	s32 count;    // 0x28
	u8 unk2C[0x4];
	f32 unk30; // 0x30
	f32 unk34; // 0x34
	f32 unk38; // 0x38
	f32 unk3C; // 0x3C
	f32 unk40; // 0x40
	u8 unk44[0x4];
	f32 unk48; // 0x48
	f32 unk4C; // 0x4C
	s32 unk50; // 0x50
} SearcherSoundLimit;

extern "C" char* searcherSoundLimitClassName;
extern "C" void* searcherSoundLimitVtable[];
extern "C" SearcherSoundLimit* searcherSoundLimitInstance;
extern "C" const f32 searcherSoundLimitZero;
extern "C" const f32 searcherSoundLimitReach;
extern "C" TObject* lbl_8042C0FC;
extern "C" void* lbl_8042C148;

extern "C" void __ct__7TObjectFP7TObject(TObject* object, TObject* parent);
extern "C" void* Malloc__9THeapCtrlFUi(void* heap, u32 size);

static inline SearcherSoundLimit* searcherSoundLimitInit(
    SearcherSoundLimit* object, TObject* parent)
{
	__ct__7TObjectFP7TObject(&object->base, parent);
	object->base.vtable = searcherSoundLimitVtable;
	object->unk30 = object->unk34 = object->unk38 = searcherSoundLimitZero;
	object->unk38                                 = searcherSoundLimitZero;
	object->unk3C                                 = searcherSoundLimitZero;
	object->unk40                                 = searcherSoundLimitReach;
	object->unk48                                 = searcherSoundLimitZero;
	object->unk4C                                 = searcherSoundLimitZero;
	object->unk50                                 = 0;
	object->base.name                             = searcherSoundLimitClassName;
	object->base.size                             = 0x54;
	object->count                                 = 0;
	searcherSoundLimitInstance                    = object;
	return object;
}

extern "C" SearcherSoundLimit* searcherSoundLimitCtor(SearcherSoundLimit* object, TObject* parent)
{
	return searcherSoundLimitInit(object, parent);
}

extern "C" void searcherSoundLimitKill(void)
{
	if (searcherSoundLimitInstance != NULL) {
		searcherSoundLimitInstance->base.flags |= 1;
	}
}

static inline void searcherSoundLimitNew(void)
{
	if (searcherSoundLimitInstance == NULL) {
		SearcherSoundLimit* object = (SearcherSoundLimit*)Malloc__9THeapCtrlFUi(lbl_8042C148, 0x54);

		if (object != NULL) {
			searcherSoundLimitInit(object, lbl_8042C0FC);
		}
	}
}

extern "C" SearcherSoundLimit* searcherSoundLimitCreate(void)
{
	if (searcherSoundLimitInstance == NULL) {
		searcherSoundLimitNew();
	}
	return searcherSoundLimitInstance;
}
