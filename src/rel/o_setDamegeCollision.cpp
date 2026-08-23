#include "types.h"

typedef struct Vec3 {
	f32 x, y, z;
} Vec3;
typedef struct Param {
	s32 slot;
	f32 x, y, z;
} Param;
typedef struct Frame {
	Vec3 pos;
	s32 rx, ry, rz;
	u8 pad18[0x14];
	Param* param;
} Frame;
typedef struct TObject {
	const char* className;
	u16 signal, tag;
	u8 links[0x10];
	void** vtable;
	s16 unk1C, objectSize;
	u8 tail[8];
} TObject;
typedef struct Motion {
	Frame* frame;
	void** vtable;
} Motion;
typedef struct DamageVolume {
	u8 head[0x14];
	f32 x, y, z;
	u8 tail[0x10];
} DamageVolume;
typedef struct TObjSetDamageCollision {
	TObject base;
	Motion motion;
	u8 collision[0x10];
	void* handle;
	u8 pad44[0x4C];
	Vec3 previous;
	s32 previousRx, previousRy, previousRz;
	u8 padA8[4];
	Vec3 oldPosition;
	Vec3 position;
	s32 rx, ry, rz;
} TObjSetDamageCollision;
typedef struct ObjectEntry {
	const char* name;
	void (*load)(void);
	void (*unload)(void);
	void (*create)(void);
	void* unk10;
	u32 flags, unk18;
	s16 id, count;
	u8 radius, unk21, pad22[2];
	const char* fieldTypes;
	const char** fieldNames;
	u8 trailingPadding[4];
} ObjectEntry;

extern "C" void* lbl_8042C110;
extern "C" void* lbl_8042C148;
extern "C" void __dl__FPv(void*);
extern "C" void __ct__7TObjectFP7TObject(TObject*, void*);
extern "C" void __dt__7TObjectFv(TObject*, s32);
extern "C" void* fn_80018A34(void*, u32);
extern "C" void fn_800189A4(void*, TObject*);
extern "C" void fn_8003BC38(void*);
extern "C" void fn_8003C200(void*, DamageVolume*, s32, s32);
extern "C" void dtor_8003C52C(void*, s32);
extern "C" void fn_8003C618(void*);
extern "C" s32 fn_8005B8BC(Motion*);
extern "C" s32 fn_8005B8D8(Motion*);
extern "C" s32 fn_8005B9F0(Motion*);
extern "C" void dtor_8005BD3C(Motion*, s32);
extern "C" void fn_8005BE6C(Motion*);

extern "C" void fn_3_1A9B0(void);
extern "C" void PDisp__7TObjectFv(void);
extern "C" void ImmAftSetRaster__7TObjectFv(void);
extern "C" void Debug__7TObjectFv(void);
extern "C" void Error__7TObjectFPc(void);
extern "C" void Render__7TObjectFv(void);

extern "C" void setDamageCollisionTDisp(TObjSetDamageCollision*) { }

extern "C" void setDamageCollisionExec(TObjSetDamageCollision* object)
{
	Frame* frame;
	if (fn_8005B9F0(&object->motion) || fn_8005B8BC(&object->motion)) {
		object->base.signal |= 1;
	} else if (fn_8005B8D8(&object->motion)) {
		frame              = object->motion.frame;
		object->position.x = frame->pos.x;
		object->position.y = frame->pos.y;
		object->position.z = frame->pos.z;
		frame              = object->motion.frame;
		object->rx         = frame->rx;
		object->ry         = frame->ry;
		object->rz         = frame->rz;
	} else {
		object->oldPosition.x = object->previous.x;
		object->oldPosition.y = object->previous.y;
		object->oldPosition.z = object->previous.z;
		object->previous.x    = object->position.x;
		object->previous.y    = object->position.y;
		object->previous.z    = object->position.z;
		object->previousRx    = object->rx;
		object->previousRy    = object->ry;
		object->previousRz    = object->rz;
		fn_8003BC38(object->collision);
	}
}

extern "C" TObjSetDamageCollision* setDamageCollisionDtor(TObjSetDamageCollision* object, s16 flags)
{
	if (object) {
		extern void* setDamageCollisionVtable[];
		object->base.vtable   = setDamageCollisionVtable;
		object->motion.vtable = setDamageCollisionVtable + 11;
		dtor_8003C52C(object->collision, 0);
		dtor_8005BD3C(&object->motion, 0);
		__dt__7TObjectFv(&object->base, 0);
		if (flags > 0)
			fn_800189A4(lbl_8042C148, &object->base);
	}
	return object;
}

extern "C" TObjSetDamageCollision* setDamageCollisionCtor(
    TObjSetDamageCollision* object, void* owner);
extern "C" const char* setDamageCollisionClassName;
extern "C" void* setDamageCollisionVtable[];
extern "C" DamageVolume setDamageCollisionVolumes[2];

extern "C" TObjSetDamageCollision* setDamageCollisionCtor(
    TObjSetDamageCollision* object, void* owner)
{
	__ct__7TObjectFP7TObject(&object->base, owner);
	fn_8005BE6C(&object->motion);
	fn_8003C618(object->collision);
	object->base.vtable                      = setDamageCollisionVtable;
	object->motion.vtable                    = setDamageCollisionVtable + 11;
	object->base.className                   = setDamageCollisionClassName;
	object->base.objectSize                  = 0xD0;
	Frame* frame                             = object->motion.frame;
	Param* param                             = frame->param;
	object->position.x                       = frame->pos.x;
	object->position.y                       = frame->pos.y;
	object->position.z                       = frame->pos.z;
	frame                                    = object->motion.frame;
	object->rx                               = frame->rx;
	object->ry                               = frame->ry;
	object->rz                               = frame->rz;
	setDamageCollisionVolumes[param->slot].x = param->x;
	setDamageCollisionVolumes[param->slot].y = param->y;
	setDamageCollisionVolumes[param->slot].z = param->z;
	fn_8003C200(object->collision, &setDamageCollisionVolumes[param->slot], 1, 4);
	return object;
}

extern "C" void setDamageCollisionEditOnChange(TObjSetDamageCollision* object, Frame* frame)
{
	Param* param = frame->param;
	if (param->slot < 0)
		param->slot = 0;
	if (param->slot > 1)
		param->slot = 1;
	if (object->handle) {
		__dl__FPv(object->handle);
		setDamageCollisionVolumes[param->slot].x = param->x;
		setDamageCollisionVolumes[param->slot].y = param->y;
		setDamageCollisionVolumes[param->slot].z = param->z;
		fn_8003C200(object->collision, &setDamageCollisionVolumes[param->slot], 1, 4);
	}
}

extern "C" void startObjSetDamageCollision(void)
{
	void* memory = fn_80018A34(lbl_8042C148, sizeof(TObjSetDamageCollision));
	if (memory) {
		TObjSetDamageCollision* object = (TObjSetDamageCollision*)memory;
		setDamageCollisionCtor(object, lbl_8042C110);
	}
}

extern "C" char setDamageCollisionDisplayName[];
extern "C" char setDamageCollisionFieldTypes[];
extern "C" const char* setDamageCollisionFieldNames[];

extern "C" ObjectEntry setDamageCollisionEntry;
extern "C" void setDamageCollisionRegister(void)
{
	setDamageCollisionEntry.flags      = 0;
	setDamageCollisionEntry.unk18      = 0;
	setDamageCollisionEntry.name       = setDamageCollisionDisplayName;
	setDamageCollisionEntry.load       = NULL;
	setDamageCollisionEntry.unload     = NULL;
	setDamageCollisionEntry.create     = startObjSetDamageCollision;
	setDamageCollisionEntry.unk10      = NULL;
	setDamageCollisionEntry.flags      = 0x20000;
	setDamageCollisionEntry.unk18      = 0;
	setDamageCollisionEntry.radius     = 30;
	setDamageCollisionEntry.id         = 100;
	setDamageCollisionEntry.count      = 2;
	setDamageCollisionEntry.unk21      = 0;
	setDamageCollisionEntry.fieldTypes = setDamageCollisionFieldTypes;
	setDamageCollisionEntry.fieldNames = setDamageCollisionFieldNames;
	if (setDamageCollisionFieldTypes)
		setDamageCollisionEntry.flags |= 8;
	else
		setDamageCollisionEntry.flags &= ~8;
}

extern "C" const char setDamageCollisionFieldSlot[];
extern "C" const char setDamageCollisionFieldX[];
extern "C" const char setDamageCollisionFieldY[];
extern "C" const char setDamageCollisionFieldZ[];
extern "C" const char* setDamageCollisionFieldNames[] = { setDamageCollisionFieldSlot,
	setDamageCollisionFieldX, setDamageCollisionFieldY, setDamageCollisionFieldZ };
extern "C" DamageVolume setDamageCollisionVolumes[2]
    = { { { 0x00, 0x00, 0xFF, 0xEF, 0x01 } }, { { 0x00, 0x07, 0xFF, 0xEF, 0x01 } } };
extern "C" char setDamageCollisionClassString[]    = { 'T', 'O', 'b', 'j', 'S', 'e', 't', 'D', 'a',
	'm', 'a', 'g', 'e', 'C', 'o', 'l', 'l', 'i', 's', 'i', 'o', 'n', 0 };
extern "C" const char* setDamageCollisionClassName = setDamageCollisionClassString;
extern "C" void setDamageCollisionEditThunk(TObjSetDamageCollision*, Frame*);
extern "C" void* setDamageCollisionVtable[] = { NULL, NULL, (void*)setDamageCollisionDtor,
	(void*)setDamageCollisionExec, (void*)fn_3_1A9B0, (void*)setDamageCollisionTDisp,
	(void*)PDisp__7TObjectFv, (void*)ImmAftSetRaster__7TObjectFv, (void*)Debug__7TObjectFv,
	(void*)Error__7TObjectFPc, (void*)Render__7TObjectFv, NULL, NULL,
	(void*)setDamageCollisionEditThunk, (void*)setDamageCollisionEditOnChange };
extern "C" char setDamageCollisionDisplayName[]
    = { 'D', 'A', 'M', 'A', 'G', 'E', ' ', 'C', 'O', 'L', 'L', 'I', 'S', 'I', 'O', 'N', 0 };
extern "C" char setDamageCollisionFieldTypes[] = { 'i', 'f', 'f', 'f', 0 };
extern "C" {
ObjectEntry setDamageCollisionEntry;
}
__declspec(section ".ctors") void (*const setDamageCollisionCtorEntry)(void)
    = setDamageCollisionRegister;

#pragma dont_inline on
extern "C" void setDamageCollisionEditThunk(TObjSetDamageCollision* adjusted, Frame* frame)
{
	setDamageCollisionEditOnChange((TObjSetDamageCollision*)((u8*)adjusted - 0x28), frame);
}
#pragma dont_inline reset
