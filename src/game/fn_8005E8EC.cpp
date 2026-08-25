#include "types.h"

// The original translation-unit name and private type names are unknown. This
// neutral filename follows the first function address; descriptive private
// identifiers below are reconstruction aids rather than recovered names.
//
// The bounds came from a data-privacy scan over the run: every lbl_ object the
// five functions reference is consumed inside them, and the next function up,
// fn_8005F194, reaches labels with ninety to a hundred and forty-five users.
//
// All five functions are byte-exact. The unit is still NonMatching, and the
// only thing left is sixteen bytes of exception metadata -- see the end of this
// note.
//
// Three shapes did the work, and they generalise:
//
//   The sentinel test reads `(s32)found != -1` while the bound test stays
//   unsigned. The target compares with `cmpwi r31, -0x1` and `cmplwi r31, 0xa`,
//   so the counter is unsigned and only the sentinel is read as signed. Writing
//   the counter as s32 fixes the sentinel and breaks the bound; the cast fixes
//   both.
//
//   fn_8005EA04 closes on a short-circuit `&&`. The target ends the request
//   path with a `bne`/`b` pair and a join where both arms write r0 before a
//   single `mr r28, r0`; this build folded that into one `beq` and returned the
//   value directly. The fold is not an optimisation flag -- every pragma the
//   compiler accepts (opt_propagation, opt_common_subs, opt_lifetimes,
//   no_register_coloring, peephole, optimization_level 0 through 3) and every
//   flag combination leaves it, and twenty different loop and goto spellings
//   all normalise to the same folded form. What produces the pair is writing
//   the two conditions as one `&&`: `if (result == NULL && data != NULL)` with
//   an `else if (result == NULL) result = NULL;` arm. Short-circuit evaluation
//   is what emits the second branch, not a missing peephole.
//
//   The unit needs -pooldata off. With pooling on, MWCC folds every one of this
//   unit's data labels into one base register plus offsets where the target
//   emits an independent lis/addi pair for each. That alone was thirty-six
//   bytes. eff_tornado.cpp already carries the same flag.
//
// Two smaller ones, kept because they are easy to undo by accident. `request`
// has to be declared before the clearing loop, used by it, and assigned again
// afterwards -- redundant as C, but it is what makes the target materialise the
// array base once into a callee-saved register. And `streamArgs` has to be two
// assignments in reverse order, `[1]` then `[0]`, not a braced initialiser: the
// initialiser makes MWCC lay down an eight-byte zero template from .sdata2
// first, four instructions the target does not have.
//
// The stack frame bounds the path buffer rather than recovering it. The target
// opens fn_8005ED88 with `stwu r1, -0x50(r1)` and saves r24 through r31, which
// leaves forty bytes between the linkage area and the register save area. A
// `char path[0x40]` cannot fit; anything from 0x20 to 0x28 produces identical
// code, so 0x20 is a bound, not a reading.
//
// WHAT BLOCKS THE FLIP TO Matching
//
//   The retail object carries a 0x30-byte extab; this build emits 0x20, so the
//   linked DOL comes out thirty-two bytes short. Three of the four entries were
//   already right. The fourth, fn_8005ED88's, carries a __dl__FPv cleanup over
//   the constructor call at +0x134, which only a real new-expression produces:
//   MWCC has to be able to free the raw allocation if the constructor throws.
//   Writing the allocation as `new ResourceArchive(...)`, with fn_80057644 as
//   the class's own operator new and fn_800BCC84 as the constructor, keeps all
//   five functions byte-exact and brings the extab to the right 0x30 bytes.
//
//   One byte inside it still differs: the cleanup record reads 0x8a80001b in
//   the target and 0x8a80001f here. The low field tracks the register the
//   compiler believes holds the pointer -- 27 against 31 -- and the target's 27
//   is the register the emitted code actually uses. Every spelling that keeps
//   the five functions byte-exact yields 31; the two that yield 24 both break a
//   function. Declaration position, an out-of-line constructor, a trivial or
//   virtual destructor, an explicit operator delete, a sized class body and
//   casting through void*, char* or u8* were all tried. This looks like MWCC
//   exception bookkeeping that the source cannot reach directly, so it is
//   written down rather than guessed at further.
//
// One claim in splits.txt that issue #297 raised is settled, and it is the
// second thing standing between this unit and Matching. lbl_80301780 is not a
// real object: it sits at offset 0x21A0 inside lbl_802FF5E0, which the code
// walks as 256 entries of 68 bytes, so it lands mid-entry -- 126 entries and 40
// bytes in -- and cannot be a symbol. dtk invents it from the single word at
// 0x80273C04 inside lbl_80270F6A that happens to equal 0x80301780; that is the
// only occurrence in the DOL and the surrounding data is high-entropy with no
// other pointer in it, so the word is data, not an address. While the unit is
// NonMatching this costs nothing, because dtk defines the phantom in its own
// generated object. On the flip to Matching the source has to define it, and it
// cannot, so the link fails with `undefined: lbl_80301780`. Marking
// lbl_80270F6A `noreloc` and deleting the symbol does clear the link error, but
// dtk writes the symbol back into symbols.txt on the next split, so that pair
// is not a durable fix and is left out of this change.
//
// The remaining claim, lbl_803039E0, stands as before: this unit owns it and
// fn_8005D498 reads it, which is allowed but is said out loud here.

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

// The retail extab carries a __dl__FPv cleanup over the constructor call at
// fn_8005ED88+0x134, which only a real new-expression produces: MWCC has to be
// able to free the raw allocation if the constructor throws. So the archive is
// built with `new`, with fn_80057644 as the class's own operator new and
// fn_800BCC84 as the constructor. Writing the two calls by hand -- the idiom
// used in adv_staffroll.cpp and ef_sparkle.cpp -- emits the same instructions
// but no exception table, which is how this unit read before.
class ResourceArchive
{
public:
	ResourceArchive(char* name, s32 flags) { fn_800BCC84(this, name, flags); }
	static void* operator new(unsigned long size) { return fn_80057644(size); }
};

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
		request    = &lbl_803039F8[i];
		void* data = request->data;
		result     = lbl_802FF5E0[request->slot].object;
		if (result == NULL && data != NULL) {
			void* expanded = fn_80012994(0x19000);
			void* input    = fn_80012994(request->size);
			fn_800D0624(input, data, request->size);
			void* end = Expand2__FPvPv(input, expanded);
			void* streamArgs[2];
			streamArgs[1] = end;
			streamArgs[0] = expanded;
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
		} else if (result == NULL) {
			result = NULL;
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
	ResourceArchive* archive = new ResourceArchive(lbl_802435C8, 0);
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
