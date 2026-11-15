#include "game/rw_engine.h"

// Reads a whole file into a new buffer (RwMalloc, rounded up to 32 bytes and invalidated from the
// data cache for the read): opens the RenderSkel path of `name` with mode lbl_8042AF20 through
// the RenderWare file interface, sizes it with skyfsGetLength and reads it in one call. Returns
// the buffer and stores the number of bytes read in *size (when given), or returns NULL and
// stores 0 when the file is missing, has no length, the buffer cannot be allocated or the read
// fails (the buffer is freed then). HYPOTHESIS: lbl_8042AF20 is "rb" (a 3-byte string).
// NonMatching (saved-register allocation only, same instructions): retail gives `size` r31 and
// reuses the path's register (r30) for the length; MWCC numbers them the other way round.
// Declaration orders (perm.py) did not reproduce it.

// The RenderWare file interface (RwOsGetFileInterface; the rw_engine.h block from +0xC4).
struct FileFunctions800426E0 {
	s32 (*rwfexist)(const char* name);                             // 0x0
	void* (*rwfopen)(const char* name, const char* mode);          // 0x4
	s32 (*rwfclose)(void* file);                                   // 0x8
	s32 (*rwfread)(void* buffer, u32 size, u32 count, void* file); // 0xC
};

extern "C" {
extern char lbl_8042AF20[3];
char* RsPathnameCreate(const char* name);
void RsPathnameDestroy(char* path);
FileFunctions800426E0* RwOsGetFileInterface(void);
s32 skyfsGetLength(void* file);
void DCInvalidateRange(void* addr, u32 nBytes);
}

extern "C" void* fn_800426E0(const char* name, u32* size)
{
	char* path                = RsPathnameCreate(name);
	FileFunctions800426E0* fs = RwOsGetFileInterface();
	void* file                = fs->rwfopen(path, lbl_8042AF20);
	RsPathnameDestroy(path);
	if (file == NULL) {
		if (size != NULL) {
			*size = 0;
		}
		return NULL;
	}
	s32 length = skyfsGetLength(file);
	if (length == -1) {
		fs->rwfclose(file);
		if (size != NULL) {
			*size = 0;
		}
		return NULL;
	}
	void* buffer = lbl_8042C9A4->rwmalloc((length + 31) & ~31);
	if (buffer == NULL) {
		fs->rwfclose(file);
		if (size != NULL) {
			*size = 0;
		}
		return NULL;
	}
	DCInvalidateRange(buffer, length);
	length = fs->rwfread(buffer, 1, length, file);
	fs->rwfclose(file);
	if (length == -1) {
		lbl_8042C9A4->rwfree(buffer);
		if (size != NULL) {
			*size = 0;
		}
		return NULL;
	}
	if (size != NULL) {
		*size = length;
	}
	return buffer;
}
