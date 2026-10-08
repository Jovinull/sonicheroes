#ifndef GAME_ENEMY_E_COMMUNICATION_H
#define GAME_ENEMY_E_COMMUNICATION_H
#include "game/pathctrl.h"

struct sEnemyCommand {
	u8 command, cid, dummy[2];
	void Send();
};
struct sEnemyCommandEx : public sEnemyCommand {
	RwV3d pos;
	f32 dist;
	void Send();
};
namespace nEnemyCommunication
{
s32 DeleteStandByEnemy(u8 communicationId);
s32 IsExistSummonEnemy(u8 communicationId);
s32 IsAnnihilated(u8 communicationId);
}
extern u16 e_uid_tbl[10];
extern u16 e_start_uid_tbl[13];
#endif
