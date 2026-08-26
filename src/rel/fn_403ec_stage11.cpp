#include "types.h"
#include "dolphin/types.h"

#pragma force_active on

struct Vec3 {
	f32 x;
	f32 y;
	f32 z;
};

struct Angle3 {
	s32 x;
	s32 y;
	s32 z;
};

struct SourceInfo {
	Vec3 offset;
	u8 index;
	s8 type;
};

struct SourceTransform {
	Vec3 position;
	Angle3 rotation;
	u8 pad18[0x14];
	SourceInfo* info;
};

struct RuntimeState {
	u8 pad00[0x28];
	SourceTransform* source;
	u8 pad2C[0x90];
	u8 index;
	u8 padBD[3];
	Vec3 position;
	Angle3 rotation;
	Vec3 offset;
	void* resource;
	u8 padE8[0x14];
	s32 type;
};

extern "C" {
extern const u32 lbl_8_rodata_A80[3]      = { 0, 0x3FC00000, 0 };
DECL_SECT(".rodata") f32 lbl_8_rodata_A8C = 3.0f;
DECL_SECT(".rodata") f32 lbl_8_rodata_A90 = 20.0f;
DECL_SECT(".rodata") f32 lbl_8_rodata_A94 = 0.0f;
DECL_SECT(".rodata") f32 lbl_8_rodata_A98 = 1.0f;
DECL_SECT(".rodata") f32 lbl_8_rodata_A9C = 0.05f;
DECL_SECT(".rodata") f32 lbl_8_rodata_AA0 = 7.0f;
DECL_SECT(".rodata") f32 lbl_8_rodata_AA4 = 0.5f;

char lbl_8_data_4368[] ATTRIBUTE_ALIGN(8) = "o_on";
char lbl_8_data_4370[]                    = "o_on2";
char lbl_8_data_4378[]                    = "o_on3";
char lbl_8_data_4380[]                    = "o_off";
char lbl_8_data_4388[]                    = "o_off2";
char lbl_8_data_4390[]                    = "o_off3";
char* lbl_8_data_4398[]                   = {
	lbl_8_data_4368,
	lbl_8_data_4370,
	lbl_8_data_4378,
	lbl_8_data_4380,
	lbl_8_data_4388,
	lbl_8_data_4390,
};
f32 lbl_8_data_43B0       = 0.4f;
f32 lbl_8_data_43B4       = 0.48f;
f32 lbl_8_data_43B8       = 0.64f;
f32 lbl_8_data_43BC       = 0.8f;
f32 lbl_8_data_43C0       = 0.08f;
char lbl_8_data_43C4[]    = "Scale X";
char lbl_8_data_43CC[]    = "Scale Y";
char lbl_8_data_43D4[]    = "Scale Z";
char lbl_8_data_43DC[]    = "No ID Referenced as 0";
char lbl_8_data_43F4[]    = "direction : up";
char* caseObjFieldNames[] = {
	lbl_8_data_43C4,
	lbl_8_data_43CC,
	lbl_8_data_43D4,
	lbl_8_data_43DC,
	lbl_8_data_43F4,
};
char lbl_8_data_4418[]  = "direction : down";
char* lbl_8_data_442C[] = { lbl_8_data_43F4, lbl_8_data_4418 };
u32 lbl_8_data_4434[]   = {
	0x1304F3E0,
	0,
	0,
	0x40200000,
	0,
	0x41700000,
	0x40A00000,
	0,
	0,
	0,
	0,
	0,
	0x0004F3E0,
	0x10380000,
	0,
	0x3FC00000,
	0,
	0x41200000,
	0x3FC00000,
	0x41200000,
	0,
	0,
	0,
	0,
	0x0004F3E0,
	0x00300000,
	0x41100000,
	0x41200000,
	0,
	0x3F800000,
	0x41200000,
	0x41200000,
	0,
	0,
	0,
	0,
	0x0004F3E0,
	0x00300000,
	0xC1100000,
	0x41200000,
	0,
	0x3F800000,
	0x41200000,
	0x41200000,
	0,
	0,
	0,
	0,
	0x0004F3E0,
	0x00300000,
	0,
	0x41200000,
	0x41100000,
	0x41200000,
	0x41200000,
	0x3F800000,
	0,
	0,
	0,
	0,
	0x0004F3E0,
	0x00300000,
	0,
	0x41200000,
	0xC1100000,
	0x41200000,
	0x41200000,
	0x3F800000,
	0,
	0,
	0,
	0,
	0x0004F3E0,
	0x00200000,
	0,
	0x418C0000,
	0,
	0x41200000,
	0x40200000,
	0x41200000,
	0,
	0,
	0,
	0,
};

void* lbl_8_bss_988;
void* lbl_8_bss_98C;
u32 lbl_8_bss_990;
u32 lbl_8_bss_994;
void* lbl_8_bss_998;
void* lbl_8_bss_99C;
void* lbl_8_bss_9A0;
void* lbl_8_bss_9A4;
void* lbl_8_bss_9A8;
void* lbl_8_bss_9AC;
u8 caseObjEntry[0x2C];
s32 lbl_8_bss_9DC;
extern u8 lbl_8042C1D0[];
extern u8 lbl_8042C180[];
extern u8 lbl_8042C298[];
extern u8 lbl_8042C388[];
extern u8 lbl_80239984[];
extern u8 lbl_80239990[];

f32 fn_800D7B00(s32 range);
u32 __cvt_fp2unsigned(f32 value);
void fn_8015498C(void* context, void* entry);
void fn_8014FF2C(void* resource);
void fn_8015BBF8(void* manager, void* resource);
void fn_80150958(void* resource);
void* fn_80150588(void* descriptor);
void fn_8015BB08(void* manager, void* resource);
void fn_80021384(void* object);
void fn_80195790(void* transform, void* matrix, f32 first, f32 second, s32 axis);
void fn_8019E880(void* object);
void fn_8019EC30(void* object, Vec3* value, s32 mode);
void fn_8019EB94(void* object, Vec3* value, s32 mode);
void* fn_8005DF98(void* object, void* child);
f32 fn_800D7AE4(s32 range);
s32 fn_8005B9F0(void* object);
s32 fn_8005B8BC(void* object);
s32 fn_8005B8D8(void* object);
s32 objGroupAllActive(s32 index);
s32 fn_80100C88(s32 index);
void fn_800B4A38(void* sound, s32 id, Vec3* position, s32, s32, s32, s32);
f32 fn_800D7328(f32 value, f32 target, f32 step);
void fn_8003BC38(void* object);
}

extern "C" void fn_8_403EC(RuntimeState* self)
{
	u8* game = *(u8**)lbl_8042C180;
	if ((s8)game[0x20] != 0)
		return;

	s32 stage = *(s32*)(game + 0x30);
	if (lbl_8_bss_9DC != stage)
		lbl_8_bss_9DC = stage;

	void* entry;
	switch (*(s32*)((u8*)self + 0xB8)) {
		case 1: {
			f32 random = fn_800D7B00(stage << 11);
			u32 index  = __cvt_fp2unsigned(lbl_8_rodata_A8C * random + lbl_8_rodata_A8C) >> 1;
			switch (index) {
				case 0:
					entry = lbl_8_bss_9A4;
					break;
				case 1:
					entry = lbl_8_bss_9AC;
					break;
				default:
					entry = lbl_8_bss_9A8;
					break;
			}
			break;
		}
		case 2:
		case 3: {
			f32 random = fn_800D7B00(stage * 3072);
			u32 index  = __cvt_fp2unsigned(lbl_8_rodata_A8C * random + lbl_8_rodata_A8C) >> 1;
			switch (index) {
				case 0:
					entry = lbl_8_bss_998;
					break;
				case 1:
					entry = lbl_8_bss_9A0;
					break;
				default:
					entry = lbl_8_bss_99C;
					break;
			}
			break;
		}
	}
	fn_8015498C(lbl_8_bss_98C, entry);
	fn_8014FF2C(self->resource);
}

extern "C" void fn_8_40868(RuntimeState* self);
extern "C" void fn_8_40B34(RuntimeState* self);

extern "C" void fn_8_40554(RuntimeState* self)
{
	if (fn_8005B9F0(&self->source) != 0 || fn_8005B8BC(&self->source) != 0) {
		*(u16*)((u8*)self + 4) |= 1;
		return;
	}
	if (fn_8005B8D8(&self->source) != 0) {
		SourceTransform* source = self->source;
		SourceInfo* info        = source->info;
		self->position          = source->position;
		self->rotation          = self->source->rotation;
		self->rotation.x        = 0;
		self->rotation.z        = 0;
		self->index             = info->index;
		f32 base                = lbl_8_rodata_A90;
		self->offset.x          = base + info->offset.x;
		self->offset.y          = base + info->offset.y;
		self->offset.z          = base + info->offset.z;
		self->type              = info->type;
		fn_8_40868(self);
		return;
	}

	s32 state = *(s32*)((u8*)self + 0xB8);
	switch (state) {
		case 1: {
			u8* groups      = *(u8**)lbl_8042C298;
			s32 groupOffset = self->index << 2;
			groups += groupOffset;
			if (*(void**)(groups + 0x30) != NULL && objGroupAllActive(self->index) == 0)
				break;
			if (fn_80100C88(self->index) == 0)
				break;
			void* sound = *(void**)lbl_8042C388;
			if (sound != NULL)
				fn_800B4A38(sound, 0x105D, &self->position, 1, 1, 0, 0);
			*(s32*)((u8*)self + 0xB8) = 2;
			break;
		}
		case 2: {
			*(f32*)((u8*)self + 0xE8)
			    = fn_800D7328(*(f32*)((u8*)self + 0xE8), lbl_8_rodata_A94, lbl_8_data_43C0);
			f32 target  = lbl_8_rodata_A94;
			f32 current = *(f32*)((u8*)self + 0xE8);
			if (target == current) {
				*(f32*)((u8*)self + 0xEC)
				    = fn_800D7328(*(f32*)((u8*)self + 0xEC), lbl_8_rodata_A94, lbl_8_data_43B0);
				*(f32*)((u8*)self + 0xF0)
				    = fn_800D7328(*(f32*)((u8*)self + 0xF0), lbl_8_rodata_A94, lbl_8_data_43B4);
				*(f32*)((u8*)self + 0xF4)
				    = fn_800D7328(*(f32*)((u8*)self + 0xF4), lbl_8_rodata_A94, lbl_8_data_43B8);
				*(f32*)((u8*)self + 0xF8)
				    = fn_800D7328(*(f32*)((u8*)self + 0xF8), lbl_8_rodata_A94, lbl_8_data_43BC);
				if (lbl_8_rodata_A94
				    == *(f32*)((u8*)self + 0xEC) + *(f32*)((u8*)self + 0xF0)
				        + *(f32*)((u8*)self + 0xF4) + *(f32*)((u8*)self + 0xF8))
					*(s32*)((u8*)self + 0xB8) = 3;
			}
			fn_8_40B34(self);
			break;
		}
		case 3:
			break;
		default:
			break;
	}
	fn_8_40868(self);

	state = *(s32*)((u8*)self + 0xB8);
	switch (state) {
		case 1:
		case 2:
		case 3:
			*(Vec3*)((u8*)self + 0xAC)   = *(Vec3*)((u8*)self + 0x90);
			*(Vec3*)((u8*)self + 0x90)   = self->position;
			*(Angle3*)((u8*)self + 0x9C) = self->rotation;
			fn_8003BC38((u8*)self + 0x30);
			break;
		default:
			break;
	}
}

extern "C" void fn_8_40868(RuntimeState* self)
{
	if (self->resource == NULL)
		return;

	u8* root   = *(u8**)((u8*)self->resource + 4);
	f32 second = fn_800D7B00(*(s32*)((u8*)self + 0xD0));
	f32 first  = lbl_8_rodata_A98 - fn_800D7AE4(*(s32*)((u8*)self + 0xD0));
	fn_80195790(root + 0x10, lbl_80239984, first, second, 0);
	fn_8019E880(root);

	Vec3 value;
	value.x = lbl_8_rodata_A9C * self->offset.x;
	value.y = lbl_8_rodata_A9C * self->offset.y;
	value.z = lbl_8_rodata_A9C * self->offset.z;
	fn_8019EC30(root, &value, 2);
	fn_8019EB94(root, &self->position, 2);

	if (self->type == 1) {
		second = fn_800D7B00(0x8000);
		first  = lbl_8_rodata_A98 - fn_800D7AE4(0x8000);
		fn_80195790(root + 0x10, lbl_80239990, first, second, 1);
		fn_8019E880(root);
	}

	root = (u8*)fn_8005DF98(root, NULL);
	Vec3 offset;
	offset.z = lbl_8_rodata_A94;
	offset.x = lbl_8_rodata_A94;
	u8* node = (u8*)fn_8005DF98(root, NULL);
	offset.y = *(f32*)((u8*)self + 0xF8);
	fn_8019EB94(node, &offset, 0);
	node     = (u8*)fn_8005DF98(root, node);
	offset.y = *(f32*)((u8*)self + 0xF4);
	fn_8019EB94(node, &offset, 0);
	node     = (u8*)fn_8005DF98(root, node);
	offset.y = *(f32*)((u8*)self + 0xF0);
	fn_8019EB94(node, &offset, 0);
	node     = (u8*)fn_8005DF98(root, node);
	offset.y = *(f32*)((u8*)self + 0xEC);
	fn_8019EB94(node, &offset, 0);

	u8* parent = node;
	u8* child  = (u8*)fn_8005DF98(parent, NULL);
	Vec3 childScale;
	childScale.x = *(f32*)((u8*)self + 0xE8);
	childScale.z = lbl_8_rodata_A98;
	childScale.y = lbl_8_rodata_A98;
	node         = (u8*)fn_8005DF98(parent, child);
	Vec3 childPosition;
	childPosition.x = *(f32*)(node + 0x40);
	childPosition.y = *(f32*)(node + 0x44);
	childPosition.z = *(f32*)(node + 0x48);
	fn_8019EC30(node, &childScale, 0);
	fn_8019EB94(node, &childPosition, 2);

	node            = (u8*)fn_8005DF98(parent, node);
	childPosition.x = *(f32*)(node + 0x40);
	childPosition.y = *(f32*)(node + 0x44);
	childPosition.z = *(f32*)(node + 0x48);
	fn_8019EC30(node, &childScale, 0);
	fn_8019EB94(node, &childPosition, 2);

	node     = (u8*)fn_8005DF98(root, parent);
	offset.y = lbl_8_rodata_A94;
	fn_8019EB94(node, &offset, 0);
}

extern "C" void fn_8_40B34(RuntimeState* self)
{
#define MODEL (*(u8**)((u8*)self + 0x40))
	s32 mode = *(s32*)((u8*)self + 0xB8);
	switch (mode) {
		case 2:
		case 3: {
			*(u32*)(MODEL + 4) |= 0x10;

			f32 x = lbl_8_rodata_A9C * self->offset.x;
			f32 y = lbl_8_rodata_A9C * self->offset.y;
			f32 z = lbl_8_rodata_A9C * self->offset.z;
			{
				u8* firstPart = MODEL;
				*(u32*)(firstPart + 0x34) &= ~0x10;
				f32* templateData         = (f32*)lbl_8_data_4434;
				*(f32*)(firstPart + 0x38) = templateData[14] * x;
				*(f32*)(firstPart + 0x3C) = templateData[15] * y;
				if (self->type == 1)
					*(f32*)(firstPart + 0x3C) = -*(f32*)(firstPart + 0x3C);
				*(f32*)(firstPart + 0x40) = templateData[16] * z;
				*(f32*)(firstPart + 0x44) = templateData[17] * x;
				*(f32*)(firstPart + 0x48) = templateData[18] * y;
				*(f32*)(firstPart + 0x4C) = templateData[19] * z;
			}

			f32 adjusted = (lbl_8_rodata_AA0 + *(f32*)((u8*)self + 0xEC)) / lbl_8_rodata_A90;
			y *= adjusted;
			s32 offset  = 0x60;
			f32* source = (f32*)((u8*)lbl_8_data_4434 + 0x60);
			for (s32 i = 0; i < 5; ++i) {
				u8* part = MODEL + offset;
				*(u32*)(part + 4) &= ~0x10;
				*(f32*)(part + 8)   = source[2] * x;
				*(f32*)(part + 0xC) = source[3] * y;
				if (self->type == 1)
					*(f32*)(part + 0xC) = -*(f32*)(part + 0xC);
				*(f32*)(part + 0x10) = source[4] * z;
				*(f32*)(part + 0x14) = source[5] * x;
				*(f32*)(part + 0x18) = source[6] * y;
				*(f32*)(part + 0x1C) = source[7] * z;
				offset += 0x30;
				source += 0xC;
			}
			f32 zero = lbl_8_rodata_A94;
			if (zero == *(f32*)((u8*)self + 0xE8))
				*(s16*)((u8*)self + 0x3A) = 6;
			else
				*(s16*)((u8*)self + 0x3A) = 7;
			break;
		}
		default: {
			*(f32*)(MODEL + 0xC) = lbl_8_rodata_AA4 * self->offset.y;
			if (self->type == 1)
				*(f32*)(MODEL + 0xC) = -*(f32*)(MODEL + 0xC);
			f32 scale             = lbl_8_rodata_AA4;
			*(f32*)(MODEL + 0x14) = scale * self->offset.x;
			*(f32*)(MODEL + 0x18) = scale * self->offset.y;
			*(f32*)(MODEL + 0x1C) = scale * self->offset.z;
			*(u32*)(MODEL + 4) &= ~0x10;
			*(u32*)(MODEL + 0x34) |= 0x10;
			*(u32*)(MODEL + 0x64) |= 0x10;
			*(u32*)(MODEL + 0x94) |= 0x10;
			*(u32*)(MODEL + 0xC4) |= 0x10;
			*(u32*)(MODEL + 0xF4) |= 0x10;
			*(u32*)(MODEL + 0x124) |= 0x10;
			*(s16*)((u8*)self + 0x3A) = 1;
			break;
		}
	}
	fn_80021384((u8*)self + 0x30);
#undef MODEL
}

extern "C" void fn_8_40DF8(RuntimeState* self)
{
	SourceTransform* source  = self->source;
	SourceInfo* info         = source->info;
	self->position           = source->position;
	self->rotation           = self->source->rotation;
	*(u32*)&self->rotation.x = 0;
	*(u32*)&self->rotation.z = 0;
	self->index              = info->index;
	f32 base                 = lbl_8_rodata_A90;
	self->offset.x           = base + info->offset.x;
	self->offset.y           = base + info->offset.y;
	self->offset.z           = base + info->offset.z;
	self->type               = info->type;
}

extern "C" void fn_8_40E88(RuntimeState* self)
{
	if (self->resource != NULL) {
		void* manager = *(void**)(*(u8**)lbl_8042C1D0 + 0x725C);
		fn_8015BBF8(manager, self->resource);
		fn_80150958(self->resource);
		self->resource = NULL;
	}
}

extern "C" void fn_8_40EE0(RuntimeState* self)
{
	if (self->resource != NULL) {
		void* manager = *(void**)(*(u8**)lbl_8042C1D0 + 0x725C);
		fn_8015BBF8(manager, self->resource);
		fn_80150958(self->resource);
		self->resource = NULL;
	}
	self->resource = fn_80150588(lbl_8_bss_988);
	void* manager  = *(void**)(*(u8**)lbl_8042C1D0 + 0x725C);
	fn_8015BB08(manager, self->resource);
}

#pragma force_active reset
