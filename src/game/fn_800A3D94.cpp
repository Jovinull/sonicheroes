#include "types.h"

extern "C" {
void CreateInstance__14TEnemyScoreManFv();
void ParalyzeEnemy__14TEnemyScoreManFi(u32, s32);
extern u32 EnemyScoreMan__14TEnemyScoreMan;
}

class EnemyBase
{
public:
	u8 pad0[0x18];
};

class Enemy : public EnemyBase
{
public:
	virtual ~Enemy();
	virtual void v08();
	virtual void v0C();
	virtual void v10();
	virtual void v14();
	virtual void v18();
	virtual void v1C();
	virtual void v20();
	virtual void v24();
	virtual void v28();
	virtual void v2C();
	virtual void v30();
	virtual void v34();
	virtual void v38();
	virtual void v3C();
	virtual void v40();
	virtual void v44();
	virtual void v48();
	virtual void v4C();
	virtual void v50();
	virtual void v54();
	virtual void v58();
	virtual void v5C();
	virtual void v60();
	virtual void v64();
	virtual void v68();
	virtual void v6C();
	virtual void v70();
	virtual void v74();
	virtual void v78();
	virtual s32 v80();

	u8 pad1C[0x224 - 0x1C];
	s32 f224;
	u8 pad228[0x238 - 0x228];
	s32 f238;
};

extern "C" s32 fn_800A3D94(Enemy* enemy)
{
	if (enemy->f224 == 0) {
		return 0;
	}
	if (enemy->v80() != 0) {
		if (EnemyScoreMan__14TEnemyScoreMan == 0) {
			CreateInstance__14TEnemyScoreManFv();
		}
		ParalyzeEnemy__14TEnemyScoreManFi(EnemyScoreMan__14TEnemyScoreMan, enemy->f238);
		return 1;
	}
	return 0;
}
