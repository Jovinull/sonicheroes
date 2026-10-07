#include "game/enemy/e_link.h"
// Local view of fields and virtual slots accessed in this TU. The opaque ranges
// stand for the other enemy bases/members, rather than an owned enemy definition.
class TObjEnemy : public TObject
{
public:
	virtual void UnknownSlot2C();
	virtual void UnknownSlot30();
	virtual void UnknownSlot34();
	virtual void UnknownSlot38();
	virtual void UnknownSlot3C();
	virtual void UnknownSlot40();
	virtual void UnknownSlot44();
	virtual void UnknownSlot48();
	virtual void UnknownSlot4C();
	virtual void UnknownSlot50();
	virtual void UnknownSlot54();
	virtual void UnknownSlot58();
	virtual void UnknownSlot5C();
	virtual void UnknownSlot60();
	virtual void UnknownSlot64();
	virtual void UnknownSlot68();
	virtual void UnknownSlot6C();
	virtual void UnknownSlot70();
	virtual void UnknownSlot74();
	virtual void UnknownSlot78();
	virtual void UnknownSlot7C();
	virtual void UnknownSlot80();
	virtual void UnknownSlot84();
	virtual void UnknownSlot88();
	virtual void UnknownSlot8C();
	virtual void UnknownSlot90();
	virtual void RcvCommand(sEnemyCommand*);
	virtual void UnknownSlot98();
	virtual void UnknownSlot9C();
	virtual void UnknownSlotA0();
	u8 unknown28[0x88];
	SETOBJ_PARAM* ObjParam;
	u8 unknownB4[0x13c - 0xb4];
	ENEMY_ID EnemyID;
	RwV3d pos;
	u8 unknown14C[0x228 - 0x14c];
	// GC moves this tail field four bytes after the PS2 metadata offset.
	ObjEnemyKey* pKey;
};
char* CL_TObjEnemyMan = "TObjEnemyMan";
extern "C" {
TObjEnemyMan* lbl_8042C578;
extern TObject* lbl_8042C10C;
}

s32 ObjEnemyKey::IsLastLink()
{
	if (pNext_Link) {
		if (pNext_Link->pLast_Loop)
			return 1;
		else
			return 0;
	}
	return 0;
}
ObjEnemyKey* ObjEnemyKey::SearchSameIDLinkTop(ENEMY_ID eid)
{
	ObjEnemyKey* pListTop = this;
	while (pListTop) {
		if (pListTop->ekKind == ENEMYKEY_KIND_ID && pListTop->pEnemy->EnemyID == eid)
			return pListTop;
		pListTop = pListTop->pNext_Link;
	}
	return 0;
}
s32 ObjEnemyKey::UnchainKey()
{
	if (!pEnemy)
		return 0;
	if (pEnemy->pKey == this) {
		if (pEnemy->pKey->pLast_Chain == this)
			pEnemy->pKey = 0;
		else {
			pEnemy->pKey             = pNext_Chain;
			pNext_Chain->pLast_Chain = pLast_Chain;
			pLast_Chain->pNext_Chain = pNext_Chain;
		}
	} else {
		pNext_Chain->pLast_Chain = pLast_Chain;
		pLast_Chain->pNext_Chain = pNext_Chain;
	}
	pLast_Chain = 0;
	pNext_Chain = 0;
	return 1;
}
s32 ObjEnemyKey::UnloopKey()
{
	if (!lbl_8042C578)
		return 0;
	if (lbl_8042C578->pLoop == this) {
		if (pNext_Loop == this)
			lbl_8042C578->pLoop = 0;
		else {
			lbl_8042C578->pLoop    = pNext_Loop;
			pNext_Loop->pLast_Loop = pLast_Loop;
			pLast_Loop->pNext_Loop = pNext_Loop;
		}
	} else {
		pNext_Loop->pLast_Loop = pLast_Loop;
		pLast_Loop->pNext_Loop = pNext_Loop;
	}
	pNext_Loop = 0;
	pLast_Loop = 0;
	return 1;
}
s32 ObjEnemyKey::UnlinkKey()
{
	if (!UnchainKey())
		return 0;
	if (pNext_Loop) {
		if (pNext_Link == this)
			UnloopKey();
		else {
			pLast_Link->pNext_Link = pNext_Link;
			pNext_Link->pLast_Link = pLast_Link;
			pNext_Link->pNext_Loop = pNext_Loop;
			pNext_Link->pLast_Loop = pLast_Loop;
			pNext_Loop->pLast_Loop = pNext_Link;
			pLast_Loop->pNext_Loop = pNext_Link;
			if (lbl_8042C578->pLoop == this)
				lbl_8042C578->pLoop = pNext_Link;
		}
	} else {
		pLast_Link->pNext_Link = pNext_Link;
		pNext_Link->pLast_Link = pLast_Link;
	}
	pNext_Link = 0;
	pLast_Link = 0;
	pNext_Loop = 0;
	pLast_Loop = 0;
	return 1;
}
s32 ObjEnemyKey::ChainKey()
{
	if (!pEnemy)
		return 0;
	ObjEnemyKey* pTop = pEnemy->pKey;
	if (pTop) {
		pTop->pLast_Chain->pNext_Chain = this;
		pLast_Chain                    = pTop->pLast_Chain;
		pNext_Chain                    = pTop;
		pTop->pLast_Chain              = this;
	} else {
		pNext_Chain  = this;
		pLast_Chain  = this;
		pEnemy->pKey = this;
	}
	return 1;
}
s32 ObjEnemyKey::LoopKey()
{
	if (!lbl_8042C578)
		return 0;
	if (!lbl_8042C578->pLoop) {
		lbl_8042C578->pLoop = this;
		pNext_Loop          = this;
		pLast_Loop          = this;
		pNext_Link          = this;
		pLast_Link          = this;
	} else {
		lbl_8042C578->pLoop->pLast_Loop->pNext_Loop = this;
		pLast_Loop                                  = lbl_8042C578->pLoop->pLast_Loop;
		pNext_Loop                                  = lbl_8042C578->pLoop;
		lbl_8042C578->pLoop->pLast_Loop             = this;
		pNext_Link                                  = this;
		pLast_Link                                  = this;
	}
	return 1;
}
s32 ObjEnemyKey::LinkKey(ObjEnemyKey* pTop)
{
	pLast_Loop                   = 0;
	pNext_Loop                   = 0;
	pTop->pLast_Link->pNext_Link = this;
	pLast_Link                   = pTop->pLast_Link;
	pNext_Link                   = pTop;
	pTop->pLast_Link             = this;
	return 1;
}
ObjEnemyKey::ObjEnemyKey(TObjEnemy* pTOE, ENEMY_ID eid)
{
	pNext_Loop        = 0;
	pLast_Loop        = 0;
	pNext_Chain       = 0;
	pLast_Chain       = 0;
	pNext_Link        = 0;
	pLast_Link        = 0;
	ObjEnemyKey* pTop = 0;
	pEnemy            = pTOE;
	ekKind            = ENEMYKEY_KIND_ID;
	if (lbl_8042C578->pLoop)
		pTop = lbl_8042C578->pLoop->SearchSameIDLinkTop(eid);
	if (!pTop) {
		if (!LoopKey())
			return;
	} else
		LinkKey(pTop);
	ChainKey();
}
TObjEnemyMan::~TObjEnemyMan()
{
	while (pLoop)
		pLoop->UnlinkKey();
}
TObjEnemyMan::TObjEnemyMan(TObject* ptp)
    : TObject(ptp)
{
	ClassName = CL_TObjEnemyMan;
	DispTime  = sizeof(TObjEnemyMan);
	pLoop     = 0;
}
// Address names retained: GC establishes pointer result / f32 result respectively.
extern "C" TObject* fn_8006298C(u32, RwV3d*, sAngle*);
extern "C" f32 fn_800D71DC(RwV3d*, RwV3d*);

void TObjEnemyMan::CreateEffect(u32 communicationId, u32 effect)
{
	sAngle ang = { 0, 0, 0 };
	if (!lbl_8042C578->pLoop)
		return;
	ObjEnemyKey* pLinkCurrent = lbl_8042C578->pLoop->SearchSameIDLinkTop(ENEMY_ID_RCVCOMMAND);
	for (;;) {
		if (!pLinkCurrent)
			break;
		TObjEnemy* pEnemyCurrent = pLinkCurrent->pEnemy;
		if (pEnemyCurrent) {
			SETOBJ_PARAM* pSetObjParam = pEnemyCurrent->ObjParam;
			if (pSetObjParam->setData.communicateId == communicationId
			    && (pSetObjParam->setData.originalCondition.Flag & 0x02000000)) {
				fn_8006298C(effect, &pEnemyCurrent->pos, &ang);
			}
		}
		if (pLinkCurrent->IsLastLink() == 1)
			break;
		pLinkCurrent = pLinkCurrent->pNext_Link;
	}
}

void TObjEnemyMan::TaskResume(u32 communicationId)
{
	if (!lbl_8042C578->pLoop)
		return;
	ObjEnemyKey* pLinkCurrent = lbl_8042C578->pLoop->SearchSameIDLinkTop(ENEMY_ID_RCVCOMMAND);
	for (;;) {
		if (!pLinkCurrent)
			break;
		TObjEnemy* pEnemyCurrent = pLinkCurrent->pEnemy;
		if (pEnemyCurrent) {
			SETOBJ_PARAM* pSetObjParam = pEnemyCurrent->ObjParam;
			if (pSetObjParam->setData.communicateId == communicationId
			    && (pSetObjParam->setData.originalCondition.Flag & 0x02000000)) {
				pEnemyCurrent->Signal &= ~4;
				pEnemyCurrent->Signal &= ~0x10;
				pEnemyCurrent->UnknownSlotA0();
			}
		}
		if (pLinkCurrent->IsLastLink() == 1)
			break;
		pLinkCurrent = pLinkCurrent->pNext_Link;
	}
}

void TObjEnemyMan::TaskSleep(u32 communicationId)
{
	if (!lbl_8042C578->pLoop)
		return;
	ObjEnemyKey* pLinkCurrent = lbl_8042C578->pLoop->SearchSameIDLinkTop(ENEMY_ID_RCVCOMMAND);
	for (;;) {
		if (!pLinkCurrent)
			break;
		TObjEnemy* pEnemyCurrent = pLinkCurrent->pEnemy;
		if (pEnemyCurrent) {
			SETOBJ_PARAM* pSetObjParam = pEnemyCurrent->ObjParam;
			if (pSetObjParam->setData.communicateId == communicationId
			    && (pSetObjParam->setData.originalCondition.Flag & 0x02000000)) {
				pEnemyCurrent->Signal |= 4;
				pEnemyCurrent->Signal |= 0x10;
				pEnemyCurrent->UnknownSlot9C();
			}
		}
		if (pLinkCurrent->IsLastLink() == 1)
			break;
		pLinkCurrent = pLinkCurrent->pNext_Link;
	}
}

void TObjEnemyMan::SendCommand(u32 communicationId, sEnemyCommandEx* com)
{
	if (!lbl_8042C578->pLoop)
		return;
	ObjEnemyKey* pLinkCurrent = lbl_8042C578->pLoop->SearchSameIDLinkTop(ENEMY_ID_RCVCOMMAND);
	for (;;) {
		if (!pLinkCurrent)
			break;
		TObjEnemy* pEnemyCurrent = pLinkCurrent->pEnemy;
		if (pEnemyCurrent) {
			if (pEnemyCurrent->ObjParam->setData.communicateId == communicationId) {
				// Unordered comparisons also dispatch, as in the GC bge guard.
				if (fn_800D71DC(&pEnemyCurrent->pos, &com->pos) < com->dist * com->dist)
					pEnemyCurrent->RcvCommand(com);
			}
		}
		if (pLinkCurrent->IsLastLink() == 1)
			break;
		pLinkCurrent = pLinkCurrent->pNext_Link;
	}
}

void TObjEnemyMan::SendCommand(u32 communicationId, sEnemyCommand* com)
{
	if (!lbl_8042C578->pLoop)
		return;
	ObjEnemyKey* pLinkCurrent = lbl_8042C578->pLoop->SearchSameIDLinkTop(ENEMY_ID_RCVCOMMAND);
	for (;;) {
		if (!pLinkCurrent)
			break;
		TObjEnemy* pEnemyCurrent = pLinkCurrent->pEnemy;
		if (pEnemyCurrent) {
			if (pEnemyCurrent->ObjParam->setData.communicateId == communicationId)
				pEnemyCurrent->RcvCommand(com);
		}
		if (pLinkCurrent->IsLastLink() == 1)
			break;
		pLinkCurrent = pLinkCurrent->pNext_Link;
	}
}

void TObjEnemyMan::DestroyInstance()
{
	if (lbl_8042C578) {
		delete lbl_8042C578;
		lbl_8042C578 = 0;
	}
}
void TObjEnemyMan::CreateInstance()
{
	if (!lbl_8042C578)
		lbl_8042C578 = new TObjEnemyMan(lbl_8042C10C);
}
