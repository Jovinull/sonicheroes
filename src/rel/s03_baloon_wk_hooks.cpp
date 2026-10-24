#include "types.h"

// The work balloon's Unload and Load hooks (s03BaloonWKUnload and
// s03BaloonWKLoad here): its two models are released, with fn_800B8ADC called
// on the first one first (the first one's pointer is the one cleared both
// times); when the module's texture dictionary is there, it is made current,
// the family's material animation is set up and both models are read from the
// module's model archive. fn_800B8BEC is called on the first one, and the
// family's callback goes over the first one's atomics twice (the second time
// once the second one is loaded).

// the family's material animation (fn_8015C6F8 and its neighbours set it up)
typedef struct S03BaloonWKMatAnim {
	u8 unk00[0x18];
} S03BaloonWKMatAnim;

extern "C" void* s03BaloonWKModel1;
extern "C" void* s03BaloonWKModel2;
extern "C" S03BaloonWKMatAnim s03BaloonWKMatAnim;
extern "C" char s03BaloonWKModelName1[];
extern "C" char s03BaloonWKModelName2[];
extern "C" u8* lbl_8042C1D0;
extern "C" u8* lbl_8042C298;
extern "C" u8 lbl_802FF5A0[];

extern "C" void fn_801A4C84(void* resource);
extern "C" void fn_800B8ADC(void* clump);
extern "C" void fn_80150958(void* clump);
extern "C" void fn_800B8BEC(void* clump, s32 flag);
extern "C" void fn_8015C728(S03BaloonWKMatAnim* anim);
extern "C" void fn_8015C6F8(S03BaloonWKMatAnim* anim, s32 a, s32 b);
extern "C" void fn_8015C704(S03BaloonWKMatAnim* anim, s32 a, s32 b);
extern "C" void fn_8015C710(S03BaloonWKMatAnim* anim, s32 a, s32 b, s32 c);
extern "C" void fn_8015C720(S03BaloonWKMatAnim* anim, s32 a);
extern "C" void fn_8014FFBC(void* clump, void* (*callback)(void*), void* data);
extern "C" void* fn_4_757C8(void* atomic);
extern "C" void LoadOneFile__7ONEFILEFPc(void* onefile, void* name);
extern "C" void* CheckFileID__7ONEFILEFPc(void* onefile, const char* name);
extern "C" void* LoadClumpEx__7ONEFILEFUiPc(void* onefile, void* id, void* archive);

extern "C" void s03BaloonWKUnload(void)
{
	if (s03BaloonWKModel1 != NULL) {
		fn_800B8ADC(s03BaloonWKModel1);
		fn_80150958(s03BaloonWKModel1);
		s03BaloonWKModel1 = NULL;
	}
	if (s03BaloonWKModel2 != NULL) {
		fn_80150958(s03BaloonWKModel2);
		s03BaloonWKModel1 = NULL;
	}
}

extern "C" void s03BaloonWKLoad(void)
{
	void* resource = *(void**)(lbl_8042C1D0 + 0x8C18);

	if (resource != NULL) {
		fn_801A4C84(resource);
	} else {
		return;
	}
	fn_8015C728(&s03BaloonWKMatAnim);
	fn_8015C6F8(&s03BaloonWKMatAnim, 3, 4);
	fn_8015C704(&s03BaloonWKMatAnim, 1, 0);
	fn_8015C710(&s03BaloonWKMatAnim, 1, 3, 6);
	fn_8015C720(&s03BaloonWKMatAnim, 0);
	LoadOneFile__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), lbl_802FF5A0);
	if ((s03BaloonWKModel1 = LoadClumpEx__7ONEFILEFUiPc(*(void**)(lbl_8042C298 + 0xA50),
	         CheckFileID__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), s03BaloonWKModelName1),
	         lbl_802FF5A0))
	    != NULL) {
		fn_800B8BEC(s03BaloonWKModel1, 0);
		fn_8014FFBC(s03BaloonWKModel1, fn_4_757C8, NULL);
	}
	LoadOneFile__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), lbl_802FF5A0);
	if ((s03BaloonWKModel2 = LoadClumpEx__7ONEFILEFUiPc(*(void**)(lbl_8042C298 + 0xA50),
	         CheckFileID__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), s03BaloonWKModelName2),
	         lbl_802FF5A0))
	    != NULL) {
		fn_8014FFBC(s03BaloonWKModel1, fn_4_757C8, NULL);
	}
}
