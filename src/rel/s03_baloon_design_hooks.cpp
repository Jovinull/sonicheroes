#include "types.h"

// The balloon design's Unload and Load hooks (s03BaloonDesignUnload and
// s03BaloonDesignLoad here): its model is released; when the module's texture
// dictionary is there, it is made current, the family's material animation is
// set up and the model is read from the module's model archive, its atomics
// then going through the family's callback.

// the family's material animation (fn_8015C6F8 and its neighbours set it up)
typedef struct S03BaloonDesignMatAnim {
	u8 unk00[0x18];
} S03BaloonDesignMatAnim;

extern "C" void* s03BaloonDesignModel;
extern "C" S03BaloonDesignMatAnim s03BaloonDesignMatAnim;
extern "C" char s03BaloonDesignModelName[];
extern "C" u8* lbl_8042C1D0;
extern "C" u8* lbl_8042C298;
extern "C" u8 lbl_802FF5A0[];

extern "C" void fn_801A4C84(void* resource);
extern "C" void fn_80150958(void* clump);
extern "C" void fn_8015C728(S03BaloonDesignMatAnim* anim);
extern "C" void fn_8015C6F8(S03BaloonDesignMatAnim* anim, s32 a, s32 b);
extern "C" void fn_8015C704(S03BaloonDesignMatAnim* anim, s32 a, s32 b);
extern "C" void fn_8015C710(S03BaloonDesignMatAnim* anim, s32 a, s32 b, s32 c);
extern "C" void fn_8015C720(S03BaloonDesignMatAnim* anim, s32 a);
extern "C" void fn_8014FFBC(void* clump, void* (*callback)(void*), void* data);
extern "C" void* fn_4_743D4(void* atomic);
extern "C" void LoadOneFile__7ONEFILEFPc(void* onefile, void* name);
extern "C" void* CheckFileID__7ONEFILEFPc(void* onefile, const char* name);
extern "C" void* LoadClumpEx__7ONEFILEFUiPc(void* onefile, void* id, void* archive);

extern "C" void s03BaloonDesignUnload(void)
{
	if (s03BaloonDesignModel != NULL) {
		fn_80150958(s03BaloonDesignModel);
		s03BaloonDesignModel = NULL;
	}
}

extern "C" void s03BaloonDesignLoad(void)
{
	void* resource = *(void**)(lbl_8042C1D0 + 0x8C18);

	if (resource != NULL) {
		fn_801A4C84(resource);
	} else {
		return;
	}
	fn_8015C728(&s03BaloonDesignMatAnim);
	fn_8015C6F8(&s03BaloonDesignMatAnim, 3, 4);
	fn_8015C704(&s03BaloonDesignMatAnim, 1, 0);
	fn_8015C710(&s03BaloonDesignMatAnim, 1, 3, 6);
	fn_8015C720(&s03BaloonDesignMatAnim, 3);
	LoadOneFile__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), lbl_802FF5A0);
	if ((s03BaloonDesignModel = LoadClumpEx__7ONEFILEFUiPc(*(void**)(lbl_8042C298 + 0xA50),
	         CheckFileID__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), s03BaloonDesignModelName),
	         lbl_802FF5A0))
	    != NULL) {
		fn_8014FFBC(s03BaloonDesignModel, fn_4_743D4, NULL);
	}
}
