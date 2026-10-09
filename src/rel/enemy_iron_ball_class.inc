// TObjEnemyIronBall, shared by rel/enemy_iron_ball_create.cpp and the units
// that define its out-of-line members. The constructor stays inline in the
// class: the factory inlines it.

#include "game/effect/eff_bomb.h"

extern "C" const f32 enemyIronBallZero[1];

struct sEnemyIronBall {
	RwV3d pos;  // 0x00
	RwV3d vec;  // 0x0C
	f32 unk18;  // 0x18
	sAngle ang; // 0x1C
	s32 time;   // 0x28
	s32 unk2C;  // 0x2C
	s32 unk30;  // 0x30

	sEnemyIronBall()
	{
		pos.x = pos.y = pos.z = enemyIronBallZero[0];
		vec.x = vec.y = vec.z = enemyIronBallZero[0];
		ang.x = ang.y = ang.z = 0;
		time                  = 300;
		unk2C                 = 1;
		unk30                 = 8;
	}
};

extern "C" char* CL_TObjEnemyIronBall;
extern "C" CCL_INFO enemyIronBallCclInfo;
extern "C" TObject* lbl_8042C10C;

class TObjEnemyIronBall : public TObject, public C_COLLI
{
public:
	sEnemyIronBall data; // 0xB0
	s32 unkE4;           // 0xE4
	RwV3d unkE8;         // 0xE8

	TObjEnemyIronBall(TObject* parent, sEnemyIronBall* param)
	    : TObject(parent)
	{
		ClassName = CL_TObjEnemyIronBall;
		DispTime  = 0xF4;
		unkE4     = 0;
		data      = *param;
		unkE8.x = unkE8.y = unkE8.z = enemyIronBallZero[0];
		Init(&enemyIronBallCclInfo, 1, 3);
		C_COLLI::pos = data.pos;
		flag &= ~0x40;
	}
	virtual void Exec();
	virtual ~TObjEnemyIronBall();

	static void Create(sEnemyIronBall* param);
};
