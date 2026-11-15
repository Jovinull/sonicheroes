// Reads a timed list from a stream (HYPOTHESIS): reads the entry count, creates the 8-byte entry
// array (fn_80194318) sized for it, resets the list state (defaults lbl_8042FF68/lbl_8042FF6C, a
// flag of 1, no cursor and no latest entry), then for each entry reads its time and the payload
// that follows its 0x1B0 chunk (fn_80201ABC), keeping the cursor at the array start and the
// latest entry by time. Returns the list, or null on a read failure. Names are inferred from this
// function only.
#include "game/rw_engine.h"

struct Entry80200934 {
	f32 time;   // 0x0
	void* data; // 0x4
};

struct TimedList80200934 {
	RwSList* entries;      // 0x0
	f32 value4;            // 0x4
	f32 value8;            // 0x8
	s32 flagC;             // 0xC
	s32 value10;           // 0x10
	Entry80200934* cursor; // 0x14
	Entry80200934* latest; // 0x18
};

#define CHUNK_ID_80200934 0x1B0

extern "C" {
extern f32 lbl_8042FF68;
extern f32 lbl_8042FF6C;
// HYPOTHESIS: RwStreamRead, RwMemNative32, _rwSListCreate, _rwSListGetNewEntries,
// _rwSListGetArray and RwStreamFindChunk.
u32 fn_801979AC(void* stream, void* buffer, u32 length);
void* fn_80193270(void* mem, u32 size);
RwSList* fn_80194318(s32 entrySize);
void* fn_80194510(RwSList* sList, s32 count);
void* fn_8019460C(RwSList* sList);
s32 fn_80192F38(void* stream, u32 type, u32* length, u32* version);
void* fn_80201ABC(void* stream);

TimedList80200934* fn_80200934(TimedList80200934* list, void* stream)
{
	u32 count = 0;
	u32 reserve;
	Entry80200934* end;
	Entry80200934* entry;

	if (fn_801979AC(stream, &count, sizeof(count)) != sizeof(count)) {
		return 0;
	}
	fn_80193270(&count, sizeof(count));
	reserve       = count;
	list->entries = fn_80194318(sizeof(Entry80200934));
	if (reserve != 0) {
		fn_80194510(list->entries, reserve);
	}
	list->value4  = lbl_8042FF68;
	list->value8  = lbl_8042FF6C;
	list->flagC   = 1;
	list->value10 = 0;
	list->cursor  = 0;
	list->latest  = 0;

	{
		Entry80200934* array = (Entry80200934*)fn_8019460C(list->entries);
		entry                = array;
		end                  = array + count;
	}
	for (; entry != end; entry++) {
		f32 time;
		void* data;

		if (fn_801979AC(stream, &time, sizeof(time)) != sizeof(time)) {
			return 0;
		}
		fn_80193270(&time, sizeof(time));
		entry->time = time;
		if (!fn_80192F38(stream, CHUNK_ID_80200934, 0, 0)) {
			return 0;
		}
		data = fn_80201ABC(stream);
		if (data == 0) {
			return 0;
		}
		entry->data  = data;
		list->cursor = (Entry80200934*)fn_8019460C(list->entries);
		if (list->latest == 0 || time > list->latest->time) {
			list->latest = entry;
		}
	}
	return list;
}
}
