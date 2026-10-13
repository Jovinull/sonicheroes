#include "types.h"

// TObjEnemySearcher::CheckHitPoint (the PS2 build's name): when the hit points
// changed, shows the hit point gauge for three seconds (with 100 more while
// the searcher sounds its siren, enemy mode 0x24) and hides the other icon;
// both icons follow the searcher. Returns whether the hit points changed.

typedef struct RwV3d {
	f32 x, y, z;
} RwV3d;

class TEnemyIconMan
{
public:
	void Off();
	void On(f32 value, f32 time, s32 extra);
	void On(f32 value, f32 time);
	void SetPos(const RwV3d* pos, const RwV3d* offset);
};

typedef struct Searcher {
	u8 unk000[0x140];
	RwV3d pos; // 0x140
	u8 unk14C[0x50];
	s32 mode; // 0x19C
	u8 unk1A0[0x4];
	f32 hitPoint; // 0x1A4
	u8 unk1A8[0x100];
	f32 shownHitPoint; // 0x2A8
	u8 unk2AC[0x4];
	TEnemyIconMan* gauge; // 0x2B0
	TEnemyIconMan* icon;  // 0x2B4
} Searcher;

extern "C" const f32 searcherIconShowTime;

extern "C" int CheckHitPoint__17TObjEnemySearcherFv(Searcher* searcher)
{
	int changed  = 0;
	f32 hitPoint = searcher->hitPoint;

	if (hitPoint != searcher->shownHitPoint) {
		searcher->shownHitPoint = hitPoint;
		if (searcher->gauge != NULL) {
			if (searcher->mode == 0x24) {
				searcher->gauge->On(hitPoint, searcherIconShowTime, 100);
			} else {
				searcher->gauge->On(hitPoint, searcherIconShowTime);
			}
		}
		if (searcher->icon != NULL) {
			searcher->icon->Off();
		}
		changed = 1;
	}
	if (searcher->gauge != NULL) {
		searcher->gauge->SetPos(&searcher->pos, NULL);
	}
	if (searcher->icon != NULL) {
		searcher->icon->SetPos(&searcher->pos, NULL);
	}
	return changed;
}
