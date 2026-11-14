// Allocates and initialises a 0x4C-byte header followed by count entries of entrySize bytes
// (HYPOTHESIS): records the count and entry size, sets the .sdata2 defaults lbl_804300F0 and
// lbl_804300F4, the index at 0x28 to -1 and the self pointer at 0x38, and clears the rest. The
// allocation is not checked. Returns the header. Field names are inferred from this function
// only.
#include "game/rw_engine.h"

struct Header8020C658 {
	void* field0;         // 0x0
	f32 value4;           // 0x4
	void* field8;         // 0x8
	void* fieldC;         // 0xC
	void* field10;        // 0x10
	f32 value14;          // 0x14
	void* field18;        // 0x18
	void* field1C;        // 0x1C
	s32 stride;           // 0x20
	s32 entrySize;        // 0x24
	s32 index;            // 0x28
	s32 count;            // 0x2C
	void* field30;        // 0x30
	void* field34;        // 0x34
	Header8020C658* self; // 0x38
	void* field3C;        // 0x3C
	void* field40;        // 0x40
	void* field44;        // 0x44
	void* field48;        // 0x48
};

extern "C" {
extern f32 lbl_804300F0;
extern f32 lbl_804300F4;

Header8020C658* fn_8020C658(s32 count, s32 entrySize)
{
	Header8020C658* header
	    = (Header8020C658*)lbl_8042C9A4->rwmalloc(count * entrySize + sizeof(Header8020C658));

	header->count     = count;
	header->field0    = 0;
	header->field8    = 0;
	header->value4    = lbl_804300F0;
	header->fieldC    = 0;
	header->value14   = lbl_804300F4;
	header->field10   = 0;
	header->field18   = 0;
	header->field1C   = 0;
	header->entrySize = entrySize;
	header->index     = -1;
	header->stride    = entrySize;
	header->field30   = 0;
	header->field34   = 0;
	header->self      = header;
	header->field3C   = 0;
	header->field44   = 0;
	header->field40   = 0;
	header->field48   = 0;
	return header;
}
}
