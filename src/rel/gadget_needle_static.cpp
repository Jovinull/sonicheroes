#include "game/enemy/e_database.h"

// TEnemyGadgetNeedle::Finalize and Initialize (the PS2 build's names), static:
// the needles' model (0x10) and UV animation (0x11) are found in the searcher
// files (enemy database kind 2) and, when both are there, the animation is set
// on the model's atomics; finalizing forgets them (needleFx*, ours).

struct RwTexDictionary;

struct UVFXInfo {
	RpUVAnimAnimation* anim; // 0x00
	u8 unk04[0x40];
};

class TEnemyGadgetNeedle
{
public:
	static void Finalize();
	static void Initialize();
};

void SetClumpCustomFXTexture(RpClump* clump, UVFXInfo* info);

extern "C" s32 needleFxFrame;
extern "C" RpUVAnimAnimation* needleFxAnim;
extern "C" RpClump* needleFxClump;
extern "C" UVFXInfo needleFxData;

void TEnemyGadgetNeedle::Finalize()
{
	needleFxFrame = 0;
	needleFxAnim  = NULL;
	needleFxClump = NULL;
}

void TEnemyGadgetNeedle::Initialize()
{
	needleFxClump = TEnemyDataBase::GetInstance()->SearchClump((eEnemyDataBase)2, 0x10);
	needleFxAnim  = TEnemyDataBase::GetInstance()->SearchUVAnim((eEnemyDataBase)2, 0x11);
	if (needleFxClump != NULL && needleFxAnim != NULL) {
		needleFxData.anim = needleFxAnim;
		SetClumpCustomFXTexture(needleFxClump, &needleFxData);
	}
	needleFxFrame = 0;
}
