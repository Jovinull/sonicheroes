#include "types.h"

// The ivy family's Load hook (tutaetcLoad here): the module's texture
// dictionary is made current and its model archive read; then, for each of its
// four entries, the first entry's model is loaded, each entry's animation and
// the animation's key list when it has one, and each entry's path when it has
// one, the path's centre being kept as the mean of its points at 0, 0.5 and 1;
// every entry gets the family's frame step.

struct DANIM_KEY;
struct RtAnimAnimation;

typedef struct RwV3d {
	f32 x; // 0x00
	f32 y; // 0x04
	f32 z; // 0x08
} RwV3d;

// one of the family's entries: the archive it is read from, its model's,
// animation's and path's names, the three once loaded, the animation's key
// list and count, its frame step and the path's centre
typedef struct TutaetcEntry {
	void* archive;         // 0x00
	const char* name;      // 0x04
	const char* animName;  // 0x08
	const char* pathName;  // 0x0C
	void* model;           // 0x10
	RtAnimAnimation* anim; // 0x14
	void* path;            // 0x18
	DANIM_KEY* keys;       // 0x1C
	s32 keyCount;          // 0x20
	f32 step;              // 0x24
	u8 unk28[0x4];         // 0x28
	RwV3d centre;          // 0x2C
	u8 unk38[0x14];        // 0x38
} TutaetcEntry;            // 0x4C

class HAnimClass
{
public:
	void GetHAnimKeyList(DANIM_KEY* keys, int count, RtAnimAnimation* animation);
};

extern "C" TutaetcEntry tutaetcTable[4];
extern "C" const f32 lbl_7_rodata_19AC; // 1
extern "C" const f32 lbl_7_rodata_19B4; // 0
extern "C" const f32 lbl_7_rodata_19BC; // 0.5
extern "C" const f32 lbl_7_rodata_19C0; // 3
extern "C" const f32 lbl_7_rodata_19C4; // 1 / 60
extern "C" u8* lbl_8042C1D0;
extern "C" u8* lbl_8042C298;
extern "C" u8 lbl_802FF5A0[];
extern HAnimClass HAnim;

extern "C" void fn_801A4C84(void* resource);
extern "C" void fn_8014D308(void* path, s32 kind, f32 t, RwV3d* out, s32 arg);
extern "C" void LoadOneFile__7ONEFILEFPc(void* onefile, void* name);
extern "C" void* CheckFileID__7ONEFILEFPc(void* onefile, const char* name);
extern "C" void* LoadClumpEx__7ONEFILEFUiPc(void* onefile, void* id, void* archive);
extern "C" void* LoadHAnimationEx__7ONEFILEFUiPc(void* onefile, void* id, void* archive);
extern "C" void* LoadSplineEx__7ONEFILEFUiPc(void* onefile, void* id, void* archive);

extern "C" void tutaetcLoad(void)
{
	RwV3d points[3];

	fn_801A4C84(*(void**)(lbl_8042C1D0 + 0x8C18));
	LoadOneFile__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), lbl_802FF5A0);
	TutaetcEntry* table = tutaetcTable;
	for (int i = 0; i < 4; i++) {
		if (i == 0) {
			table[i].model = LoadClumpEx__7ONEFILEFUiPc(*(void**)(lbl_8042C298 + 0xA50),
			    CheckFileID__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), table[i].name),
			    table[i].archive);
		}
		if (table[i].animName != NULL) {
			table[i].anim
			    = (RtAnimAnimation*)LoadHAnimationEx__7ONEFILEFUiPc(*(void**)(lbl_8042C298 + 0xA50),
			        CheckFileID__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), table[i].animName),
			        table[i].archive);
			HAnim.GetHAnimKeyList(table[i].keys, table[i].keyCount, table[i].anim);
		}
		if (table[i].pathName != NULL) {
			table[i].path = LoadSplineEx__7ONEFILEFUiPc(*(void**)(lbl_8042C298 + 0xA50),
			    CheckFileID__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), table[i].pathName),
			    table[i].archive);
			fn_8014D308(table[i].path, 10, lbl_7_rodata_19B4, &points[0], 0);
			fn_8014D308(table[i].path, 10, lbl_7_rodata_19BC, &points[1], 0);
			fn_8014D308(table[i].path, 10, lbl_7_rodata_19AC, &points[2], 0);
			table[i].centre.x = (points[0].x + points[1].x + points[2].x) / lbl_7_rodata_19C0;
			table[i].centre.y = (points[0].y + points[1].y + points[2].y) / lbl_7_rodata_19C0;
			table[i].centre.z = (points[0].z + points[1].z + points[2].z) / lbl_7_rodata_19C0;
		}
		table[i].step = lbl_7_rodata_19C4;
	}
}
