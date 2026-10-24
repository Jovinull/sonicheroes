#include "types.h"
#include "game/one.h"

// The big fireworks' Unload and Load hooks (bigfireworksUnload and
// bigfireworksLoad here): every model of each of its five sets is released;
// the module's texture dictionary is made current, and each set's archive
// (its name with the archive extension) is read into an archive of its own,
// working in a 0x800-byte buffer from the engine's allocator, its 30 models
// loaded from the archive's files 2 onwards with each one's kind set to 0x14.

// one model of a set: its kind and the model once loaded
typedef struct BigfireworksModel {
	s32 kind;    // 0x00
	void* model; // 0x04
} BigfireworksModel;

extern "C" BigfireworksModel bigfireworksModels[5][30];
extern "C" char* bigfireworksSetNames[5];
extern "C" char bigfireworksArchiveFormat[];
extern "C" u8* lbl_8042C1D0;
extern "C" u8* lbl_8042C9A4;

extern "C" int sprintf(char* buffer, const char* format, ...);
extern "C" void fn_801A4C84(void* resource);
extern "C" void fn_80150958(void* clump);

extern "C" void bigfireworksUnload(void)
{
	s32 j;
	s32 i;

	for (i = 0; i < 5; i++) {
		for (j = 0; j < 30; j++) {
			if (bigfireworksModels[i][j].model != NULL) {
				fn_80150958(bigfireworksModels[i][j].model);
				bigfireworksModels[i][j].model = NULL;
			}
		}
	}
}

extern "C" void bigfireworksLoad(void)
{
	char name[0x40];
	ONEFILE* onefile;
	s32 j;
	s32 i;
	void* buffer;

	fn_801A4C84(*(void**)(lbl_8042C1D0 + 0x8C18));
	onefile = new ONEFILE(NULL, 0);
	buffer  = (*(void* (**)(u32))(lbl_8042C9A4 + 0x134))(0x800);

	for (i = 0; i < 5; i++) {
		sprintf(name, bigfireworksArchiveFormat, bigfireworksSetNames[i]);
		onefile->LoadOneFile(name);
		onefile->exBuffer = buffer;
		for (j = 0; j < 30; j++) {
			bigfireworksModels[i][j].model = onefile->LoadClumpEx(j + 2, NULL);
			bigfireworksModels[i][j].kind  = 0x14;
		}
	}
	(*(void (**)(void*))(lbl_8042C9A4 + 0x138))(buffer);
	delete onefile;
}
