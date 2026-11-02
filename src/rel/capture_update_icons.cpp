#include "types.h"

// The capture enemy's icon update (captureUpdateIcons here), the same in the
// seven stage modules that carry the capture: when its life changed since the
// last call, the life icon is shown again with the new life (kind 0x24 keeps
// it up for 0x5A frames) and the search icon is hidden. Both icons then
// follow the enemy, raised by the module's icon offset. Returns whether the
// life changed.

typedef struct RwV3d {
	f32 x, y, z;
} RwV3d;

class TEnemyIconMan
{
public:
	void On(f32 life, f32 maxLife, s32 time);
	void On(f32 life, f32 maxLife);
	void Off();
	void SetPos(const RwV3d* pos, const RwV3d* offset);
};

typedef struct Capture {
	u8 unk000[0x140];
	RwV3d pos; // 0x140
	u8 unk14C[0x50];
	s32 kind; // 0x19C
	u8 unk1A0[0x4];
	f32 life; // 0x1A4
	u8 unk1A8[0xA4];
	f32 shownLife; // 0x24C
	f32 maxLife;   // 0x250
	u8 unk254[0x9C];
	TEnemyIconMan* lifeIcon;   // 0x2F0
	TEnemyIconMan* searchIcon; // 0x2F4
} Capture;

extern "C" const RwV3d captureIconOffset;

extern "C" s32 captureUpdateIcons(Capture* object)
{
	s32 changed = 0;
	f32 life    = object->life;

	if (life != object->shownLife) {
		object->shownLife = life;
		if (object->lifeIcon != NULL) {
			if (object->kind == 0x24) {
				object->lifeIcon->On(life, object->maxLife, 0x5A);
			} else {
				object->lifeIcon->On(life, object->maxLife);
			}
		}
		if (object->searchIcon != NULL) {
			object->searchIcon->Off();
		}
		changed = 1;
	}
	if (object->lifeIcon != NULL) {
		object->lifeIcon->SetPos(&object->pos, &captureIconOffset);
	}
	if (object->searchIcon != NULL) {
		object->searchIcon->SetPos(&object->pos, &captureIconOffset);
	}
	return changed;
}
