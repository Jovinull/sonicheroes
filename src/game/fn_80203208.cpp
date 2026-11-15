// Reads the typed entry table of an fn_802038AC object from a stream (HYPOTHESIS; the reader
// counterpart of fn_80202EF0): reads the entry count, creates the object's two growable arrays
// when missing (4-byte list at +0x18, 0x10-byte entries at +0x14, as fn_80202E8C does), appends
// that many entries and reads each one's type, id, value and fourth word before handing it to
// the type's reader in lbl_80298DF8. Returns the object, or null on failure. Names follow
// fn_80202EF0.
#include "game/object_802038AC.h"

struct Entry80203208 {
	s32 type; // 0x0
	s32 id;   // 0x4: -1 when unused
	union {
		s32 value;
		void* data;
	} u;       // 0x8
	s32 wordC; // 0xC
};

// Per-type handlers, 0xC bytes each; the stream reader is the second word.
struct EntryType80203208 {
	void* destroy;                                                             // 0x0
	void* (*read)(Object802038AC* object, Entry80203208* entry, void* stream); // 0x4
	void* copy;                                                                // 0x8
};

extern "C" {
extern EntryType80203208 lbl_80298DF8[];
// HYPOTHESIS: RwStreamReadInt32 and the SList helpers.
void* fn_80193884(void* stream, void* ints, u32 numBytes);
RwSList* fn_80194318(s32 entrySize);
void* fn_80194510(RwSList* sList, s32 count);
}

// Creates the object's entry arrays (the body of fn_80202E8C). Returns the object, or null.
static inline Object802038AC* CreateLists80203208(Object802038AC* object)
{
	if ((object->part18 = fn_80194318(sizeof(s32))) == 0) {
		return 0;
	}
	if ((object->part14 = fn_80194318(sizeof(Entry80203208))) == 0) {
		return 0;
	}
	return object;
}

static inline Entry80203208* ReadEntry80203208(
    Object802038AC* object, Entry80203208* entry, void* stream)
{
	entry->type    = 0;
	entry->id      = -1;
	entry->u.value = 0;
	entry->u.data  = 0;
	if (fn_80193884(stream, &entry->type, sizeof(s32)) == 0) {
		return 0;
	}
	if (fn_80193884(stream, &entry->id, sizeof(s32)) == 0) {
		return 0;
	}
	if (fn_80193884(stream, &entry->u, sizeof(s32)) == 0) {
		return 0;
	}
	if (fn_80193884(stream, &entry->wordC, sizeof(s32)) == 0) {
		return 0;
	}
	if (lbl_80298DF8[entry->type].read(object, entry, stream) == 0) {
		return 0;
	}
	return entry;
}

extern "C" {
Object802038AC* fn_80203208(Object802038AC* object, void* stream)
{
	s32 count;

	if (fn_80193884(stream, &count, sizeof(count)) == 0) {
		return 0;
	}
	if (count > 0) {
		s32 i;
		Entry80203208* entry;
		if (object->part14 == 0 && CreateLists80203208(object) == 0) {
			return 0;
		}
		entry = (Entry80203208*)fn_80194510((RwSList*)object->part14, count);
		if (entry == 0) {
			return 0;
		}
		for (i = 0; i < count; i++) {
			if (ReadEntry80203208(object, entry, stream) == 0) {
				return 0;
			}
			entry++;
		}
	}
	return object;
}
}
