// Opens a stream (HYPOTHESIS: RenderWare RwStreamOpen): takes a stream from the stream module's
// free list (lbl_8042C978) and sets it up for its type: an open file whose position can be read
// (rwftell), a file name opened for reading, writing or appending ("rb", "wb", "ab"; error
// 0x80000002 when it cannot be opened), a memory block read from its start, written from scratch
// or appended to its end, or a custom stream copied from the caller. Bad access types raise error
// 0xD and bad stream types 0xE. Returns the stream, or null after returning it to the free list.
// NonMatching: retail keeps the type, access type and data in r29/r27/r30 with a fifth saved
// register, and builds the null defaults from the result register; this source allocates them
// differently (three more instructions, 132 words). Tried an inline initialiser with early returns
// (the RenderWare shape), a separate result, sized string externs and an empty null branch.
#include "game/rw_engine.h"
#include "MSL_C/string.h"

#define RW_STREAM_FILE      1
#define RW_STREAM_FILE_NAME 2
#define RW_STREAM_MEMORY    3
#define RW_STREAM_CUSTOM    4

#define RW_STREAM_READ   1
#define RW_STREAM_WRITE  2
#define RW_STREAM_APPEND 3

#define RW_ERROR_STREAM_ACCESS    0xD
#define RW_ERROR_STREAM_TYPE      0xE
#define RW_ERROR_STREAM_FILE_OPEN ((s32)0x80000002)

// Memory block of a memory stream (HYPOTHESIS: RwMemory).
struct RwMemory80198000 {
	u8* start;  // 0x0
	u32 length; // 0x4
};

// Stream (HYPOTHESIS: RwStream; the union holds the file, memory or custom state).
struct RwStream80198000 {
	s32 type;       // 0x0
	s32 accessType; // 0x4
	s32 position;   // 0x8
	union {
		void* file; // 0xC
		struct {
			u32 position; // 0xC
			u32 size;     // 0x10
			u8* block;    // 0x14
		} memory;
		u8 custom[0x14]; // 0xC
	} data;
	s32 rwOwned; // 0x20
};

extern "C" {
// Stream module bookkeeping; its globals start with the stream free list (HYPOTHESIS).
extern RwModuleInfo lbl_8042C978;
// Access mode strings "rb", "wb" and "ab".
extern char lbl_8042BE00[3];
extern char lbl_8042BE04[3];
extern char lbl_8042BE08[3];

#define RW_STREAM_FREE_LIST (*(RwFreeList**)((u8*)lbl_8042C9A4 + lbl_8042C978.globalsOffset))

static inline void RecordError80198000(s32 code)
{
	RwError error;
	error.pluginID  = RW_ID_CORE_PLUGIN;
	error.errorCode = fn_8019408C(code);
	fn_80193FE8(&error);
}

// HYPOTHESIS: _rwStreamInitialize, inlined.
static inline RwStream80198000* StreamInitialize80198000(
    RwStream80198000* stream, s32 rwOwned, s32 type, s32 accessType, void* data)
{
	stream->type       = type;
	stream->accessType = accessType;
	stream->rwOwned    = rwOwned;
	switch (type) {
		case RW_STREAM_FILE:
			if (lbl_8042C9A4->rwftell(data) == -1) {
				return 0;
			}
			stream->data.file = data;
			break;
		case RW_STREAM_FILE_NAME: {
			void* file = 0;
			switch (accessType) {
				case RW_STREAM_READ:
					file = lbl_8042C9A4->rwfopen((const char*)data, lbl_8042BE00);
					break;
				case RW_STREAM_WRITE:
					file = lbl_8042C9A4->rwfopen((const char*)data, lbl_8042BE04);
					break;
				case RW_STREAM_APPEND:
					file = lbl_8042C9A4->rwfopen((const char*)data, lbl_8042BE08);
					break;
				default:
					RecordError80198000(RW_ERROR_STREAM_ACCESS);
					break;
			}
			if (file == 0) {
				RwError error;
				error.pluginID  = RW_ID_CORE_PLUGIN;
				error.errorCode = fn_8019408C(RW_ERROR_STREAM_FILE_OPEN, data);
				fn_80193FE8(&error);
				return 0;
			}
			stream->data.file = file;
			break;
		}
		case RW_STREAM_MEMORY: {
			RwMemory80198000* memory = (RwMemory80198000*)data;
			switch (accessType) {
				case RW_STREAM_READ:
					stream->data.memory.position = 0;
					stream->data.memory.size     = memory->length;
					stream->data.memory.block    = memory->start;
					break;
				case RW_STREAM_WRITE:
					stream->data.memory.position = 0;
					stream->data.memory.size     = 0;
					stream->data.memory.block    = 0;
					break;
				case RW_STREAM_APPEND:
					stream->data.memory.position = memory->length;
					stream->data.memory.size     = memory->length;
					stream->data.memory.block    = memory->start;
					break;
				default:
					RecordError80198000(RW_ERROR_STREAM_ACCESS);
					return 0;
			}
			break;
		}
		case RW_STREAM_CUSTOM:
			memcpy(stream->data.custom, data, sizeof(stream->data.custom));
			break;
		default:
			RecordError80198000(RW_ERROR_STREAM_TYPE);
			return 0;
	}
	return stream;
}

RwStream80198000* fn_80198000(s32 type, s32 accessType, void* data)
{
	RwStream80198000* stream = (RwStream80198000*)lbl_8042C9A4->freeListAlloc(RW_STREAM_FREE_LIST);

	RwStream80198000* result = 0;

	if (stream != 0) {
		result = StreamInitialize80198000(stream, 1, type, accessType, data);
	}
	if (result == 0) {
		lbl_8042C9A4->freeListFree(RW_STREAM_FREE_LIST, stream);
		stream = 0;
	}
	return stream;
}
}
