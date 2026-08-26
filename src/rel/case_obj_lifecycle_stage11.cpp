#include "types.h"

extern "C" {
extern void* lbl_8_bss_988;
extern void* lbl_8_bss_98C;
extern u32 lbl_8_bss_990;
extern u32 lbl_8_bss_994;
extern void* lbl_8_bss_998;
extern void* lbl_8_bss_99C;
extern void* lbl_8_bss_9A0;
extern void* lbl_8_bss_9A4;
extern void* lbl_8_bss_9A8;
extern void* lbl_8_bss_9AC;
extern char* lbl_8_data_4398[];
extern char* lbl_8_data_442C[];
extern char* caseObjFieldNames[];
extern char lbl_8_data_45D4[];
extern char lbl_8_data_45E0[];
extern char lbl_8_data_45F0[];
extern u32 lbl_8_data_4590[];
extern u32 caseObjVtable[];
extern u32 lbl_8_data_4434[];
extern f32 lbl_8_rodata_AB4;
extern f32 lbl_8_rodata_AB8;
extern f32 lbl_8_rodata_A90;
extern f32 lbl_8_rodata_A94;
extern f32 lbl_8_rodata_A98;
extern f32 lbl_8_rodata_AA8;
extern f32 lbl_8_rodata_AAC;
extern f32 lbl_8_rodata_AB0;
extern u8 lbl_8042C1D0[];
extern u8 lbl_8042C298[];

void* fn_8005EC0C();
void* fn_801A4BBC(void* context, const char* name);
void* fn_8005EA04(const char* name);
void* fn_8005E410(void* resource, s32 index, const char* name);
void __ct__7TObjectFP7TObject(void* self, void* parent);
void fn_8005BE6C(void* controller);
void fn_8003C618(void* object);
s32 objGroupAllActive(s32 index);
s32 fn_80100C88(s32 index);
void fn_8015BBF8(void* manager, void* resource);
void fn_80150958(void* resource);
void* fn_80150588(void* resource);
void fn_8015BB08(void* manager, void* resource);
void fn_8_40868(void* self);
void* fn_8005E1DC(void* resource, s32 index, const char* name);
void fn_801491A8();
void fn_8005D5C8(void* resource, s32 index);
void* fn_8005F490(void* resource);
void fn_8003C200(void* object, void* data, s32 count, s32 type);
void fn_8_40B34(void* self);
}

struct CaseInfo {
	f32 x;
	f32 y;
	f32 z;
	u8 index;
	s8 direction;
};

struct CasePlacement {
	u8 pad00[0x2C];
	CaseInfo* info;
};

struct Vec3 {
	f32 x, y, z;
};

struct CaseObject {
	u8 pad00[0x28];
	CasePlacement* placement;
	u8 pad2C[4];
	u8 controller[0x88];
	s32 state;
	u8 index;
	u8 padBD;
	u16 fieldBE;
	Vec3 position;
	s32 angleX;
	s32 angleY;
	s32 angleZ;
	Vec3 scale;
	void* resource;
	f32 valueE8;
	f32 valueEC;
	f32 valueF0;
	f32 valueF4;
	f32 valueF8;
	s32 direction;
};

extern "C" CaseObject* caseObjCtor(CaseObject* self, void* parent)
{
	__ct__7TObjectFP7TObject(self, parent);
	fn_8005BE6C(&self->placement);
	fn_8003C618(self->controller);
	*(void**)((u8*)self + 0x18) = caseObjVtable;
	*(void**)((u8*)self + 0x2C) = (u8*)caseObjVtable + 0x2C;
	*(u32*)((u8*)self + 0x00)   = lbl_8_data_4590[0];
	*(u16*)((u8*)self + 0x1E)   = 0x100;

	CaseInfo* info                   = self->placement->info;
	self->position                   = *(Vec3*)self->placement;
	CasePlacement* rotationPlacement = self->placement;
	self->angleX                     = *(s32*)((u8*)rotationPlacement + 0xC);
	self->angleY                     = *(s32*)((u8*)rotationPlacement + 0x10);
	self->angleZ                     = *(s32*)((u8*)rotationPlacement + 0x14);
	self->angleX                     = 0;
	self->angleZ                     = 0;
	self->index                      = info->index;
	f32 base                         = lbl_8_rodata_A90;
	self->scale.x                    = base + info->x;
	self->scale.y                    = base + info->y;
	self->scale.z                    = base + info->z;
	self->direction                  = info->direction;
	self->fieldBE                    = 0;
	self->valueE8                    = lbl_8_rodata_A98;
	f32 initial                      = lbl_8_rodata_AA8;
	self->valueEC                    = initial;
	self->valueF0                    = initial;
	self->valueF4                    = lbl_8_rodata_AAC;
	self->valueF8                    = lbl_8_rodata_AB0;
	self->resource                   = NULL;

	u8* groups      = *(u8**)lbl_8042C298;
	u8 index        = self->index;
	s32 groupOffset = index << 2;
	groups += groupOffset;
	if ((*(void**)(groups + 0x30) == NULL || objGroupAllActive(index) != 0)
	    && fn_80100C88(self->index) != 0) {
		self->state   = 3;
		f32 zero      = lbl_8_rodata_A94;
		self->valueE8 = zero;
		self->valueEC = zero;
		self->valueF0 = zero;
		self->valueF4 = zero;
		self->valueF8 = zero;
	} else {
		self->state = 1;
	}

	if (self->resource != NULL) {
		void* manager = *(void**)(*(u8**)lbl_8042C1D0 + 0x725C);
		fn_8015BBF8(manager, self->resource);
		fn_80150958(self->resource);
		self->resource = NULL;
	}
	self->resource = fn_80150588(lbl_8_bss_988);
	void* manager  = *(void**)(*(u8**)lbl_8042C1D0 + 0x725C);
	fn_8015BB08(manager, self->resource);
	fn_8_40868(self);

	fn_8005E1DC(self->resource, 0, lbl_8_data_45D4);
	fn_801491A8();
	u32 flags = *(u32*)((u8*)self->placement + 0x18);
	fn_8005D5C8(self->resource, ((flags & 0x001C0000) >> 18) + 4);

	void* found = NULL;
	char** name = lbl_8_data_4398;
	while (found == NULL) {
		found = fn_8005E1DC(self->resource, 0, *name);
		++name;
	}
	void* model  = fn_8005F490(found);
	*(u32*)model = 0x10;
	fn_8003C200(self->controller, lbl_8_data_4434, 7, 5);
	fn_8_40B34(self);
	return self;
}

extern "C" void caseObjUnload()
{
	lbl_8_bss_988 = NULL;
	lbl_8_bss_990 = 0;
	lbl_8_bss_994 = 0;
}

extern "C" void fn_8_412E4(void*, CasePlacement* placement)
{
	CaseInfo* info = placement->info;
	if (info->x < lbl_8_rodata_AB4)
		info->x = lbl_8_rodata_AB4;
	if (info->x >= lbl_8_rodata_AB8)
		info->x = lbl_8_rodata_AB8;
	if (info->y < lbl_8_rodata_AB4)
		info->y = lbl_8_rodata_AB4;
	if (info->y >= lbl_8_rodata_AB8)
		info->y = lbl_8_rodata_AB8;
	if (info->z < lbl_8_rodata_AB4)
		info->z = lbl_8_rodata_AB4;
	if (info->z >= lbl_8_rodata_AB8)
		info->z = lbl_8_rodata_AB8;
	if (info->direction < 0)
		info->direction = 0;
	if (info->direction > 1)
		info->direction = 1;
	caseObjFieldNames[4] = lbl_8_data_442C[info->direction];
}

extern "C" void caseObjLoad()
{
	void* context = fn_8005EC0C();
	lbl_8_bss_998 = fn_801A4BBC(context, lbl_8_data_4398[0]);
	lbl_8_bss_99C = fn_801A4BBC(context, lbl_8_data_4398[1]);
	lbl_8_bss_9A0 = fn_801A4BBC(context, lbl_8_data_4398[2]);
	lbl_8_bss_9A4 = fn_801A4BBC(context, lbl_8_data_4398[3]);
	lbl_8_bss_9A8 = fn_801A4BBC(context, lbl_8_data_4398[4]);
	lbl_8_bss_9AC = fn_801A4BBC(context, lbl_8_data_4398[5]);

	lbl_8_bss_988        = fn_8005EA04(lbl_8_data_45E0);
	lbl_8_bss_98C        = NULL;
	register char** name = lbl_8_data_4398;
	while (lbl_8_bss_98C == NULL) {
		lbl_8_bss_98C = fn_8005E410(lbl_8_bss_988, 0, *name);
		++name;
	}

	lbl_8_bss_994 = (u32)fn_8005EA04(lbl_8_data_45F0);
	lbl_8_bss_990 = (u32)fn_8005E410(lbl_8_bss_988, 0, lbl_8_data_45D4);
}
