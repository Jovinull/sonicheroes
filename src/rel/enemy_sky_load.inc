// The sky loader shared by the stages 26-28 sky enemies (TObjEnemyStg27Cloud
// in 26 and 27, TObjEnemyCloud in 28): Finalize frees the two effect
// animations and the three sky models; Initialize loads the stage's one-file,
// its three sky models and two effect animations, gives each model its
// animation (the third shares the second's) as the custom texture effect and
// restarts the frame counters the cloud's Disp watches. Each module keeps it
// out of line as the class's statics and inlined into the stage's object
// set's Unload and Load. A unit defines SKY_LOADER (the linkage), SKY_FINALIZE
// and SKY_INITIALIZE (the names) and SKY(x) (the module's name for each sky
// table) before including it.

#include "types.h"

struct RpClump;
struct RwTexDictionary;
struct RpUVAnimAnimation;

struct UVFXInfo {
	RpUVAnimAnimation* anim; // 0x00
	u8 unk04[0x40];
}; // 0x44

class ONEFILE
{
public:
	void LoadOneFile(char* path);
	u32 CheckFileID(char* name);
	RpClump* LoadClumpEx(u32 id, char* path);
	RpUVAnimAnimation* LoadUVAnimationEx(u32 id, char* path);
};

struct StageFiles {
	u8 unk000[0xA50];
	ONEFILE* file; // 0xA50
};

struct GameWorld {
	u8 unk0000[0x8C18];
	RwTexDictionary* dictionary; // 0x8C18
};

void SetClumpCustomFXTexture(RpClump* clump, UVFXInfo* info);

extern "C" {
extern StageFiles* lbl_8042C298;
extern GameWorld* lbl_8042C1D0;
extern char lbl_802FF5A0[];
extern char* SKY(ModelNames)[3];
extern char* SKY(AnimNames)[2];
extern RpClump* SKY(Models)[3];
extern RpUVAnimAnimation* SKY(FxAnim)[2];
extern UVFXInfo SKY(FxData)[3];
extern s32 SKY(LastFrame)[3];
void fn_801A4C84(RwTexDictionary* dictionary);
void fn_8011B7CC(RpUVAnimAnimation* anim);
void fn_80150958(RpClump* clump);
}

SKY_LOADER void SKY_FINALIZE(void)
{
	s32 i;

	for (i = 0; i < 2; i++) {
		if (SKY(FxAnim)[i] != NULL) {
			fn_8011B7CC(SKY(FxAnim)[i]);
			SKY(FxAnim)[i] = NULL;
		}
	}
	for (s32 j = 0; j < 3; j++) {
		if (SKY(Models)[j] != NULL) {
			fn_80150958(SKY(Models)[j]);
			SKY(Models)[j] = NULL;
		}
	}
}

SKY_LOADER void SKY_INITIALIZE(void)
{
	s32 i;

	fn_801A4C84(lbl_8042C1D0->dictionary);
	lbl_8042C298->file->LoadOneFile(lbl_802FF5A0);
	for (i = 0; i < 3; i++) {
		SKY(Models)[i] = lbl_8042C298->file->LoadClumpEx(
		    lbl_8042C298->file->CheckFileID(SKY(ModelNames)[i]), lbl_802FF5A0);
	}
	for (i = 0; i < 2; i++) {
		SKY(FxAnim)[i] = lbl_8042C298->file->LoadUVAnimationEx(
		    lbl_8042C298->file->CheckFileID(SKY(AnimNames)[i]), lbl_802FF5A0);
	}
	if (SKY(Models)[0] != NULL && SKY(FxAnim)[0] != NULL) {
		SKY(FxData)[0].anim = SKY(FxAnim)[0];
		SetClumpCustomFXTexture(SKY(Models)[0], &SKY(FxData)[0]);
	}
	if (SKY(Models)[1] != NULL && SKY(FxAnim)[1] != NULL) {
		SKY(FxData)[1].anim = SKY(FxAnim)[1];
		SetClumpCustomFXTexture(SKY(Models)[1], &SKY(FxData)[1]);
	}
	if (SKY(Models)[2] != NULL && SKY(FxAnim)[1] != NULL) {
		SKY(FxData)[2].anim = SKY(FxAnim)[1];
		SetClumpCustomFXTexture(SKY(Models)[2], &SKY(FxData)[2]);
	}
	SKY(LastFrame)[0] = 0;
	SKY(LastFrame)[1] = 0;
	SKY(LastFrame)[2] = 0;
}
