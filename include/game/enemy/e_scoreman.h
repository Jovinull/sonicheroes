#ifndef GAME_ENEMY_E_SCOREMAN_H
#define GAME_ENEMY_E_SCOREMAN_H
#include "types.h"
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

class PARAM_SCORE
{
};
class ScoreSavedStateBase
{
};
struct sBitFlag {
	u32 Flag;
};
// Provisional GC model: PARAM_SCORE is corroborated at 0x28. The adjustment
// to 0x29 is represented by a second empty base; its original type and whether
// it was a base or member are unverified. The first aligned counter is at 0x2c.
// counter58 is an additional GC field absent from the PS2 class metadata.
class TEnemyScoreMan : public TObject, public PARAM_SCORE, public ScoreSavedStateBase
{
public:
	static void AddTechnicPointForParalyzeEnemy(s32 playernumber, s32 num);
	static void AddTechnicPointForTornadoEnemy(s32 teamnumber, s32 num);
	static void AddTechnicPointForDestroyEnemy(s32 playernumber, s32 num);
	void SaveDestroyEnemyTotalGoal();
	void SaveDestroyEnemyTotal();
	void ParalyzeEnemy(s32 playernumber);
	void TornadoEnemy(s32 teamnumber);
	void DestroyEnemy(s32 playernumber);
	void AddScore(s32 playernumber, s32 score);
	virtual void Exec();
	void ResetVariable();
	virtual ~TEnemyScoreMan();
	TEnemyScoreMan(TObject*);
	static void DeleteInstance();
	static void CreateInstance();
	static TEnemyScoreMan* EnemyScoreMan;
	s32 mDestroyEnemyNum, mTornadoEnemyNum, mParalyzeEnemyNum;
	s32 mPlayerNumForDestroy, mTeamNumForTornado, mPlayerNumForParalyze;
	s32 mDestroyEnemyTmr, mTornadoEnemyTmr;
	sBitFlag mScoreManFlag;
	s32 mDestroyEnemyTotal, mSaveDestroyEnemyTotal;
	s32 counter58; // GC-only field; original spelling is unknown.
};
extern "C" void fn_8011C0E8(TEnemyScoreMan*);
extern "C" void fn_8011C13C(TEnemyScoreMan*);
#endif
