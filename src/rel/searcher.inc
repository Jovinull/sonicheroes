// TObjEnemySearcher (the PS2 build's name), the floating searcher enemy with a
// gadget (search light, machine gun, shot, bomb, laser or needle), as far as
// the C units for its members use it.

typedef struct RwV3d {
	f32 x, y, z;
} RwV3d;

typedef struct sAngle {
	s32 x, y, z;
} sAngle;

typedef struct RwFrame RwFrame;

typedef struct RpClump {
	u8 unk00[0x4];
	RwFrame* frame; // 0x04
} RpClump;

struct THeapCtrl {
	void* Malloc(u32 size);
};

extern "C" THeapCtrl* lbl_8042C148;

struct TEnemyGadgetBase {
	char* name; // 0x00
	u16 flags;  // 0x04, 0x10: asleep
	u8 unk06[0x12];
};

// TEnemyGadget's vtable as in game/enemy/e_gadget.h up to slot 0x40, the PS2
// build's Cancel (DelClump there, inline, which would put a copy in each unit
// that calls it; its object check pins that name)
class TEnemyGadget : public TEnemyGadgetBase
{
public:
	enum eGadgetMode {
		E_GM_NOACTION,
		E_GM_STANDBY,
		E_GM_PREATTACK,
		E_GM_ATTACK,
		E_GM_POSTATTACK,
	};

	virtual ~TEnemyGadget();
	virtual void Exec();
	virtual void Disp();
	virtual void TDisp();
	virtual void PDisp();
	virtual void ImmAftSetRaster();
	virtual void Debug();
	virtual void Error(char* message);
	virtual void Render();
	virtual void SetClump(RpClump* clump);
	virtual void Update();
	virtual void DispOpaq();
	virtual void DispTrans();
	virtual s32 ReqGadgetMode(eGadgetMode mode);
	virtual void Cancel();

	u8 unk1C[0xC];
	void* pOwner;      // 0x28
	RpClump* pClump;   // 0x2C
	eGadgetMode gmode; // 0x30
	s32 IsKilled;      // 0x34

	static void* operator new(unsigned long size) { return lbl_8042C148->Malloc(size); }
	s32 CheckCameraFrustum(const RwV3d* pos, f32 radius);
};

// TObjEnemy's virtuals up to GetCurrentLightNum (slot 0x90), declared as
// rel/e_flyer_stage11.cpp has them so a virtual call takes the retail slot
// (TObjSetObj's part of the vtable comes before TObjEnemy's own slots); only
// declared, so nothing of the class is emitted here
struct SETDATA_PARAM;
enum ENEMY_MD { ENEMY_MD_0 };

struct TObjectHdr {
	u8 pad00[0x18];
};

class TObject : public TObjectHdr
{
public:
	virtual ~TObject();
	virtual void Exec();
	virtual void Disp();
	virtual void TDisp();
	virtual void PDisp();
	virtual void ImmAftSetRaster();
	virtual void Debug();
	virtual void Error(char*);
	virtual void Render();

	u8 pad1C[0x94];
};

struct SetObjHdr {
	SETDATA_PARAM* frame;
};

class TObjSetObj : public SetObjHdr
{
public:
	virtual void EditOnChange(SETDATA_PARAM*);
};

class TObjEnemy : public TObject, public TObjSetObj
{
public:
	enum eCtrlSMode { CTRL_SMODE_0 };

	virtual ~TObjEnemy();
	virtual void CheckDamage2();
	virtual void DestroyMyself();
	virtual void Explosion();
	virtual void InitMode(ENEMY_MD);
	virtual void ExecMode(ENEMY_MD);
	virtual void ExitMode(ENEMY_MD);
	virtual void CtrlMode(ENEMY_MD, eCtrlSMode);
	virtual void Update();
	virtual void UpdateOnEdit();
	virtual void DispOpaq();
	virtual void DispTrans();
	virtual void DispShadow();
	virtual void DispOpaqOnEdit();
	virtual void Virtual33D94();
	virtual void KillMySelf();
	virtual s32 CheckCameraFrustumTest(const RwV3d*, f32);
	virtual s32 CheckCameraFrustumTestForShadow(const RwV3d*, f32);
	virtual void AddScore();
	virtual s32 CanCheckTechnicPointForThunderShoot();
	virtual s32 IsSleep();
	virtual void AddItemBox(RwV3d*);
	virtual RwV3d* Virtual33D98();
	virtual s32 GetCurrentLightNum();
};

class TEnemyIconMan
{
public:
	void Off();
	void On(f32 value, f32 time, s32 extra);
	void On(f32 value, f32 time);
	void SetPos(const RwV3d* pos, const RwV3d* offset);
};

class TEnemyScoreMan
{
public:
	static void CreateInstance();
	static TEnemyScoreMan* EnemyScoreMan;
	void AddScore(s32 playernumber, s32 score);
};

typedef struct SearcherSet {
	RwV3d pos; // 0x00
	u8 unk0C[0x4];
	s32 angle; // 0x10
	u8 unk14[0x16];
	u8 group; // 0x2A, the summoning group
} SearcherSet;

typedef struct SearcherColli {
	u8 unk00[0x34];
	u32 flags; // 0x34, 0x10: off
} SearcherColli;

// ENEMYMTNMAN (the PS2 build's name), the enemy's motion manager, as far as
// these units use it
class ENEMYMTNMAN
{
public:
	ENEMYMTNMAN();
	~ENEMYMTNMAN();

	u8 unk00[0x1C];
	s32 active; // 0x1C
	u8 unk20[0xC];
	struct ENEMY_MOTION* motions; // 0x2C
	RpClump* clump;               // 0x30
	u8 unk34[0x18];
};

typedef struct Searcher {
	char* name; // 0x00
	u16 signal; // 0x04, 1: kill
	u8 unk06[0x32];
	SearcherColli* colli; // 0x38
	u8 unk3C[0x74];
	SearcherSet* set; // 0xB0
	u8 unk0B4[0x34];
	RpClump* clump; // 0xE8
	u8 unk0EC[0x1A];
	u16 colliFlags; // 0x106, 2: on the ground, 4: hit a wall
	u8 unk108[0x38];
	RwV3d pos;  // 0x140
	sAngle ang; // 0x14C
	u8 unk158[0x4];
	f32 speedY; // 0x15C
	u8 unk160[0x14];
	s32 aimAngY; // 0x174
	u8 unk178[0x8];
	s32 turnSpeed; // 0x180
	u8 unk184[0x18];
	s32 mode; // 0x19C
	u8 unk1A0[0x4];
	f32 hitPoint; // 0x1A4
	f32 gravity;  // 0x1A8
	u8 unk1AC[0x14];
	RwV3d home;   // 0x1C0
	RwV3d aimPos; // 0x1CC
	u8 unk1D8[0x58];
	s32 breaker; // 0x230
	u8 unk234[0xC];
	RpClump* bodyClump;  // 0x240
	RpClump* clumps[4];  // 0x244, lit body, dark body, lit and dark parts
	s32 lit;             // 0x254
	s32 field258;        // 0x258
	ENEMYMTNMAN* motion; // 0x25C
	s32 field260;        // 0x260
	u8 unk264[0x4];
	TEnemyGadget* gadget; // 0x268
	s32 bobAngle;         // 0x26C
	RwV3d spin;           // 0x270
	f32 spinSpeed;        // 0x27C
	s32 walking;          // 0x280
	u8 unk284[0x8];
	f32 leanX;            // 0x28C
	f32 leanZ;            // 0x290
	f32 shadowFade;       // 0x294, how fast the shadow fades with height
	s32 shadowOn;         // 0x298
	s32 mgunAttackAngle;  // 0x29C, 0x3000 down or 0xD000 up
	s32 field2A0;         // 0x2A0
	f32 aimDistance;      // 0x2A4
	f32 shownHitPoint;    // 0x2A8
	f32 maxHitPoint;      // 0x2AC
	TEnemyIconMan* gauge; // 0x2B0
	TEnemyIconMan* icon;  // 0x2B4
	u8 unk2B8[0xC];
	s32 turning;        // 0x2C4
	s32 field2C8;       // 0x2C8
	RwV3d shadowPos;    // 0x2CC, -1000000 high: no ground
	RwV3d shadowNormal; // 0x2D8
	s32 request;        // 0x2E4, the enemy mode it asks the strategy for
	u8 unk2E8[0x14];
	RwV3d savedAim;      // 0x2FC, the walk's aim while it is away
	RwFrame* jetFrame;   // 0x308
	s32 field30C;        // 0x30C
	RpClump* partsClump; // 0x310
	s32 plainTexture;    // 0x314
	s32 state;           // 0x318, 2: no shadow
	s32 kind;            // 0x31C, 6: search light
	s32 moveType;        // 0x320
	f32 walkSpeed;       // 0x324
	f32 shotSpeed;       // 0x328
	s32 readyWait;       // 0x32C
	s32 attackWait;      // 0x330
	u8 unk334[0xC];
	void* field340; // 0x340
	void* field344; // 0x344
} Searcher;

// the searcher as the C++ class its virtual calls need
static inline TObjEnemy* searcherEnemy(Searcher* searcher)
{
	return (TObjEnemy*)searcher;
}

extern "C" f32 fn_800D7B00(s32 angle);
extern "C" const f32 searcherBobHeight;

// TObjEnemySearcher::CtrlWaitPos (the PS2 build's name): bobs up and down
// around the home height while it moves. The enemy modes inline it;
// rel/searcher_ctrl.cpp has the out-of-line copy (SEARCHER_CTRL_WAIT_POS_INLINE
// empty).
#ifndef SEARCHER_CTRL_WAIT_POS_INLINE
#define SEARCHER_CTRL_WAIT_POS_INLINE inline
#endif

extern "C" SEARCHER_CTRL_WAIT_POS_INLINE void CtrlWaitPos__17TObjEnemySearcherFv(Searcher* searcher)
{
	if (searcher->turning) {
		searcher->bobAngle += 0x100;
		searcher->pos.y = searcher->home.y + searcherBobHeight * fn_800D7B00(searcher->bobAngle);
	}
}
