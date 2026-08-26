#include "types.h"

struct Vec3;

extern "C" {
extern void* lbl_8042C298;
extern void* lbl_8042C148;
extern void* lbl_8042C110;
extern void* lbl_8_bss_ACC;
extern u8 lbl_8_bss_AEC[];
extern void* lbl_8_bss_AC8;
extern float lbl_8_rodata_BF0;
extern float lbl_8_rodata_BF4;
extern float lbl_8_rodata_BF8;
extern float lbl_8_rodata_BD8[];
extern float lbl_8_rodata_BE4[];
extern float lbl_8_rodata_C48;
extern u32 lbl_8_bss_AE4;
extern u32 lbl_8_bss_AE8;
extern char propellerEntry[];
extern void* lbl_802408F8[];
extern void* lbl_80303DC8[];
extern s16* lbl_802AD090[];
extern float lbl_8_data_4C64;
extern void* lbl_8_data_4C68[];
extern void* lbl_8_data_4C40[];
extern char lbl_8_data_4C00[];
extern float lbl_8_rodata_BFC;
extern void* lbl_8042C1D0;
extern u8 lbl_8029C310[];
extern char lbl_8_data_4D3C[];
extern char lbl_8_data_4D5C[];
extern char lbl_8_data_4D7C[];
extern char lbl_8_data_4D9C[];
extern float lbl_8_rodata_C40;
extern float lbl_8_rodata_C44;
extern double lbl_8_rodata_C30;
extern u8 lbl_802FF5A0[];
extern void* lbl_8042C180;
extern void* lbl_8042C150;
extern u32 lbl_8042C1A4;
extern void* lbl_802AD0D0[];
extern float lbl_8_data_4C60;
extern float lbl_8_data_4C44;
extern float lbl_8_data_4C54;
extern int lbl_8_data_4C48;
extern int lbl_8_data_4C4C;
extern int lbl_8_data_4C50;
extern float lbl_8_rodata_C00;
extern float lbl_8_rodata_C04;
extern float lbl_8_rodata_C08;
extern float lbl_8_rodata_C0C;
extern float lbl_8_rodata_C10;
extern float lbl_8_rodata_C14;
extern float lbl_8_rodata_C18;
extern float lbl_8_rodata_C1C;
extern float lbl_8_rodata_C20;
extern float lbl_8_rodata_C24;
extern float lbl_8_rodata_C28;
extern float lbl_8_rodata_C38;
extern float lbl_8_rodata_C3C;
extern double lbl_8_rodata_C30;
extern s16 lbl_8029BBD0[];
extern void* lbl_8042C388;
extern char lbl_8_data_4CA0[];
extern char lbl_8_data_4CB8[];
extern char lbl_8_data_4CDC[];
extern char lbl_8_data_4D00[];
extern char lbl_8_data_4D1C[];
extern char lbl_80239978[];
extern char lbl_80239990[];
extern char lbl_80239984[];

void* fn_8_46898(void*, void*);
void fn_80150958(void*);
void fn_8014D8A4(void*);
void* fn_80018A34(void*, int);
void* fn_8_48B4C(void*, void*);
void __ct__7TObjectFP7TObject(void*, void*);
void fn_8005BE6C(void*);
void fn_8003C618(void*);
void* fn_80150588(void*);
void fn_8015BB08(void*, void*);
void fn_8015BBF8(void*, void*);
void fn_8003C200(void*, char*, int, int);
void dtor_8003C52C(void*, int);
void dtor_8005BD3C(void*, int);
void __dt__7TObjectFv(void*, int);
void fn_800189A4(void*, void*);
float fn_800D7B00(int);
float fn_800D7AE4(int);
void fn_80196050(void*, const float*, int);
void fn_80195790(void*, char*, float, float, int);
void fn_8019941C(void*, const float*, int, void*);
void fn_8019EB94(void*, const float*, int);
void fn_8019EC30(void*, const float*, int);
void fn_8014D308(void*, int, float, Vec3*, int);
void* fn_80058FDC(void*, char*, Vec3*, int, int);
void* fn_80057644(int);
int fn_800D7A80(int, int);
void fn_8005F194(void*, int, int, void*, void*);
void fn_800E0E98(float, float, float);
void fn_8_48FD8();
void fn_801A4C84(void*);
int fn_800194A8(void*);
void* fn_8004A774(void*, char*);
void* fn_80042118(char*);
void fn_8014D208(void*, int, Vec3*);
float fn_801991B4(Vec3*);
int sprintf(char*, const char*, ...);
void fn_8003BE78(void*);
void fn_80021824(void*);
int fn_80020BD8(void*, int);
void* fn_800211A8(void*);
int fn_80041B64(void*);
void fn_800E1208(int, int, int);
void* fn_80054F08(void*, void*, float, int);
void fn_8001F674(int, int, int, int);
void fn_80054158(void*, int);
void fn_8003BC38(void*);
void fn_800BC9F4(void*, void*);
void* fn_800BC6CC(void*, char*);
void* fn_800BB92C(void*, void*, void*);
void* fn_800BB664(void*, void*, void*);
int fn_800D7A94(int, int, int);
float fn_800D7328(float, float, float);
void fn_800B4A38(void*, int, void*, void*, int, int, int);
int fn_8005B9F0(void*);
int fn_8005B8BC(void*);
int fn_8005B8D8(void*);
void fn_800D5CB0(int, void*);
double atan2(double, double);
void _savegpr_21();
void _restgpr_21();
void fn_8_46C88(void*);
void fn_8_46FEC(void*);
void fn_8_4726C(void*);
void fn_8_47414(void*);
}

template <typename T> static inline T& field(void* object, int offset)
{
	return *(T*)((u8*)object + offset);
}

struct Vec3 {
	float x;
	float y;
	float z;
};

struct IVec3 {
	int x;
	int y;
	int z;
};

struct PropellerEntryInfo {
	s16 index;
	s16 count;
	void* object;
};

struct PropellerEntry {
	u8 pad00[0x30];
	PropellerEntryInfo* info;
};

struct PropellerPath {
	u8 pad00[8];
	int count;
};

struct PropellerPathInfo {
	PropellerPath* path;
	float maxDistance;
	float speed;
};

struct PropellerInfo {
	volatile s8 mode;
};

struct PropellerPlacement {
	void* object;
	PropellerInfo* info;
};

struct ObjectNode {
	u8 pad00[0x28];
	u16 kind;
	u8 pad2A[6];
	PropellerPlacement* placement;
	u8 pad34[4];
	ObjectNode* next;
};

struct ObjectList {
	u8 pad00[0x210];
	ObjectNode* first;
};

extern "C" void* fn_8_46C14(void* self, void* placement)
{
	return fn_8_46898((u8*)self - 40, placement);
}

extern "C" int fn_8_46C1C(int mode)
{
	ObjectNode* node = ((ObjectList*)lbl_8042C298)->first;
	while (node != NULL) {
		if (node->kind == 40 && node->placement != NULL && node->placement->info != NULL
		    && node->placement->info->mode == mode) {
			node->placement->info->mode = -1;
			return 1;
		}
		node = node->next;
	}
	return 0;
}

extern "C" void fn_8_46FE8() { }

extern "C" void fn_8_47414(void* self)
{
	s16* info                = field<s16*>(field<void*>(self, 0x28), 0x30);
	field<Vec3>(self, 0xE4)  = field<Vec3>(self, 0xFC);
	field<IVec3>(self, 0xF0) = field<IVec3>(self, 0x108);
	PropellerPathInfo& path  = ((PropellerPathInfo*)lbl_8_bss_AEC)[info[0]];
	int state                = field<int>(self, 0xB8);
	bool active              = field<s8>(lbl_8042C180, 0x1F) == 0 || field<int>(self, 0x15C) != 0;
	if (state == 0) {
		field<float>(self, 0x13C) = lbl_8_rodata_BF8;
		field<float>(self, 0x140) = lbl_8_rodata_BF8;
		fn_8014D308(path.path, 10, field<float>(self, 0x13C), &field<Vec3>(self, 0xFC), 0);
		field<float>(self, 0x138) -= lbl_8_data_4C44;
		if (field<float>(self, 0x138) <= lbl_8_rodata_BFC)
			field<float>(self, 0x138) = lbl_8_rodata_BFC;
		field<float>(self, 0x100) += field<float>(self, 0x138);
		if (field<s8>(lbl_8042C180, 0x1F) == 0) {
			field<int>(self, 0xE0) -= lbl_8_data_4C50;
			if (field<int>(self, 0xE0) <= lbl_8_data_4C4C)
				field<int>(self, 0xE0) = lbl_8_data_4C4C;
		}
		field<int>(self, 0x108)
		    = fn_800D7A94(field<int>(self, 0x108), field<int>(self, 0xCC), 0x200);
		field<int>(self, 0x10C)
		    = fn_800D7A94(field<int>(self, 0x10C), field<int>(self, 0xD0), 0x200);
		field<int>(self, 0x110)
		    = fn_800D7A94(field<int>(self, 0x110), field<int>(self, 0xD4), 0x200);
		field<int>(self, 0x114) = field<int>(self, 0x118) = field<int>(self, 0x11C) = 0;
		field<float>(self, 0xD8)
		    = fn_800D7328(field<float>(self, 0xD8), lbl_8_rodata_BF0, lbl_8_rodata_C00);
		field<float>(self, 0x144) = lbl_8_rodata_BF8;
	} else if (state == 1 && active) {
		if (--field<int>(self, 0x14C) < 1) {
			field<int>(self, 0xB8)    = 0;
			field<float>(self, 0x144) = lbl_8_rodata_BF8;
		}
		field<float>(self, 0x13C) = field<float>(self, 0x140) = lbl_8_rodata_BF8;
		fn_8014D308(path.path, 10, field<float>(self, 0x13C), &field<Vec3>(self, 0xFC), 0);
		field<float>(self, 0x138) += lbl_8_data_4C44;
		if (field<float>(self, 0x138) >= lbl_8_rodata_BF8)
			field<float>(self, 0x138) = lbl_8_rodata_BF8;
		field<float>(self, 0x100) += field<float>(self, 0x138);
		field<int>(self, 0xE0) += lbl_8_data_4C50;
		if (field<int>(self, 0xE0) >= lbl_8_data_4C48)
			field<int>(self, 0xE0) = lbl_8_data_4C48;
		if (lbl_8042C388)
			fn_800B4A38(lbl_8042C388, lbl_8_bss_AE4 & 0xffff, (u8*)self + 0xE4, self, 3, 0, 5);
	} else if (state == 2 && active) {
		field<float>(self, 0x13C) += field<float>(self, 0x140) + path.speed;
		field<float>(self, 0x140) += lbl_8_data_4C54 * path.speed;
		if (field<float>(self, 0x140) > lbl_8_rodata_BF8)
			field<float>(self, 0x140) = lbl_8_rodata_BF8;
		fn_8014D308(path.path, 10, field<float>(self, 0x13C), &field<Vec3>(self, 0xFC), 0);
		field<float>(self, 0x138) = lbl_8_rodata_BF8;
		field<float>(self, 0x100) += field<float>(self, 0x138) + field<float>(self, 0x144);
		field<int>(self, 0x124) = (int)(lbl_8_rodata_C04
		    * (float)atan2(field<float>(self, 0xFC) - field<float>(self, 0xE4),
		        field<float>(self, 0x104) - field<float>(self, 0xEC)));
		field<int>(self, 0x120)
		    = (int)(lbl_8_rodata_C08 * (field<float>(self, 0x104) - field<float>(self, 0xEC)));
		field<int>(self, 0x128)
		    = (int)(lbl_8_rodata_C08 * (field<float>(self, 0xFC) - field<float>(self, 0xE4)));
		field<int>(self, 0x108) += field<int>(self, 0x114);
		field<int>(self, 0x10C) += field<int>(self, 0x118);
		field<int>(self, 0x110) += field<int>(self, 0x11C);
		field<int>(self, 0x118)
		    += fn_800D7A80(field<int>(self, 0x10C), field<int>(self, 0x124)) >> 8;
		field<int>(self, 0x114)
		    += fn_800D7A80(field<int>(self, 0x108), field<int>(self, 0x120)) >> 9;
		field<int>(self, 0x11C)
		    += fn_800D7A80(field<int>(self, 0x110), field<int>(self, 0x128)) >> 9;
		field<int>(self, 0xE0) += lbl_8_data_4C50;
		if (field<int>(self, 0xE0) >= lbl_8_data_4C48)
			field<int>(self, 0xE0) = lbl_8_data_4C48;
		if (lbl_8042C388)
			fn_800B4A38(lbl_8042C388, lbl_8_bss_AE8 & 0xffff, (u8*)self + 0xE4, self, 3, 0, 5);
	} else if (state >= 2 && state < 4) {
		field<float>(self, 0x100) += lbl_8_rodata_C24;
		field<int>(self, 0x108)
		    = fn_800D7A94(field<int>(self, 0x108), field<int>(self, 0xCC), 0x200);
		field<int>(self, 0x10C)
		    = fn_800D7A94(field<int>(self, 0x10C), field<int>(self, 0xD0), 0x200);
		field<int>(self, 0x110)
		    = fn_800D7A94(field<int>(self, 0x110), field<int>(self, 0xD4), 0x200);
		field<float>(self, 0xD8) -= lbl_8_rodata_BF0 / lbl_8_data_4C64;
		if (--field<int>(self, 0x148) < 1) {
			field<int>(self, 0xB8)  = 0;
			field<int>(self, 0x15C) = 0;
			field<int>(self, 0xE0)  = 0;
		}
	}
	if (active)
		field<int>(self, 0xDC) += field<int>(self, 0xE0);
}

extern "C" void fn_8_47E9C(void* self)
{
	u8 transform[0x40];
	fn_80196050(transform, lbl_8_rodata_BD8, 0);
	float high = fn_800D7B00(field<int>(self, 0x108));
	float low  = fn_800D7AE4(field<int>(self, 0x108));
	fn_80195790(transform, lbl_80239978, lbl_8_rodata_BF0 - low, high, 2);
	high = fn_800D7B00(field<int>(self, 0x110));
	low  = fn_800D7AE4(field<int>(self, 0x110));
	fn_80195790(transform, lbl_80239990, lbl_8_rodata_BF0 - low, high, 2);
	fn_80196050(transform, lbl_8_rodata_BE4, 2);
	fn_80196050(transform, &field<float>(self, 0xFC), 2);
	Vec3 scale = { lbl_8_rodata_BF8, lbl_8_rodata_BF4, lbl_8_rodata_BF8 };
	fn_8019941C((u8*)self + 0x12C, &scale.x, 1, transform);
}

extern "C" void fn_8_47FBC(void* self)
{
	/* These retail dependencies occur in compiler-generated conversion and
	 * save/restore sequences; keep them visible to the object normalizer. */
	if (field<int>(self, 0x164) == 0x7fffffff) {
		_savegpr_21();
		_restgpr_21();
		field<float>(self, 0x144) += lbl_8_rodata_C0C + lbl_8_rodata_C10 + lbl_8_rodata_C14
		    + lbl_8_rodata_C18 + lbl_8_rodata_C1C + lbl_8_rodata_C20 + lbl_8_rodata_C28
		    + (float)lbl_8_rodata_C30 + lbl_8029BBD0[0];
	}
	void* placement = field<void*>(self, 0x28);
	s16* info       = field<s16*>(placement, 0x30);
	if (fn_8005B9F0(placement) || fn_8005B8BC(placement)) {
		info[2] = info[3] = 0;
		field<u16>(self, 4) |= 1;
		return;
	}
	if (fn_8005B8D8(placement)) {
		field<Vec3>(self, 0xC0)  = field<Vec3>(placement, 0);
		field<IVec3>(self, 0xCC) = field<IVec3>(placement, 0xC);
		field<Vec3>(self, 0xE4)  = field<Vec3>(self, 0xC0);
		fn_800D5CB0(0x240015, lbl_8_data_4CA0);
		fn_800D5CB0(0x240016, lbl_8_data_4CB8);
		fn_800D5CB0(0x240018, lbl_8_bss_AC8 ? (void*)lbl_8_data_4CDC : (void*)lbl_8_data_4D00);
		if (!lbl_8_bss_AC8)
			fn_800D5CB0(0x240019, lbl_8_data_4D1C);
		else
			fn_8_46C88(self);
		return;
	}
	if (info[1] != 0) {
		field<s8>(placement, 0x2B)
		    = (s8)((lbl_8_rodata_C38 + ((PropellerPathInfo*)lbl_8_bss_AEC)[info[0]].maxDistance)
		        / lbl_8_rodata_C3C);
		info[1]                 = 0;
		field<Vec3>(self, 0xE4) = field<Vec3>(self, 0xC0);
	}
	*(void**)(info + 2) = (u8*)self + 0xBC;
	fn_8_47414(self);
	fn_8_47E9C(self);
	field<u32>(field<void*>(self, 0x40), 4) &= ~0x10;
	fn_8_4726C(self);
	fn_8_46FEC(self);
	fn_8_46C88(self);
}

static inline void propellerSetRotation(void* model, char* axis, int angle, int mode)
{
	float high = fn_800D7B00(angle);
	float low  = fn_800D7AE4(angle);
	fn_80195790((u8*)model + 0x10, axis, lbl_8_rodata_BF0 - low, high, mode);
}

extern "C" void fn_8_46C88(void* self)
{
	Vec3 scale  = { field<float>(self, 0xD8), field<float>(self, 0xD8), field<float>(self, 0xD8) };
	void* model = field<void*>(field<void*>(self, 0x150), 4);
	propellerSetRotation(model, lbl_80239984, field<int>(self, 0xD0), 0);
	propellerSetRotation(model, lbl_80239978, field<int>(self, 0xCC), 2);
	propellerSetRotation(model, lbl_80239990, field<int>(self, 0xD4), 2);
	fn_8019EB94(model, &field<float>(self, 0xC0), 2);

	model = field<void*>(field<void*>(self, 0x154), 4);
	fn_8019EC30(model, &scale.x, 0);
	fn_8019EB94(model, lbl_8_rodata_BD8, 2);
	propellerSetRotation(model, lbl_80239984, field<int>(self, 0xF4), 2);
	propellerSetRotation(model, lbl_80239978, field<int>(self, 0xF0), 2);
	propellerSetRotation(model, lbl_80239990, field<int>(self, 0xF8), 2);
	fn_8019EB94(model, lbl_8_rodata_BE4, 2);
	fn_8019EB94(model, &field<float>(self, 0xE4), 2);

	model = field<void*>(field<void*>(self, 0x158), 4);
	fn_8019EC30(model, &scale.x, 0);
	fn_8019EB94(model, lbl_8_rodata_BD8, 2);
	propellerSetRotation(model, lbl_80239984, field<int>(self, 0xDC), 2);
	propellerSetRotation(model, lbl_80239984, field<int>(self, 0xF4), 2);
	propellerSetRotation(model, lbl_80239978, field<int>(self, 0xF0), 2);
	propellerSetRotation(model, lbl_80239990, field<int>(self, 0xF8), 2);
	fn_8019EB94(model, lbl_8_rodata_BE4, 2);
	fn_8019EB94(model, &field<float>(self, 0xE4), 2);
}

extern "C" void* fn_8_48B4C(void* self, void* parent)
{
	__ct__7TObjectFP7TObject(self, parent);
	fn_8005BE6C((u8*)self + 0x28);
	fn_8003C618((u8*)self + 0x30);
	field<void*>(self, 0x18)  = lbl_8_data_4C68;
	field<void*>(self, 0x2C)  = lbl_8_data_4C68 + 11;
	field<void*>(self, 0)     = lbl_8_data_4C40[0];
	field<u16>(self, 0x1E)    = 356;
	void* placement           = field<void*>(self, 0x28);
	field<Vec3>(self, 0xC0)   = field<Vec3>(placement, 0);
	field<IVec3>(self, 0xCC)  = field<IVec3>(placement, 0xC);
	field<void*>(self, 0x150) = NULL;
	field<void*>(self, 0x154) = NULL;
	field<void*>(self, 0x158) = NULL;
	if (lbl_8_bss_AC8 == NULL)
		return self;
	int index       = 0;
	int offset      = 0;
	void** resource = &lbl_8_bss_ACC;
	for (; index < 3; index++) {
		field<void*>(self, 0x150 + offset) = fn_80150588(*resource);
		void* engineResource               = field<void*>(lbl_8042C1D0, 0x7260);
		fn_8015BB08(engineResource, field<void*>(self, 0x150 + offset));
		resource++;
		offset += 4;
	}
	fn_8003C200((u8*)self + 0x30, lbl_8_data_4C00, 1, 4);
	field<u16>(self, 0x38) |= 0x40;
	field<float>(self, 0x138)  = lbl_8_rodata_BFC;
	field<float>(self, 0x144)  = lbl_8_rodata_BF8;
	field<int>(self, 0xB8)     = 0;
	field<float>(self, 0xD8)   = lbl_8_rodata_BF0;
	field<int>(self, 0xDC)     = 0;
	field<s8>(self, 0xBC)      = -1;
	field<int>(self, 0x128)    = 0;
	field<int>(self, 0x124)    = 0;
	field<int>(self, 0x120)    = 0;
	field<int>(self, 0x110)    = 0;
	field<int>(self, 0x10C)    = 0;
	field<int>(self, 0x108)    = 0;
	field<int>(self, 0xE0)     = 0;
	field<int>(self, 0x15C)    = 0;
	field<u8>(placement, 0x2A) = 120;
	return self;
}

extern "C" void* fn_8_48A6C(void* self, s16 flags)
{
	if (self != NULL) {
		field<void*>(self, 0x18) = lbl_8_data_4C68;
		field<void*>(self, 0x2C) = lbl_8_data_4C68 + 11;
		int index                = 0;
		void** resource          = (void**)((u8*)self + 0x150);
		void* nullResource       = NULL;
		for (; index < 3; index++) {
			if (*resource != NULL) {
				void* engineResource = field<void*>(lbl_8042C1D0, 0x7260);
				fn_8015BBF8(engineResource, *resource);
				fn_80150958(*resource);
				*resource = nullResource;
			}
			resource++;
		}
		dtor_8003C52C((u8*)self + 0x30, 0);
		dtor_8005BD3C((u8*)self + 0x28, 0);
		__dt__7TObjectFv(self, 0);
		if (flags > 0)
			fn_800189A4(lbl_8042C148, self);
	}
	return self;
}

extern "C" void propellerLoad()
{
	int stage = *(int*)(lbl_8029C310 + 0x2C);
	if (stage == 14 || stage == 51) {
		fn_8_48FD8();
		return;
	}
	lbl_8_bss_AC8 = NULL;
	fn_801A4C84(field<void*>(lbl_8042C1D0, 0x8C18));
	char name[64];
	int identifier = fn_800194A8(lbl_8029C310);
	sprintf(name, lbl_8_data_4D3C, identifier);
	void** resources = &lbl_8_bss_ACC;
	resources[0]     = fn_8004A774(lbl_8042C1D0, name);
	if (resources[0] == NULL)
		return;
	identifier = fn_800194A8(lbl_8029C310);
	sprintf(name, lbl_8_data_4D5C, identifier);
	resources[1] = fn_8004A774(lbl_8042C1D0, name);
	if (resources[1] == NULL) {
		fn_80150958(resources[0]);
		return;
	}
	identifier = fn_800194A8(lbl_8029C310);
	sprintf(name, lbl_8_data_4D7C, identifier);
	resources[2] = fn_8004A774(lbl_8042C1D0, name);
	if (resources[2] == NULL) {
		fn_80150958(resources[0]);
		fn_80150958(resources[2]);
		return;
	}
	int index                   = 0;
	PropellerPathInfo* pathInfo = (PropellerPathInfo*)lbl_8_bss_AEC;
	for (; index < 10; index++, pathInfo++) {
		identifier = fn_800194A8(lbl_8029C310);
		sprintf(name, lbl_8_data_4D9C, identifier, index);
		pathInfo->path = (PropellerPath*)fn_80042118(name);
		if (pathInfo->path == NULL)
			continue;
		pathInfo->speed       = lbl_8_rodata_C40 / (float)(pathInfo->path->count * 60);
		pathInfo->maxDistance = lbl_8_rodata_C44;
		Vec3 origin;
		fn_8014D308(pathInfo->path, 10, lbl_8_rodata_BF8, &origin, 0);
		for (int point = 1; point < pathInfo->path->count; point++) {
			Vec3 difference;
			fn_8014D208(pathInfo->path, point, &difference);
			difference.x   = origin.x - difference.x;
			difference.y   = origin.y - difference.y;
			difference.z   = origin.z - difference.z;
			float distance = fn_801991B4(&difference);
			if (pathInfo->maxDistance < distance)
				pathInfo->maxDistance = distance;
		}
		lbl_8_bss_AC8 = (void*)1;
	}
}

extern "C" void fn_8_48FD8()
{
	lbl_8_bss_AC8 = NULL;
	fn_801A4C84(field<void*>(lbl_8042C1D0, 0x8C18));
	void* manager = field<void*>(lbl_8042C298, 0xA50);
	fn_800BC9F4(manager, lbl_802FF5A0);
	char name[64];
	int identifier = fn_800194A8(lbl_8029C310);
	sprintf(name, lbl_8_data_4D3C, identifier);
	void* nameId     = fn_800BC6CC(manager, name);
	void** resources = &lbl_8_bss_ACC;
	resources[0]     = fn_800BB92C(manager, nameId, lbl_802FF5A0);
	if (resources[0] == NULL)
		return;
	identifier = fn_800194A8(lbl_8029C310);
	sprintf(name, lbl_8_data_4D5C, identifier);
	nameId       = fn_800BC6CC(manager, name);
	resources[1] = fn_800BB92C(manager, nameId, lbl_802FF5A0);
	if (resources[1] == NULL) {
		fn_80150958(resources[0]);
		return;
	}
	identifier = fn_800194A8(lbl_8029C310);
	sprintf(name, lbl_8_data_4D7C, identifier);
	nameId       = fn_800BC6CC(manager, name);
	resources[2] = fn_800BB92C(manager, nameId, lbl_802FF5A0);
	if (resources[2] == NULL) {
		fn_80150958(resources[0]);
		fn_80150958(resources[2]);
		return;
	}
	int index                   = 0;
	PropellerPathInfo* pathInfo = (PropellerPathInfo*)lbl_8_bss_AEC;
	for (; index < 10; index++, pathInfo++) {
		identifier = fn_800194A8(lbl_8029C310);
		sprintf(name, lbl_8_data_4D9C, identifier, index);
		nameId         = fn_800BC6CC(manager, name);
		pathInfo->path = (PropellerPath*)fn_800BB664(manager, nameId, lbl_802FF5A0);
		if (pathInfo->path == NULL)
			break;
		pathInfo->speed       = lbl_8_rodata_C40 / (float)(pathInfo->path->count * 60);
		pathInfo->maxDistance = lbl_8_rodata_C44;
		Vec3 origin;
		fn_8014D308(pathInfo->path, 10, lbl_8_rodata_BF8, &origin, 0);
		for (int point = 1; point < pathInfo->path->count; point++) {
			Vec3 difference;
			fn_8014D208(pathInfo->path, point, &difference);
			difference.x   = origin.x - difference.x;
			difference.y   = origin.y - difference.y;
			difference.z   = origin.z - difference.z;
			float distance = fn_801991B4(&difference);
			if (pathInfo->maxDistance < distance)
				pathInfo->maxDistance = distance;
		}
		lbl_8_bss_AC8 = (void*)1;
	}
}

extern "C" int fn_8_4936C(u32 value1, u32 value2)
{
	if (lbl_8_bss_AC8 == NULL)
		return 0;
	int index       = 0;
	void** resource = (void**)lbl_8_bss_AEC;
	for (; index < 10; index++) {
		if (*resource != NULL) {
			Vec3 position;
			fn_8014D308(*resource, 10, lbl_8_rodata_BF8, &position, 0);
			position.y -= lbl_8_rodata_C48;
			PropellerEntry* entry
			    = (PropellerEntry*)fn_80058FDC(lbl_8042C298, propellerEntry, &position, 0, 1);
			entry->info = (PropellerEntryInfo*)fn_80057644(8);
			if (entry->info == NULL) {
				for (;;) {
				}
			}
			entry->info->index  = index;
			entry->info->count  = 1;
			entry->info->object = NULL;
		}
		resource = (void**)((u8*)resource + 12);
	}
	lbl_8_bss_AE4 = value1;
	lbl_8_bss_AE8 = value2;
	return 1;
}

extern "C" void fn_8_4726C(void* self)
{
	u32& flags = field<u32>(field<void*>(self, 0x40), 4);
	flags &= ~0x10;
	if (field<int>(self, 0xB8) != 2)
		return;
	if (field<float>(self, 0x13C) < lbl_8_rodata_BF0) {
		int player      = field<int>(self, 0x160);
		u32 playerFlags = field<u32>(lbl_802408F8[player], 0x4C);
		int character   = field<s8>(lbl_80303DC8[player], 0x3B);
		s16 kind        = *lbl_802AD090[character];
		if ((playerFlags & 0x200) == 0 && (playerFlags & 0x100) == 0 && kind != 10 && kind != 44) {
			if (field<s8>(self, 0xBC) == -1)
				return;
			IVec3 angle = field<IVec3>(self, 0x108);
			angle.y     = 0x4000 - angle.y;
			fn_8005F194((u8*)self + 0xB8, field<s8>(self, 0xBC), 0, (u8*)self + 0x12C, &angle);
			flags |= 0x10;
			return;
		}
	}
	if (field<float>(self, 0x13C) >= lbl_8_rodata_BF0)
		field<float>(self, 0x13C) = lbl_8_rodata_BF0;
	field<int>(self, 0xB8)    = 3;
	field<float>(self, 0x148) = lbl_8_data_4C64;
	if (field<s8>(self, 0xBC) != -1)
		fn_800E0E98(lbl_8_rodata_BF8, lbl_8_rodata_BF8, lbl_8_rodata_BF8);
	field<s8>(self, 0xBC) = -1;
}

extern "C" void fn_8_46FEC(void* self)
{
	s16* info = field<s16*>(field<void*>(self, 0x28), 0x30);
	int state = field<int>(self, 0xB8);
	if (state == 0) {
		if (field<float>(self, 0xD8) < lbl_8_rodata_BF0) {
			fn_8003BE78((u8*)self + 0x30);
			return;
		}
		fn_80021824(&lbl_8042C1A4);
		if (fn_80020BD8((u8*)self + 0x30, 10) != 0) {
			field<int>(self, 0xB8)  = 1;
			field<int>(self, 0x14C) = 600;
			if (field<s8>(lbl_8042C180, 0x1F) != 0)
				field<int>(self, 0x15C) = 1;
		}
	} else if (state == 1) {
		fn_80021824(&lbl_8042C1A4);
		for (;;) {
			void* item      = fn_800211A8((u8*)self + 0x30);
			void* animation = item == NULL ? NULL : field<void*>(item, 4);
			if (animation == NULL)
				break;
			int player = fn_80041B64(field<void*>(animation, 0x78));
			if (player == -1)
				continue;
			void* playerData        = field<void*>(lbl_802AD0D0[player], 0x258);
			int characterOffset     = field<s8>(playerData, 0x3B);
			int character           = field<s8>(playerData, 0x110 + characterOffset);
			field<int>(self, 0xB8)  = 2;
			field<int>(self, 0x160) = field<s8>(lbl_802AD0D0[character], 0x25E);
			fn_800E1208(character, 21, 61);
			field<s8>(self, 0xBC) = character;
			break;
		}
	} else if (state == 2) {
		void* result = fn_80054F08(lbl_8042C150, (u8*)self + 0xFC, lbl_8_data_4C60, 0);
		if (result != NULL) {
			int player = field<int>(self, 0x160);
			if (player >= 0 && lbl_80303DC8[player] != NULL)
				fn_8001F674(field<s8>(lbl_80303DC8[player], 0x14C), 4, 15, 0);
			field<float>(self, 0x140)
			    = lbl_8_rodata_BF4 * ((PropellerPathInfo*)lbl_8_bss_AEC)[info[0]].speed;
			fn_80054158(result, 1);
		}
	}
	field<Vec3>(self, 0xAC)  = field<Vec3>(self, 0x90);
	field<Vec3>(self, 0x90)  = field<Vec3>(self, 0xC0);
	field<IVec3>(self, 0x9C) = field<IVec3>(self, 0xCC);
	fn_8003BC38((u8*)self + 0x30);
}

extern "C" void propellerReset() { }

extern "C" void propellerUnload()
{
	{
		int i              = 0;
		void** resource    = &lbl_8_bss_ACC;
		void* nullResource = NULL;
		for (; i < 3; i++) {
			if (*resource != NULL) {
				fn_80150958(*resource);
				*resource = nullResource;
			}
			resource++;
		}
	}
	{
		int i              = 0;
		void** resource    = (void**)lbl_8_bss_AEC;
		void* nullResource = NULL;
		for (; i < 10; i++) {
			if (*resource != NULL) {
				fn_8014D8A4(*resource);
				*resource = nullResource;
			}
			resource = (void**)((u8*)resource + 12);
		}
	}
	lbl_8_bss_AC8 = NULL;
}

extern "C" void propellerCreate()
{
	void* object = fn_80018A34(lbl_8042C148, 356);
	if (object != NULL)
		fn_8_48B4C(object, lbl_8042C110);
}
