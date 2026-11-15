// Writes bytes to a stream (HYPOTHESIS: RwStreamWrite): file streams write through the engine
// file functions (a short write raises error 0x8000001C of plugin 1), memory streams allocate a
// 0x200-byte block on first use and grow it (by 0x200, or by the write length when larger) before
// copying, raising error 0x80000013 when memory runs out, and custom streams call their write
// function; other stream types raise error 0xE. Returns the stream, or null on failure.
#include "game/rw_engine.h"
#include "MSL_C/string.h"

// Stream types (HYPOTHESIS: RwStreamType).
#define RW_STREAM_FILE      1
#define RW_STREAM_FILE_NAME 2
#define RW_STREAM_MEMORY    3
#define RW_STREAM_CUSTOM    4

#define RW_ERROR_END_OF_STREAM  5
#define RW_ERROR_INVALID_STREAM 0xE
#define RW_ERROR_WRITE          ((s32)0x8000001C)
#define RW_STREAM_MEMORY_CHUNK  0x200
#define RW_SEEK_CUR             1

// Stream (HYPOTHESIS: RwStream); the union at 0xC depends on the type.
struct RwStream80197B48 {
	s32 type;       // 0x0
	s32 accessType; // 0x4
	s32 position;   // 0x8
	union {
		void* fpFile; // file streams
		struct {
			u32 position; // 0xC
			u32 nSize;    // 0x10
			u8* memBlock; // 0x14
		} memory;
		struct {
			void* sfnclose;                                              // 0xC
			u32 (*sfnread)(void* data, void* buffer, u32 length);        // 0x10
			s32 (*sfnwrite)(void* data, const void* buffer, u32 length); // 0x14
			s32 (*sfnskip)(void* data, u32 offset);                      // 0x18
			void* data;                                                  // 0x1C
		} custom;
	} Type;
};

static inline void RecordError80197B48(s32 code)
{
	RwError error;
	error.pluginID  = 1;
	error.errorCode = fn_8019408C(code);
	fn_80193FE8(&error);
}

static inline void RecordNoMemory80197B48(u32 size)
{
	RwError error;
	error.pluginID  = 1;
	error.errorCode = fn_8019408C(RW_ERROR_NO_MEMORY, size);
	fn_80193FE8(&error);
}

// Records the out-of-memory error for growing a memory stream by newSize - nSize bytes.
static inline void RecordGrowError80197B48(RwStream80197B48* stream, u32 newSize)
{
	RwError error;
	error.pluginID  = 1;
	error.errorCode = fn_8019408C(RW_ERROR_NO_MEMORY, newSize - stream->Type.memory.nSize);
	fn_80193FE8(&error);
}

extern "C" {
RwStream80197B48* fn_80197B48(RwStream80197B48* stream, const void* buffer, u32 length)
{
	switch (stream->type) {
		case RW_STREAM_FILE:
		case RW_STREAM_FILE_NAME: {
			u32 written = lbl_8042C9A4->rwfwrite(buffer, 1, length, stream->Type.fpFile);
			if (written != length) {
				RecordError80197B48(RW_ERROR_WRITE);
				return 0;
			}
		}
			return stream;
		case RW_STREAM_MEMORY:
			if (stream->Type.memory.memBlock == 0) {
				stream->Type.memory.memBlock = (u8*)lbl_8042C9A4->rwmalloc(RW_STREAM_MEMORY_CHUNK);
				if (stream->Type.memory.memBlock == 0) {
					RecordNoMemory80197B48(RW_STREAM_MEMORY_CHUNK);
					return 0;
				}
				stream->Type.memory.nSize = RW_STREAM_MEMORY_CHUNK;
			}
			if (stream->Type.memory.nSize - stream->Type.memory.position < length) {
				u32 newSize;
				u8* block;
				if (length < RW_STREAM_MEMORY_CHUNK) {
					newSize = stream->Type.memory.nSize + RW_STREAM_MEMORY_CHUNK;
				} else {
					newSize = length + stream->Type.memory.nSize;
				}
				block = (u8*)lbl_8042C9A4->rwrealloc(stream->Type.memory.memBlock, newSize);
				if (block == 0) {
					RecordGrowError80197B48(stream, newSize);
					return 0;
				}
				stream->Type.memory.memBlock = block;
				stream->Type.memory.nSize    = newSize;
			}
			memcpy(stream->Type.memory.memBlock + stream->Type.memory.position, buffer, length);
			stream->Type.memory.position += length;
			return stream;
		case RW_STREAM_CUSTOM:
			if (stream->Type.custom.sfnwrite(stream->Type.custom.data, buffer, length)) {
				return stream;
			}
			return 0;
		default:
			RecordError80197B48(RW_ERROR_INVALID_STREAM);
			return 0;
	}
}
}
