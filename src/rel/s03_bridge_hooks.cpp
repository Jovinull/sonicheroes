#include "types.h"

// The bridge's Unload and Load hooks (s03BridgeUnload and s03BridgeLoad
// here): each of its five parts' animation (a morph for type-1 parts, a
// hierarchy animation for type-2 ones) and model are released, the model
// through fn_800B8ADC first when bit 0 of its flags is set. When the module's
// texture dictionary is there, it is made current and the family's material
// animations are set up (the retail code resets the second one and then
// configures the first again). The module's model archive is read and each
// part loads its morph (type 1, frame count kept) and its model by its name
// with the matching extension, the model through fn_800B8BEC (flags bit 0),
// fn_800BDF30 (bit 2) and the family's callback (with 1 for the third part).
// Type-2 parts then get their animation and type-4 parts a fixed length. The
// dictionary also goes through fn_800BE274 before the parts and fn_800BE1F4
// after them.

// one of the bridge's parts: its type and flags, the model and its animation
// once loaded, the animation's length and its file name
typedef struct S03BridgePart {
	s8 type;  // 0x00
	u8 flags; // 0x01
	u8 unk02[0x2];
	void* model;      // 0x04
	void* animation;  // 0x08
	f32 duration;     // 0x0C
	const char* name; // 0x10
} S03BridgePart;      // 0x14

// the family's material animations (fn_8015C6F8 and its neighbours set them up)
typedef struct S03BridgeMatAnim {
	u8 unk00[0x18];
} S03BridgeMatAnim;

extern "C" u8 s03BridgeParts[];
extern "C" S03BridgeMatAnim s03BridgeMatAnim;
extern "C" S03BridgeMatAnim s03BridgeMatAnim2;
extern "C" char s03BridgeMorphFormat[];
extern "C" char s03BridgeNameFormat[];
extern "C" char s03BridgeAnimationFormat[];
extern "C" const f32 lbl_4_rodata_1320;
extern "C" u8* lbl_8042C1D0;
extern "C" u8* lbl_8042C298;
extern "C" u8 lbl_8042C340[];
extern "C" u8 lbl_802FF5A0[];

extern "C" int sprintf(char* buffer, const char* format, ...);
extern "C" void fn_801A4C84(void* resource);
extern "C" void fn_80150958(void* clump);
extern "C" void fn_8013BD74(void* morph);
extern "C" void fn_8020C2D8(void* animation);
extern "C" void fn_800B8ADC(void* clump);
extern "C" void fn_800B8BEC(void* clump, s32 flag);
extern "C" void fn_800BDF30(void* clump);
extern "C" void fn_800BE1F4(void* resource);
extern "C" void fn_800BE274(void* resource);
extern "C" void fn_8015C728(S03BridgeMatAnim* anim);
extern "C" void fn_8015C6F8(S03BridgeMatAnim* anim, s32 a, s32 b);
extern "C" void fn_8015C704(S03BridgeMatAnim* anim, s32 a, s32 b);
extern "C" void fn_8015C710(S03BridgeMatAnim* anim, s32 a, s32 b, s32 c);
extern "C" void fn_8015C720(S03BridgeMatAnim* anim, s32 a);
extern "C" void fn_8014FFBC(void* clump, void* (*callback)(void*), void* data);
extern "C" void* fn_4_79128(void* atomic);
extern "C" void LoadOneFile__7ONEFILEFPc(void* onefile, void* name);
extern "C" void* CheckFileID__7ONEFILEFPc(void* onefile, const char* name);
extern "C" void* LoadClumpEx__7ONEFILEFUiPc(void* onefile, void* id, void* archive);
extern "C" void* LoadHAnimationEx__7ONEFILEFUiPc(void* onefile, void* id, void* archive);
extern "C" void* LoadDeltaMorphEx__7ONEFILEFUiPc(void* onefile, void* id, void* archive);
extern "C" f32 GetTotalFrame__10DAnimClassFP17RpDMorphAnimation(void* anim, void* morph);

extern "C" void s03BridgeUnload(void)
{
	S03BridgePart* part = (S03BridgePart*)s03BridgeParts;

	for (u8 i = 0; i < 5; i++) {
		if (part->animation != NULL) {
			if (part->type == 1) {
				fn_8013BD74(part->animation);
			}
			if (part->type == 2) {
				fn_8020C2D8(part->animation);
			}
			part->animation = NULL;
		}
		if (part->model != NULL) {
			if (part->flags & 1) {
				fn_800B8ADC(part->model);
			}
			fn_80150958(part->model);
			part->model = NULL;
		}
		part++;
	}
}

extern "C" void s03BridgeLoad(void)
{
	char name[0x20];
	void* resource = *(void**)(lbl_8042C1D0 + 0x8C18);

	if (resource != NULL) {
		fn_801A4C84(resource);
	} else {
		return;
	}
	fn_8015C728(&s03BridgeMatAnim);
	fn_8015C6F8(&s03BridgeMatAnim, 3, 4);
	fn_8015C704(&s03BridgeMatAnim, 1, 0);
	fn_8015C710(&s03BridgeMatAnim, 1, 3, 6);
	fn_8015C720(&s03BridgeMatAnim, 3);
	fn_8015C728(&s03BridgeMatAnim2);
	fn_8015C6F8(&s03BridgeMatAnim, 3, 4);
	fn_8015C704(&s03BridgeMatAnim, 1, 0);
	fn_8015C710(&s03BridgeMatAnim, 1, 3, 6);
	fn_8015C720(&s03BridgeMatAnim, 0);
	fn_800BE274(*(void**)(lbl_8042C1D0 + 0x8C18));
	LoadOneFile__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), lbl_802FF5A0);
	S03BridgePart* part = (S03BridgePart*)s03BridgeParts;

	for (u8 i = 0; i < 5; i++) {
		if (part->type == 1) {
			sprintf(name, s03BridgeMorphFormat, part->name);
			void* morph = LoadDeltaMorphEx__7ONEFILEFUiPc(*(void**)(lbl_8042C298 + 0xA50),
			    CheckFileID__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), name), lbl_802FF5A0);
			if (morph != NULL) {
				part->duration
				    = GetTotalFrame__10DAnimClassFP17RpDMorphAnimation(lbl_8042C340, morph);
				part->animation = morph;
			}
		}
		sprintf(name, s03BridgeNameFormat, part->name);
		part->model = LoadClumpEx__7ONEFILEFUiPc(*(void**)(lbl_8042C298 + 0xA50),
		    CheckFileID__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), name), lbl_802FF5A0);
		if (part->model != NULL && (part->flags & 1)) {
			fn_800B8BEC(part->model, 0);
		}
		if (part->model != NULL && (part->flags & 4)) {
			fn_800BDF30(part->model);
		}
		if (part->model != NULL) {
			if (i == 2) {
				fn_8014FFBC(part->model, fn_4_79128, (void*)1);
			} else {
				fn_8014FFBC(part->model, fn_4_79128, NULL);
			}
		}
		if (part->type == 2) {
			sprintf(name, s03BridgeAnimationFormat, part->name);
			void* animation = LoadHAnimationEx__7ONEFILEFUiPc(*(void**)(lbl_8042C298 + 0xA50),
			    CheckFileID__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), name), lbl_802FF5A0);
			if (animation != NULL) {
				part->duration  = *(f32*)((u8*)animation + 0xC);
				part->animation = animation;
			}
		} else if (part->type == 4) {
			part->duration = lbl_4_rodata_1320;
		}
		part++;
	}
	fn_800BE1F4(*(void**)(lbl_8042C1D0 + 0x8C18));
}
