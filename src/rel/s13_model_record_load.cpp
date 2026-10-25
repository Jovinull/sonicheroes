#include "types.h"

// fn_9_765CC, which the stage 13 and 14 families' Load hooks run over their
// model records: the model is loaded and set up as s13ModelInfoLoad does an
// info's (under the name given or the record's own), then the record's
// animation, by its kind, is loaded under the same name and its length kept: a
// hierarchical animation, a delta morph, or a UV animation handed to the
// model's first atomic through a new FX buffer.

struct RpClump;
struct RpAtomic;
struct RtAnimAnimation;
struct RpDMorphAnimation;
struct RpUVAnimAnimation;

// the flags of a model info
typedef struct S13ModelFlags {
	u16 bits; // 0x00
} S13ModelFlags;

// one of the stage's larger model records
typedef struct S13ModelRecord {
	S13ModelFlags flags; // 0x00
	u8 unk02[0x6];
	S13ModelFlags stage15Flags; // 0x08
	u8 unk0A[0x6];
	RpClump* model; // 0x10
	s8 animKind;    // 0x14
	u8 unk15[0x3];
	void* anim;       // 0x18
	f32 length;       // 0x1C
	void* animBuffer; // 0x20
	u8 unk24[0x4];
	const char* name; // 0x28
} S13ModelRecord;     // 0x2C

// the shared material animation (fn_8015C6F8 and its neighbours set it up)
typedef struct MatAnim {
	u8 unk00[0x18];
} MatAnim;

// the game state: only the stage is read here
typedef struct GameState {
	u8 unk00[0x2C];
	s32 stage; // 0x2C
} GameState;

// the hierarchical animation: only its duration is read here
struct RtAnimAnimation {
	u8 unk00[0xC];
	f32 duration; // 0x0C
};

class DAnimClass
{
public:
	f32 GetTotalFrame(RpDMorphAnimation* animation);
};

extern "C" GameState lbl_8029C310;
extern "C" MatAnim* s13ModelInfoMatAnim;
extern "C" char s13ModelInfoNameFormat[];
extern "C" char s13ModelRecordHAnimFormat[];
extern "C" char s13ModelRecordDMorphFormat[];
extern "C" char s13ModelRecordUVAnimFormat[];
extern "C" DAnimClass lbl_8042C340;
extern "C" u8* lbl_8042C9A4;
extern "C" u8* lbl_8042C298;
extern "C" u8 lbl_802FF5A0[];

extern "C" int sprintf(char* buffer, const char* format, ...);
extern "C" void* CheckFileID__7ONEFILEFPc(void* onefile, const char* name);
extern "C" RpClump* LoadClumpEx__7ONEFILEFUiPc(void* onefile, void* id, void* archive);
extern "C" RtAnimAnimation* LoadHAnimationEx__7ONEFILEFUiPc(void* onefile, void* id, void* archive);
extern "C" RpDMorphAnimation* LoadDeltaMorphEx__7ONEFILEFUiPc(
    void* onefile, void* id, void* archive);
extern "C" RpUVAnimAnimation* LoadUVAnimationEx__7ONEFILEFUiPc(
    void* onefile, void* id, void* archive);
extern "C" void fn_800B8BEC(RpClump* clump, s32 a);
extern "C" void fn_800BDF30(RpClump* clump);
extern "C" void fn_8003C640(RpClump* clump);
extern "C" void fn_8015C728(MatAnim* anim);
extern "C" void fn_8015C6F8(MatAnim* anim, s32 a, s32 b);
extern "C" void fn_8015C704(MatAnim* anim, s32 a, s32 b);
extern "C" void fn_8015C710(MatAnim* anim, s32 a, s32 b, s32 c);
extern "C" void fn_8015C720(MatAnim* anim, s32 a);
extern "C" void fn_8014FFBC(RpClump* clump, void* (*callback)(void*), void* data);
extern "C" void* fn_9_76DAC(void* atomic);
void objRpClumpForAllGeometrysToIgnoreLights(RpClump* clump);
void objRpClumpForAllGeometrysToModulateMaterialColor(RpClump* clump);
RpAtomic* objRpClumpGetAtomic(RpClump* clump, RpAtomic* after);
void AtomicSetCustomFXTexture(RpAtomic* atomic, void* data);
f32 objRpUVAnimAnimationGetTotalFrame(RpUVAnimAnimation* animation);

// the stage's shared material animation, made and set up on first use
inline MatAnim* s13ModelInfoGetMatAnim(void)
{
	if (s13ModelInfoMatAnim != NULL) {
		return s13ModelInfoMatAnim;
	}
	s13ModelInfoMatAnim = (MatAnim*)operator new(sizeof(MatAnim));
	if (s13ModelInfoMatAnim != NULL) {
		fn_8015C728(s13ModelInfoMatAnim);
		fn_8015C6F8(s13ModelInfoMatAnim, 3, 4);
		fn_8015C704(s13ModelInfoMatAnim, 1, 0);
		fn_8015C710(s13ModelInfoMatAnim, 1, 3, 6);
		fn_8015C720(s13ModelInfoMatAnim, 3);
		return s13ModelInfoMatAnim;
	}
	return NULL;
}

// the record's flags: its second set on stage 15 when it asks for it
inline S13ModelFlags* s13ModelRecordFlags(S13ModelRecord* record)
{
	s32 stage            = lbl_8029C310.stage;
	S13ModelFlags* flags = &record->flags;

	if ((record->flags.bits & 0x200) && stage == 15) {
		flags = &record->stage15Flags;
	}
	return flags;
}

extern "C" void fn_9_765CC(S13ModelRecord* record, const char* name)
{
	char path[64];
	const char* base;
	S13ModelFlags* flags = s13ModelRecordFlags(record);

	base = name != NULL ? name : record->name;
	sprintf(path, s13ModelInfoNameFormat, base);
	record->model = LoadClumpEx__7ONEFILEFUiPc(*(void**)(lbl_8042C298 + 0xA50),
	    CheckFileID__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), path), lbl_802FF5A0);
	if (record->model != NULL) {
		if (flags->bits & 0x1) {
			fn_800B8BEC(record->model, 0);
		}
		if (flags->bits & 0x4) {
			fn_800B8BEC(record->model, 0);
		}
		if (flags->bits & 0x10) {
			fn_800BDF30(record->model);
		}
		if (flags->bits & 0x20) {
			fn_8003C640(record->model);
		}
		if (flags->bits & 0x8) {
			objRpClumpForAllGeometrysToIgnoreLights(record->model);
		}
		if (flags->bits & 0x40) {
			objRpClumpForAllGeometrysToModulateMaterialColor(record->model);
		}
		if (flags->bits & 0x400) {
			RpClump* model = record->model;
			MatAnim* anim  = s13ModelInfoGetMatAnim();
			if (anim != NULL) {
				fn_8014FFBC(model, fn_9_76DAC, anim);
			}
		}
	}
	switch (record->animKind) {
		case 2: {
			sprintf(path, s13ModelRecordHAnimFormat, base);
			RtAnimAnimation* anim = LoadHAnimationEx__7ONEFILEFUiPc(*(void**)(lbl_8042C298 + 0xA50),
			    CheckFileID__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), path), lbl_802FF5A0);
			if (anim != NULL) {
				record->length = anim->duration;
				record->anim   = anim;
			}
		} break;
		case 1: {
			sprintf(path, s13ModelRecordDMorphFormat, base);
			RpDMorphAnimation* anim
			    = LoadDeltaMorphEx__7ONEFILEFUiPc(*(void**)(lbl_8042C298 + 0xA50),
			        CheckFileID__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), path), lbl_802FF5A0);
			if (anim != NULL) {
				record->length = lbl_8042C340.GetTotalFrame(anim);
				record->anim   = anim;
			}
		} break;
		case 3: {
			sprintf(path, s13ModelRecordUVAnimFormat, base);
			RpUVAnimAnimation* anim
			    = LoadUVAnimationEx__7ONEFILEFUiPc(*(void**)(lbl_8042C298 + 0xA50),
			        CheckFileID__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), path), lbl_802FF5A0);
			if (anim != NULL) {
				if (record->model != NULL && anim != NULL) {
					record->animBuffer = (*(void* (**)(u32))(lbl_8042C9A4 + 0x134))(0x44);
					if (record->animBuffer != NULL) {
						*(RpUVAnimAnimation**)record->animBuffer = anim;
						AtomicSetCustomFXTexture(
						    objRpClumpGetAtomic(record->model, NULL), record->animBuffer);
					}
				}
				record->anim   = anim;
				record->length = objRpUVAnimAnimationGetTotalFrame(anim);
			}
		} break;
	}
}
