#include "types.h"

extern "C" {
extern void* lbl_8042C110;
extern void* lbl_8042C148;
extern void* lbl_8042C180;
extern void* lbl_8042C1D0;
extern void* lbl_8042C2A0;
extern void* lbl_8042C388;
extern void* lbl_80303DC8;
extern void* lbl_8029C310;
extern void* lbl_802D5E80;
extern void* lbl_8_data_4E28[];
extern void* lbl_8_data_4EAC[];
extern void* lbl_8_data_4F30;
extern void* lbl_8_data_4F54;
extern void* lbl_8_data_5014;
extern void* lbl_8_data_5024;
extern char lbl_8_data_4FD4[];
extern char lbl_8_data_5060[];
extern char lbl_8_data_5074[];
extern char lbl_8_data_5088[];
extern char lbl_8_data_509C[];
extern void* lbl_8_bss_C08;
extern void* lbl_8_bss_C0C;
extern void* lbl_8_bss_C10;
extern void* lbl_8_bss_C14;
extern void* lbl_8_data_4FB8;
extern float lbl_8_rodata_CB0;
extern float lbl_8_rodata_CD8;
extern float lbl_8_rodata_CDC;
extern float lbl_8_rodata_CE0;
extern float lbl_8_rodata_CE8;
extern float lbl_8_rodata_CEC;
extern float lbl_8_rodata_CF0;
extern float lbl_8_rodata_CF4;
extern float lbl_8_rodata_CF8;
extern float lbl_8_rodata_CFC;
extern float lbl_8_rodata_D00;
extern float lbl_8_rodata_D04;
extern float lbl_8_rodata_D08;
extern float lbl_8_rodata_D0C;
extern float lbl_8_rodata_D10;
extern char lbl_80239978[];
extern char lbl_80239984[];
extern char lbl_80239990[];

void* fn_80018A34(void*, u32);
void* fn_80057644(u32);
void __ct__7TObjectFP7TObject(void*, void*);
void __dt__7TObjectFv(void*, s32);
void __dl__FPv(void*);
void fn_800189A4(void*, void*);
void fn_8005BE6C(...);
void fn_8003C618(...);
void fn_8003BF04(...);
void dtor_8003C52C(...);
void dtor_8005BD3C(...);
void* fn_80150588(...);
void fn_8015BB08(...);
void fn_8015BBF8(...);
void fn_80150958(void*);
void fn_8005D5C8(...);
void* fn_8005EA04(void*);
void* fn_8005E410(void*, s32, void*);
f32 fn_800D7328(f32, f32, f32);
void fn_8_49630(...);
void fn_8_497B0(...);
int fn_8005B9F0(void*);
int fn_8005B8BC(void*);
s32 fn_8005B8D8(void*);
void fn_8003BC38(...);
void fn_8019ED68(...);
void fn_8019EC30(...);
void fn_8019EB94(...);
void fn_80194234(...);
void fn_80194294(...);
extern void fn_801942C0(s32 mode, void* verts, s32 count);
void fn_801AF914(s32);
void fn_800A7594(...);
void* fn_8005EC0C(void);
void* fn_801A4BBC(...);
void* fn_8_4B14C(void*, s16, void*, int, int, void*);
void* fn_8_4D0CC(void*, void*);
}

template <typename T> static inline T& field(void* object, int offset)
{
	return *(T*)((u8*)object + offset);
}

struct Vec3 {
	float x, y, z;
};

static void drawGoalRingModel(void* self);
extern "C" int fn_8_4AC50(void* self);

static void unlinkParticle(void* particle)
{
	void* owner = field<void*>(particle, 0x20);
	if (field<int>(particle, 0x2C) == 1)
		field<int>(owner, 0x38)--;
	void* first    = field<void*>(owner, 0x3C);
	void* previous = field<void*>(particle, 0x24);
	void* next     = field<void*>(particle, 0x28);
	if (first == particle) {
		field<void*>(owner, 0x3C) = next;
		if (next != NULL)
			field<void*>(next, 0x24) = previous;
	} else if (field<void*>(first, 0x24) == particle) {
		field<void*>(previous, 0x28) = NULL;
		field<void*>(first, 0x24)    = previous;
	} else {
		field<void*>(previous, 0x28) = next;
		field<void*>(next, 0x24)     = previous;
	}
	field<void*>(particle, 0x28) = NULL;
	field<void*>(particle, 0x24) = NULL;
}

extern "C" void fn_8_4A4CC(int group, int type, int subtype, void* data)
{
	if ((u32)group >= 4 || (u32)subtype >= 13)
		return;
	if (lbl_8_data_4E28[group] == NULL) {
		void* parent = lbl_8042C2A0 != NULL ? lbl_8042C2A0 : lbl_8042C110;
		void* object = fn_80018A34(lbl_8042C148, 0x40);
		if (object != NULL) {
			__ct__7TObjectFP7TObject(object, parent);
			field<void*>(object, 0x18) = lbl_8_data_4F54;
			field<void*>(object, 0)    = lbl_8_data_4F30;
			field<u16>(object, 0x1E)   = 0x40;
			field<int>(object, 0x2C)   = 0;
			field<float>(object, 0x34) = lbl_8_rodata_CB0;
			field<void*>(object, 0x3C) = NULL;
			field<int>(object, 0x30)   = group;
			lbl_8_data_4E28[group]     = object;
			field<int>(object, 0x28)   = 1;
			field<int>(object, 0x38)   = 0;
		}
	}
	if (lbl_8_data_4E28[group] != NULL) {
		void* particle = fn_80057644(0x3C);
		if (particle != NULL)
			fn_8_4B14C(particle, 1, lbl_8_data_4E28[group], type, subtype, data);
	}
}

extern "C" void fn_8_4AF64(float, float, float, void*);

extern "C" void fn_8_4A63C(void* self)
{
	if (self == NULL || field<s8>(lbl_8042C180, 0x21) != 0 || field<s8>(lbl_8042C180, 0x1A) == 0)
		return;
	int count = fn_8_4AC50(self);
	if (count <= 0)
		return;
	int oldCull, oldBlend, oldDepth;
	fn_80194294(6, &oldCull);
	fn_80194294(8, &oldBlend);
	fn_80194294(0x14, &oldDepth);
	fn_80194234(6, 1);
	fn_80194234(8, 1);
	fn_80194234(0x14, 1);
	fn_801AF914(1);
	float x = lbl_8_rodata_CB0;
	for (void* item = field<void*>(self, 0x3C); item != NULL; item = field<void*>(item, 0x28)) {
		if (field<int>(item, 0x2C) != 0)
			fn_8_4AF64(x, field<float>(self, 0x34), field<float>(item, 0x1C), item);
		x += lbl_8_rodata_CB0;
	}
	fn_80194234(6, oldCull);
	fn_80194234(8, oldBlend);
	fn_80194234(0x14, oldDepth);
}

extern "C" void fn_8_4AAE8(void* self)
{
	int count = 0;
	for (void* item = field<void*>(self, 0x3C); item != NULL; item = field<void*>(item, 0x28))
		count++;
	int group = field<int>(self, 0x30);
	if (count > 8 && lbl_8_data_4E28[group] == self)
		lbl_8_data_4E28[group] = NULL;
	int state = field<int>(self, 0x28);
	if (state == 1) {
		int timer = field<int>(self, 0x2C)++;
		if ((float)timer > lbl_8_rodata_CD8)
			field<int>(self, 0x28) = 2;
	} else if (state == 2) {
		field<float>(self, 0x34)
		    = fn_800D7328(field<float>(self, 0x34), lbl_8_rodata_CDC, lbl_8_rodata_CE0);
		if (field<float>(self, 0x34) <= lbl_8_rodata_CDC)
			field<int>(self, 0x28) = 3;
	} else if (state == 3) {
		field<u16>(self, 4) |= 1;
		if (lbl_8_data_4E28[group] == self)
			lbl_8_data_4E28[group] = NULL;
	}
}

extern "C" int fn_8_4AC50(void* self)
{
	int count = 0;
	for (void* item = field<void*>(self, 0x3C); item != NULL; item = field<void*>(item, 0x28))
		count++;
	return count;
}

extern "C" void fn_8_4AC70(void*, void* particle)
{
	unlinkParticle(particle);
}

extern "C" void fn_8_4AD0C(void* self, void* particle)
{
	void* first = field<void*>(self, 0x3C);
	if (first == NULL) {
		field<void*>(self, 0x3C)     = particle;
		field<void*>(particle, 0x28) = NULL;
		field<void*>(particle, 0x24) = particle;
	} else {
		void* tail                   = field<void*>(first, 0x24);
		field<void*>(tail, 0x28)     = particle;
		field<void*>(first, 0x24)    = particle;
		field<void*>(particle, 0x28) = NULL;
		field<void*>(particle, 0x24) = tail;
	}
	if (field<int>(particle, 0x2C) == 1)
		field<int>(self, 0x38)++;
}

extern "C" void* fn_8_4AD60(void* self, s16 flags)
{
	if (self != NULL) {
		field<void*>(self, 0x18) = lbl_8_data_4F54;
		int group                = field<int>(self, 0x30);
		if (lbl_8_data_4E28[group] == self)
			lbl_8_data_4E28[group] = NULL;
		while (field<void*>(self, 0x3C) != NULL) {
			void* particle = field<void*>(self, 0x3C);
			unlinkParticle(particle);
			__dl__FPv(particle);
		}
		__dt__7TObjectFv(self, 0);
		if (flags > 0)
			fn_800189A4(lbl_8042C148, self);
	}
	return self;
}

extern "C" void* fn_8_4AEB4(void* self, void* parent, int group)
{
	__ct__7TObjectFP7TObject(self, parent);
	field<void*>(self, 0x18) = lbl_8_data_4F54;
	field<void*>(self, 0)    = lbl_8_data_4F30;
	field<u16>(self, 0x1E)   = 0x40;
	field<int>(self, 0x2C)   = 0;
	field<float>(self, 0x34) = lbl_8_rodata_CB0;
	field<void*>(self, 0x3C) = NULL;
	field<int>(self, 0x30)   = group;
	if (lbl_8_data_4E28[group] == NULL)
		lbl_8_data_4E28[group] = self;
	field<int>(self, 0x28) = 1;
	field<int>(self, 0x38) = 0;
	return self;
}

extern "C" void fn_8_4AF64(float x, float y, float radius, void* particle)
{
	if (particle == NULL || field<int>(particle, 0x2C) == 0)
		return;
	float bounds[4] = { x - radius, x + radius, y - radius, y + radius };
	fn_801942C0(4, bounds, 4);
	fn_800A7594();
}
extern "C" void fn_8_4B064() { }

extern "C" void* fn_8_4B068(void* self, s16 flags)
{
	if (self != NULL) {
		unlinkParticle(self);
		if (flags > 0)
			__dl__FPv(self);
	}
	return self;
}

extern "C" void* fn_8_4B14C(
    void* self, s16 initialize, void* owner, int type, int subtype, void* data)
{
	if (initialize != 0) {
		field<void*>(self, 0x32) = (u8*)self + 0x30;
		field<void*>(self, 4)    = (u8*)self + 0x30;
		field<void*>(self, 0x36) = (u8*)self + 0x31;
		field<void*>(self, 8)    = (u8*)self + 0x31;
		field<void*>(self, 0)    = (u8*)self + 0x32;
		field<void*>(self, 0xC)  = (u8*)self + 0x3A;
	}
	field<void*>(self, 0x20)  = owner;
	field<int>(self, 0x10)    = subtype;
	field<int>(self, 0x18)    = 0;
	field<float>(self, 0x1C)  = lbl_8_rodata_CDC;
	field<void*>(self, 0x2C)  = data;
	field<int>(self, 0x14)    = 1;
	field<float>(owner, 0x34) = lbl_8_rodata_CB0;
	field<int>(owner, 0x2C)   = 0;
	field<int>(owner, 0x28)   = 1;
	fn_8_4AD0C(owner, self);
	field<int>(self, 0x10) = subtype;
	(void)type;
	return self;
}

extern "C" void fn_8_4B574()
{
	for (int i = 0; i < 4; i++) {
		if (lbl_8_data_4E28[i] != NULL)
			field<u16>(lbl_8_data_4E28[i], 4) |= 1;
		lbl_8_data_4E28[i] = NULL;
	}
	for (int i = 0; i < 13; i++)
		lbl_8_data_4EAC[i * 2] = NULL;
}

extern "C" void fn_8_4B684()
{
	for (int i = 0; i < 4; i++)
		lbl_8_data_4E28[i] = NULL;
	void* archive = fn_8005EC0C();
	for (int i = 0; i < 13; i++) {
		if (lbl_8_data_4EAC[i * 2 + 1] != NULL)
			lbl_8_data_4EAC[i * 2] = fn_801A4BBC(archive);
	}
}

extern "C" int fn_8_4B710()
{
	int mode = field<int>(lbl_80303DC8, 0x34);
	if (mode == 3)
		return 1;
	if ((mode == 1 || mode == 2) && field<s8>(lbl_8042C180, 0x28) == 1)
		return 1;
	return 0;
}

extern "C" void fn_8_4B7C8(void* self)
{
	if (field<int>(self, 0xB8) != 1 || field<s8>(lbl_8042C180, 0x22) != 0)
		return;
	if (fn_8_4B710())
		field<int>(self, 0xB8) = 2;
}

extern "C" void fn_8_4BA1C(void* self)
{
	if (field<s8>(lbl_8042C180, 0x20) == 0 && fn_8_4B710())
		drawGoalRingModel(self);
}

extern "C" void fn_8_4BB84(void* self)
{
	if (field<s8>(lbl_8042C180, 0x20) == 0 && !fn_8_4B710()
	    && field<float>(self, 0xD8) > lbl_8_rodata_CE8)
		drawGoalRingModel(self);
}

static void drawGoalRingModel(void* self)
{
	void* resource = field<void*>(self, 0xEC);
	if (resource == NULL)
		resource = field<void*>(self, 0xF0);
	if (resource == NULL)
		return;
	void* model = field<void*>(resource, 4);
	fn_8019ED68(field<float>(self, 0xDC), model, lbl_80239984, 0);
	Vec3 scale = { field<float>(self, 0xD8), lbl_8_rodata_CF0, field<float>(self, 0xD8) };
	fn_8019EC30(model, &scale, 2);
	fn_8019EB94(model, (u8*)self + 0xBC, 2);
}

extern "C" void fn_8_4BD90(void* self)
{
	void* placement = (u8*)self + 0x28;
	if (fn_8005B9F0(placement) || fn_8005B8BC(placement)) {
		field<u16>(self, 4) |= 1;
		return;
	}
	if (fn_8005B8D8(placement)) {
		field<Vec3>(self, 0xBC) = field<Vec3>(field<void*>(self, 0x28), 0);
		field<Vec3>(self, 0xC8) = field<Vec3>(field<void*>(self, 0x28), 0xC);
		drawGoalRingModel(self);
		return;
	}
	if (field<s8>(lbl_8042C180, 0x22) != 0)
		field<int>(self, 0xB8) = 2;
	int state = field<int>(self, 0xB8);
	if (state == 1) {
		if (field<s8>(lbl_8042C180, 0x1F) == 0) {
			field<float>(self, 0xDC) += lbl_8_rodata_CF8;
			field<float>(self, 0xE0) += lbl_8_rodata_CF0;
			field<float>(self, 0xE4) -= lbl_8_rodata_CFC;
			field<float>(self, 0xE8) += lbl_8_rodata_D00;
		}
		field<Vec3>(self, 0xAC) = field<Vec3>(self, 0x90);
		field<Vec3>(self, 0x90) = field<Vec3>(self, 0xBC);
		field<Vec3>(self, 0x9C) = field<Vec3>(self, 0xC8);
		fn_8003BC38((u8*)self + 0x30);
	} else if (state == 2) {
		if (field<float>(self, 0xD8) <= lbl_8_rodata_CE8)
			return;
		if (field<s8>(lbl_8042C180, 0x1F) == 0) {
			field<float>(self, 0xDC) += lbl_8_rodata_D08;
			field<float>(self, 0xE0) += lbl_8_rodata_D0C;
			field<float>(self, 0xE4) -= lbl_8_rodata_CF8;
			field<float>(self, 0xE8) += lbl_8_rodata_CF0;
		}
		field<float>(self, 0xD8)
		    = fn_800D7328(field<float>(self, 0xD8), lbl_8_rodata_CE8, lbl_8_rodata_D10);
	}
	drawGoalRingModel(self);
}

extern "C" void fn_8_4CD1C(void* self)
{
	drawGoalRingModel(self);
}

extern "C" void* fn_8_4CFB4(void* self, s16 flags)
{
	if (self != NULL) {
		field<void*>(self, 0x18) = lbl_8_data_5024;
		void** resources         = &field<void*>(self, 0xEC);
		for (int i = 0; i < 3; i++) {
			if (resources[i] != NULL) {
				fn_80150958(resources[i]);
				resources[i] = NULL;
			}
		}
		fn_80150958(field<void*>(self, 0xFC));
		field<void*>(self, 0xFC) = NULL;
		dtor_8003C52C((u8*)self + 0x30, 0);
		dtor_8005BD3C((u8*)self + 0x28, 0);
		__dt__7TObjectFv(self, 0);
		if (flags > 0)
			fn_800189A4(lbl_8042C148, self);
	}
	return self;
}

extern "C" void* fn_8_4D0CC(void* self, void* parent)
{
	__ct__7TObjectFP7TObject(self, parent);
	fn_8005BE6C((u8*)self + 0x28);
	fn_8003C618((u8*)self + 0x30);
	field<void*>(self, 0x18) = lbl_8_data_5024;
	field<void*>(self, 0)    = lbl_8_data_5014;
	field<u16>(self, 0x1E)   = 0x100;
	void* placement          = field<void*>(self, 0x28);
	field<Vec3>(self, 0xBC)  = field<Vec3>(placement, 0);
	field<Vec3>(self, 0xC8)  = field<Vec3>(placement, 0xC);
	field<float>(self, 0xD8) = lbl_8_rodata_CF0;
	field<float>(self, 0xDC) = lbl_8_rodata_CE8;
	field<float>(self, 0xE0) = lbl_8_rodata_CE8;
	field<float>(self, 0xE4) = lbl_8_rodata_CE8;
	field<float>(self, 0xE8) = lbl_8_rodata_CE8;
	field<int>(self, 0xB8)   = 1;
	field<void*>(self, 0xEC) = fn_80150588(lbl_8_bss_C08);
	field<void*>(self, 0xF0) = fn_80150588(lbl_8_bss_C0C);
	field<void*>(self, 0xF4) = fn_80150588(lbl_8_bss_C10);
	field<void*>(self, 0xFC) = fn_80150588(lbl_8_bss_C14);
	fn_8003BF04((u8*)self + 0x30, lbl_8_data_4FD4, 1, 5);
	field<u16>(self, 0x38) |= 0x40;
	return self;
}

extern "C" void fn_8_4D37C() { }

extern "C" void goalRingUnload()
{
	fn_8_49630();
	lbl_8_bss_C08 = lbl_8_bss_C0C = lbl_8_bss_C10 = lbl_8_bss_C14 = NULL;
	lbl_8_data_4FB8                                               = NULL;
}

extern "C" void goalRingLoad()
{
	lbl_8_bss_C08 = fn_8005EA04(lbl_8_data_5060);
	lbl_8_bss_C0C = fn_8005EA04(lbl_8_data_5074);
	lbl_8_bss_C10 = fn_8005EA04(lbl_8_data_5088);
	lbl_8_bss_C14 = fn_8005EA04(lbl_8_data_509C);
	if (lbl_8_bss_C14 != NULL)
		lbl_8_data_4FB8 = fn_8005E410(lbl_8_bss_C14, 0, 0);
	fn_8_497B0();
}

extern "C" void goalRingCreate()
{
	void* object = fn_80018A34(lbl_8042C148, 0x100);
	if (object != NULL)
		fn_8_4D0CC(object, lbl_8042C110);
}
