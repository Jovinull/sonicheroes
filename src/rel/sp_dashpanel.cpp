#include "types.h"

// Stage40's special-stage dash-panel editor object. This complete TU owns the
// object lifecycle, collision/power update, resource hooks, editor callback,
// registration record, vtable initializer, and constructor entry.

struct Vec3 {
	f32 x, y, z;
};

struct DashpanelParams {
	f32 power;
	s16 noControlTime;
};

struct SpDashpanelObject {
	u8 base[0x28];
	void* motion;
	u8 pad2C[0x10];
	s8 playerCooldown[8];
	s16 noControlTime;
	u8 pad46[2];
	Vec3 position;
	s32 rotation[3];
	f32 power;
	u8 pad68[0xC];
	void* matrix;
};

extern "C" {
void markSampleForDeletion(void*);
void* __nw__10TObjSampleFUl(u32);
void __dl__10TObjSampleFPv(void*);
void __dl__FPv(void*);
void __ct__7TObjectFP7TObject(void*, void*);
void __dt__7TObjectFv(void*, s16);
void fn_8005BE6C(void*);
void dtor_8005BD3C(void*, s16);
void fn_16_93C3C(void*);
void fn_16_93BE8(void*, s32);
void fn_16_4DF58(void*);
void fn_16_4DEC8(void*);
void fn_16_4D7D8(void*);
void fn_16_4E554(void*);
void fn_16_4E384(void*);
void* setupObjClass(
    void*, char*, void*, void*, void*, void*, u32, u32, u8, u16, u16, u8, char*, char**);
void copyVec3(void*, void*);
void fn_16_6B5C(void*, void*);

extern void* lbl_8042C110;
}

f32 spDashpanelMinimumPower  = 0.0f;
f32 spDashpanelMaximumPower  = 100.0f;
char spDashpanelPowerField[] = "Power(Def. 5.0f)";
char spDashpanelTimerField[] = "No Ctrl Time(Frm)";
char spDashpanelClassName[]  = "TObjDashpanel";
void* spDashpanelVtable[15];
char spDashpanelDisplayName[] = "SP DASHPANEL OBJECT";
char spDashpanelFieldTypes[]  = "fs";
char* spDashpanelFieldNames[] = { spDashpanelPowerField, spDashpanelTimerField };
u8 spDashpanelRegistration[0x90];

extern "C" void fn_16_7FA94(s32* direction)
{
	direction[0] = 0;
	direction[1] = -0x8000;
	direction[2] = 0;
}

extern "C" void fn_16_7FB98(SpDashpanelObject* object)
{
	for (s32 i = 0; i < 8; ++i) {
		if (object->playerCooldown[i] > 0)
			--object->playerCooldown[i];
	}
}

extern "C" void fn_16_7FE10(void) { }

extern "C" void fn_16_7FF68(SpDashpanelObject* object);

extern "C" void fn_16_7FE14(SpDashpanelObject* object)
{
	DashpanelParams* params = *(DashpanelParams**)((u8*)object->motion + 0x2C);
	copyVec3(&object->position, object->motion);
	fn_16_6B5C(object->rotation, (u8*)object->motion + 0xC);
	object->power         = params->power;
	object->noControlTime = params->noControlTime;
	fn_16_7FF68(object);
	fn_16_7FB98(object);
}

extern "C" void fn_16_7FF68(SpDashpanelObject* object)
{
	fn_16_7FA94(object->rotation);
}

extern "C" SpDashpanelObject* fn_16_801A4(SpDashpanelObject* object, s16 flags)
{
	if (object != NULL) {
		if (object->matrix != NULL) {
			__dl__FPv(object->matrix);
			object->matrix = NULL;
		}
		fn_16_4DF58((u8*)object + 0x68);
		fn_16_4DEC8((u8*)object + 0x68);
		fn_16_93BE8((u8*)object + 0x30, 0);
		dtor_8005BD3C((u8*)object + 0x28, 0);
		__dt__7TObjectFv(object, 0);
		if (flags > 0)
			__dl__10TObjSampleFPv(object);
	}
	return object;
}

extern "C" SpDashpanelObject* fn_16_8025C(SpDashpanelObject* object, void* owner)
{
	__ct__7TObjectFP7TObject(object, owner);
	fn_8005BE6C((u8*)object + 0x28);
	fn_16_93C3C((u8*)object + 0x30);
	copyVec3(&object->position, object->motion);
	fn_16_6B5C(object->rotation, (u8*)object->motion + 0xC);
	DashpanelParams* params = *(DashpanelParams**)((u8*)object->motion + 0x2C);
	object->power           = params->power;
	object->noControlTime   = params->noControlTime;
	object->matrix          = NULL;
	for (s32 i = 0; i < 8; ++i)
		object->playerCooldown[i] = 0;
	fn_16_7FF68(object);
	return object;
}

extern "C" void fn_16_803DC(void*, void* motion)
{
	DashpanelParams* params = *(DashpanelParams**)((u8*)motion + 0x2C);
	if (params->power < spDashpanelMinimumPower)
		params->power = spDashpanelMinimumPower;
	if (params->power > spDashpanelMaximumPower)
		params->power = spDashpanelMaximumPower;
	if (params->noControlTime < 0)
		params->noControlTime = 0;
}

extern "C" void fn_16_8046C(void)
{
	fn_16_4D7D8(spDashpanelVtable);
	fn_16_4E554(spDashpanelVtable);
}

extern "C" void fn_16_804A0(void) { }

extern "C" void fn_16_80518(void)
{
	SpDashpanelObject* object = (SpDashpanelObject*)__nw__10TObjSampleFUl(0x78);
	if (object != NULL)
		fn_16_8025C(object, lbl_8042C110);
}

extern "C" void fn_16_80568(void)
{
	setupObjClass(spDashpanelRegistration, spDashpanelDisplayName, (void*)fn_16_804A0,
	    (void*)fn_16_8046C, (void*)fn_16_80518, NULL, 0x20000, 0, 0x1E, 0x15F0, 2, 0,
	    spDashpanelFieldTypes, spDashpanelFieldNames);
}

extern "C" void fn_16_805F4(SpDashpanelObject* motionView)
{
	fn_16_803DC((u8*)motionView - 0x28, motionView);
}

extern "C" void fn_16_805FC(void)
{
	fn_16_4E384(spDashpanelVtable);
}

__declspec(section ".ctors") void (*const spDashpanelCtorEntry)(void) = fn_16_80568;
