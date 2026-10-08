#ifndef GAME_ENEMY_E_SHOCKWAVE_H
#define GAME_ENEMY_E_SHOCKWAVE_H
#include "types.h"
#include "game/pathctrl.h"
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

struct RpClump;
struct RwFrame;
struct sShockWave {
	RwV3d pos;
	sShockWave();
};
struct sShockWaveModelParam {
	RwV3d scale;
	f32 alpha, rotate;
};
class TEnemyShockWave : public TObject
{
public:
	void UpdateShockWaveModelParam();
	void InitShockWaveModelParam();
	virtual void TDisp();
	virtual void Exec();
	void DestroyClump();
	void CloneClump();
	void ResetVariable();
	virtual ~TEnemyShockWave();
	TEnemyShockWave(TObject*, const sShockWave*);
	static void Finalize();
	static void Initialize();
	static void Create(const sShockWave*);
	sShockWave mParam;
	RpClump* mpClump;
	s32 mTimer;
	sShockWaveModelParam ShockWaveModelParam[4];
	RwFrame* mpFrame[4];
};
#endif
