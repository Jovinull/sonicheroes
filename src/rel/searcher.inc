// TObjEnemySearcher (the PS2 build's name), the floating searcher enemy with a
// gadget (search light, machine gun, shot, bomb, laser or needle), as far as
// the C units for its members use it.

typedef struct RwV3d {
	f32 x, y, z;
} RwV3d;

typedef struct sAngle {
	s32 x, y, z;
} sAngle;

typedef struct RpClump RpClump;

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
	virtual s32 ReqGadgetMode(s32 mode);
	virtual void Cancel();
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
} SearcherSet;

typedef struct Searcher {
	u8 unk000[0xB0];
	SearcherSet* set; // 0xB0
	u8 unk0B4[0x34];
	RpClump* clump; // 0xE8
	u8 unk0EC[0x54];
	RwV3d pos;  // 0x140
	sAngle ang; // 0x14C
	u8 unk158[0x1C];
	s32 aimAngY; // 0x174
	u8 unk178[0x8];
	s32 turnSpeed; // 0x180
	u8 unk184[0x18];
	s32 mode; // 0x19C
	u8 unk1A0[0x4];
	f32 hitPoint; // 0x1A4
	u8 unk1A8[0x18];
	RwV3d home;   // 0x1C0
	RwV3d aimPos; // 0x1CC
	u8 unk1D8[0x58];
	s32 breaker; // 0x230
	u8 unk234[0x10];
	RpClump* clumps[4]; // 0x244, lit body, dark body, lit and dark parts
	s32 lit;            // 0x254
	u8 unk258[0x10];
	TEnemyGadget* gadget; // 0x268
	u8 unk26C[0x20];
	f32 leanX; // 0x28C
	f32 leanZ;      // 0x290
	f32 shadowFade; // 0x294, how fast the shadow fades with height
	s32 shadowOn;   // 0x298
	s32 mgunAttackAngle; // 0x29C, 0x3000 down or 0xD000 up
	u8 unk2A0[0x4];
	f32 aimDistance; // 0x2A4
	f32 shownHitPoint; // 0x2A8
	u8 unk2AC[0x4];
	TEnemyIconMan* gauge; // 0x2B0
	TEnemyIconMan* icon;  // 0x2B4
	u8 unk2B8[0xC];
	s32 turning; // 0x2C4
	u8 unk2C8[0x4];
	RwV3d shadowPos;    // 0x2CC, -1000000 high: no ground
	RwV3d shadowNormal; // 0x2D8
	u8 unk2E4[0x2C];
	RpClump* partsClump; // 0x310
	s32 plainTexture;    // 0x314
	s32 state;           // 0x318, 2: no shadow
	s32 kind;  // 0x31C, 6: search light
} Searcher;

// the searcher as the C++ class its virtual calls need
static inline TObjEnemy* searcherEnemy(Searcher* searcher)
{
	return (TObjEnemy*)searcher;
}
