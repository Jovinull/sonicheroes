#ifndef GAME_ENEMY_E_LINK_H
#define GAME_ENEMY_E_LINK_H
#include "types.h"
#include "game/setObj.h"
class TObject;
struct TObjectBase {
	char* ClassName;
	u16 Signal, Tag;
	TObject* Prev;
	TObject* Next;
	TObject* Parent;
	TObject* Child;
};
struct THeapCtrl {
	void* Malloc(u32);
	void Free(void*);
};
extern "C" THeapCtrl* lbl_8042C148;
class TObject : public TObjectBase
{
public:
	TObject(TObject*);
	virtual ~TObject();
	virtual void Exec();
	virtual void Disp();
	virtual void TDisp();
	virtual void PDisp();
	virtual void ImmAftSetRaster();
	virtual void Debug();
	virtual void Error(char*);
	virtual void Render();
	u16 ExecTime, DispTime, TDispTime, PDispTime, ImmAftSetRasterTime;
	// Natural two-byte tail padding to 0x28; no named filler needed.
	static void* operator new(unsigned long size) { return lbl_8042C148->Malloc(size); }
	static void operator delete(void* p) { lbl_8042C148->Free(p); }
};

enum ENEMY_ID { ENEMY_ID_UNKNOWN, ENEMY_ID_RCVCOMMAND, ENEMY_ID_END };
enum ENEMYKEY_KIND { ENEMYKEY_KIND_ID, ENEMYKEY_KIND_AREA, ENEMYKEY_KIND_END };
struct sEnemyCommand {
	u8 command, cid, dummy[2];
};
struct sEnemyCommandEx : public sEnemyCommand {
	RwV3d pos;
	f32 dist;
};
class TObjEnemy;
class ObjEnemyKey
{
public:
	ObjEnemyKey(TObjEnemy*, ENEMY_ID);
	s32 IsLastLink();
	ObjEnemyKey* SearchSameIDLinkTop(ENEMY_ID);
	s32 UnchainKey();
	s32 UnlinkKey();
	s32 UnloopKey();
	s32 ChainKey();
	s32 LinkKey(ObjEnemyKey*);
	s32 LoopKey();
	ENEMYKEY_KIND ekKind;
	ObjEnemyKey* pNext_Loop;
	ObjEnemyKey* pLast_Loop;
	ObjEnemyKey* pNext_Chain;
	ObjEnemyKey* pLast_Chain;
	ObjEnemyKey* pNext_Link;
	ObjEnemyKey* pLast_Link;
	TObjEnemy* pEnemy;
};
class TObjEnemyMan : public TObject
{
public:
	TObjEnemyMan(TObject*);
	virtual ~TObjEnemyMan();
	static void CreateEffect(u32, u32);
	static void TaskResume(u32);
	static void TaskSleep(u32);
	static void SendCommand(u32, sEnemyCommandEx*);
	static void SendCommand(u32, sEnemyCommand*);
	static void DestroyInstance();
	static void CreateInstance();
	ObjEnemyKey* pLoop;
};
extern char* CL_TObjEnemyMan;
// Original singleton spelling is not recovered.
extern "C" TObjEnemyMan* lbl_8042C578;
#endif
