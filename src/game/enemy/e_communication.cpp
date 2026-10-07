#include "game/enemy/e_communication.h"
#include "game/setObj.h"

// Accessed GameCube prefix of the external TObjSetGen object.
struct SetGenListView {
	u8 prefix[0x30];
	SETOBJ_PARAM* listTop[256];
	SETOBJ_PARAM* GetCommunicateList(u8 id) { return listTop[id]; }
};
extern "C" {
extern SetGenListView* lbl_8042C298;
void fn_800593D0(SetGenListView*, u8, SETOBJ_PARAM*);
void fn_800FDF70(u32, sEnemyCommandEx*);
void fn_800FE090(u32, sEnemyCommand*);
}

u16 e_uid_tbl[10] = { 0x1500, 0x1510, 0x1520, 0x1530, 0x1540, 0x1570, 0x1590, 0x15c0, 0x15d0, 0 };
u16 e_start_uid_tbl[13] = { 0x1500, 0x1510, 0x1520, 0x1530, 0x1540, 0x1570, 0x1590, 0x15c0, 0x15d0,
	0x63, 0x60, 0x65, 0 };

s32 nEnemyCommunication::DeleteStandByEnemy(u8 communicationId)
{
	SETOBJ_PARAM* plist = lbl_8042C298->GetCommunicateList(communicationId);
	if (!plist)
		return 1;
	while (plist) {
		for (s32 idx = 0; e_start_uid_tbl[idx]; idx++) {
			if (plist->setData.uniqueId == e_start_uid_tbl[idx]) {
				if (plist->setData.condition.Flag & 0x02000000) {
					fn_800593D0(lbl_8042C298, communicationId, plist);
					plist->setData.condition.Flag &= ~1;
				}
				break;
			}
		}
		plist = plist->next;
	}
	return 1;
}

s32 nEnemyCommunication::IsExistSummonEnemy(u8 communicationId)
{
	SETOBJ_PARAM* plist = lbl_8042C298->GetCommunicateList(communicationId);
	if (!plist)
		return 0;
	s32 num = 0;
	while (plist) {
		for (s32 idx = 0; e_start_uid_tbl[idx]; idx++) {
			if (plist->setData.uniqueId == e_start_uid_tbl[idx]) {
				if (plist->setData.condition.Flag & 0x02000000)
					num++;
				break;
			}
		}
		plist = plist->next;
	}
	return num > 0;
}

s32 nEnemyCommunication::IsAnnihilated(u8 communicationId)
{
	SETOBJ_PARAM* plist = lbl_8042C298->GetCommunicateList(communicationId);
	if (!plist)
		return 1;
	while (plist) {
		for (s32 idx = 0; e_uid_tbl[idx]; idx++) {
			if (plist->setData.uniqueId == e_uid_tbl[idx])
				return 0;
		}
		plist = plist->next;
	}
	return 1;
}
void sEnemyCommandEx::Send()
{
	fn_800FDF70(cid, this);
}
void sEnemyCommand::Send()
{
	fn_800FE090(cid, this);
}
