#include "types.h"

// The kazariobj family's Load hook (kazariobjLoad here): the module's texture
// dictionary is made current, the family's material animation is set up and
// each entry's model is loaded by its name, its atomics going through the
// family's callback.

// one entry of the family's table: its file name and the model once loaded
typedef struct KazariobjEntry {
	const char* name; // 0x0
	void* object;     // 0x4
} KazariobjEntry;     // 0x8

// the family's material animation (fn_8015C6F8 and its neighbours set it up)
typedef struct KazariobjMatAnim {
	u8 unk00[0x18];
} KazariobjMatAnim;

extern "C" KazariobjEntry kazariobjTable[3];
extern "C" KazariobjMatAnim kazariobjMatAnim;
extern "C" u8* lbl_8042C1D0;
extern "C" u8* lbl_8042C298;
extern "C" u8 lbl_802FF5A0[];

extern "C" void fn_801A4C84(void* resource);
extern "C" void fn_8015C728(KazariobjMatAnim* anim);
extern "C" void fn_8015C6F8(KazariobjMatAnim* anim, s32 a, s32 b);
extern "C" void fn_8015C704(KazariobjMatAnim* anim, s32 a, s32 b);
extern "C" void fn_8015C710(KazariobjMatAnim* anim, s32 a, s32 b, s32 c);
extern "C" void fn_8015C720(KazariobjMatAnim* anim, s32 a);
extern "C" void fn_8014FFBC(void* clump, void* (*callback)(void*), void* data);
extern "C" void* fn_7_7A178(void* atomic);
extern "C" void* CheckFileID__7ONEFILEFPc(void* onefile, const char* name);
extern "C" void* LoadClumpEx__7ONEFILEFUiPc(void* onefile, void* id, void* archive);

extern "C" void kazariobjLoad(void)
{
	fn_801A4C84(*(void**)(lbl_8042C1D0 + 0x8C18));
	fn_8015C728(&kazariobjMatAnim);
	fn_8015C6F8(&kazariobjMatAnim, 3, 6);
	fn_8015C704(&kazariobjMatAnim, 1, 0);
	fn_8015C710(&kazariobjMatAnim, 1, 1, 6);
	fn_8015C720(&kazariobjMatAnim, 3);
	KazariobjEntry* table = kazariobjTable;

	for (int i = 0; i < 3; i++) {
		table[i].object = LoadClumpEx__7ONEFILEFUiPc(*(void**)(lbl_8042C298 + 0xA50),
		    CheckFileID__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), table[i].name), lbl_802FF5A0);
		if (table[i].object != NULL) {
			fn_8014FFBC(table[i].object, fn_7_7A178, NULL);
		}
	}
}
