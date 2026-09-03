#include "types.h"

extern "C" {
extern void* lbl_8042C110;
extern void* lbl_8042C118;
extern void* lbl_8042C148;
extern void* lbl_8042C178;
extern u8 lbl_802D5E80[];
extern void* lbl_802AD070[];
extern void* lbl_8_bss_D38;
extern void* lbl_8_bss_D3C;
extern s8 lbl_8_bss_D40[];
extern void* lbl_8_bss_D50;
extern void* lbl_8_bss_D54;
extern void* lbl_8_bss_D58;
extern void* lbl_8_bss_D5C;
extern void* lbl_8_bss_D60;
extern u8 lbl_8_data_5588[];
extern void* lbl_8_data_559C;
extern void* lbl_8_data_55B8;
extern void* lbl_8_data_55CC;
extern void* lbl_8_data_55F8;
extern float lbl_8_rodata_D38;
extern float lbl_8_rodata_D3C;
extern float lbl_8_rodata_D40;
extern float lbl_8_rodata_D58;

void __ct__7TObjectFP7TObject(void*, void*);
void __dt__7TObjectFv(void*, s32);
void* fn_80018A34(...);
void fn_800189A4(void*, void*);
void fn_8005BE6C(...);
void dtor_8005BD3C(...);
int fn_8005B9F0(void*);
int fn_8005B8BC(void*);
s32 fn_8005B8D8(void*);
void fn_80052DAC(...);
void fn_8014FFBC(...);
void fn_801527A4(void*, void*, void*);
f32 fn_801991B4(void* v);
f32 fn_800D7218(void*, void*);
}

template <typename T> static inline T& field(void* object, int offset)
{
	return *(T*)((u8*)object + offset);
}

struct Vec3 {
	float x, y, z;
};

extern "C" void fn_8_4E0A4(float red, float green, float blue, float alpha)
{
	field<s8>(lbl_8_bss_D5C, 4) = (s8)(lbl_8_rodata_D38 + lbl_8_rodata_D3C * red);
	field<s8>(lbl_8_bss_D5C, 5) = (s8)(lbl_8_rodata_D38 + lbl_8_rodata_D3C * green);
	field<s8>(lbl_8_bss_D5C, 6) = (s8)(lbl_8_rodata_D38 + lbl_8_rodata_D3C * blue);
	field<s8>(lbl_8_bss_D5C, 7) = (s8)(lbl_8_rodata_D38 + lbl_8_rodata_D3C * alpha);
}

extern "C" void fn_8_4E144()
{
	if (lbl_8_bss_D5C != NULL) {
		field<u8>(lbl_8_bss_D5C, 4) = lbl_8_data_5588[0];
		field<u8>(lbl_8_bss_D5C, 5) = lbl_8_data_5588[1];
		field<u8>(lbl_8_bss_D5C, 6) = lbl_8_data_5588[2];
		field<u8>(lbl_8_bss_D5C, 7) = lbl_8_data_5588[3];
	}
	lbl_8_bss_D5C = lbl_8_bss_D58 = lbl_8_bss_D54 = lbl_8_bss_D50 = NULL;
}

extern "C" void fn_8_4E290(void* object)
{
	if (lbl_8_bss_D5C == NULL)
		lbl_8_bss_D5C = object;
}

extern "C" void fn_8_4E2AC(void* object)
{
	if (lbl_8_bss_D54 == NULL)
		lbl_8_bss_D54 = object;
}

extern "C" void fn_8_4E1A8()
{
	lbl_8_bss_D50 = lbl_8_bss_D54 = NULL;
	fn_8014FFBC(NULL, fn_8_4E2AC, NULL);
	if (lbl_8_bss_D54 != NULL) {
		lbl_8_bss_D58 = field<void*>(lbl_8_bss_D54, 0x18);
		field<u32>(lbl_8_bss_D58, 8) |= 0x40;
	}
	lbl_8_bss_D5C = NULL;
	if (lbl_8_bss_D58 != NULL)
		fn_801527A4(lbl_8_bss_D58, fn_8_4E290, NULL);
	if (lbl_8_bss_D50 != NULL)
		lbl_8_bss_D60 = field<void*>(lbl_8_bss_D50, 4);
	if (lbl_8_bss_D5C != NULL)
		for (int i = 0; i < 4; i++)
			lbl_8_data_5588[i] = field<u8>(lbl_8_bss_D5C, 4 + i);
}

extern "C" void fn_8_4E2C8(s8 player)
{
	for (void* object = lbl_8_bss_D3C; object != NULL; object = field<void*>(object, 0x3C)) {
		if (field<s8>(object, 0x39) == 1 && field<s8>(object, 0x30 + player) == 1)
			field<s8>(object, 0x30 + player) = 0;
	}
}

extern "C" void fn_8_4E318(void* first)
{
	lbl_8_bss_D3C = first;
}
extern "C" void* fn_8_4E328()
{
	return lbl_8_bss_D3C;
}

extern "C" void fn_8_4E338(void* self)
{
	if (lbl_8_bss_D3C == NULL) {
		field<u16>(self, 4) |= 1;
		return;
	}
	s8 selected[8];
	for (int i = 0; i < 8; i++)
		selected[i] = -1;
	for (void* object = lbl_8_bss_D3C; object != NULL; object = field<void*>(object, 0x3C)) {
		for (int i = 0; i < 8; i++) {
			if (field<s8>(object, 0x30 + i) == 1 && selected[i] < 0)
				selected[i] = field<s8>(object, 0x38);
		}
	}
	for (int i = 0; i < 8; i++) {
		if (selected[i] != lbl_8_bss_D40[i * 2])
			fn_80052DAC(lbl_802D5E80, i);
		lbl_8_bss_D40[i * 2] = selected[i];
	}
}

extern "C" void* fn_8_4E588(void* self, s16 flags)
{
	if (self != NULL) {
		field<void*>(self, 0x18) = lbl_8_data_55CC;
		for (int i = 0; i < 8; i++)
			fn_80052DAC(lbl_802D5E80, i);
		if (lbl_8_bss_D38 == self)
			lbl_8_bss_D38 = NULL;
		__dt__7TObjectFv(self, 0);
		if (flags > 0)
			fn_800189A4(lbl_8042C148, self);
	}
	return self;
}

extern "C" void* fn_8_4E654(void* self, void* parent)
{
	__ct__7TObjectFP7TObject(self, parent);
	field<void*>(self, 0x18) = lbl_8_data_55CC;
	field<void*>(self, 0)    = lbl_8_data_55B8;
	field<u16>(self, 0x1E)   = 0x28;
	for (int i = 0; i < 16; i++)
		lbl_8_bss_D40[i] = -1;
	return self;
}

extern "C" void fn_8_4E700() { }

extern "C" int fn_8_4E704(void* self, int player)
{
	void* placement = field<void*>(self, 0x28);
	u8* config      = field<u8*>(placement, 0x2C);
	if (lbl_802AD070[player] == NULL)
		return 0;
	void* collision = field<void*>(lbl_802AD070[player], 0x38);
	if (collision == NULL)
		return 0;
	Vec3 extent = { field<float>(config, 4), field<float>(config, 8), field<float>(config, 0xC) };
	float distance = fn_800D7218((u8*)collision + 8, placement);
	float radius   = field<float>(collision, 0x14);
	if (config[2] == 0)
		return fn_801991B4(&extent) + radius >= distance;
	if (config[2] == 1)
		return extent.x + radius >= distance;
	return extent.y + radius >= distance;
}

extern "C" void fn_8_4EB14(void* self)
{
	u8* config = field<u8*>(field<void*>(self, 0x28), 0x2C);
	if (fn_8005B9F0((u8*)self + 0x28) || fn_8005B8BC((u8*)self + 0x28)) {
		field<u16>(self, 4) |= 1;
		return;
	}
	if (fn_8005B8D8((u8*)self + 0x28)) {
		field<u8>(self, 0x38) = config[0];
		field<u8>(self, 0x39) = config[1];
	}
	for (int player = 0; player < 8; player++) {
		bool touching = fn_8_4E704(self, player) != 0;
		if (config[1] == 0) {
			if (touching) {
				fn_8_4E2C8(player);
				field<u8>(self, 0x30 + player) = 1;
			}
		} else if (config[1] == 3) {
			if (touching) {
				fn_8_4E2C8(player);
				field<u8>(self, 0x30 + player) = 0;
			}
		} else {
			field<u8>(self, 0x30 + player) = touching;
		}
	}
}

extern "C" void fn_3_4EE40(void*, void* placement)
{
	u8* config = field<u8*>(placement, 0x2C);
	if ((s8)config[0] < 0)
		config[0] = 0;
	if (config[0] > 0x12)
		config[0] = 0x12;
	if ((s8)config[1] < 0)
		config[1] = 0;
	if (config[1] > 3)
		config[1] = 3;
	if ((s8)config[2] < 0)
		config[2] = 0;
	if (config[2] > 3)
		config[2] = 3;
	for (int i = 0; i < 3; i++)
		if (field<float>(config, 4 + i * 4) < lbl_8_rodata_D40)
			field<float>(config, 4 + i * 4) = lbl_8_rodata_D40;
}

extern "C" void* fn_8_4EFB8(void* self, s16 flags)
{
	if (self != NULL) {
		field<void*>(self, 0x18) = lbl_8_data_55F8;
		if (lbl_8_bss_D3C == self)
			lbl_8_bss_D3C = field<void*>(self, 0x3C);
		else
			for (void* item = lbl_8_bss_D3C; item != NULL; item = field<void*>(item, 0x3C))
				if (field<void*>(item, 0x3C) == self) {
					field<void*>(item, 0x3C) = field<void*>(self, 0x3C);
					break;
				}
		dtor_8005BD3C((u8*)self + 0x28, 0);
		__dt__7TObjectFv(self, 0);
		if (flags > 0)
			fn_800189A4(lbl_8042C148, self);
	}
	return self;
}

extern "C" void* fn_8_4F084(void* self, void* parent)
{
	__ct__7TObjectFP7TObject(self, parent);
	fn_8005BE6C((u8*)self + 0x28);
	field<void*>(self, 0x18) = lbl_8_data_55F8;
	field<void*>(self, 0)    = lbl_8_data_559C;
	field<u16>(self, 0x1E)   = 0x40;
	if (lbl_8_bss_D38 == NULL) {
		void* manager = fn_80018A34(lbl_8042C148, 0x28);
		if (manager == NULL) {
			field<u16>(self, 4) |= 1;
			return self;
		}
		lbl_8_bss_D38 = fn_8_4E654(manager, lbl_8042C118);
	}
	for (int i = 0; i < 8; i++)
		field<u8>(self, 0x30 + i) = 0;
	u8* config            = field<u8*>(field<void*>(self, 0x28), 0x2C);
	field<u8>(self, 0x38) = config[0];
	field<u8>(self, 0x39) = config[1];
	void* tail            = lbl_8_bss_D3C;
	if (tail == NULL)
		lbl_8_bss_D3C = self;
	else {
		while (field<void*>(tail, 0x3C) != NULL)
			tail = field<void*>(tail, 0x3C);
		field<void*>(tail, 0x3C) = self;
	}
	field<void*>(self, 0x3C) = NULL;
	return self;
}

extern "C" void lightCollisionCreate()
{
	void* object = fn_80018A34(lbl_8042C148, 0x40);
	if (object != NULL)
		fn_8_4F084(object, lbl_8042C110);
}
