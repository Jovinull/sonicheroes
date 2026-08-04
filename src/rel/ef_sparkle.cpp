#include "types.h"

struct RwV3d {
	f32 x;
	f32 y;
	f32 z;
};

static u32 CalcInt(u32, u32);

struct PARTICLE_INSTANCE {
	u8 pad00[0x0C];
	s16 angle;
	s16 angleStep;
	u8 pad10[4];
	f32 scale;
	u8 pad18[4];
	RwV3d position;
	f32 field28;
	u8 pad2C[4];
	RwV3d velocity;
	f32 phase;
};

class ParticleHeader
{
public:
	u8 base[0x54];
};

class PARTICLE_MATERIAL : public ParticleHeader
{
public:
	PARTICLE_MATERIAL(s32, const void*);
	~PARTICLE_MATERIAL();

	virtual void MoveManager();
	virtual void DispManager();
	virtual s32 Move(PARTICLE_INSTANCE*);
	virtual void Disp(PARTICLE_INSTANCE*);
	virtual PARTICLE_INSTANCE* AllocInstance();
	virtual PARTICLE_INSTANCE* CreateInstance();
};

class EfSparkle : public PARTICLE_MATERIAL
{
public:
	u8 pad58[0x24];
	u32 kind;

	EfSparkle(u32);
	~EfSparkle();
	virtual s32 Move(PARTICLE_INSTANCE*);
};

extern "C" {
EfSparkle* __dt__9EfSparkleFv(EfSparkle*, s16);
EfSparkle* __ct__9EfSparkleFUi(EfSparkle*, u32);
void fn_800657EC(void*, s32, const void*);
void dtor_800654F4(void*, s16);
void fn_80064380(void*);
void* fn_80057644(u32);
void __dl__FPv(void*);
void* fn_8005FAE8(const char*, void*);
void fn_8005FA8C(void*, void*);
void fn_8005E00C(void*, s32);
void copyVec3(RwV3d*, const RwV3d*);
s32 fn_16_F20(void*, s32);
u32 fn_801C28D8();
u32 __cvt_fp2unsigned(f32);

extern void* lbl_16_data_3D00[];

extern EfSparkle* check_16_bss_A24;
extern EfSparkle* check_16_bss_A28;
extern EfSparkle* check_16_bss_A2C;
extern EfSparkle* check_16_bss_A30;
extern void* check_16_bss_A34;
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
	u32 color;
	s32 field08;
	void* texture;
	void* offsets;
	u32 field14;
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
	0x00300000,
	-1,
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

#define RANDOM_UNIT() ((f32)(s32)fn_801C28D8())

void ReleaseTextureEfSparkle()
{
	if (check_16_bss_A30 != 0) {
		__dt__9EfSparkleFv(lbl_16_bss_A30, 1);
		lbl_16_bss_A30 = 0;
	}
	if (check_16_bss_A2C != 0) {
		__dt__9EfSparkleFv(lbl_16_bss_A2C, 1);
		lbl_16_bss_A2C = 0;
	}
	if (check_16_bss_A28 != 0) {
		__dt__9EfSparkleFv(lbl_16_bss_A28, 1);
		lbl_16_bss_A28 = 0;
	}
	if (check_16_bss_A24 != 0) {
		__dt__9EfSparkleFv(lbl_16_bss_A24, 1);
		lbl_16_bss_A24 = 0;
	}
	if (check_16_bss_A34 != 0) {
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
	fn_8005E00C(lbl_16_bss_A34, 2);

	if (lbl_16_bss_A24 == 0) {
		EfSparkle* sparkle = (EfSparkle*)fn_80057644(0x80);
		if (sparkle != 0)
			sparkle = __ct__9EfSparkleFUi(sparkle, 0);
		lbl_16_bss_A24 = sparkle;
	}

	if (lbl_16_bss_A28 == 0) {
		EfSparkle* sparkle = (EfSparkle*)fn_80057644(0x80);
		if (sparkle != 0)
			sparkle = __ct__9EfSparkleFUi(sparkle, 1);
		lbl_16_bss_A28 = sparkle;
	}

	if (lbl_16_bss_A2C == 0) {
		EfSparkle* sparkle = (EfSparkle*)fn_80057644(0x80);
		if (sparkle != 0)
			sparkle = __ct__9EfSparkleFUi(sparkle, 2);
		lbl_16_bss_A2C = sparkle;
	}

	if (lbl_16_bss_A30 == 0) {
		EfSparkle* sparkle = (EfSparkle*)fn_80057644(0x80);
		if (sparkle != 0)
			sparkle = __ct__9EfSparkleFUi(sparkle, 3);
		lbl_16_bss_A30 = sparkle;
	}
}

PARTICLE_INSTANCE* CreateSparkleR(RwV3d* position, RwV3d* velocity, f32 scale, f32 phase)
{
	PARTICLE_INSTANCE* particle = lbl_16_bss_A2C->CreateInstance();
	if (particle == 0)
		return 0;

	copyVec3(&particle->position, position);
	copyVec3(&particle->velocity, velocity);
	particle->scale     = scale;
	particle->angle     = (s16)(s32)(lbl_16_rodata_9B0
	    * (RANDOM_UNIT() * lbl_16_rodata_9B8 * lbl_16_rodata_9B4 - lbl_16_rodata_9BC));
	particle->angleStep = (s16)(s32)(lbl_16_rodata_9B0
	    * (RANDOM_UNIT() * lbl_16_rodata_9B8 * lbl_16_rodata_9C0 - lbl_16_rodata_9C4));
	particle->field28 += RANDOM_UNIT() * lbl_16_rodata_9B8;
	particle->phase = phase;
	return particle;
}

PARTICLE_INSTANCE* CreateSparkle(RwV3d* position, RwV3d* velocity, f32 scale, f32 phase)
{
	PARTICLE_INSTANCE* particle = lbl_16_bss_A28->CreateInstance();
	if (particle == 0)
		return 0;

	copyVec3(&particle->position, position);
	copyVec3(&particle->velocity, velocity);
	particle->scale = scale;
	particle->angle
	    = (s16)(s32)(RANDOM_UNIT() * lbl_16_rodata_9B8 * lbl_16_rodata_9D0 * lbl_16_rodata_9B0);
	particle->angleStep = (s16)(s32)(lbl_16_rodata_9B0
	    * (RANDOM_UNIT() * lbl_16_rodata_9B8 * lbl_16_rodata_9D4 - lbl_16_rodata_9D8));
	particle->field28 += RANDOM_UNIT() * lbl_16_rodata_9B8;
	particle->phase = phase;
	return particle;
}

extern "C" PARTICLE_INSTANCE* fn_16_2E3C4(RwV3d* position, RwV3d* velocity, f32 scale)
{
	PARTICLE_INSTANCE* particle;
	if (fn_16_F20(lbl_8042C180, 0x1F) != 0)
		particle = lbl_16_bss_A30->CreateInstance();
	else
		particle = lbl_16_bss_A24->CreateInstance();
	if (particle == 0)
		return 0;

	copyVec3(&particle->position, position);
	copyVec3(&particle->velocity, velocity);
	particle->scale     = scale;
	particle->angle     = (s16)(s32)(lbl_16_rodata_9B0
	    * (RANDOM_UNIT() * lbl_16_rodata_9B8 * lbl_16_rodata_9B4 - lbl_16_rodata_9BC));
	particle->angleStep = (s16)(s32)(lbl_16_rodata_9B0
	    * (RANDOM_UNIT() * lbl_16_rodata_9B8 * lbl_16_rodata_9DC - lbl_16_rodata_9E0));
	particle->field28 += RANDOM_UNIT() * lbl_16_rodata_9B8;
	particle->phase = RANDOM_UNIT() * lbl_16_rodata_9B8 * lbl_16_rodata_9E4;
	return particle;
}

s32 EfSparkle::Move(PARTICLE_INSTANCE* particle)
{
	particle->angle += particle->angleStep;
	particle->scale += *(f32*)(base + 0x20);
	particle->position.x += particle->velocity.x;
	particle->position.y += particle->velocity.y;
	particle->position.z += particle->velocity.z;
	particle->velocity.x *= *(f32*)(base + 0x18);
	particle->velocity.y = *(f32*)(base + 0x1C) + particle->velocity.y * *(f32*)(base + 0x18);
	particle->velocity.z *= *(f32*)(base + 0x18);

	if (kind == 0) {
		particle->angle
		    = (s16)((s32)(lbl_16_rodata_9B0
		                * (f32)((s32)CalcInt(__cvt_fp2unsigned(particle->phase), 0x10) - 8))
		        + 0x4000);
		particle->phase += lbl_16_rodata_9E8;
	}

	if (*(u32*)(base + 0x34) != 0) {
		particle->field28 += *(f32*)(base + 0x10);
		if ((u16)(s32)particle->field28 >= *(s16*)(base + 0xE)) {
			particle->field28 = (f32)(*(s16*)(base + 0xE) - 1);
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
    : PARTICLE_MATERIAL(5, &lbl_16_data_3CD0)
{
	kind                = materialKind;
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

EfSparkle::~EfSparkle() { }

extern "C" void __sinit_ef_sparkle_cpp()
{
	*(void**)((u8*)&lbl_16_data_3CD0 + 0xC) = lbl_16_bss_A20;
}

__declspec(section ".ctors") void (*const EfSparkleCtorEntry)() = __sinit_ef_sparkle_cpp;

#pragma force_active on
extern const u32 efSparkleRodataPadding = 0;
#pragma force_active reset
