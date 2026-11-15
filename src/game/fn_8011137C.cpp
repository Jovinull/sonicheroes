// Starts a clip of a player (HYPOTHESIS; names inferred) when it is idle (no data, no sound
// handle): for the languages 1-5 swaps the ids 0x188/0x18E for 0x2CB/0x2CC, then finds the entry
// of that id in its table (0x80) matching the variant (-1 matches any; entries with variant -1
// match every variant), ending at an empty entry. A found entry becomes current (data, length,
// start, variant, index) and, when the sound table lbl_8025BA98 has a sound for the id and
// variant, that sound is played (fn_800CB368). Returns 0 when busy, 1 otherwise.
// NonMatching: register allocation of the table walk differs (declaration orders tried).
#include "types.h"

struct Entry8011137C {
	s16 id;      // 0x0
	s16 variant; // 0x2
	u32 data;    // 0x4
	s16 length;  // 0x8
	s16 start;   // 0xA
};

struct Sound8011137C {
	s32 value; // 0x0
	s16 id;    // 0x4
	s16 sub;   // 0x6
};

struct Player8011137C {
	u8 pad0[0x2C];
	u32 data;             // 0x2C
	s32 length;           // 0x30
	s32 id;               // 0x34
	s32 requested;        // 0x38
	s32 start;            // 0x3C
	s32 position;         // 0x40
	s32 variant;          // 0x44
	s32 requestedVariant; // 0x48
	s32 index;            // 0x4C
	s32 first;            // 0x50
	s32 unk54;            // 0x54
	s32 handle;           // 0x58
	s32 sound;            // 0x5C
	u8 pad60[0x64 - 0x60];
	s32 unk64; // 0x64
	s32 unk68; // 0x68
	u8 pad6C[0x80 - 0x6C];
	Entry8011137C* entries; // 0x80
};

struct MainState8011137C {
	u8 pad0[0x13];
	s8 language; // 0x13
};

extern "C" {
extern MainState8011137C* lbl_8042C180;
extern Sound8011137C lbl_8025BA98[];
s32 fn_800CB368(s32 sound, s32 mode, s32 variant);
}

static inline s32 findSound(Player8011137C* self)
{
	s32 id = self->id;
	s32 i;

	for (i = 0; lbl_8025BA98[i].id != -1; i++) {
		if (id == lbl_8025BA98[i].id && self->variant == lbl_8025BA98[i].sub) {
			return lbl_8025BA98[i].value;
		}
	}
	return -1;
}

extern "C" s32 fn_8011137C(Player8011137C* self, s32 variant, s32 id)
{
	Entry8011137C* entry;
	s32 target;
	s32 language;
	s32 i;

	if (self->data != 0 || self->handle != -1) {
		return 0;
	}
	i        = 0;
	language = lbl_8042C180->language;
	if (language == 1 || (u32)(language - 2) <= 2 || language == 5) {
		if (id == 0x188) {
			id = 0x2CB;
		} else if (id == 0x18E) {
			id = 0x2CC;
		}
	}
	self->requested = id;
	self->id        = id;
	entry           = self->entries;
	target          = self->id;
	for (;; entry++, i++) {
		s16 entryId      = entry->id;
		s16 entryVariant = entry->variant;

		if (entryId == target && (variant == -1 || entryVariant == variant || entryVariant == -1)) {
			self->requestedVariant = variant;
			self->start = self->position = self->entries[i].start;
			self->data                   = self->entries[i].data;
			self->length                 = self->entries[i].length;
			self->variant                = entryVariant;
			self->unk54                  = 0;
			self->index = self->first = i;
			self->unk64 = self->unk68 = -1;
			self->sound               = findSound(self);
			if (self->sound != -1) {
				self->handle = fn_800CB368(self->sound, 3, self->variant);
			}
			break;
		}
		if (entryId == 0 && self->entries[i].length == 0 && self->entries[i].data == 0) {
			break;
		}
	}
	return 1;
}
