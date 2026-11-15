// Reads bytes from a stream (HYPOTHESIS: RwStreamRead): file streams read through the engine file
// functions (a short read raises error 5 of plugin 1 at end of file, read error 0x8000001A
// otherwise), memory streams copy from their block (an overrun is clamped to the remaining bytes
// and raises error 5), custom streams call their read function; other stream types raise error
// 0xE. Returns the number of bytes read.
#include "game/rw_engine.h"
#include "MSL_C/string.h"

// Stream types (HYPOTHESIS: RwStreamType).
#define RW_STREAM_FILE      1
#define RW_STREAM_FILE_NAME 2
#define RW_STREAM_MEMORY    3
#define RW_STREAM_CUSTOM    4

#define RW_ERROR_END_OF_STREAM  5
#define RW_ERROR_INVALID_STREAM 0xE
#define RW_ERROR_READ           ((s32)0x8000001A)
#define RW_SEEK_CUR             1

// Stream (HYPOTHESIS: RwStream); the union at 0xC depends on the type.
struct RwStream801979AC {
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
			void* sfnclose;                                       // 0xC
			u32 (*sfnread)(void* data, void* buffer, u32 length); // 0x10
			void* sfnwrite;                                       // 0x14
			s32 (*sfnskip)(void* data, u32 offset);               // 0x18
			void* data;                                           // 0x1C
		} custom;
	} Type;
};

static inline void RecordError801979AC(s32 code)
{
	RwError error;
	error.pluginID  = 1;
	error.errorCode = fn_8019408C(code);
	fn_80193FE8(&error);
}

extern "C" {
u32 fn_801979AC(RwStream801979AC* stream, void* buffer, u32 length)
{
	switch (stream->type) {
		case RW_STREAM_FILE:
		case RW_STREAM_FILE_NAME: {
			void* file = stream->Type.fpFile;
			u32 count  = lbl_8042C9A4->rwfread(buffer, 1, length, file);
			if (count != length) {
				if (lbl_8042C9A4->rwfeof(file)) {
					RecordError801979AC(RW_ERROR_END_OF_STREAM);
				} else {
					RecordError801979AC(RW_ERROR_READ);
				}
			}
			return count;
		}
		case RW_STREAM_MEMORY: {
			u32 available = stream->Type.memory.nSize - stream->Type.memory.position;
			if (length > available) {
				length = available;
				RecordError801979AC(RW_ERROR_END_OF_STREAM);
			}
			memcpy(buffer, stream->Type.memory.memBlock + stream->Type.memory.position, length);
			stream->Type.memory.position += length;
			return length;
		}
		case RW_STREAM_CUSTOM:
			return stream->Type.custom.sfnread(stream->Type.custom.data, buffer, length);
		default:
			RecordError801979AC(RW_ERROR_INVALID_STREAM);
			return 0;
	}
}
}
