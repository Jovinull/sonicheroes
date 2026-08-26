#include "types.h"

// Stage40's special-stage dash-ring editor object. This TU owns the complete
// lifecycle, player-trigger update, rendering, editor clamp, registration, and
// constructor entry for "SP DASHRING OBJECT".

struct Vec3 {
	f32 x, y, z;
};

struct DashringParams {
	f32 power;
	s16 noControlTime;
};

struct SpDashringObject {
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
void copyVec3(void*, void*);
void fn_16_900(void*, void*);
void* setupObjClass(
    void*, char*, void*, void*, void*, void*, u32, u32, u8, u16, u16, u8, char*, char**);

extern void* lbl_8042C110;
}

f32 spDashringMinimumPower  = 0.0f;
f32 spDashringMaximumPower  = 100.0f;
char spDashringPowerField[] = "Power(Def. 5.0f)";
char spDashringTimerField[] = "No Ctrl Time(Frm)";
char spDashringClassName[]  = "TObjDashring";
void* spDashringVtable[15];
char spDashringDisplayName[] = "SP DASHRING OBJECT";
char spDashringFieldTypes[]  = "fs";
char* spDashringFieldNames[] = { spDashringPowerField, spDashringTimerField };
u8 spDashringRegistration[0x30];

extern "C" void fn_16_80624(s32* direction, SpDashringObject*)
{
	direction[0] = 0;
	direction[1] = -0x8000;
	direction[2] = 0;
}

extern "C" void fn_16_80794(SpDashringObject* object)
{
	for (s32 i = 0; i < 8; ++i) {
		if (object->playerCooldown[i] > 0)
			--object->playerCooldown[i];
	}
}

extern "C" void fn_16_80BF8(SpDashringObject*) { }

extern "C" void fn_16_80C38(SpDashringObject*) { }

extern "C" void fn_16_80F30(SpDashringObject* object);

extern "C" void fn_16_80DDC(SpDashringObject* object)
{
	DashringParams* params = *(DashringParams**)((u8*)object->motion + 0x2C);
	copyVec3(&object->position, object->motion);
	fn_16_900(object->rotation, (u8*)object->motion + 0xC);
	object->power         = params->power;
	object->noControlTime = params->noControlTime;
	fn_16_80F30(object);
	fn_16_80794(object);
}

extern "C" void fn_16_80F30(SpDashringObject* object)
{
	fn_16_80624(object->rotation, object);
}

extern "C" SpDashringObject* fn_16_810D4(SpDashringObject* object, s16 flags)
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

extern "C" SpDashringObject* fn_16_8118C(SpDashringObject* object, void* owner)
{
	__ct__7TObjectFP7TObject(object, owner);
	fn_8005BE6C((u8*)object + 0x28);
	fn_16_93C3C((u8*)object + 0x30);
	copyVec3(&object->position, object->motion);
	fn_16_900(object->rotation, (u8*)object->motion + 0xC);
	DashringParams* params = *(DashringParams**)((u8*)object->motion + 0x2C);
	object->power          = params->power;
	object->noControlTime  = params->noControlTime;
	object->matrix         = NULL;
	for (s32 i = 0; i < 8; ++i)
		object->playerCooldown[i] = 0;
	fn_16_80F30(object);
	return object;
}

extern "C" void fn_16_812EC(void*, void* motion)
{
	DashringParams* params = *(DashringParams**)((u8*)motion + 0x2C);
	if (params->power < spDashringMinimumPower)
		params->power = spDashringMinimumPower;
	if (params->power > spDashringMaximumPower)
		params->power = spDashringMaximumPower;
	if (params->noControlTime < 0)
		params->noControlTime = 0;
}

extern "C" void fn_16_8137C(void)
{
	fn_16_4D7D8(spDashringVtable);
	fn_16_4E554(spDashringVtable);
}

extern "C" void fn_16_813B0(void) { }

extern "C" void fn_16_81428(void)
{
	SpDashringObject* object = (SpDashringObject*)__nw__10TObjSampleFUl(0x78);
	if (object != NULL)
		fn_16_8118C(object, lbl_8042C110);
}

extern "C" void fn_16_81478(void)
{
	setupObjClass(spDashringRegistration, spDashringDisplayName, (void*)fn_16_813B0,
	    (void*)fn_16_8137C, (void*)fn_16_81428, NULL, 0x20000, 0, 0x1E, 0x15F1, 2, 0,
	    spDashringFieldTypes, spDashringFieldNames);
}

extern "C" void fn_16_81504(SpDashringObject* motionView)
{
	fn_16_812EC((u8*)motionView - 0x28, motionView);
}

__declspec(section ".ctors") void (*const spDashringCtorEntry)(void) = fn_16_81478;
