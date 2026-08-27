#include "types.h"

extern "C" {
extern void* lbl_8042C180;
extern void* lbl_8_bss_B90;
extern void* lbl_8_bss_B94;
extern void* lbl_8_bss_B98;
extern void* lbl_8_bss_B9C;
extern void* lbl_8_bss_BA0;
extern void* lbl_8_bss_BA4;
extern char lbl_8_data_4DC0[];
extern void* lbl_8_data_4DE8;
extern char lbl_8_data_4DF0[];
extern char lbl_8_data_4E10[];
extern float lbl_8_rodata_C50;
extern float lbl_8_rodata_C54;
extern float lbl_8_rodata_C58;
extern float lbl_8_rodata_C5C;
extern float lbl_8_rodata_C60;
extern float lbl_8_rodata_C64;
extern float lbl_8_rodata_C68;
extern float lbl_8_rodata_C6C;
extern float lbl_8_rodata_C70;
extern float lbl_8_rodata_C74;
extern float lbl_8_rodata_C78;
extern float lbl_8_rodata_C7C;
extern float lbl_8_rodata_C80;
extern float lbl_8_rodata_C84;
extern float lbl_8_rodata_C88;
extern float lbl_8_rodata_C8C;
extern double lbl_8_rodata_C90;
extern float lbl_8_rodata_C98;
extern float lbl_8_rodata_C9C;
extern float lbl_8_rodata_CA0;
extern float lbl_8_rodata_CA4;
extern float lbl_8_rodata_CA8;

void __dt__17PARTICLE_MATERIALFv(...);
void __ct__17PARTICLE_MATERIALF8Pt_FLAGSP11SPRITE_INFO(...);
void __dl__FPv(void*);
void* fn_80057644(...);
void* fn_8005FAE8(void*, void*);
void fn_8005FA8C(void*, void*);
void fn_8005E00C(...);
void fn_80064380(void*);
u32 fn_801C28D8();
}

template <typename T> static inline T& field(void* object, int offset)
{
	return *(T*)((u8*)object + offset);
}

struct Vec3 {
	float x, y, z;
};

typedef void* (*AllocateParticle)(void*);

static void destroyMaterial(void*& material)
{
	if (material == NULL)
		return;
	field<void*>(material, 0x54) = lbl_8_data_4DF0;
	__dt__17PARTICLE_MATERIALFv(material, 0);
	__dl__FPv(material);
	material = NULL;
}

extern "C" void fn_8_49630()
{
	destroyMaterial(lbl_8_bss_BA0);
	destroyMaterial(lbl_8_bss_B9C);
	destroyMaterial(lbl_8_bss_B98);
	destroyMaterial(lbl_8_bss_B94);
	if (lbl_8_bss_BA4 != NULL) {
		fn_8005FA8C(lbl_8_bss_BA4, &lbl_8_data_4DE8);
		lbl_8_bss_B90 = NULL;
		lbl_8_bss_BA4 = NULL;
	}
}

static void setMaterialConstants(void* material, int type)
{
	field<int>(material, 0x7C) = type;
	field<s16>(material, 0xC)  = 0;
	field<s16>(material, 0xE)  = 0x10;
	if (type == 1) {
		field<float>(material, 0x10) = lbl_8_rodata_C60;
		field<float>(material, 0x18) = lbl_8_rodata_C64;
		field<float>(material, 0x20) = lbl_8_rodata_C68;
		field<float>(material, 0x1C) = lbl_8_rodata_C6C;
	} else if (type == 2) {
		field<float>(material, 0x10) = lbl_8_rodata_C70;
		field<float>(material, 0x18) = lbl_8_rodata_C74;
		field<float>(material, 0x20) = lbl_8_rodata_C78;
		field<float>(material, 0x1C) = lbl_8_rodata_C7C;
	} else {
		if (type == 3)
			fn_80064380(material);
		field<float>(material, 0x10) = lbl_8_rodata_C50;
		field<float>(material, 0x18) = lbl_8_rodata_C54;
		field<float>(material, 0x20) = lbl_8_rodata_C58;
		field<float>(material, 0x1C) = lbl_8_rodata_C5C;
	}
}

extern "C" void* fn_8_4A354(void* self, int type)
{
	__ct__17PARTICLE_MATERIALF8Pt_FLAGSP11SPRITE_INFO(self, 5, lbl_8_data_4DC0);
	field<void*>(self, 0x54) = lbl_8_data_4DF0;
	setMaterialConstants(self, type);
	return self;
}

extern "C" void fn_8_497B0()
{
	if (lbl_8_bss_BA4 == NULL)
		lbl_8_bss_BA4 = fn_8005FAE8(lbl_8_data_4E10, &lbl_8_data_4DE8);
	lbl_8_bss_B90 = lbl_8_data_4DE8;
	fn_8005E00C(lbl_8_bss_BA4, 2);
	void** materials[4] = { &lbl_8_bss_B94, &lbl_8_bss_B98, &lbl_8_bss_B9C, &lbl_8_bss_BA0 };
	for (int type = 0; type < 4; type++) {
		if (*materials[type] == NULL) {
			void* material = fn_80057644(0x80);
			if (material != NULL)
				*materials[type] = fn_8_4A354(material, type);
		}
	}
}

static void* allocateParticle(void* material)
{
	void* vtable              = field<void*>(material, 0x54);
	AllocateParticle allocate = field<AllocateParticle>(vtable, 0x1C);
	return allocate(material);
}

static float randomSigned()
{
	u32 value = fn_801C28D8();
	return (float)((double)(s32)value - lbl_8_rodata_C90);
}

static void copyParticle(
    void* particle, float life, float phase, const Vec3* position, const Vec3* velocity)
{
	field<Vec3>(particle, 0x1C)  = *position;
	field<Vec3>(particle, 0x30)  = *velocity;
	field<float>(particle, 0x14) = life;
	field<float>(particle, 0x28) += lbl_8_rodata_C88 * randomSigned();
	field<float>(particle, 0x3C) = phase;
}

extern "C" void* fn_8_49AE8(float life, float phase, const Vec3* position, const Vec3* velocity)
{
	void* particle = allocateParticle(lbl_8_bss_B9C);
	if (particle == NULL)
		return NULL;
	copyParticle(particle, life, phase, position, velocity);
	field<s16>(particle, 0xC) = (s16)(lbl_8_rodata_C80
	    * (lbl_8_rodata_C84 * lbl_8_rodata_C88 * randomSigned() - lbl_8_rodata_C8C));
	field<s16>(particle, 0xE) = (s16)(lbl_8_rodata_C80
	    * (lbl_8_rodata_C58 * lbl_8_rodata_C88 * randomSigned() - lbl_8_rodata_C68));
	return particle;
}

extern "C" void* fn_8_49CF4(float life, float phase, const Vec3* position, const Vec3* velocity)
{
	void* particle = allocateParticle(lbl_8_bss_B98);
	if (particle == NULL)
		return NULL;
	copyParticle(particle, life, phase, position, velocity);
	field<s16>(particle, 0xC)
	    = (s16)(lbl_8_rodata_C80 * lbl_8_rodata_C98 * lbl_8_rodata_C88 * randomSigned());
	field<s16>(particle, 0xE) = (s16)(lbl_8_rodata_C80
	    * (lbl_8_rodata_C9C * lbl_8_rodata_C88 * randomSigned() - lbl_8_rodata_C78));
	return particle;
}

extern "C" void* objEmitBurst(float life, const Vec3* position, const Vec3* velocity)
{
	void* material = field<s8>(lbl_8042C180, 0x1F) == 0 ? lbl_8_bss_B94 : lbl_8_bss_BA0;
	void* particle = allocateParticle(material);
	if (particle == NULL)
		return NULL;
	copyParticle(particle, life, 0.0f, position, velocity);
	field<s16>(particle, 0xC)    = (s16)(lbl_8_rodata_C80
	    * (lbl_8_rodata_C84 * lbl_8_rodata_C88 * randomSigned() - lbl_8_rodata_C8C));
	field<s16>(particle, 0xE)    = (s16)(lbl_8_rodata_C80
	    * (lbl_8_rodata_CA0 * lbl_8_rodata_C88 * randomSigned() - lbl_8_rodata_C74));
	field<float>(particle, 0x3C) = lbl_8_rodata_CA4 * lbl_8_rodata_C88 * randomSigned();
	return particle;
}

extern "C" int fn_8_4A170(void* material, void* particle)
{
	field<s16>(particle, 0xC) += field<s16>(particle, 0xE);
	field<float>(particle, 0x14) += field<float>(material, 0x20);
	field<Vec3>(particle, 0x1C).x += field<Vec3>(particle, 0x30).x;
	field<Vec3>(particle, 0x1C).y += field<Vec3>(particle, 0x30).y;
	field<Vec3>(particle, 0x1C).z += field<Vec3>(particle, 0x30).z;
	field<Vec3>(particle, 0x30).x *= field<float>(material, 0x18);
	field<Vec3>(particle, 0x30).y = field<float>(material, 0x1C)
	    + field<Vec3>(particle, 0x30).y * field<float>(material, 0x18);
	field<Vec3>(particle, 0x30).z *= field<float>(material, 0x18);
	if (field<int>(material, 0x7C) == 0)
		field<float>(particle, 0x3C) += lbl_8_rodata_CA8;
	if (field<int>(material, 0x34) == 0)
		return 1;
	field<float>(particle, 0x28) += field<float>(material, 0x10);
	if ((int)field<float>(particle, 0x28) < field<s16>(material, 0xE))
		return 1;
	field<float>(particle, 0x28) = (float)(field<s16>(material, 0xE) - 1);
	return 0;
}

extern "C" u32 fn_8_4A334(u32 value, u32 limit)
{
	u32 period = limit * 2;
	value %= period;
	return value < limit ? value : period - value;
}

extern "C" void fn_8_4A4B0()
{
	field<void*>(lbl_8_data_4DC0, 0xC) = lbl_8_bss_B90;
}

extern "C" __declspec(section ".ctors") void (*objectEffectsCtor)() = fn_8_4A4B0;
