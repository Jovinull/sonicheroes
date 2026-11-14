// Creates a list of 0x9C-byte entries matching the word list at offset 0x4 of the source
// (HYPOTHESIS: RenderWare SList helpers _rwSListCreate, _rwSListGetNumEntries,
// _rwSListGetNewEntries and _rwSListGetArray): one entry per source word, holding that word with
// its other known fields cleared. The new list is not checked for allocation failure. Returns the
// list. Field names are inferred from this function only.
#include "game/rw_engine.h"

struct Entry802013C4 {
	void* field0; // 0x0
	u32 id;       // 0x4
	void* field8; // 0x8
	u8 padC[0x4C - 0xC];
	void* field4C; // 0x4C
	u8 pad50[0x60 - 0x50];
	void* field60; // 0x60
	u8 pad64[0x74 - 0x64];
	void* field74; // 0x74
	u8 pad78[0x88 - 0x78];
	void* field88; // 0x88
	u8 pad8C[0x9C - 0x8C];
};

struct Source802013C4 {
	u8 pad0[0x4];
	RwSList* ids; // 0x4: list of u32
};

extern "C" {
RwSList* fn_80194318(s32 entrySize);
void* fn_80194510(RwSList* list, s32 count);
void* fn_8019460C(RwSList* list);
s32 fn_8019469C(RwSList* list);

RwSList* fn_802013C4(Source802013C4* source)
{
	Entry802013C4* array;
	Entry802013C4* entry;
	Entry802013C4* end;
	RwSList* list;
	u32* id;

	list = fn_80194318(sizeof(Entry802013C4));

	if (fn_8019469C(source->ids)) {
		fn_80194510(list, fn_8019469C(source->ids));
		array = (Entry802013C4*)fn_8019460C(list);
		end   = array + fn_8019469C(list);
		id    = (u32*)fn_8019460C(source->ids);
		for (entry = array; entry != end; entry++) {
			entry->field0  = 0;
			entry->field8  = 0;
			entry->field4C = 0;
			entry->field60 = 0;
			entry->field74 = 0;
			entry->field88 = 0;
			entry->id      = *id++;
		}
	}
	return list;
}
}
