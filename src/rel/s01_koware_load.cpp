#include "types.h"

// The breakable wall's Load hook (s01KowareLoad here): when the stage's
// resources are there they are kept and set up, the module's model archive is
// read, the 13 pieces' models are loaded by their stage-prefixed names, and
// the first piece's geometry has one flag cleared.

struct RpClump;

struct RpGeometry {
	u8 unk00[0x8];
	u32 flags; // 0x08
};

struct RpAtomic {
	u8 unk00[0x18];
	RpGeometry* geometry; // 0x18
};

RpAtomic* objRpClumpGetAtomic(RpClump* clump, RpAtomic* after);

extern "C" {
extern void* s01KowareResource;
extern RpClump* s01KowareModels[13];
extern const char* s01KowareModelNames[13];
extern char s01KowareNameFormat[];
extern u8* lbl_8042C1D0;
extern u8* lbl_8042C298;
extern u8 lbl_802FF5A0[];

int sprintf(char* buffer, const char* format, ...);
void fn_801A4C84(void* resource);
void fn_800B8CC4(RpAtomic* atomic, s32 flag);
void LoadOneFile__7ONEFILEFPc(void* onefile, void* name);
void* CheckFileID__7ONEFILEFPc(void* onefile, const char* name);
RpClump* LoadClumpEx__7ONEFILEFUiPc(void* onefile, void* id, void* archive);
}

extern "C" void s01KowareLoad(void)
{
	char name[0x20];
	void* resource = *(void**)(lbl_8042C1D0 + 0x8C18);

	if (resource != NULL) {
		s01KowareResource = resource;
		fn_801A4C84(resource);
	} else {
		return;
	}
	LoadOneFile__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), lbl_802FF5A0);
	for (u32 i = 0; i < 13; i++) {
		sprintf(name, s01KowareNameFormat, s01KowareModelNames[i]);
		s01KowareModels[i] = LoadClumpEx__7ONEFILEFUiPc(*(void**)(lbl_8042C298 + 0xA50),
		    CheckFileID__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), name), lbl_802FF5A0);
	}
	RpAtomic* atomic = objRpClumpGetAtomic(s01KowareModels[0], NULL);
	fn_800B8CC4(atomic, 0);
	atomic->geometry->flags &= ~0x20;
}
