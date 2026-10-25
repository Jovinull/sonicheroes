#include "types.h"

// The s13Bigmovship family's Unload and Load hooks (s13BigmovshipUnload and
// s13BigmovshipLoad here): its two model infos and four part infos are
// released; when the module's model archive is there, it is read and each
// model info and part info loaded.

// one of the stage's model infos (s13ModelInfoRelease and s13ModelInfoLoad
// handle them)
typedef struct S13ModelInfo {
	u8 unk00[0x18];
} S13ModelInfo; // 0x18

// one of the stage's part infos (fn_9_75E60 releases them, fn_9_75F08 loads
// them)
typedef struct S13PartInfo {
	u8 unk00[0x14];
} S13PartInfo; // 0x14

extern "C" S13ModelInfo s13BigmovshipModels[2];
extern "C" S13PartInfo s13BigmovshipParts[4];
extern "C" u8* lbl_8042C1D0;
extern "C" u8* lbl_8042C298;
extern "C" u8 lbl_802FF5A0[];

extern "C" void fn_801A4C84(void* resource);
extern "C" void LoadOneFile__7ONEFILEFPc(void* onefile, void* name);
extern "C" void s13ModelInfoRelease(S13ModelInfo* info);
extern "C" void s13ModelInfoLoad(S13ModelInfo* info, const char* name);
extern "C" void fn_9_75E60(S13PartInfo* part);
extern "C" void fn_9_75F08(S13PartInfo* part, const char* name);

extern "C" void s13BigmovshipUnload(void)
{
	S13ModelInfo* info = (S13ModelInfo*)s13BigmovshipModels;

	for (u8 i = 0; i < 2; i++) {
		s13ModelInfoRelease(info);
		info++;
	}
	S13PartInfo* part = (S13PartInfo*)s13BigmovshipParts;
	for (u8 i = 0; i < 4; i++) {
		fn_9_75E60(part);
		part++;
	}
}

extern "C" void s13BigmovshipLoad(void)
{
	void* resource = *(void**)(lbl_8042C1D0 + 0x8C18);
	if (resource != NULL) {
		fn_801A4C84(resource);
	} else {
		return;
	}
	LoadOneFile__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), lbl_802FF5A0);
	S13ModelInfo* info = (S13ModelInfo*)s13BigmovshipModels;
	for (u8 i = 0; i < 2; i++) {
		s13ModelInfoLoad(info, NULL);
		info++;
	}
	S13PartInfo* part = (S13PartInfo*)s13BigmovshipParts;
	for (u8 i = 0; i < 4; i++) {
		fn_9_75F08(part, NULL);
		part++;
	}
}
