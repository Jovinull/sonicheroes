#include "types.h"

// The capture enemy's score hook (captureAddScore here), the same in the
// seven stage modules that carry the capture: 200 points to the player that
// beat it, 400 for the special kind.

class TEnemyScoreMan
{
public:
	void AddScore(s32 player, s32 score);
	static void CreateInstance();
	static TEnemyScoreMan* EnemyScoreMan;
};

typedef struct Capture {
	u8 unk000[0x230];
	s32 player; // 0x230
	u8 unk234[0x348];
	s32 special; // 0x57C
} Capture;

extern "C" void captureAddScore(Capture* object)
{
	if (object->special == 0) {
		if (TEnemyScoreMan::EnemyScoreMan == NULL) {
			TEnemyScoreMan::CreateInstance();
		}
		TEnemyScoreMan::EnemyScoreMan->AddScore(object->player, 200);
		return;
	}
	if (TEnemyScoreMan::EnemyScoreMan == NULL) {
		TEnemyScoreMan::CreateInstance();
	}
	TEnemyScoreMan::EnemyScoreMan->AddScore(object->player, 400);
}
