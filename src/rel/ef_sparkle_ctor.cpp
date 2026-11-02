#include "types.h"

// EfSparkle's constructor (the PS2 build's name) in the stage modules' own
// particle effects: the engine material is built with flags 5 and the module's
// sparkle sprite, and the material's pattern speed (+0x10), damping (+0x18),
// lift (+0x1C) and growth (+0x20) are set for its kind; kind 3 is kind 0 made
// additive first (fn_80064380). The same in twelve stage modules (stage11D's
// copy is part of rel/object_effects_stage11.cpp); the class is the one of
// rel/ef_sparkle.cpp.

struct RwV3d {
	f32 x;
	f32 y;
	f32 z;
};

static u32 CalcInt(u32, u32);

class PARTICLE_MATERIAL;
struct IMPRIM_WORK;
struct sAngle {
	s32 x, y, z;
};
struct PARTICLE_INSTANCE {
	PARTICLE_INSTANCE* pNext;
	PARTICLE_MATERIAL* pMaterial;
	u8 nowFlag;
	s16 timer;
	s16 nowRot;
	s16 nowRotSpd;
	u32 nowColor;
	f32 nowScl;
	f32 nowSclSpd;
	RwV3d nowPos;
	f32 nowPattern;
	f32 nowPatternSpd;
	RwV3d nowSpd;
	f32 zofs;
	void* others;
	IMPRIM_WORK* ImPrimWork;
};

struct SPRITE_INFO;
enum Pt_FLAGS { Pt_NON_FLAG = 0, ALL_Pt_FLAGS = -1 };

class ParticleHeader
{
public:
	u8 base[0x54];
};

class PARTICLE_MATERIAL : public ParticleHeader
{
public:
	PARTICLE_MATERIAL(Pt_FLAGS, SPRITE_INFO*);
	~PARTICLE_MATERIAL();

	virtual void MoveManager();
	virtual void DispManager();
	virtual s32 Move(PARTICLE_INSTANCE*);
	virtual void Disp(PARTICLE_INSTANCE*);
	virtual PARTICLE_INSTANCE* AllocInstance();
	virtual PARTICLE_INSTANCE* CreateInstance();
	RwV3d pos;
	sAngle ang;
	RwV3d vec;
};

class EfSparkle : public PARTICLE_MATERIAL
{
public:
	u32 type;

	EfSparkle(u32);
	~EfSparkle();
	virtual s32 Move(PARTICLE_INSTANCE*);
};

extern "C" {
extern SPRITE_INFO efSparkleSpriteInfo;
extern const f32 efSparklePatternSpeedA;
extern const f32 efSparkleDampingA;
extern const f32 efSparkleGrowthA;
extern const f32 efSparkleLiftA;
extern const f32 efSparklePatternSpeedB;
extern const f32 efSparkleDampingB;
extern const f32 efSparkleGrowthB;
extern const f32 efSparkleLiftB;
extern const f32 efSparklePatternSpeedC;
extern const f32 efSparkleDampingC;
extern const f32 efSparkleGrowthC;
extern const f32 efSparkleLiftC;
void fn_80064380(void*);
}

EfSparkle::EfSparkle(u32 materialKind)
    : PARTICLE_MATERIAL((Pt_FLAGS)5, &efSparkleSpriteInfo)
{
	type                = materialKind;
	*(u16*)(base + 0xC) = 0;
	*(u16*)(base + 0xE) = 0x10;

	switch (materialKind) {
		case 3:
			fn_80064380(this);
		case 0:
			*(f32*)(base + 0x10) = efSparklePatternSpeedA;
			*(f32*)(base + 0x18) = efSparkleDampingA;
			*(f32*)(base + 0x20) = efSparkleGrowthA;
			*(f32*)(base + 0x1C) = efSparkleLiftA;
			break;
		case 1:
			*(f32*)(base + 0x10) = efSparklePatternSpeedB;
			*(f32*)(base + 0x18) = efSparkleDampingB;
			*(f32*)(base + 0x20) = efSparkleGrowthB;
			*(f32*)(base + 0x1C) = efSparkleLiftB;
			break;
		case 2:
			*(f32*)(base + 0x10) = efSparklePatternSpeedC;
			*(f32*)(base + 0x18) = efSparkleDampingC;
			*(f32*)(base + 0x20) = efSparkleGrowthC;
			*(f32*)(base + 0x1C) = efSparkleLiftC;
			break;
	}
}
