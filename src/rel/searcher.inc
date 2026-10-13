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

typedef struct Searcher {
	u8 unk000[0x140];
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
	u8 unk1A8[0x88];
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
	u8 unk29C[0xC];
	f32 shownHitPoint; // 0x2A8
	u8 unk2AC[0x4];
	TEnemyIconMan* gauge; // 0x2B0
	TEnemyIconMan* icon;  // 0x2B4
	u8 unk2B8[0xC];
	s32 turning; // 0x2C4
	u8 unk2C8[0x4];
	RwV3d shadowPos;    // 0x2CC, -1000000 high: no ground
	RwV3d shadowNormal; // 0x2D8
	u8 unk2E4[0x34];
	s32 state; // 0x318, 2: no shadow
	s32 kind;  // 0x31C, 6: search light
} Searcher;
