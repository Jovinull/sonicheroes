// Closes a stream (HYPOTHESIS: RwStreamClose): file streams (type 2) close their file with the
// engine fclose (the result is whether it returned 0), memory streams (type 3) not opened for
// reading report their block (start at 0x14, size at 0xC) through the optional memory
// descriptor, custom streams (type 4) call their close callback with their data; type 1 needs
// nothing. Other types record core error 0xE and return 0. A stream allocated by the engine
// (word 0x20) goes back to the stream free list. Field names are inferred from this function.
#include "game/rw_engine.h"

struct Stream80197ED8 {
	s32 type;       // 0x0
	s32 accessType; // 0x4: 1 = read
	u8 pad8[0x4];
	void* word0C; // 0xC: file, memory size or custom close callback
	u8 pad10[0x4];
	void* word14; // 0x14: memory start
	u8 pad18[0x4];
	void* customData; // 0x1C
	s32 rwOwned;      // 0x20
};

// Memory block descriptor (HYPOTHESIS: RwMemory).
struct Memory80197ED8 {
	void* start;  // 0x0
	void* length; // 0x4
};

extern "C" {
// Stream module bookkeeping; the stream free list is the first field of its globals.
extern RwModuleInfo lbl_8042C978;

s32 fn_80197ED8(Stream80197ED8* stream, Memory80197ED8* memory)
{
	s32 result;

	switch (stream->type) {
		case 1:
			result = 1;
			break;
		case 2:
			result = (lbl_8042C9A4->rwfclose(stream->word0C) == 0) ? 1 : 0;
			break;
		case 3:
			if (stream->accessType != 1 && memory) {
				memory->start  = stream->word14;
				memory->length = stream->word0C;
			}
			result = 1;
			break;
		case 4:
			if (stream->word0C) {
				((void (*)(void*))stream->word0C)(stream->customData);
			}
			result = 1;
			break;
		default: {
			RwError error;
			error.pluginID  = RW_ID_CORE_PLUGIN;
			error.errorCode = fn_8019408C(0xE);
			fn_80193FE8(&error);
			return 0;
		}
	}
	if (stream->rwOwned) {
		lbl_8042C9A4->freeListFree(
		    *(RwFreeList**)((u8*)lbl_8042C9A4 + lbl_8042C978.globalsOffset), stream);
	}
	return result;
}
}
