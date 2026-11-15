// Reads the whole file `name` into `buffer` (after invalidating the data cache over its length)
// through the RenderWare OS file interface and returns the number of bytes read, or -1 when the
// file cannot be opened. The mode string is lbl_8042AF20 (see fn_80042554).
// NonMatching (14 words, register allocation): the retail code keeps the path and the length in
// the same saved register (r29) and the file in r30; MWCC swaps the path and the file. Tried: all
// declaration orders, a scoped path, both branch orders.
#include "types.h"

// The RwFileFunctions slots used (fopen +0x4, fclose +0x8, fread +0xC).
struct RwFileFunctions800425E8 {
	void* rwfexist;                                              // 0x0
	void* (*rwfopen)(const char* name, const char* access);      // 0x4
	s32 (*rwfclose)(void* fp);                                   // 0x8
	u32 (*rwfread)(void* buffer, u32 size, u32 count, void* fp); // 0xC
};

extern "C" {
extern char lbl_8042AF20[4];
char* RsPathnameCreate(const char* name);
void RsPathnameDestroy(char* name);
RwFileFunctions800425E8* RwOsGetFileInterface(void);
s32 skyfsGetLength(void* fp);
void DCInvalidateRange(void* addr, u32 length);

s32 fn_800425E8(const char* name, void* buffer)
{
	char* path;
	RwFileFunctions800425E8* files;
	void* fp;
	s32 length;

	path  = RsPathnameCreate(name);
	files = RwOsGetFileInterface();
	fp    = files->rwfopen(path, lbl_8042AF20);
	RsPathnameDestroy(path);
	if (fp == NULL) {
		length = -1;
	} else {
		length = skyfsGetLength(fp);
		DCInvalidateRange(buffer, length);
		length = files->rwfread(buffer, 1, length, fp);
		files->rwfclose(fp);
	}
	return length;
}
}
