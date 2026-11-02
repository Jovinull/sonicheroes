// TEnemyPowerCore (the PS2 build's name), the bonus stages' power core
// (31D-33D), as C++: a TObject that is also its own collision (C_COLLI at
// 0x28) with its spawn parameters (sEnemyPowerCore) at 0xB0. The constructor
// copies the parameters, clones the two loaded power core models, sets the
// collision up and finds the ground below. A unit that emits the constructor
// defines POWER_CORE_CTOR empty first; TEnemyPowerCore::Create inlines it.

#ifndef POWER_CORE_CTOR
#define POWER_CORE_CTOR inline
#endif

typedef struct RwV3d {
	f32 x, y, z;
} RwV3d;

struct RpClump;
struct sAngle;
struct CCL_INFO;

struct TObjectBase {
	const char* name; // 0x00
	u16 signal;       // 0x04
	u8 unk06[0x12];
};

extern "C" void* lbl_8042C148;
extern "C" void* Malloc__9THeapCtrlFUi(void* heap, u32 size);

class TObject : public TObjectBase
{
public:
	TObject(TObject* parent);
	virtual ~TObject();

	static void* operator new(unsigned long size)
	{
		return Malloc__9THeapCtrlFUi(lbl_8042C148, size);
	}

	u8 unk1C[0x2];
	u16 size; // 0x1E
	u8 unk20[0x8];
}; // 0x28

typedef struct sAngleView {
	s32 x, y, z;
} sAngleView;

class C_COLLI
{
public:
	C_COLLI();
	void Init(CCL_INFO* info, s32 count, u8 kind);
	void Entry();

	u8 unk00[0x8];
	u16 flags; // 0x08
	u8 unk0A[0x56];
	RwV3d pos;      // 0x60
	sAngleView ang; // 0x6C
	u8 unk78[0x4];
	RwV3d prev; // 0x7C
}; // 0x88

extern "C" const f32 powerCoreManZero;
extern "C" const f32 powerCoreManReach;

struct sEnemyPowerCore {
	RwV3d pos; // 0x00
	struct {
		f32 unk0C; // 0x0C
		f32 unk10; // 0x10
	} range;
	s32 unk14;  // 0x14
	f32 unk18;  // 0x18
	f32 ground; // 0x1C
	s32 type;   // 0x20

	sEnemyPowerCore()
	{
		pos.x = pos.y = pos.z = powerCoreManZero;
		pos.z                 = powerCoreManZero;
		range.unk0C           = powerCoreManZero;
		range.unk10           = powerCoreManReach;
		unk18                 = powerCoreManZero;
		ground                = powerCoreManZero;
		type                  = 0;
	}
};

extern "C" const char* powerCoreClassName;
extern "C" RpClump* powerCoreModels[2];
extern "C" CCL_INFO powerCoreCollision;
extern "C" const f32 powerCoreShadowRise;
extern "C" const f32 powerCoreRadius;
extern "C" RpClump* fn_80150588(RpClump* clump);
f32 GetShadowPos(RwV3d* pos, sAngle* ang, s32 mode);

class TEnemyPowerCore : public TObject, public C_COLLI
{
public:
	TEnemyPowerCore(TObject* parent, const sEnemyPowerCore* params);
	virtual ~TEnemyPowerCore();

	sEnemyPowerCore params; // 0xB0
	RpClump* body;          // 0xD4
	RpClump* shine;         // 0xD8
	s32 unkDC;              // 0xDC
	s32 shown;              // 0xE0
	s32 unkE4;              // 0xE4
	s32 unkE8;              // 0xE8
};

POWER_CORE_CTOR TEnemyPowerCore::TEnemyPowerCore(TObject* parent, const sEnemyPowerCore* from)
    : TObject(parent)
    , C_COLLI()
{
	name   = powerCoreClassName;
	size   = 0xEC;
	params = *from;
	body   = NULL;
	shine  = NULL;
	unkE8  = 0;
	unkDC  = 0;
	body   = fn_80150588(powerCoreModels[0]);
	shine  = fn_80150588(powerCoreModels[1]);
	Init(&powerCoreCollision, 1, 4);
	unkE4 = 0x19;
	{
		RwV3d at = params.pos;

		at.y += powerCoreShadowRise;
		params.ground = GetShadowPos(&at, NULL, 0);
		params.ground += powerCoreRadius;
	}
}

typedef struct GameState {
	u8 unk00[0x18];
	s32 mode; // 0x18
} GameState;

extern "C" GameState lbl_8029C310;

// Whether the game is in modes 1 to 3, where the power cores stand still.
static inline u8 powerCoreGameRange(s32 mode)
{
	u8 in = 1;

	if (!((u32)(mode - 1) <= 1)) {
		in = 0;
	}
	return in;
}

static inline s32 powerCoreGameStopped(void)
{
	u8 stop;
	s32 mode = lbl_8029C310.mode;

	stop = 1;
	if (!powerCoreGameRange(mode) && mode != 3) {
		stop = 0;
	}
	return stop;
}
