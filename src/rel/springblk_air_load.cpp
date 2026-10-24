#include "types.h"

// The springblkAir family's Load hook (springblkAirLoad here): the module's
// texture dictionary is made current, the family's material animation is set
// up, the module's model archive is read and each entry's model loaded by its
// name from its archive.

// one entry of the family's table: its file name and archive, and the model
// once loaded
typedef struct SpringblkAirEntry {
	const char* name; // 0x00
	void* archive;    // 0x04
	u8 unk08[0x4];
	void* object;    // 0x0C
} SpringblkAirEntry; // 0x10

// the family's material animation (fn_8015C6F8 and its neighbours set it up)
typedef struct SpringblkAirMatAnim {
	u8 unk00[0x18];
} SpringblkAirMatAnim;

extern "C" SpringblkAirEntry springblkAirTable[7];
extern "C" SpringblkAirMatAnim springblkAirMatAnim;
extern "C" u8* lbl_8042C1D0;
extern "C" u8* lbl_8042C298;
extern "C" u8 lbl_802FF5A0[];

extern "C" void fn_801A4C84(void* resource);
extern "C" void fn_8015C728(SpringblkAirMatAnim* anim);
extern "C" void fn_8015C6F8(SpringblkAirMatAnim* anim, s32 a, s32 b);
extern "C" void fn_8015C704(SpringblkAirMatAnim* anim, s32 a, s32 b);
extern "C" void fn_8015C710(SpringblkAirMatAnim* anim, s32 a, s32 b, s32 c);
extern "C" void fn_8015C720(SpringblkAirMatAnim* anim, s32 a);
extern "C" void LoadOneFile__7ONEFILEFPc(void* onefile, void* name);
extern "C" void* CheckFileID__7ONEFILEFPc(void* onefile, const char* name);
extern "C" void* LoadClumpEx__7ONEFILEFUiPc(void* onefile, void* id, void* archive);

extern "C" void springblkAirLoad(void)
{
	fn_801A4C84(*(void**)(lbl_8042C1D0 + 0x8C18));
	fn_8015C728(&springblkAirMatAnim);
	fn_8015C6F8(&springblkAirMatAnim, 3, 4);
	fn_8015C704(&springblkAirMatAnim, 1, 0);
	fn_8015C710(&springblkAirMatAnim, 1, 3, 8);
	fn_8015C720(&springblkAirMatAnim, 3);
	LoadOneFile__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), lbl_802FF5A0);
	SpringblkAirEntry* table = springblkAirTable;

	for (int i = 0; i < 7; i++) {
		table[i].object = LoadClumpEx__7ONEFILEFUiPc(*(void**)(lbl_8042C298 + 0xA50),
		    CheckFileID__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), table[i].name),
		    table[i].archive);
	}
}
