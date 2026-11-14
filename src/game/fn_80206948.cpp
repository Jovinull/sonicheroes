// Starts a note on an audio pool slot (see game/audio_system.h): looks up how many voices the
// channel's bank/program needs for the key (fn_80207D7C), frees enough voices by stealing notes of
// at most `priority` when the free voices do not cover it, or else takes a free note object
// (stealing one when none is free), then fills it, gives it its voices (fn_80208CE4 and
// fn_8020735C) and starts them (fn_80207C58). Returns the note, or null when the key has no
// records or no note or voice could be had.
// NonMatching: 366 of 367 instructions with the same control flow; saved registers are colored
// differently (retail keeps need in r31, program in r30, bank in r24 and shares r3 between the
// steal loop index and the note), so most words differ. Compiled with -use_lmw_stmw on.
#include "game/audio_system.h"

extern "C" {
int fn_80207D7C(int bank, unsigned int index, int key);
int fn_80208C38(void);
PoolListNode* fn_80206328(PoolListNode** list, PoolListNode* prev);
PoolListNode* fn_80206340(PoolListNode** list, int (*pred)(PoolListNode* node));
void fn_8020641C(PoolListNode* target, PoolListNode** list, void (*fn)(PoolListNode* node));
int fn_80206804(PoolListNode* node);
void fn_80206890(PoolListNode* node);
PoolEntry10C* fn_80208CE4(PoolObject* note, int b, int c);
int fn_8020735C(PoolListNode** list, PoolEntry10C* voice);
void fn_80207C58(PoolListNode** list, int bank, unsigned int index, int key, int param);

// Removes a note from its slot's object list.
static inline void ReleaseNote(PoolObject* note)
{
	if (note != 0) {
		PoolListNode** objects = &note->slot->objects;
		if (*objects != 0) {
			PoolListNode* found;
			lbl_8042CF6C->searchKey = note;
			found                   = fn_80206340(objects, fn_80206804);
			if (found != 0) {
				fn_8020641C(found, objects, fn_80206890);
			}
		}
	}
}

// Takes the next used note of at most `priority`, releasing it.
static inline PoolObject* StealNote(int priority)
{
	int i;
	for (i = 0; i < 0x40; i++) {
		int index        = (lbl_8042CF6C->nextNote + i) % 0x40;
		PoolObject* note = &lbl_8042CF6C->notes[index];
		if (note->used != 0 && note->priority <= priority) {
			ReleaseNote(note);
			lbl_8042CF6C->nextNote = index + 1;
			return &lbl_8042CF6C->notes[index];
		}
	}
	return 0;
}

// Takes the next unused note.
static inline PoolObject* FindFreeNote(void)
{
	int i;
	for (i = 0; i < 0x40; i++) {
		int index = (lbl_8042CF6C->nextNote + i) % 0x40;
		if (lbl_8042CF6C->notes[index].used == 0) {
			lbl_8042CF6C->nextNote = index + 1;
			return &lbl_8042CF6C->notes[index];
		}
	}
	return 0;
}

PoolObject* fn_80206948(
    PoolSlot* s, unsigned int ch, unsigned int key, unsigned int velocity, int priority)
{
	int program = s->channels[ch].f0C;
	int bank    = s->channels[ch].f08;
	int need    = fn_80207D7C(bank, program, key);
	int over;
	PoolObject* note;
	int i;
	if (need <= 0) {
		return 0;
	}
	over = need - (lbl_8042CF6C->voiceCount - fn_80208C38());
	if (over < 0) {
		over = 0;
	}
	if (over != 0) {
		note = 0;
		if (over <= 0) {
			note = StealNote(priority);
		} else {
			int remaining = over;
			while (remaining > 0) {
				for (i = 0; i < 0x40; i++) {
					int index     = (lbl_8042CF6C->nextNote + i) % 0x40;
					PoolObject* p = &lbl_8042CF6C->notes[index];
					if (p->used != 0 && p->priority <= priority) {
						int voices = 0;
						if (p != 0) {
							PoolListNode* v;
							for (v = 0; (v = fn_80206328(&p->entries, v)) != 0;) {
								if (v->data != 0) {
									voices++;
								}
							}
						}
						remaining -= voices;
						ReleaseNote(p);
						lbl_8042CF6C->nextNote = index + 1;
						note                   = &lbl_8042CF6C->notes[index];
						break;
					}
				}
				if (remaining == over) {
					break;
				}
			}
		}
		if (note == 0) {
			return 0;
		}
	} else {
		note = FindFreeNote();
		if (note == 0) {
			note = StealNote(priority);
			if (note == 0) {
				return 0;
			}
		}
	}
	note->slot     = s;
	note->key      = key;
	note->channel  = ch;
	note->velocity = velocity;
	note->priority = priority;
	note->count    = need;
	note->used     = 1;
	note->entries  = 0;
	for (i = 0; i < need; i++) {
		PoolEntry10C* voice = fn_80208CE4(note, 5, 0);
		if (voice == 0) {
			ReleaseNote(note);
			return 0;
		}
		if (fn_8020735C(&note->entries, voice) == 0) {
			ReleaseNote(note);
			return 0;
		}
	}
	fn_80207C58(&note->entries, bank, program, key, velocity);
	return note;
}
}
