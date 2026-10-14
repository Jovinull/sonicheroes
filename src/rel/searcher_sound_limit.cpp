#include "types.h"

// TObjEnemySearcherSoundLimit (its class name string; searcherSoundLimit* here,
// the PS2 build has a general TEnemySELimit): a single object that collects up
// to four searchers a frame that want their sound and plays it for each, or
// does nothing while the game is paused or ending. The modules with the other
// searcher (stage28D, 31D-33D) share only the destructor, as
// rel/searcher_sound_limit_dtor.cpp. Two functions only forget the instance
// (their callers are inlined or gone; the names are ours).

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
	TObject base;        // 0x00
	s32 count;           // 0x28
	TObject* entries[4]; // 0x2C
} SearcherSoundLimit;

typedef struct GameState {
	u8 unk00[0x18];
	s32 mode; // 0x18
} GameState;

extern "C" GameState lbl_8029C310;
extern "C" void* lbl_8042C388;

extern "C" void* lbl_8042C114;
extern "C" void* lbl_8042C148;
extern "C" char* searcherSoundLimitClassName;
extern "C" void* searcherSoundLimitVtable[];
extern "C" SearcherSoundLimit* searcherSoundLimitInstance;

extern "C" void fn_800B4A38(void* sound, s32 id, void* position, void* owner, s32 a, s32 b, s32 c);
extern "C" void* Malloc__9THeapCtrlFUi(void* heap, u32 size);
extern "C" void Free__9THeapCtrlFPv(void* heap, TObject* object);
extern "C" void __dt__7TObjectFv(TObject* object, s32 flags);
extern "C" void __ct__7TObjectFP7TObject(TObject* object, void* parent);

static inline bool IsPausedMode(s32 mode)
{
	return mode == 1 || mode == 2;
}

static inline s32 IsStoppedMode(s32 mode)
{
	return IsPausedMode(mode) || mode == 3;
}

extern "C" void searcherSoundLimitExec(SearcherSoundLimit* self)
{
	if (IsStoppedMode(lbl_8029C310.mode)) {
		self->base.flags |= 1;
	} else {
		s32 i;

		for (i = 0; i < self->count; i++) {
			TObject* entry = self->entries[i];

			if (entry != NULL && lbl_8042C388 != NULL) {
				fn_800B4A38(lbl_8042C388, 0x4000, (u8*)entry + 0x140, entry, 3, 0, 2);
			}
		}
		self->count = 0;
	}
}

extern "C" void searcherSoundLimitEntry(SearcherSoundLimit* self, TObject* entry)
{
	if (self->count >= 4) {
		return;
	}
	self->entries[self->count++] = entry;
}

extern "C" SearcherSoundLimit* searcherSoundLimitDtor(SearcherSoundLimit* object, s16 flags)
{
	if (object != NULL) {
		object->base.vtable = searcherSoundLimitVtable;

		searcherSoundLimitInstance = NULL;
		__dt__7TObjectFv(&object->base, 0);

		if (flags > 0) {
			Free__9THeapCtrlFPv(lbl_8042C148, &object->base);
		}
	}
	return object;
}

extern "C" SearcherSoundLimit* searcherSoundLimitCtor(SearcherSoundLimit* self, void* parent)
{
	__ct__7TObjectFP7TObject(&self->base, parent);
	self->base.vtable = searcherSoundLimitVtable;
	self->base.name   = searcherSoundLimitClassName;
	self->base.size   = sizeof(SearcherSoundLimit);
	self->entries[0]  = NULL;
	self->entries[1]  = NULL;
	self->entries[2]  = NULL;
	self->entries[3]  = NULL;
	self->count       = 0;

	searcherSoundLimitInstance = self;
	return self;
}

extern "C" void searcherSoundLimitAdd(TObject* entry)
{
	if (searcherSoundLimitInstance != NULL) {
		searcherSoundLimitEntry(searcherSoundLimitInstance, entry);
	}
}

extern "C" void searcherSoundLimitCreate(void)
{
	if (searcherSoundLimitInstance == NULL) {
		SearcherSoundLimit* self
		    = (SearcherSoundLimit*)Malloc__9THeapCtrlFUi(lbl_8042C148, sizeof(SearcherSoundLimit));

		if (self != NULL) {
			searcherSoundLimitCtor(self, lbl_8042C114);
		}
	}
}

extern "C" void searcherSoundLimitForget(void)
{
	searcherSoundLimitInstance = NULL;
}

extern "C" void searcherSoundLimitForget2(void)
{
	searcherSoundLimitInstance = NULL;
}
