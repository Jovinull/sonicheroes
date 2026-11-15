// Skips bytes in a stream (HYPOTHESIS: RwStreamSkip): file streams seek forward from the current
// position (a failed seek at end of file raises error 5 of plugin 1), memory streams advance their
// position (an overrun clamps it to the size and raises error 5), custom streams call their skip
// function; other stream types raise error 0xE. Returns the stream, or null on failure.
#include "game/rw_engine.h"

// Stream types (HYPOTHESIS: RwStreamType).
#define RW_STREAM_FILE      1
#define RW_STREAM_FILE_NAME 2
#define RW_STREAM_MEMORY    3
#define RW_STREAM_CUSTOM    4

#define RW_ERROR_END_OF_STREAM  5
#define RW_ERROR_INVALID_STREAM 0xE
#define RW_SEEK_CUR             1

// Stream (HYPOTHESIS: RwStream); the union at 0xC depends on the type.
struct RwStream80197D70 {
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
			void* sfnclose;                         // 0xC
			void* sfnread;                          // 0x10
			void* sfnwrite;                         // 0x14
			s32 (*sfnskip)(void* data, u32 offset); // 0x18
			void* data;                             // 0x1C
		} custom;
	} Type;
};

static inline void RecordError80197D70(s32 code)
{
	RwError error;
	error.pluginID  = 1;
	error.errorCode = fn_8019408C(code);
	fn_80193FE8(&error);
}

extern "C" {
RwStream80197D70* fn_80197D70(RwStream80197D70* stream, u32 offset)
{
	if (offset == 0) {
		return stream;
	}
	switch (stream->type) {
		case RW_STREAM_FILE:
		case RW_STREAM_FILE_NAME: {
			void* file = stream->Type.fpFile;
			if (lbl_8042C9A4->rwfseek(file, offset, RW_SEEK_CUR)) {
				if (lbl_8042C9A4->rwfeof(file)) {
					RecordError80197D70(RW_ERROR_END_OF_STREAM);
				}
				return 0;
			}
			return stream;
		}
		case RW_STREAM_MEMORY:
			if (stream->Type.memory.position + offset > stream->Type.memory.nSize) {
				stream->Type.memory.position = stream->Type.memory.nSize;
				RecordError80197D70(RW_ERROR_END_OF_STREAM);
				return 0;
			}
			stream->Type.memory.position += offset;
			return stream;
		case RW_STREAM_CUSTOM:
			if (stream->Type.custom.sfnskip(stream->Type.custom.data, offset)) {
				return stream;
			}
			return 0;
		default:
			RecordError80197D70(RW_ERROR_INVALID_STREAM);
			return 0;
	}
}
}
