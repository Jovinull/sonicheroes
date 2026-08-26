#include "types.h"

extern "C" {
extern f32 lbl_8_rodata_B34;
extern f32 lbl_8_rodata_B38;
extern f32 lbl_8_rodata_B3C;
extern f32 lbl_8_rodata_B40;
extern f32 lbl_8_rodata_AD4;
extern f32 lbl_8_rodata_AE8;
extern f32 lbl_8_rodata_AEC;
extern f32 lbl_8_rodata_B10;
extern f32 lbl_8_rodata_B14;
extern f32 lbl_8_rodata_AC0[];
extern f32 lbl_8_data_4618;
extern u32 lbl_8_data_46D4;
extern u32 rollDoorVtable[];
extern f32 lbl_8_data_4664[];
extern char lbl_8_data_4714[];
extern char lbl_8_data_4728[];
extern void* lbl_8_bss_9E0;
extern void* lbl_8_bss_9E4;
extern void* lbl_8_bss_9E8;

void* fn_8005EA04(const char* name);
void* fn_8005E410(void* resource, s32 index, const char* name);
void __ct__7TObjectFP7TObject(void* self, void* parent);
void fn_8005BE6C(void* placement);
void fn_8003C618(void* controller);
void* fn_80150588(void* resource);
void fn_8015BB08(void* manager, void* resource);
f32 fn_800D7B00(s32 angle);
f32 fn_800D7AE4(s32 angle);
void fn_80195790(void* object, const void* axis, f32 first, f32 second, s32 mode);
void fn_8019EB94(void* object, const void* vector, s32 mode);
void fn_8019EC30(void* object, const void* vector, s32 mode);
void* fn_8005DF98(void* object, s32 index);
void fn_8005D5C8(void* resource, s32 index);
void fn_8003C200(void* controller, const void* data, s32 count, s32 type);
void fn_80021384(void* controller);
extern u8 lbl_8042C1D0[];
extern f32 lbl_80239978[];
extern f32 lbl_80239984[];
extern f32 lbl_80239990[];
}

struct RollDoorInfo {
	f32 first;
	f32 second;
	s16 value;
};

struct RollDoorPlacement {
	u8 pad00[0x2C];
	RollDoorInfo* info;
};

struct Vec3 {
	f32 x, y, z;
};

struct RawVec3 {
	u32 x, y, z;
};

#define SET_ROTATION(object, axis, angle, mode)                                                    \
	do {                                                                                           \
		f32 second = fn_800D7B00(angle);                                                           \
		f32 first  = lbl_8_rodata_AE8 - fn_800D7AE4(angle);                                        \
		fn_80195790((u8*)(object) + 0x10, axis, first, second, mode);                              \
	} while (0)
#pragma opt_common_subs off
extern "C" void* rollDoorCtor(void* self, void* parent)
{
	u8* object = (u8*)self;
	__ct__7TObjectFP7TObject(self, parent);
	fn_8005BE6C(object + 0x28);
	fn_8003C618(object + 0x30);
	*(void**)(object + 0x18) = rollDoorVtable;
	*(void**)(object + 0x2C) = (u8*)rollDoorVtable + 0x2C;
	*(u32*)(object + 0x00)   = lbl_8_data_46D4;
	*(u16*)(object + 0x1E)   = 0xF4;

	Vec3* positionPlacement = *(Vec3* volatile*)(object + 0x28);
	*(Vec3*)(object + 0xC0) = *positionPlacement;
	u8* rotationPlacement   = *(u8* volatile*)(object + 0x28);
	*(s32*)(object + 0xCC)  = *(s32*)(rotationPlacement + 0x0C);
	*(s32*)(object + 0xD0)  = *(s32*)(rotationPlacement + 0x10);
	*(s32*)(object + 0xD4)  = *(s32*)(rotationPlacement + 0x14);
	u8* fieldPlacement      = *(u8* volatile*)(object + 0x28);
	RollDoorInfo* info      = *(RollDoorInfo**)(fieldPlacement + 0x2C);
	*(f32*)(object + 0xDC)  = lbl_8_rodata_AD4 + info->first;
	*(s32*)(object + 0xE0)  = (s32)(lbl_8_rodata_B10 * info->second);
	*(s16*)(object + 0xBC)  = info->value;
	*(s32*)(object + 0xD8)  = 0;
	f32 initial             = lbl_8_rodata_AEC;
	*(f32*)(object + 0xE4)  = initial;
	*(f32*)(object + 0xE8)  = initial;
	*(s32*)(object + 0xB8)  = 1;

	*(void**)(object + 0xEC) = fn_80150588(lbl_8_bss_9E0);
	fn_8015BB08(*(void**)(*(u8**)lbl_8042C1D0 + 0x725C), *(void**)(object + 0xEC));
	*(void**)(object + 0xF0) = fn_80150588(lbl_8_bss_9E4);

	u8* firstModel = *(u8**)(*(u8**)(object + 0xEC) + 4);
	SET_ROTATION(firstModel, lbl_80239984, *(s32*)(object + 0xD0) + 0x8000, 0);
	SET_ROTATION(firstModel, lbl_80239978, *(s32*)(object + 0xCC), 2);
	SET_ROTATION(firstModel, lbl_80239990, *(s32*)(object + 0xD4), 2);
	fn_8019EB94(firstModel, object + 0xC0, 2);

	Vec3 unit;
	Vec3 partPosition;
	Vec3 zero;
	zero.x = zero.y = zero.z = lbl_8_data_4618;
	fn_8019EC30(firstModel, &zero, 1);
	void* part     = fn_8005DF98(firstModel, 0);
	part           = fn_8005DF98(part, 0);
	part           = fn_8005DF98(part, 0);
	u8* secondPart = (u8*)part;
	partPosition   = *(Vec3*)(secondPart + 0x40);
	s32 extraAngle = (s32)(lbl_8_rodata_B10 * *(f32*)(object + 0xE4));
	SET_ROTATION(secondPart, lbl_80239978, extraAngle, 0);
	fn_8019EB94(secondPart, &partPosition, 2);

	u8* secondModel = *(u8**)(*(u8**)(object + 0xF0) + 4);
	SET_ROTATION(secondModel, lbl_80239984, *(s32*)(object + 0xD0) + 0x8000, 0);
	SET_ROTATION(secondModel, lbl_80239978, *(s32*)(object + 0xCC), 2);
	SET_ROTATION(secondModel, lbl_80239990, *(s32*)(object + 0xD4), 2);
	fn_8019EB94(secondModel, object + 0xC0, 2);
	fn_8019EC30(secondModel, &zero, 1);
	*(RawVec3*)&unit = *(RawVec3*)lbl_8_rodata_AC0;
	fn_8019EB94(secondModel, &unit, 1);
	SET_ROTATION(secondModel, lbl_80239978, extraAngle, 1);
	if (*(f32*)(object + 0xE8) < lbl_8_rodata_AEC)
		fn_80195790(secondModel + 0x10, lbl_80239984, lbl_8_rodata_B14, lbl_8_rodata_AEC, 1);

	u32 flags = *(u32*)(*(u8**)(object + 0x28) + 0x18);
	fn_8005D5C8(*(void**)(object + 0xEC), ((flags & 0x001C0000) >> 18) + 4);
	fn_8003C200(object + 0x30, lbl_8_data_4664, 2, 4);

	s32 fieldOffset = 0;
	for (s32 i = 0; i < 2; ++i) {
		*(f32*)(*(u8* volatile*)(object + 0x40) + fieldOffset + 0x08) *= lbl_8_data_4618;
		*(f32*)(*(u8* volatile*)(object + 0x40) + fieldOffset + 0x0C) *= lbl_8_data_4618;
		*(f32*)(*(u8* volatile*)(object + 0x40) + fieldOffset + 0x10) *= lbl_8_data_4618;
		*(f32*)(*(u8* volatile*)(object + 0x40) + fieldOffset + 0x14) *= lbl_8_data_4618;
		*(f32*)(*(u8* volatile*)(object + 0x40) + fieldOffset + 0x1C) *= lbl_8_data_4618;
		u8* entry = *(u8* volatile*)(object + 0x40) + fieldOffset;
		if (entry[1] == 11)
			*(f32*)(entry + 0x18) = *(f32*)(entry + 0x14) - *(f32*)(entry + 0x1C);
		else
			*(f32*)(entry + 0x18) *= lbl_8_data_4618;
		fieldOffset += 0x30;
	}
	fn_80021384(object + 0x30);
	return self;
}
#pragma opt_common_subs reset

extern "C" void fn_8_43FF8(void*, RollDoorPlacement* placement)
{
	RollDoorInfo* info = placement->info;
	{
		register f32 value = info->first;
		register f32 bound = lbl_8_rodata_B34;
		if (value < bound)
			info->first = bound;
	}
	{
		register f32 value = info->first;
		register f32 bound = lbl_8_rodata_B38;
		if (value > bound)
			info->first = bound;
	}
	{
		register f32 value = info->second;
		register f32 bound = lbl_8_rodata_B3C;
		if (value < bound)
			info->second = bound;
	}
	{
		register f32 value = info->second;
		register f32 bound = lbl_8_rodata_B40;
		if (value > bound)
			info->second = bound;
	}
	if (info->value < 0)
		info->value = 0;
	if (info->value > 0x7FFF)
		info->value = 0x7FFF;
}

extern "C" void rollDoorUnload()
{
	lbl_8_bss_9E0 = NULL;
}

extern "C" void rollDoorLoad()
{
	lbl_8_bss_9E0 = fn_8005EA04(lbl_8_data_4714);
	lbl_8_bss_9E4 = fn_8005EA04(lbl_8_data_4728);
	if (lbl_8_bss_9E4 != NULL)
		lbl_8_bss_9E8 = fn_8005E410(lbl_8_bss_9E4, 0, NULL);
}
