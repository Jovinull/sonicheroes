#include "types.h"

#pragma force_active on

// Complete stage11 TObjNoOttottoCollision translation unit. The object copies
// its placement transform into a shared two-entry joint table and rebuilds the
// collision when the editor changes either the selected joint or its offsets.

typedef struct JointParam {
	s32 index;
	f32 x;
	f32 y;
	f32 z;
} JointParam;

typedef struct JointEntry {
	u8 pad00[0x14];
	f32 x;
	f32 y;
	f32 z;
	u8 pad20[0x10];
} JointEntry;

typedef struct BobXform {
	f32 x;
	f32 y;
	f32 z;
	u32 rotX;
	u32 rotY;
	u32 rotZ;
	u8 pad18[0x14];
	JointParam* param;
} BobXform;

typedef struct SetdataParam {
	u8 pad00[0x2C];
	JointParam* param;
} SetdataParam;

typedef struct OttottoObject {
	u32 field00;
	u16 flags;
	u8 pad06[0x12];
	void* vtable;
	u8 pad1C[2];
	u16 field1E;
	u8 pad20[8];
	BobXform* transform;
	void* field2C;
	u8 collision[0x10];
	void* allocation;
	u8 pad44[0x4C];
	f32 previousX;
	f32 previousY;
	f32 previousZ;
	u32 previousRotX;
	u32 previousRotY;
	u32 previousRotZ;
	u8 padA8[4];
	f32 savedX;
	f32 savedY;
	f32 savedZ;
	f32 currentX;
	f32 currentY;
	f32 currentZ;
	u32 currentRotX;
	u32 currentRotY;
	u32 currentRotZ;
} OttottoObject;

typedef struct ObjectEntry {
	const char* name;
	void (*load)(void);
	void (*unload)(void);
	void (*create)(void);
	void (*reset)(void);
	u32 flags;
	u32 unk18;
	s16 unk1C;
	s16 unk1E;
	u8 unk20;
	u8 unk21;
	u8 pad22[2];
	const char* fieldTypes;
	const char** fieldNames;
} ObjectEntry;

extern "C" {

void fn_8_DCE3C(OttottoObject*);
OttottoObject* fn_8_DCF34(OttottoObject*, s16);
void fn_8_DD0D4(OttottoObject*, SetdataParam*);
void fn_8_DCE38(void);
void fn_3_1A9B0(void);
void PDisp__7TObjectFv(void);
void ImmAftSetRaster__7TObjectFv(void);
void Debug__7TObjectFv(void);
void Error__7TObjectFPc(void);
void Render__7TObjectFv(void);
void fn_8_DD368(void*, SetdataParam*);

extern char lbl_8_data_1A350[];
extern char lbl_8_data_1A358[];
extern char lbl_8_data_1A35C[];
extern char lbl_8_data_1A360[];

const char* noOttottoCollisionFieldNames[] = {
	lbl_8_data_1A350,
	lbl_8_data_1A358,
	lbl_8_data_1A35C,
	lbl_8_data_1A360,
};

JointEntry lbl_8_data_1A374[] = {
	{ { 0x23, 0x00, 0xF0, 0x00 }, 0.0f, 0.0f, 0.0f, { 0 } },
	{ { 0x23, 0x07, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x02 }, 0.0f, 0.0f, 0.0f, { 0 } },
};

char lbl_8_data_1A3D4[]      = "TObjSetNoOttottoCollision";
const char* lbl_8_data_1A3F0 = lbl_8_data_1A3D4;
void* lbl_8_data_1A3F4[]     = {
	NULL,
	NULL,
	(void*)fn_8_DCF34,
	(void*)fn_8_DCE3C,
	(void*)fn_3_1A9B0,
	(void*)fn_8_DCE38,
	(void*)PDisp__7TObjectFv,
	(void*)ImmAftSetRaster__7TObjectFv,
	(void*)Debug__7TObjectFv,
	(void*)Error__7TObjectFPc,
	(void*)Render__7TObjectFv,
	NULL,
	NULL,
	(void*)fn_8_DD368,
	(void*)fn_8_DD0D4,
};
char noOttottoCollisionDisplayName[] = "NO OTTOTTO COLLISION";
char noOttottoCollisionFieldTypes[]  = "ifff";
ObjectEntry noOttottoCollisionEntry;

extern void* lbl_8042C148;
extern void* lbl_8042C110;

s32 fn_8005B9F0(void*);
s32 fn_8005B8BC(void*);
s32 fn_8005B8D8(void*);
void fn_8003BC38(void*);
void __ct__7TObjectFP7TObject(void*, void*);
void fn_8005BE6C(void*);
void fn_8003C618(void*);
void fn_8003C200(void*, void*, s32, s32);
void dtor_8003C52C(void*, s32);
void dtor_8005BD3C(void*, s32);
void __dt__7TObjectFv(void*, s32);
void fn_800189A4(void*, void*);
void __dl__FPv(void*);
void* fn_80018A34(void*, s32);
void* fn_8_DCCAC(void*);

void* fn_8_DCE30(void* object)
{
	return fn_8_DCCAC((u8*)object - 0x28);
}

void fn_8_DCE38(void) { }

void fn_8_DCE3C(OttottoObject* object)
{
	if (fn_8005B9F0(&object->transform) != 0 || fn_8005B8BC(&object->transform) != 0) {
		object->flags |= 1;
	} else if (fn_8005B8D8(&object->transform) != 0) {
		BobXform* transform = object->transform;
		object->currentX    = transform->x;
		object->currentY    = transform->y;
		object->currentZ    = transform->z;

		transform           = object->transform;
		object->currentRotX = transform->rotX;
		object->currentRotY = transform->rotY;
		object->currentRotZ = transform->rotZ;
	} else {
		object->savedX = object->previousX;
		object->savedY = object->previousY;
		object->savedZ = object->previousZ;

		object->previousX = object->currentX;
		object->previousY = object->currentY;
		object->previousZ = object->currentZ;

		object->previousRotX = object->currentRotX;
		object->previousRotY = object->currentRotY;
		object->previousRotZ = object->currentRotZ;
		fn_8003BC38(object->collision);
	}
}

OttottoObject* fn_8_DCF34(OttottoObject* object, s16 flag)
{
	if (object != NULL) {
		object->vtable  = lbl_8_data_1A3F4;
		object->field2C = (u8*)lbl_8_data_1A3F4 + 0x2C;
		dtor_8003C52C(object->collision, 0);
		dtor_8005BD3C(&object->transform, 0);
		__dt__7TObjectFv(object, 0);
		if (flag > 0) {
			fn_800189A4(lbl_8042C148, object);
		}
	}
	return object;
}

OttottoObject* fn_8_DCFCC(OttottoObject* object, void* owner)
{
	__ct__7TObjectFP7TObject(object, owner);
	fn_8005BE6C(&object->transform);
	fn_8003C618(object->collision);
	object->vtable  = lbl_8_data_1A3F4;
	object->field2C = (u8*)lbl_8_data_1A3F4 + 0x2C;
	object->field00 = (u32)lbl_8_data_1A3F0;
	object->field1E = 0xD0;

	BobXform* transform = object->transform;
	JointParam* param   = transform->param;
	object->currentX    = transform->x;
	object->currentY    = transform->y;
	object->currentZ    = transform->z;
	transform           = object->transform;
	object->currentRotX = transform->rotX;
	object->currentRotY = transform->rotY;
	object->currentRotZ = transform->rotZ;

	lbl_8_data_1A374[param->index].x = param->x;
	lbl_8_data_1A374[param->index].y = param->y;
	lbl_8_data_1A374[param->index].z = param->z;
	fn_8003C200(object->collision, &lbl_8_data_1A374[param->index], 1, 4);
	return object;
}

void fn_8_DD0D4(OttottoObject* object, SetdataParam* setdata)
{
	JointParam* param = setdata->param;
	if (param->index < 0) {
		param->index = 0;
	}
	if (param->index > 1) {
		param->index = 1;
	}
	if (object->allocation != NULL) {
		__dl__FPv(object->allocation);
		lbl_8_data_1A374[param->index].x = param->x;
		lbl_8_data_1A374[param->index].y = param->y;
		lbl_8_data_1A374[param->index].z = param->z;
		fn_8003C200(object->collision, &lbl_8_data_1A374[param->index], 1, 4);
	}
}

void noOttottoCollisionCreate(void)
{
	void* result = fn_80018A34(lbl_8042C148, 0xD0);
	if (result != NULL) {
		OttottoObject* object = (OttottoObject*)result;
		__ct__7TObjectFP7TObject(object, lbl_8042C110);
		fn_8005BE6C(&object->transform);
		fn_8003C618(object->collision);
		object->vtable  = lbl_8_data_1A3F4;
		object->field2C = (u8*)lbl_8_data_1A3F4 + 0x2C;
		object->field00 = (u32)lbl_8_data_1A3F0;
		object->field1E = 0xD0;

		BobXform* transform = object->transform;
		JointParam* param   = transform->param;
		object->currentX    = transform->x;
		object->currentY    = transform->y;
		object->currentZ    = transform->z;
		transform           = object->transform;
		object->currentRotX = transform->rotX;
		object->currentRotY = transform->rotY;
		object->currentRotZ = transform->rotZ;

		lbl_8_data_1A374[param->index].x = param->x;
		lbl_8_data_1A374[param->index].y = param->y;
		lbl_8_data_1A374[param->index].z = param->z;
		fn_8003C200(object->collision, &lbl_8_data_1A374[param->index], 1, 4);
	}
}

void noOttottoCollisionRegister(void)
{
	noOttottoCollisionEntry.flags      = 0;
	noOttottoCollisionEntry.unk18      = 0;
	noOttottoCollisionEntry.name       = noOttottoCollisionDisplayName;
	noOttottoCollisionEntry.load       = NULL;
	noOttottoCollisionEntry.unload     = NULL;
	noOttottoCollisionEntry.create     = noOttottoCollisionCreate;
	noOttottoCollisionEntry.reset      = NULL;
	noOttottoCollisionEntry.flags      = 0x20000;
	noOttottoCollisionEntry.unk18      = 0;
	noOttottoCollisionEntry.unk20      = 10;
	noOttottoCollisionEntry.unk1C      = 130;
	noOttottoCollisionEntry.unk1E      = 2;
	noOttottoCollisionEntry.unk21      = 0;
	noOttottoCollisionEntry.fieldTypes = noOttottoCollisionFieldTypes;
	noOttottoCollisionEntry.fieldNames = noOttottoCollisionFieldNames;
	if (noOttottoCollisionFieldTypes != NULL) {
		noOttottoCollisionEntry.flags |= 8;
	} else {
		noOttottoCollisionEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const noOttottoCollisionCtorEntry)(void)
    = noOttottoCollisionRegister;

#pragma dont_inline on
void fn_8_DD368(void* object, SetdataParam* setdata)
{
	fn_8_DD0D4((OttottoObject*)((u8*)object - 0x28), setdata);
}
#pragma dont_inline reset
}

#pragma force_active reset
