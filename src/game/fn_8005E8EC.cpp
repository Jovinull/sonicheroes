#include "types.h"

// The original translation-unit name and private type names are unknown. This
// neutral filename follows the first function address; descriptive private
// identifiers below are reconstruction aids rather than recovered names.
//
// The bounds came from a data-privacy scan over the run: every lbl_ object the
// five functions reference is consumed inside them, and the next function up,
// fn_8005F194, reaches labels with ninety to a hundred and forty-five users.
// See issue #297. Three claims in splits.txt are still unargued and are tracked
// there: lbl_80301780 (8800 bytes, no user anywhere in the DOL), lbl_80243570
// (only user fn_8005F194, which is the next unit) and lbl_803039E0 (used here
// and by fn_8005D498 -- not wrong on its own, a unit can own a global another
// reads, but it should be said out loud).
//
// NOT MATCHING: two of the five functions are byte-exact, fn_8005EC0C and
// fn_8005EC14.
//
//   fn_8005E8EC is the right length now and thirty-five bytes differ, all of
//   them register fields plus one branch. Two things got it there and are worth
//   remembering for the other two. The sentinel test has to read
//   `(s32)found != -1` while the bound test stays unsigned: the target compares
//   with `cmpwi r31, -0x1` and `cmplwi r31, 0xa`, so the counter is unsigned and
//   only the sentinel is looked at as signed. Writing the counter as s32 fixes
//   the sentinel and breaks the bound; the cast fixes both.
//
//   What is left in it, and in the other two, is the same pair everywhere: the
//   target writes an address constant straight into its callee-saved register
//   where this build goes through r0 and copies, and the target leaves
//   `bne .L_next` followed by `b .L_out` where this build folds the two into a
//   single `beq .L_out`. The fold is not the peephole flag -- the unit already
//   builds with -opt noschedule,nopeephole, and every other combination tried
//   (none, nopeephole alone, noschedule alone, level=4) is worse. Five loop
//   spellings all normalise to the folded form.
//
//   fn_8005EA04 is twelve bytes short. It gained sixteen of those by recomputing
//   `lbl_802FF5E0[i].object` from the index instead of reusing the walked
//   `entry` pointer -- the target really does rebuild base + i * 0x44 rather
//   than reuse the cursor it already has. The same recompute applied to the
//   `request` accesses in the second half overshoots to 524 and, more to the
//   point, misaligns the function badly (81 differing rows against 66), so it
//   is not simply more of the same.
//
//   fn_8005ED88 is the right length now and twenty-seven bytes differ, all of
//   them one register swap: the target keeps the archive handle in r27 and the
//   scratch buffer in r29, this build has them the other way round. Getting
//   there took four things.
//
//   The big one is a build flag, not source: the unit needs -pooldata off. With
//   pooling on, MWCC notices that every one of this unit's data labels lives in
//   its own sections and folds them into one base register plus offsets --
//   `addi r3, r25, 0x4400`, `addi r4, r31, 0x188` and so on -- where the target
//   emits an independent lis/addi pair for each. That alone was thirty-six
//   bytes. eff_tornado.cpp already carries the same flag.
//
//   The stack frame gave away the path buffer. The target opens with
//   `stwu r1, -0x50(r1)` and saves r24 through r31, which leaves forty bytes
//   between the linkage area and the register save area. A `char path[0x40]`
//   cannot fit there; anything from 0x20 to 0x28 produces identical code, so
//   the size is only bounded, not recovered, and 0x20 is what is written.
//
//   The clearing loop shares the array base with the walk that follows it, and
//   the target materialises that base once into a callee-saved register. That
//   needs `request` declared before the loop, used by it, and assigned again
//   afterwards -- redundant as C, but it is what produces the single
//   materialisation.
//
//   Last, materialData has to be declared and initialised before material, with
//   material's call split out into its own statement, or the `li rN, 0` lands
//   after the fn_80041FF4 call instead of before it.

struct ResourceEntry {
	char name[0x40];
	void* object;
};

struct ResourceRequest {
	char name[0x40];
	void* data;
	u32 size;
	u32 slot;
	void* dictionary;
};

extern "C" {
char* strchr(const char*, s32);
s32 strncmp(const char*, const char*, u32);
char* strcpy(char*, const char*);
void* memset(void*, s32, u32);
s32 sprintf(char*, const char*, ...);
void Exec__22TObjSetDamageCollisionFv(void);
void EndEffTornado__Fv(void);
void InitEffTornado__Fv(void);
void startObjSetDamageCollision__Fv(void);
s32 fn_801C3C04(const char*, const char*);
void fn_80150958(void*);
void fn_8020C2D8(void*);
void fn_8011B7CC(void*);
void* fn_80012994(u32);
void fn_800126C8(void*);
void fn_800D0624(void*, void*, u32);
void* Expand2__FPvPv(void*, void*);
void fn_801A4C84(void*);
void* fn_80198000(s32, s32, void*);
s32 fn_80192F38(void*, s32, s32, s32);
void* fn_80150B88(void*);
void fn_80197ED8(void*, s32);
void fn_8014FFBC(void*, void*, s32);
void fn_800D075C(void*);
void* fn_801471DC(void);
void fn_801471C8(void*);
void fn_8014705C(void*);
void fn_801A46D0(void*);
void* texLoadTexDictionaryFile__FPc(char*);
void fn_801A4778(void*, void*, s32);
void* fn_80041FF4(char*);
void* fn_80146EA8(void*);
void* fn_80057644(u32);
void fn_800BCC84(void*, char*, s32);
void* fn_800BC694(void*, u32);
void fn_80112718(void);
void* fn_800BC370(void*, u32, void*, void*);
void* fn_800BC46C(void*, u32, void*);
void* fn_800BBF20(void*, u32, void*);
void* fn_800BBE0C(void*, u32, void*);
void fn_800BCBD4(void*, s32);
void fn_8005D498(void);
void fn_8005BEC4(void);
void fn_8005E03C(void);
void fn_8015C728(void*);
void fn_8015C6F8(void*, s32, s32);
void fn_8015C704(void*, s32, s32);
void fn_8015C710(void*, s32, s32, s32);
void fn_8015C720(void*, s32);

void fn_8010F3CC(void);
void fn_8010CA00(void);
void fn_8010C0C0(void);
void fn_8010AD10(void);
void fn_801043EC(void);
void fn_80100130(void);
void fn_800FAB00(void);
void fn_800F6FDC(void);
void fn_800F45A8(void);
void fn_800D0310(void);
void fn_800C968C(void);
void fn_800BDD5C(void);
void fn_800BDDA0(void);
void fn_800C9894(void);
void fn_800D0360(void);
void fn_800F45C8(void);
void fn_800F7038(void);
void fn_800FAB54(void);
void fn_80100144(void);
void fn_80104410(void);
void fn_8010AD48(void);
void fn_8010C108(void);
void fn_8010CA14(void);
void fn_8010F3F4(void);

#pragma force_active on
char lbl_80243418[]                     = "OBJ_BOBSLEIGH.DFF";
char lbl_8024342C[]                     = "OBJ_BBS_LAUNCHER.DFF";
char lbl_80243444[]                     = "OBJ_BOBSTOP.DFF";
char lbl_80243454[]                     = "OBJ_ROLLDOOR.DFF";
char lbl_80243468[]                     = "OBJ_SWB.DFF";
char lbl_80243474[]                     = "OBJ_TARGET.DFF";
char lbl_80243484[]                     = "OBJ_WEIGHT.DFF";
char lbl_80243494[]                     = "OBJ_WEIGHT_BROKEN.DFF";
char lbl_802434AC[]                     = "EF_RDOOR.DFF";
__declspec(export) char* lbl_802434BC[] = { lbl_80243418, lbl_8024342C, lbl_80243444, lbl_80243454,
	lbl_80243468, lbl_80243474, lbl_80243484, lbl_80243494, lbl_802434AC };
char lbl_802434E0[]                     = "OBJ_DSHR.DFF";
char lbl_802434F0[]                     = "OBJ_DUSHP.DFF";
char lbl_80243500[]                     = "EFF_BOB_ON.DFF";
char lbl_80243510[]                     = "EF_FIBALL.DFF";
char lbl_80243520[]                     = "EF_FCHG_BEAM.DFF";
char lbl_80243534[]                     = "EF_FLOWARP.DFF";
char lbl_80243544[]                     = "OBJ_JBOARD.DFF";
__declspec(export) char* lbl_80243554[] = { lbl_802434E0, lbl_802434F0, lbl_80243500, lbl_80243510,
	lbl_80243520, lbl_80243534, lbl_80243544 };
f32 lbl_80243570[] = { 8.5f, 9.0f, 6.4f, 9.0f, 19.0f, 8.5f, 9.0f, 25.0f, 6.3f, 8.5f, 22.0f, 6.2f };
__declspec(export) char lbl_802435A0[] = "./textures/obj_common.txd";
__declspec(export) char lbl_802435BC[] = "mte_gcn.mtd";
__declspec(export) char lbl_802435C8[] = "comobj.one";

char lbl_8042B228[] = "DFF";
char lbl_8042B22C[] = "ANM";
char lbl_8042B230[] = "UVB";

ResourceEntry lbl_802FF5E0[0x100];
u8 lbl_803039E0[0x18];
ResourceRequest lbl_803039F8[10];
void* lbl_8042C2A8;
#pragma force_active reset
}

extern "C" void fn_8005E8EC(void)
{
	s32 i                = 0;
	ResourceEntry* entry = lbl_802FF5E0;
	do {
		u32 found                = 0;
		ResourceRequest* request = lbl_803039F8;
		while (TRUE) {
			if (fn_801C3C04(request->name, entry->name) != 0) {
				request++;
				found++;
				if (found < 10)
					continue;
				found = -1;
			} else {
				break;
			}
			break;
		}
		if ((s32)found != -1) {
			char* extension = strchr(entry->name, '.');
			if (extension != NULL) {
				if (strncmp(extension + 1, lbl_8042B228, 3) == 0)
					fn_80150958(entry->object);
				else if (strncmp(extension + 1, lbl_8042B22C, 3) == 0)
					fn_8020C2D8(entry->object);
				else if (strncmp(extension + 1, lbl_8042B230, 3) == 0)
					fn_8011B7CC(entry->object);
				entry->object  = NULL;
				entry->name[0] = 0;
			}
		}
		entry++;
		i++;
	} while (i < 0x100);
}

extern "C" void* fn_8005EA04(char* name)
{
	void* result         = NULL;
	s32 i                = 0;
	ResourceEntry* entry = lbl_802FF5E0;
	while (TRUE) {
		if (fn_801C3C04(entry->name, name) != 0) {
			entry++;
			i++;
			if (i < 0x100)
				continue;
			i = -1;
		}
		break;
	}
	if (i != -1) {
		result = lbl_802FF5E0[i].object;
		goto done;
	}

	i                        = 0;
	ResourceRequest* request = lbl_803039F8;
	while (TRUE) {
		if (fn_801C3C04(request->name, name) != 0) {
			request++;
			i++;
			if ((u32)i < 10)
				continue;
			i = -1;
		}
		break;
	}
	if (i != -1) {
		if (lbl_802FF5E0[request->slot].object != NULL)
			return lbl_802FF5E0[request->slot].object;
		if (request->data != NULL) {
			void* expanded = fn_80012994(0x19000);
			void* input    = fn_80012994(request->size);
			fn_800D0624(input, request->data, request->size);
			void* end           = Expand2__FPvPv(input, expanded);
			void* streamArgs[2] = { expanded, end };
			fn_801A4C84(request->dictionary);
			void* stream = fn_80198000(3, 1, streamArgs);
			if (fn_80192F38(stream, 0x10, 0, 0) != 0)
				lbl_802FF5E0[request->slot].object = fn_80150B88(stream);
			fn_80197ED8(stream, 0);
			fn_800126C8(input);
			fn_800126C8(expanded);
			strcpy(lbl_802FF5E0[request->slot].name, request->name);
			if (lbl_802FF5E0[request->slot].object != NULL)
				fn_8014FFBC(lbl_802FF5E0[request->slot].object, (void*)fn_8005D498, 0);
			result = lbl_802FF5E0[request->slot].object;
		}
	}
done:
	return result;
}

extern "C" void* fn_8005EC0C(void)
{
	return lbl_8042C2A8;
}

extern "C" void fn_8005EC14(void)
{
	Exec__22TObjSetDamageCollisionFv();
	fn_8010F3CC();
	fn_8010CA00();
	fn_8010C0C0();
	fn_8010AD10();
	fn_801043EC();
	fn_80100130();
	fn_800FAB00();
	fn_800F6FDC();
	fn_800F45A8();
	fn_800D0310();
	fn_800C968C();
	fn_800BDD5C();
	EndEffTornado__Fv();
	for (s32 i = 0; i < 0x100; i++) {
		char* extension = strchr(lbl_802FF5E0[i].name, '.');
		if (extension != NULL) {
			if (strncmp(extension + 1, lbl_8042B228, 3) == 0)
				fn_80150958(lbl_802FF5E0[i].object);
			else if (strncmp(extension + 1, lbl_8042B22C, 3) == 0)
				fn_8020C2D8(lbl_802FF5E0[i].object);
			else if (strncmp(extension + 1, lbl_8042B230, 3) == 0)
				fn_8011B7CC(lbl_802FF5E0[i].object);
			lbl_802FF5E0[i].object = NULL;
		}
	}
	for (u32 i = 0; i < 10; i++)
		if (lbl_803039F8[i].data != NULL)
			fn_800D075C(lbl_803039F8[i].data);
	void* object = fn_801471DC();
	if (object != NULL) {
		fn_801471C8(NULL);
		fn_8014705C(object);
	}
	if (lbl_8042C2A8 != NULL) {
		fn_801A46D0(lbl_8042C2A8);
		lbl_8042C2A8 = NULL;
	}
}

extern "C" void fn_8005ED88(void)
{
	fn_8015C728(lbl_803039E0);
	fn_8015C6F8(lbl_803039E0, 3, 6);
	fn_8015C704(lbl_803039E0, 1, 0);
	fn_8015C710(lbl_803039E0, 1, 3, 10);
	fn_8015C720(lbl_803039E0, 3);
	if (lbl_8042C2A8 == NULL) {
		char path[0x20];
		sprintf(path, lbl_802435A0);
		lbl_8042C2A8 = texLoadTexDictionaryFile__FPc(path);
		if (lbl_8042C2A8 == NULL)
			return;
		fn_801A4778(lbl_8042C2A8, (void*)fn_8005E03C, 6);
	}
	void* material;
	void* materialData = NULL;
	material           = fn_80041FF4(lbl_802435BC);
	if (material != NULL) {
		if (fn_80192F38(material, 0x21, 0, 0) != 0)
			materialData = fn_80146EA8(material);
		fn_80197ED8(material, 0);
	}
	if (materialData != NULL)
		fn_801471C8(materialData);
	void* archive = fn_80057644(0x58);
	if (archive != NULL)
		fn_800BCC84(archive, lbl_802435C8, 0);
	if (archive != NULL) {
		fn_801A4C84(lbl_8042C2A8);
		u32 i;
		void* workspace          = fn_80012994(0x25800);
		ResourceRequest* request = lbl_803039F8;
		for (u32 i = 0; i < 10; i++)
			request[i].data = NULL;
		request = lbl_803039F8;
		for (i = 0; i < 0x100; i++) {
			char* source = (char*)fn_800BC694(archive, i);
			if (source == NULL) {
				memset(&lbl_802FF5E0[i], 0, 0x40);
				lbl_802FF5E0[i].object = NULL;
				continue;
			}
			strcpy(lbl_802FF5E0[i].name, source);
			char* extension = strchr(lbl_802FF5E0[i].name, '.');
			if (extension == NULL)
				continue;
			fn_80112718();
			if (strncmp(extension + 1, lbl_8042B228, 3) == 0) {
				s32 special = FALSE;
				for (u32 j = 0; j < 9; j++)
					if (fn_801C3C04(lbl_802FF5E0[i].name, lbl_802434BC[j]) == 0) {
						special = TRUE;
						break;
					}
				if (special) {
					lbl_802FF5E0[i].object = NULL;
					request->data          = fn_800BC370(archive, i, workspace, &request->size);
					request->slot          = i;
					strcpy(request->name, lbl_802FF5E0[i].name);
					lbl_802FF5E0[i].name[0] = 0;
					request->dictionary     = lbl_8042C2A8;
					request++;
				} else {
					lbl_802FF5E0[i].object = fn_800BC46C(archive, i, workspace);
					for (u32 j = 0; j < 7; j++)
						if (fn_801C3C04(lbl_802FF5E0[i].name, lbl_80243554[j]) == 0) {
							fn_8014FFBC(lbl_802FF5E0[i].object, (void*)fn_8005BEC4, 0);
							break;
						}
				}
				if (lbl_802FF5E0[i].object != NULL)
					fn_8014FFBC(lbl_802FF5E0[i].object, (void*)fn_8005D498, 0);
			} else if (strncmp(extension + 1, lbl_8042B22C, 3) == 0)
				lbl_802FF5E0[i].object = fn_800BBF20(archive, i, workspace);
			else if (strncmp(extension + 1, lbl_8042B230, 3) == 0)
				lbl_802FF5E0[i].object = fn_800BBE0C(archive, i, workspace);
			else
				lbl_802FF5E0[i].object = NULL;
		}
		if (workspace != NULL)
			fn_800126C8(workspace);
		fn_800BCBD4(archive, 1);
	} else
		memset(lbl_802FF5E0, 0, 0x4400);
	InitEffTornado__Fv();
	fn_800BDDA0();
	fn_800C9894();
	fn_800D0360();
	fn_800F45C8();
	fn_800F7038();
	fn_800FAB54();
	fn_80100144();
	fn_80104410();
	fn_8010AD48();
	fn_8010C108();
	fn_8010CA14();
	fn_8010F3F4();
	startObjSetDamageCollision__Fv();
}
