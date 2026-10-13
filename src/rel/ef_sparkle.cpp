#include "types.h"

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
void fn_800657EC(void*, s32, const void*);
void dtor_800654F4(void*, s16);
void fn_80064380(void*);
void __dl__FPv(void*);
void* fn_8005FAE8(const char*, void*);
void fn_8005FA8C(void*, void*);
void objChangeTextureFilterMode__FP15RwTexDictionary19RwTextureFilterMode(void*, s32);
void copyVec3(RwV3d*, const RwV3d*);
s32 fn_16_F20(void*, s32);
u32 rand();
u32 __cvt_fp2unsigned(f32);

extern void* lbl_16_data_3D00[];

extern EfSparkle* lbl_16_bss_A24;
extern EfSparkle* lbl_16_bss_A28;
extern EfSparkle* lbl_16_bss_A2C;
extern EfSparkle* lbl_16_bss_A30;
extern void* lbl_16_bss_A34;
extern void* lbl_8042C180;

extern void* lbl_802435D8;
}

#define lbl_16_rodata_9B0 182.04444885253906f
#define lbl_16_rodata_9B4 80.0f
#define lbl_16_rodata_9B8 3.0517578125e-05f
#define lbl_16_rodata_9BC 40.0f
#define lbl_16_rodata_9C0 0.1f
#define lbl_16_rodata_9C4 0.05f
#define lbl_16_rodata_9D0 360.0f
#define lbl_16_rodata_9D4 2.0f
#define lbl_16_rodata_9D8 1.0f
#define lbl_16_rodata_9DC 1.8f
#define lbl_16_rodata_9E0 0.9f
#define lbl_16_rodata_9E4 16.0f
#define lbl_16_rodata_9E8 0.2666666805744171f
#define lbl_16_rodata_9EC 0.6000000238418579f
#define lbl_16_rodata_9F0 0.9300000071525574f
#define lbl_16_rodata_9F4 0.0f
#define lbl_16_rodata_9F8 0.11999999731779099f
#define lbl_16_rodata_9FC 0.9639999866485596f
#define lbl_16_rodata_A00 -0.004999999888241291f
#define lbl_16_rodata_A04 0.699999988079071f
#define lbl_16_rodata_A08 -0.05000000074505806f

struct SPRITE_INFO {
	u32 flags;
	s16 maxNum;
	u32 color;
	void* texture;
	void* uvTable;
	void* data;
};

struct TEXTURE_ENTRY {
	void* texture;
	char* name;
};

struct TEXTURE_LIST {
	TEXTURE_ENTRY* entries;
	u32 count;
};

SPRITE_INFO lbl_16_data_3CD0 = {
	0x502,
	48,
	0xFFFFFFFF,
	0,
	&lbl_802435D8,
	0,
};
char lbl_16_data_3CE8[]        = "ef_uv00";
TEXTURE_ENTRY lbl_16_data_3CF0 = {
	0,
	lbl_16_data_3CE8,
};
TEXTURE_LIST lbl_16_data_3CF8 = {
	&lbl_16_data_3CF0,
	1,
};
char lbl_16_data_3D20[] = "./textures/ef_uv00.txd";

void* lbl_16_bss_A20;
EfSparkle* lbl_16_bss_A24;
EfSparkle* lbl_16_bss_A28;
EfSparkle* lbl_16_bss_A2C;
EfSparkle* lbl_16_bss_A30;
void* lbl_16_bss_A34;

#define RANDOM_UNIT() ((f32)(s32)rand())

void ReleaseTextureEfSparkle()
{
	if (lbl_16_bss_A30 != 0) {
		delete lbl_16_bss_A30;
		lbl_16_bss_A30 = 0;
	}
	if (lbl_16_bss_A2C != 0) {
		delete lbl_16_bss_A2C;
		lbl_16_bss_A2C = 0;
	}
	if (lbl_16_bss_A28 != 0) {
		delete lbl_16_bss_A28;
		lbl_16_bss_A28 = 0;
	}
	if (lbl_16_bss_A24 != 0) {
		delete lbl_16_bss_A24;
		lbl_16_bss_A24 = 0;
	}
	if (lbl_16_bss_A34 != 0) {
		fn_8005FA8C(lbl_16_bss_A34, &lbl_16_data_3CF8);
		lbl_16_bss_A20 = 0;
		lbl_16_bss_A34 = 0;
	}
}

void LoadTextureEfSparkle()
{
	if (lbl_16_bss_A34 == 0)
		lbl_16_bss_A34 = fn_8005FAE8(lbl_16_data_3D20, &lbl_16_data_3CF8);

	lbl_16_bss_A20                          = *(void**)*(void**)&lbl_16_data_3CF8;
	*(void**)((u8*)&lbl_16_data_3CD0 + 0xC) = lbl_16_bss_A20;
	objChangeTextureFilterMode__FP15RwTexDictionary19RwTextureFilterMode(lbl_16_bss_A34, 2);

	if (lbl_16_bss_A24 == 0) {
		lbl_16_bss_A24 = new EfSparkle(0);
	}

	if (lbl_16_bss_A28 == 0) {
		lbl_16_bss_A28 = new EfSparkle(1);
	}

	if (lbl_16_bss_A2C == 0) {
		lbl_16_bss_A2C = new EfSparkle(2);
	}

	if (lbl_16_bss_A30 == 0) {
		lbl_16_bss_A30 = new EfSparkle(3);
	}
}

PARTICLE_INSTANCE* CreateSparkleR(RwV3d* position, RwV3d* velocity, f32 scale, f32 phase)
{
	PARTICLE_INSTANCE* particle = lbl_16_bss_A2C->CreateInstance();
	if (particle == 0)
		return 0;

	copyVec3(&particle->nowPos, position);
	copyVec3(&particle->nowSpd, velocity);
	particle->nowScl    = scale;
	particle->nowRot    = (s16)(s32)(lbl_16_rodata_9B0
	    * (RANDOM_UNIT() * lbl_16_rodata_9B8 * lbl_16_rodata_9B4 - lbl_16_rodata_9BC));
	particle->nowRotSpd = (s16)(s32)(lbl_16_rodata_9B0
	    * (RANDOM_UNIT() * lbl_16_rodata_9B8 * lbl_16_rodata_9C0 - lbl_16_rodata_9C4));
	particle->nowPattern += RANDOM_UNIT() * lbl_16_rodata_9B8;
	particle->zofs = phase;
	return particle;
}

PARTICLE_INSTANCE* CreateSparkle(RwV3d* position, RwV3d* velocity, f32 scale, f32 phase)
{
	PARTICLE_INSTANCE* particle = lbl_16_bss_A28->CreateInstance();
	if (particle == 0)
		return 0;

	copyVec3(&particle->nowPos, position);
	copyVec3(&particle->nowSpd, velocity);
	particle->nowScl = scale;
	particle->nowRot
	    = (s16)(s32)(RANDOM_UNIT() * lbl_16_rodata_9B8 * lbl_16_rodata_9D0 * lbl_16_rodata_9B0);
	particle->nowRotSpd = (s16)(s32)(lbl_16_rodata_9B0
	    * (RANDOM_UNIT() * lbl_16_rodata_9B8 * lbl_16_rodata_9D4 - lbl_16_rodata_9D8));
	particle->nowPattern += RANDOM_UNIT() * lbl_16_rodata_9B8;
	particle->zofs = phase;
	return particle;
}

PARTICLE_INSTANCE* CreateSparkle(RwV3d* position, RwV3d* velocity, f32 scale)
{
	PARTICLE_INSTANCE* particle;
	if (fn_16_F20(lbl_8042C180, 0x1F) != 0)
		particle = lbl_16_bss_A30->CreateInstance();
	else
		particle = lbl_16_bss_A24->CreateInstance();
	if (particle == 0)
		return 0;

	copyVec3(&particle->nowPos, position);
	copyVec3(&particle->nowSpd, velocity);
	particle->nowScl    = scale;
	particle->nowRot    = (s16)(s32)(lbl_16_rodata_9B0
	    * (RANDOM_UNIT() * lbl_16_rodata_9B8 * lbl_16_rodata_9B4 - lbl_16_rodata_9BC));
	particle->nowRotSpd = (s16)(s32)(lbl_16_rodata_9B0
	    * (RANDOM_UNIT() * lbl_16_rodata_9B8 * lbl_16_rodata_9DC - lbl_16_rodata_9E0));
	particle->nowPattern += RANDOM_UNIT() * lbl_16_rodata_9B8;
	particle->zofs = RANDOM_UNIT() * lbl_16_rodata_9B8 * lbl_16_rodata_9E4;
	return particle;
}

s32 EfSparkle::Move(PARTICLE_INSTANCE* particle)
{
	particle->nowRot += particle->nowRotSpd;
	particle->nowScl += *(f32*)(base + 0x20);
	particle->nowPos.x += particle->nowSpd.x;
	particle->nowPos.y += particle->nowSpd.y;
	particle->nowPos.z += particle->nowSpd.z;
	particle->nowSpd.x *= *(f32*)(base + 0x18);
	particle->nowSpd.y = *(f32*)(base + 0x1C) + particle->nowSpd.y * *(f32*)(base + 0x18);
	particle->nowSpd.z *= *(f32*)(base + 0x18);

	if (type == 0) {
		particle->nowRot
		    = (s16)((s32)(lbl_16_rodata_9B0
		                * (f32)((s32)CalcInt(__cvt_fp2unsigned(particle->zofs), 0x10) - 8))
		        + 0x4000);
		particle->zofs += lbl_16_rodata_9E8;
	}

	if (*(u32*)(base + 0x34) != 0) {
		particle->nowPattern += *(f32*)(base + 0x10);
		if ((u16)(s32)particle->nowPattern >= *(s16*)(base + 0xE)) {
			particle->nowPattern = (f32)(*(s16*)(base + 0xE) - 1);
			return 0;
		}
		return 1;
	}
	return 1;
}

static u32 CalcInt(u32 value, u32 range)
{
	u32 doubleRange = range * 2;
	u32 result      = value % doubleRange;
	if (result >= range)
		result = doubleRange - result;
	return result;
}

EfSparkle::EfSparkle(u32 materialKind)
    : PARTICLE_MATERIAL((Pt_FLAGS)5, &lbl_16_data_3CD0)
{
	type                = materialKind;
	*(u16*)(base + 0xC) = 0;
	*(u16*)(base + 0xE) = 0x10;

	switch (materialKind) {
		case 3:
			fn_80064380(this);
		case 0:
			*(f32*)(base + 0x10) = lbl_16_rodata_9EC;
			*(f32*)(base + 0x18) = lbl_16_rodata_9F0;
			*(f32*)(base + 0x20) = lbl_16_rodata_9C0;
			*(f32*)(base + 0x1C) = lbl_16_rodata_9F4;
			break;
		case 1:
			*(f32*)(base + 0x10) = lbl_16_rodata_9F8;
			*(f32*)(base + 0x18) = lbl_16_rodata_9FC;
			*(f32*)(base + 0x20) = lbl_16_rodata_9C4;
			*(f32*)(base + 0x1C) = lbl_16_rodata_A00;
			break;
		case 2:
			*(f32*)(base + 0x10) = lbl_16_rodata_A04;
			*(f32*)(base + 0x18) = lbl_16_rodata_9E0;
			*(f32*)(base + 0x20) = lbl_16_rodata_9D8;
			*(f32*)(base + 0x1C) = lbl_16_rodata_A08;
			break;
	}
}

extern "C" void __sinit_ef_sparkle_cpp()
{
	*(void**)((u8*)&lbl_16_data_3CD0 + 0xC) = lbl_16_bss_A20;
}

__declspec(section ".ctors") void (*const EfSparkleCtorEntry)() = __sinit_ef_sparkle_cpp;

EfSparkle::~EfSparkle() { }

#pragma force_active on
// Preserve the configured residual zero extent; original declaration is unknown.
extern const u32 efSparkleRodataPadding = 0;
#pragma force_active reset
