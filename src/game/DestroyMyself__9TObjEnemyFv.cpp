// TObjEnemy::DestroyMyself (symbol name from the retail map): finishes a destroyed enemy. It
// flags its set object (0x01000000 on the stages listed in lbl_80239F34, 0x10000000 | 0x200 in
// game modes 4/8 on stages 4/5; HYPOTHESIS for the roles), adds the score, ends the set object
// and explodes. When the destroyer (+0x230, a player index or -1) is known, it drops a power
// core for that player's team and adds the item box, and credits the enemy to the score manager.
#include "game/enemy/e_obj_enemy.h"

struct GameState800A2F88 {
	u8 pad0[0x2C];
	s32 unknown2C; // 0x2C (see fn_800A2D50)
};

struct GameMode800A2F88 {
	u8 pad0[0x24];
	s8 mode; // 0x24
};

struct Player800A2F88 {
	u8 pad0[0x9BC];
	s8 team; // 0x9BC
};

struct Team800A2F88 {
	u8 pad0[0x3A];
	s8 leader; // 0x3A
	u8 pad3B[0x110 - 0x3B];
	s8 kinds[3]; // 0x110 (HYPOTHESIS: the character kind of each team slot)
};

class TEnemyPowerCoreMan
{
public:
	static TEnemyPowerCoreMan* GetInstance();
	void Entry(const RwV3d*, s32);
};

class TEnemyScoreMan
{
public:
	static TEnemyScoreMan* EnemyScoreMan;
	static void CreateInstance();
	void DestroyEnemy(s32 playernumber);
	static TEnemyScoreMan* GetInstance()
	{
		if (!EnemyScoreMan) {
			CreateInstance();
		}
		return EnemyScoreMan;
	}
};

extern "C" {
extern GameState800A2F88 lbl_8029C310;
extern const s32 lbl_80239F34[];
extern GameMode800A2F88* lbl_8042C180;
extern Player800A2F88* lbl_802AD070[];
extern Team800A2F88* lbl_80303DC8[];
void fn_8011C0E8(TEnemyScoreMan*);
}

// Same helper as fn_800A2D50.
static inline s32 IsInList(const s32* list, s32 id)
{
	for (; *list != -1; list++) {
		if (id == *list) {
			return 1;
		}
	}
	return 0;
}

void TObjEnemy::DestroyMyself()
{
	if (IsInList(lbl_80239F34, lbl_8029C310.unknown2C)) {
		ObjParam->setData.condition.Flag |= 0x01000000;
	}
	AddScore();
	if (lbl_8042C180->mode == 4 || lbl_8042C180->mode == 8) {
		if (lbl_8029C310.unknown2C == 4 || lbl_8029C310.unknown2C == 5) {
			ObjParam->setData.condition.Flag |= 0x10000000;
			ObjParam->setData.condition.Flag |= 0x200;
		}
	}
	SetEnd();
	Explosion();
	if (destroyer != -1) {
		Player800A2F88* player = lbl_802AD070[destroyer];

		if (player) {
			Team800A2F88* team = lbl_80303DC8[player->team];

			if (team) {
				TEnemyPowerCoreMan::GetInstance()->Entry(&position, team->kinds[team->leader]);
				AddItemBox(&position);
			}
		}
	}
	if (destroyer != -1) {
		TEnemyScoreMan::GetInstance()->DestroyEnemy(destroyer);
	}
	fn_8011C0E8(TEnemyScoreMan::GetInstance());
}
