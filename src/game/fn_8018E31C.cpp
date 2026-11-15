// Handles a PNG chunk the reader does not know (HYPOTHESIS: libpng 1.2 png_handle_unknown): marks
// the image as past IDAT for a non-IDAT chunk after IDAT, checks the chunk name (fn_8018E60C),
// rejects an unknown critical chunk unless it is always handled (fn_8017C500) or a user callback
// exists ("unknown critical chunk", lbl_8028FE3C). When unknown chunks are kept, reads the chunk,
// offers it to the user callback and stores it with png_set_unknown_chunks (fn_80190FCC) unless
// the callback took it; otherwise skips it. Finishes with the CRC check.
#include "game/png_internal.h"
#include "MSL_C/string.h"

#define PNG_HANDLE_CHUNK_ALWAYS 3

// Unknown chunk record (HYPOTHESIS: png_unknown_chunk).
struct PngUnknownChunk8018E31C {
	u8 name[5]; // 0x0
	u8* data;   // 0x8
	u32 size;   // 0xC
};

extern "C" {
// MSL string functions this unit uses.
int memcmp(const void* lhs, const void* rhs, u32 size);
char* strcpy(char* dst, const char* src);
// "IDAT" (png_IDAT).
extern u8 lbl_8042F4F0[5];
// "unknown critical chunk".
extern char lbl_8028FE3C[];

// HYPOTHESIS: png_malloc, png_free, png_check_chunk_name, png_handle_as_unknown and
// png_set_unknown_chunks.
void* fn_8017CDA4(PngStruct* png, u32 size);
void fn_8017CE74(PngStruct* png, void* ptr);
void fn_8018E60C(PngStruct* png, u8* chunkName);
s32 fn_8017C500(PngStruct* png, u8* chunkName);
void fn_80190FCC(PngStruct* png, void* info, PngUnknownChunk8018E31C* chunks, s32 numChunks);

void fn_8018E31C(PngStruct* png, void* info, u32 length)
{
	u32 skip = 0;

	if (png->mode & PNG_HAVE_IDAT) {
		if (memcmp(png->chunkName, lbl_8042F4F0, 4)) {
			png->mode |= PNG_AFTER_IDAT;
		}
	}

	fn_8018E60C(png, png->chunkName);

	if (!(png->chunkName[0] & 0x20)) {
		if (fn_8017C500(png, png->chunkName) != PNG_HANDLE_CHUNK_ALWAYS
		    && png->readUserChunkFn == 0) {
			fn_8017C6D4(png, lbl_8028FE3C);
		}
	}

	if (png->flags & PNG_FLAG_KEEP_UNKNOWN_CHUNKS) {
		PngUnknownChunk8018E31C chunk;

		strcpy((char*)chunk.name, (char*)png->chunkName);
		chunk.data = (u8*)fn_8017CDA4(png, length);
		chunk.size = length;
		PngCrcRead(png, chunk.data, length);
		if (png->readUserChunkFn != 0) {
			if (png->readUserChunkFn(png, &chunk) <= 0) {
				if (!(png->chunkName[0] & 0x20)) {
					if (fn_8017C500(png, png->chunkName) != PNG_HANDLE_CHUNK_ALWAYS) {
						fn_8017C6D4(png, lbl_8028FE3C);
					}
				}
				fn_80190FCC(png, info, &chunk, 1);
			}
		} else {
			fn_80190FCC(png, info, &chunk, 1);
		}
		fn_8017CE74(png, chunk.data);
	} else {
		skip = length;
	}

	PngCrcFinish(png, skip, lbl_8028F2F8);
}
}
