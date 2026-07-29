#include "types.h"

struct Vec3 {
	float x, y, z;
};

struct TObject {
	const char* className;
	u16 signal;
	u16 tag;
	TObject* prev;
	TObject* next;
	TObject* parent;
	TObject* child;
	void** vtable;
	s16 unk1C;
	s16 objectSize;
	s16 unk20;
	s16 unk22;
	s16 unk24;
	s16 unk26;

	TObject(TObject*);
	~TObject();
	static void* operator new(unsigned long);
	static void operator delete(void*);
};

struct VoiceEntry {
	s32 id;
	Vec3 position;
};

struct TEnemyVoiceCtrlEx : TObject {
	s32 capacity;
	s32 count;
	u32 voice;
	s32 mode;
	VoiceEntry* entries;

	TEnemyVoiceCtrlEx(s32, u32, s32);
};

struct SEEntry {
	s32 id;
	s32 type;
};

struct TEnemySELimit : TObject {
	SEEntry* entries;
	s32 count;
	s32 index;

	TEnemySELimit(void*, const SEEntry*);
};

struct TEnemyVoiceCtrl : TObject {
	s32* entries;
	s32 count;
	s32 index;

	TEnemyVoiceCtrl(void*, const s32*);
};

struct AudioState {
	u8 pad00[0x30];
	s32 field30;
	u8 pad34[8];
	s32 field3C;
	u8 pad40[0x18];
	s32 field58;
};

enum GameMode {
	GAME_MODE_ONE   = 1,
	GAME_MODE_TWO   = 2,
	GAME_MODE_THREE = 3,
};

struct GameModeState {
	u8 pad00[0x18];
	s32 mode;
};

struct Heap;

extern "C" {
extern void* lbl_8028CFE4[];
extern void* lbl_8028D010[];
extern void* lbl_8028D03C[];
extern Heap* lbl_8042C148;
extern TObject* lbl_8042C114;
extern void* lbl_8042C388;
extern AudioState* lbl_8042C610;

extern const char* lbl_8042BCB8;
extern const char* lbl_8042BCB4;
extern const char* lbl_8042BCB0;
extern GameModeState lbl_8029C310;

void __dt__7TObjectFv(TObject*, s32);
void __ct__7TObjectFP7TObject(TObject*, void*);
void fn_800189A4(void*, void*);
void* fn_80018A34(Heap*, u32);
void* fn_800575C8(u32);
void fn_80057578(void*);
void fn_800B4A38(void*, u16, Vec3*, s32, s32, s32, s32);
void* memcpy(void*, const void*, u32);
s32 fn_80103178(s32);
void fn_80111260(AudioState*, s32, s32);
void fn_801112F0(AudioState*, s32);
void fn_8001898C();
void fn_80018984();
void fn_80018988();
void fn_80018950();
void fn_80018954();
void fn_80017854();
void fn_80018958();
}

inline void* TObject::operator new(unsigned long size)
{
	return fn_80018A34(lbl_8042C148, size);
}

inline TEnemyVoiceCtrlEx::TEnemyVoiceCtrlEx(s32 mode_, u32 voice_, s32 capacity_)
    : TObject(lbl_8042C114)
{
	vtable     = lbl_8028CFE4;
	className  = lbl_8042BCB8;
	objectSize = sizeof(TEnemyVoiceCtrlEx);
	capacity   = capacity_;
	count      = 0;
	voice      = voice_;
	mode       = mode_;
	entries    = (VoiceEntry*)fn_800575C8(capacity * sizeof(VoiceEntry));
}

inline TEnemySELimit::TEnemySELimit(void* owner, const SEEntry* source)
    : TObject((TObject*)owner)
{
	vtable               = lbl_8028D010;
	className            = lbl_8042BCB4;
	objectSize           = sizeof(TEnemySELimit);
	entries              = NULL;
	count                = 0;
	index                = 0;
	const SEEntry* entry = source;
	while (1) {
		if (entry->id == -1)
			break;
		entry++;
		count++;
	}
	if (count > 0) {
		entries = (SEEntry*)fn_800575C8(count * sizeof(SEEntry));
		memcpy(entries, source, count * sizeof(SEEntry));
	}
}

inline TEnemyVoiceCtrl::TEnemyVoiceCtrl(void* owner, const s32* source)
    : TObject((TObject*)owner)
{
	vtable           = lbl_8028D03C;
	className        = lbl_8042BCB0;
	objectSize       = sizeof(TEnemyVoiceCtrl);
	entries          = NULL;
	count            = 0;
	index            = 0;
	const s32* entry = source;
	while (1) {
		if (*entry == -1)
			break;
		entry++;
		count++;
	}
	if (count > 0) {
		entries = (s32*)fn_800575C8(count * sizeof(s32));
		memcpy(entries, source, count * sizeof(s32));
	}
}

static inline s32 IsInvalidGameMode(s32 mode)
{
	return mode == GAME_MODE_ONE || mode == GAME_MODE_TWO || mode == GAME_MODE_THREE;
}

extern "C" void fn_80139738(TEnemyVoiceCtrlEx* self, const VoiceEntry* entry)
{
	if (self->count >= self->capacity)
		return;
	self->entries[self->count] = *entry;
	self->count++;
}

extern "C" void fn_80139784(TEnemyVoiceCtrlEx* self, s32 id, const Vec3* position)
{
	if (self->count >= self->capacity)
		return;
	self->entries[self->count].id       = id;
	self->entries[self->count].position = *position;
	self->count++;
}

extern "C" void fn_801397DC(TEnemyVoiceCtrlEx* self)
{
	s32 i;
	s32 j;
	switch (self->mode) {
		case 0:
			for (i = 0; i < self->count; i++) {
				if (lbl_8042C388 != NULL)
					fn_800B4A38(
					    lbl_8042C388, (u16)self->voice, &self->entries[i].position, 0, 1, 0, 0);
			}
			break;
		case 1:
			for (j = 0; j < self->count; j++) {
				if (lbl_8042C388 != NULL)
					fn_800B4A38(lbl_8042C388, (u16)self->voice, &self->entries[j].position,
					    self->entries[j].id, 3, 0, 2);
			}
			break;
	}
	self->count = 0;
}

extern "C" TEnemyVoiceCtrlEx* fn_801398E4(TEnemyVoiceCtrlEx* self, s16 flags)
{
	if (self != NULL) {
		self->vtable = lbl_8028CFE4;
		if (self->entries != NULL) {
			fn_80057578(self->entries);
			self->entries = NULL;
		}
		self->voice    = 0;
		self->count    = 0;
		self->capacity = 0;
		self->mode     = 2;
		__dt__7TObjectFv(self, 0);
		if (flags > 0)
			fn_800189A4(lbl_8042C148, self);
	}
	return self;
}

extern "C" TEnemyVoiceCtrlEx* fn_80139984(s32 mode, u32 voice, s32 capacity)
{
	return new TEnemyVoiceCtrlEx(mode, voice, capacity);
}

extern "C" void fn_80139A24(TEnemySELimit* self)
{
	s32 ready;
	if (*(volatile s32*)&self->count == 0) {
		self->signal |= 1;
		return;
	}
	s32 invalid = IsInvalidGameMode(lbl_8029C310.mode);
	if (invalid) {
		self->signal |= 1;
		return;
	}
	s32 index = self->index;
	if (index > self->count - 1) {
		self->signal |= 1;
		return;
	}
	AudioState* audio = lbl_8042C610;
	ready             = 0;
	if (audio->field30 == 0 && audio->field3C == 0 && audio->field58 == -1)
		ready = 1;
	if (!ready)
		return;

	if (self->entries[index].type == 0) {
		s32 handle = fn_80103178(0);
		if (handle == -1)
			return;
		fn_80111260(lbl_8042C610, handle, self->entries[self->index].id);
		self->index++;
	} else if (self->entries[index].type == 1) {
		fn_801112F0(lbl_8042C610, self->entries[index].id);
		self->index++;
	} else {
		self->signal |= 1;
	}
}

extern "C" TEnemySELimit* fn_80139BB8(TEnemySELimit* self, s16 flags)
{
	if (self != NULL) {
		self->vtable = lbl_8028D010;
		if (self->entries != NULL) {
			fn_80057578(self->entries);
			self->entries = NULL;
		}
		__dt__7TObjectFv(self, 0);
		if (flags > 0)
			fn_800189A4(lbl_8042C148, self);
	}
	return self;
}

extern "C" void fn_80139C40(void* owner, const SEEntry* source)
{
	new TEnemySELimit(owner, source);
}

extern "C" void fn_80139D28(TEnemyVoiceCtrl* self)
{
	if (*(volatile s32*)&self->count == 0) {
		self->signal |= 1;
		return;
	}
	s32 invalid = IsInvalidGameMode(lbl_8029C310.mode);
	if (invalid) {
		self->signal |= 1;
		return;
	}
	if (self->index > self->count - 1) {
		self->signal |= 1;
		return;
	}
	AudioState* audio = lbl_8042C610;
	s32 ready         = 0;
	if (audio->field30 == 0 && audio->field3C == 0 && audio->field58 == -1)
		ready = 1;
	if (!ready)
		return;
	fn_801112F0(audio, self->entries[self->index]);
	self->index++;
}

extern "C" TEnemyVoiceCtrl* fn_80139E54(TEnemyVoiceCtrl* self, s16 flags)
{
	if (self != NULL) {
		self->vtable = lbl_8028D03C;
		if (self->entries != NULL) {
			fn_80057578(self->entries);
			self->entries = NULL;
		}
		__dt__7TObjectFv(self, 0);
		if (flags > 0)
			fn_800189A4(lbl_8042C148, self);
	}
	return self;
}

extern "C" void fn_80139EDC(void* owner, const s32* source)
{
	new TEnemyVoiceCtrl(owner, source);
}

extern "C" {
char lbl_8028CFB0[] = "TEnemyVoiceCtrl";
char lbl_8028CFC0[] = "TEnemyVoiceCtrlEx";
char lbl_8028CFD4[] = "TEnemySELimit";

void* lbl_8028CFE4[] = {
	NULL,
	NULL,
	(void*)fn_801398E4,
	(void*)fn_801397DC,
	(void*)fn_8001898C,
	(void*)fn_80018984,
	(void*)fn_80018988,
	(void*)fn_80018950,
	(void*)fn_80018954,
	(void*)fn_80017854,
	(void*)fn_80018958,
};

void* lbl_8028D010[] = {
	NULL,
	NULL,
	(void*)fn_80139BB8,
	(void*)fn_80139A24,
	(void*)fn_8001898C,
	(void*)fn_80018984,
	(void*)fn_80018988,
	(void*)fn_80018950,
	(void*)fn_80018954,
	(void*)fn_80017854,
	(void*)fn_80018958,
};

void* lbl_8028D03C[] = {
	NULL,
	NULL,
	(void*)fn_80139E54,
	(void*)fn_80139D28,
	(void*)fn_8001898C,
	(void*)fn_80018984,
	(void*)fn_80018988,
	(void*)fn_80018950,
	(void*)fn_80018954,
	(void*)fn_80017854,
	(void*)fn_80018958,
};
}
