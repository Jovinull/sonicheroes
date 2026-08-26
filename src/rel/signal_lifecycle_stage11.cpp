#include "types.h"

extern "C" {
extern void* lbl_8_bss_A60;
extern void* lbl_8_bss_A64;
extern void* lbl_8_bss_A68;
extern void* lbl_8_bss_A6C;
extern void* lbl_8_bss_A70;
extern void* lbl_8_bss_A74;
extern void* lbl_8_bss_A78;
extern void* lbl_8_bss_A7C;
extern void* lbl_8_bss_A80;
extern void* lbl_8_bss_A84;
extern void* lbl_8_bss_A88;
extern void* lbl_8_bss_A8C;
extern void* lbl_8_bss_A90;
extern void* lbl_8_bss_A94;
struct SignalNames {
	char* first[8];
	char* last[3];
};
extern SignalNames lbl_8_data_4B00;
extern char lbl_8_data_4BC4[];
extern char lbl_8_data_4BD4[];
extern void* signalVtable[];
extern void* lbl_8_data_4B78[];
extern char lbl_8_data_4B3C[];
extern float lbl_8_rodata_BA8;
extern float lbl_8_rodata_BB0;
extern float lbl_8_rodata_BC4;
extern float lbl_8_rodata_BC8;
extern double lbl_8_rodata_BD0;
extern char lbl_80239978[];
extern char lbl_80239984[];
extern char lbl_80239990[];

void __ct__7TObjectFP7TObject(void*, void*);
void fn_8005BE6C(void*);
void fn_8003C618(void*);
void* fn_80150588(void*);
float fn_800D7B00(int);
float fn_800D7AE4(int);
void fn_80195790(void*, char*, float, float, int);
void fn_8019EB94(void*, void*, int);
void fn_8003BF04(void*, char*, int, int);
float fn_800D8BC4(void*, int*, int);
void fn_8005D5C8(void*, int);
void* fn_8005E1DC(void*, int, char*);
int* fn_8005F490();
void* fn_8005EC0C();
void* fn_801A4BBC(void*, char*);
void* fn_8005EA04(char*);
void* fn_8005E410(void*, int, char*);
}

struct SignalInfo {
	s8 mode;
};

struct SignalPlacement {
	float position[3];
	int values[3];
	u32 flags;
	u8 pad1C[0x10];
	SignalInfo* info;
};

struct Signal {
	u8 pad00[0x18];
	void* vtable;
	u16 pad1C;
	u16 kind;
	u8 pad20[8];
	SignalPlacement* placement;
	void* secondaryVtable;
	u8 member30[0x88];
	u8 mode;
	u8 padB9[3];
	float position[3];
	float positionCopy[3];
	int values[3];
	void* resource;
	float fieldE4;
	float fieldE8;
	float fieldEC;
	float fieldF0;
	float fieldF4;
	float fieldF8;
};

struct SignalModel {
	u8 pad00[0x10];
	u8 transforms[1];
};

static inline float signalIntToScaledFloat(int value)
{
	union {
		double value;
		u32 words[2];
	} converted;
	converted.words[0] = 0x43300000;
	converted.words[1] = value ^ 0x80000000;
	return lbl_8_rodata_BC8 * (converted.value - lbl_8_rodata_BD0);
}

extern "C" Signal* signalCtor(Signal* self, void* parent)
{
	__ct__7TObjectFP7TObject(self, parent);
	fn_8005BE6C(&self->placement);
	fn_8003C618(self->member30);
	self->vtable          = signalVtable;
	self->secondaryVtable = signalVtable + 11;
	*(void**)self         = lbl_8_data_4B78[0];
	self->kind            = 252;

	SignalInfo* info      = self->placement->info;
	self->position[0]     = self->placement->position[0];
	self->position[1]     = self->placement->position[1];
	self->position[2]     = self->placement->position[2];
	self->positionCopy[0] = self->position[0];
	self->positionCopy[1] = self->position[1];
	self->positionCopy[2] = self->position[2];
	self->values[0]       = self->placement->values[0];
	self->values[1]       = self->placement->values[1];
	self->values[2]       = self->placement->values[2];
	self->mode            = info->mode;

	self->resource     = fn_80150588(lbl_8_bss_A60);
	SignalModel* model = *(SignalModel**)((u8*)self->resource + 4);
	float high         = fn_800D7B00(self->values[1]);
	float low          = fn_800D7AE4(self->values[1]);
	fn_80195790(model->transforms, lbl_80239984, lbl_8_rodata_BB0 - low, high, 0);
	high = fn_800D7B00(self->values[0]);
	low  = fn_800D7AE4(self->values[0]);
	fn_80195790(model->transforms, lbl_80239978, lbl_8_rodata_BB0 - low, high, 2);
	high = fn_800D7B00(self->values[2]);
	low  = fn_800D7AE4(self->values[2]);
	fn_80195790(model->transforms, lbl_80239990, lbl_8_rodata_BB0 - low, high, 2);
	fn_8019EB94(model, self->position, 2);
	fn_8003BF04(self->member30, lbl_8_data_4B3C, 1, 4);

	self->fieldE8 = lbl_8_rodata_BA8;
	if ((self->placement->flags & 0x20000) != 0) {
		int result[3];
		self->fieldE8 = fn_800D8BC4(self->position, result, 1);
		if (self->fieldE8 != lbl_8_rodata_BA8) {
			self->fieldE4 = self->position[0];
			self->fieldE8 += lbl_8_rodata_BC4;
			self->fieldEC = self->position[2];
			self->fieldF0 = signalIntToScaledFloat(result[0]);
			self->fieldF4 = signalIntToScaledFloat(self->values[1]);
			self->fieldF8 = signalIntToScaledFloat(result[2]);
		}
	}

	fn_8005D5C8(self->resource, ((self->placement->flags & 0x1C0000) >> 18) + 4);
	void* found = NULL;
	char** name = lbl_8_data_4B00.last;
	while (found == NULL) {
		found = fn_8005E1DC(self->resource, 0, *name);
		name++;
	}
	int* state = fn_8005F490();
	*state     = 16;
	return self;
}

extern "C" void fn_8_46898(void*, SignalPlacement* placement)
{
	SignalInfo* info = placement->info;
	if (info->mode < 0)
		info->mode = 0;
	if (info->mode >= 3)
		info->mode = 2;
}

extern "C" void signalUnload()
{
	lbl_8_bss_A60 = NULL;
	lbl_8_bss_A64 = NULL;
}

extern "C" void signalLoad()
{
	void* context = fn_8005EC0C();
	lbl_8_bss_A74 = fn_801A4BBC(context, lbl_8_data_4B00.first[0]);
	lbl_8_bss_A78 = fn_801A4BBC(context, lbl_8_data_4B00.first[1]);
	lbl_8_bss_A7C = fn_801A4BBC(context, lbl_8_data_4B00.first[2]);
	lbl_8_bss_A80 = fn_801A4BBC(context, lbl_8_data_4B00.first[5]);
	lbl_8_bss_A84 = fn_801A4BBC(context, lbl_8_data_4B00.first[6]);
	lbl_8_bss_A88 = fn_801A4BBC(context, lbl_8_data_4B00.first[7]);
	lbl_8_bss_A8C = fn_801A4BBC(context, lbl_8_data_4B00.last[0]);
	lbl_8_bss_A90 = fn_801A4BBC(context, lbl_8_data_4B00.last[1]);
	lbl_8_bss_A94 = fn_801A4BBC(context, lbl_8_data_4B00.last[2]);

	lbl_8_bss_A60 = fn_8005EA04(lbl_8_data_4BC4);
	if (lbl_8_bss_A60 != NULL) {
		lbl_8_bss_A68 = NULL;
		char** name   = lbl_8_data_4B00.first;
		while (lbl_8_bss_A68 == NULL) {
			lbl_8_bss_A68 = fn_8005E410(lbl_8_bss_A60, 0, *name);
			name++;
		}

		lbl_8_bss_A6C = NULL;
		name          = lbl_8_data_4B00.last;
		while (lbl_8_bss_A6C == NULL) {
			lbl_8_bss_A6C = fn_8005E410(lbl_8_bss_A60, 0, *name);
			name++;
		}
	}

	lbl_8_bss_A64 = fn_8005EA04(lbl_8_data_4BD4);
	lbl_8_bss_A70 = fn_8005E410(lbl_8_bss_A64, 0, NULL);
}
