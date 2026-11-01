#include "types.h"

// ReleaseTextureEfSparkle (the PS2 build's name) in the stage modules' own
// particle effects, the same in twelve stage modules (stage11D's copy is part
// of rel/object_effects_stage11.cpp): the four sparkle materials are deleted
// (EfSparkle's destructor inline), last first, and the texture dictionary is
// released once with its texture entry.

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
	~EfSparkle() { }
	virtual s32 Move(PARTICLE_INSTANCE*);
};

extern "C" {
void __dl__FPv(void*);
void fn_8005FA8C(void* dictionary, void* entry);
extern EfSparkle* efSparkleMaterial0;
extern EfSparkle* efSparkleMaterial1;
extern EfSparkle* efSparkleMaterial2;
extern EfSparkle* efSparkleMaterial3;
extern void* efSparkleTexture;
extern void* efSparkleTexDict;
extern u8 efSparkleTextureEntry[];
}

void ReleaseTextureEfSparkle()
{
	if (efSparkleMaterial3 != NULL) {
		delete efSparkleMaterial3;
		efSparkleMaterial3 = NULL;
	}
	if (efSparkleMaterial2 != NULL) {
		delete efSparkleMaterial2;
		efSparkleMaterial2 = NULL;
	}
	if (efSparkleMaterial1 != NULL) {
		delete efSparkleMaterial1;
		efSparkleMaterial1 = NULL;
	}
	if (efSparkleMaterial0 != NULL) {
		delete efSparkleMaterial0;
		efSparkleMaterial0 = NULL;
	}
	if (efSparkleTexDict != NULL) {
		fn_8005FA8C(efSparkleTexDict, efSparkleTextureEntry);
		efSparkleTexture = NULL;
		efSparkleTexDict = NULL;
	}
}
