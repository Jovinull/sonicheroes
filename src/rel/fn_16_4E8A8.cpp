#include "types.h"

extern "C" {
char* RsPathnameCreate(const char* name);
void RsPathnameDestroy(char* path);
void* fn_8011B6F0(const char* fileName);
s32 CheckFileID__7ONEFILEFPc(u32 onefile, char* name);
void* LoadUVAnimationEx__7ONEFILEFUiPc(u32 onefile, s32 id, char* archive);
}

extern "C" void fn_16_4E8A8(void** out, char* name, u32 arg2, char* archive)
{
	char* path;
	s32 id;

	if (arg2 == 0) {
		path = RsPathnameCreate(name);
		*out = fn_8011B6F0(path);
		RsPathnameDestroy(path);
		return;
	}
	if (archive != NULL) {
		id = CheckFileID__7ONEFILEFPc(arg2, name);
		if (id >= 0) {
			*out = LoadUVAnimationEx__7ONEFILEFUiPc(arg2, id, archive);
		}
	}
}
