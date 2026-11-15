// Returns the length of file `name` (skyfsGetLength), or -1 when it cannot be opened. The file is
// opened through the RenderWare OS file interface with the mode string lbl_8042AF20 (HYPOTHESIS:
// "rb") and closed again.
#include "types.h"

// The two RwFileFunctions slots used (fopen at +0x4, fclose at +0x8).
struct RwFileFunctions80042554 {
	void* rwfexist;                                         // 0x0
	void* (*rwfopen)(const char* name, const char* access); // 0x4
	s32 (*rwfclose)(void* fp);                              // 0x8
};

extern "C" {
extern char lbl_8042AF20[4];
char* RsPathnameCreate(const char* name);
void RsPathnameDestroy(char* name);
RwFileFunctions80042554* RwOsGetFileInterface(void);
s32 skyfsGetLength(void* fp);

s32 fn_80042554(const char* name)
{
	char* path                     = RsPathnameCreate(name);
	RwFileFunctions80042554* files = RwOsGetFileInterface();
	void* fp                       = files->rwfopen(path, lbl_8042AF20);
	s32 length;

	RsPathnameDestroy(path);
	if (fp == NULL) {
		return -1;
	}
	length = skyfsGetLength(fp);
	files->rwfclose(fp);
	return length;
}
}
