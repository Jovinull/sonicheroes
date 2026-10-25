#include "types.h"

// The stage 13 and 14 families' part infos (an animation without a model of
// its own): fn_9_75E60 releases the part's animation by its kind (a delta
// morph, a hierarchical animation, or a UV animation with its FX buffer freed)
// and forgets it; fn_9_75F08 loads it by its kind under the name given (or the
// part's own) and keeps its length, a UV animation getting a new FX buffer.
// Like a model record's load, it first formats the model's name too, which it
// then does not use.

struct RtAnimAnimation;
struct RpDMorphAnimation;
struct RpUVAnimAnimation;

// one of the stage's part infos
typedef struct S13PartInfo {
	s8 animKind; // 0x00
	u8 unk01[0x3];
	void* anim;       // 0x04
	f32 length;       // 0x08
	void* animBuffer; // 0x0C
	const char* name; // 0x10
} S13PartInfo;        // 0x14

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
extern "C" RtAnimAnimation* LoadHAnimationEx__7ONEFILEFUiPc(void* onefile, void* id, void* archive);
extern "C" RpDMorphAnimation* LoadDeltaMorphEx__7ONEFILEFUiPc(
    void* onefile, void* id, void* archive);
extern "C" RpUVAnimAnimation* LoadUVAnimationEx__7ONEFILEFUiPc(
    void* onefile, void* id, void* archive);
extern "C" void fn_8013BD74(void* anim);
extern "C" void fn_8020C2D8(void* anim);
extern "C" void fn_8011B7CC(void* anim);
f32 objRpUVAnimAnimationGetTotalFrame(RpUVAnimAnimation* animation);

extern "C" void fn_9_75E60(S13PartInfo* part)
{
	if (part->anim != NULL) {
		switch (part->animKind) {
			case 2:
				fn_8020C2D8(part->anim);
				break;
			case 1:
				fn_8013BD74(part->anim);
				break;
			case 3:
				fn_8011B7CC(part->anim);
				if (part->animBuffer != NULL) {
					(*(void (**)(void*))(lbl_8042C9A4 + 0x138))(part->animBuffer);
					part->animBuffer = NULL;
				}
				break;
		}
		part->anim = NULL;
	}
}

extern "C" void fn_9_75F08(S13PartInfo* part, const char* name)
{
	char path[64];
	const char* base = name != NULL ? name : part->name;

	sprintf(path, s13ModelInfoNameFormat, base);
	switch (part->animKind) {
		case 2: {
			sprintf(path, s13ModelRecordHAnimFormat, base);
			RtAnimAnimation* anim = LoadHAnimationEx__7ONEFILEFUiPc(*(void**)(lbl_8042C298 + 0xA50),
			    CheckFileID__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), path), lbl_802FF5A0);
			if (anim != NULL) {
				part->length = anim->duration;
				part->anim   = anim;
			}
		} break;
		case 1: {
			sprintf(path, s13ModelRecordDMorphFormat, base);
			RpDMorphAnimation* anim
			    = LoadDeltaMorphEx__7ONEFILEFUiPc(*(void**)(lbl_8042C298 + 0xA50),
			        CheckFileID__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), path), lbl_802FF5A0);
			if (anim != NULL) {
				part->length = lbl_8042C340.GetTotalFrame(anim);
				part->anim   = anim;
			}
		} break;
		case 3: {
			sprintf(path, s13ModelRecordUVAnimFormat, base);
			RpUVAnimAnimation* anim
			    = LoadUVAnimationEx__7ONEFILEFUiPc(*(void**)(lbl_8042C298 + 0xA50),
			        CheckFileID__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), path), lbl_802FF5A0);
			if (anim != NULL) {
				part->animBuffer = (*(void* (**)(u32))(lbl_8042C9A4 + 0x134))(0x44);
				if (part->animBuffer != NULL) {
					*(RpUVAnimAnimation**)part->animBuffer = anim;
				}
				part->anim   = anim;
				part->length = objRpUVAnimAnimationGetTotalFrame(anim);
			}
		} break;
	}
}
