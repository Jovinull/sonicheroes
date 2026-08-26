#include "types.h"

// Stage40 editor object that places and updates a configurable set of particle
// emitters. The retail data names the object "PUT PARTICLE" and describes its
// editable emitter slots. This TU owns the complete object method family,
// registration record, constructor entry, vtable/data, and parameter storage.

struct PutParticleParams {
	s8 count;
	s8 selected;
	s8 mode;
	s8 emitter;
	s8 emitters[6];
};

struct PutParticleObject {
	u8 base[0x28];
	void* motion;
	u8 pad2C[0xC];
	void** particles;
	s32 count;
	s8* emitters;
	s32 selected;
	s8 mode;
	u8 pad49[3];
	s32 emitter;
};

extern "C" {
void markSampleForDeletion(void*);
void* __nw__10TObjSampleFUl(u32);
void __dl__10TObjSampleFPv(void*);
void __ct__7TObjectFP7TObject(void*, void*);
void __dt__7TObjectFv(void*, s16);
void fn_8005BE6C(void*);
void dtor_8005BD3C(void*, s16);
void fn_16_93C3C(void*);
void fn_16_93BE8(void*, s32);
void* fn_16_528A4(s32, s32, void*, void*, s32, s32, s32);
void fn_16_52ACC(void*, void*);
void fn_16_52A6C(void*, void*);
void fn_16_4E384(void*);
void* setupObjClass(
    void*, char*, void*, void*, void*, void*, u32, u32, u8, u16, u16, u8, char*, char**);

extern void* lbl_8042C110;
}

char putParticleClassName[] = "PUTPARTICLE";
void* putParticleVtable[15];
char putParticleDisplayName[] = "PUT PARTICLE";
char putParticleFieldTypes[]  = "ccccccccc";
char* putParticleFieldNames[9];
u8 putParticleRegistration[0x80];

extern "C" void fn_16_7EDF4(PutParticleObject* object)
{
	PutParticleParams* params = *(PutParticleParams**)((u8*)object->motion + 0x2C);
	object->selected          = params->emitter;
	object->mode              = params->selected;
	object->emitter           = params->emitters[0];
}

extern "C" void fn_16_7EE30(PutParticleObject* object)
{
	if (object->particles != NULL) {
		for (s32 i = 0; i < object->count; ++i) {
			if (object->particles[i] != NULL)
				markSampleForDeletion(object->particles[i]);
		}
	}
}

extern "C" void fn_16_7EEE0(PutParticleObject* object, s32 count)
{
	fn_16_7EE30(object);
	object->count = count;
}

extern "C" void fn_16_7F0A8(void) { }

extern "C" void fn_16_7F0AC(PutParticleObject* object)
{
	for (s32 i = 0; i < object->count; ++i) {
		if (object->particles[i] != NULL) {
			fn_16_52ACC(object->particles[i], object->motion);
			fn_16_52A6C(object->particles[i], (u8*)object->motion + 0xC);
		}
	}
}

extern "C" void fn_16_7F1F4(PutParticleObject* object)
{
	if (object->particles != NULL) {
		for (s32 i = 0; i < object->count; ++i) {
			if (object->particles[i] != NULL)
				markSampleForDeletion(object->particles[i]);
			object->particles[i] = NULL;
		}
	}
}

extern "C" void fn_16_7F27C(PutParticleObject* object, s8 index)
{
	if (object->particles[index] != NULL)
		markSampleForDeletion(object->particles[index]);
	object->particles[index] = NULL;
	if (object->emitters[index] >= 0)
		object->particles[index] = fn_16_528A4(
		    0, object->emitters[index] + 0x23, object->motion, (u8*)object->motion + 0xC, 0, 0, 1);
}

extern "C" void fn_16_7F34C(PutParticleObject* object)
{
	for (s32 i = 0; i < object->count; ++i)
		fn_16_7F27C(object, (s8)i);
}

extern "C" void fn_16_7F418(PutParticleObject* object, s8 index)
{
	if (object->particles[index] != NULL)
		markSampleForDeletion(object->particles[index]);
	object->particles[index] = NULL;
}

extern "C" void fn_16_7F48C(PutParticleObject* object)
{
	PutParticleParams* params = *(PutParticleParams**)((u8*)object->motion + 0x2C);
	if (object->count != params->count)
		fn_16_7EEE0(object, params->count);
	fn_16_7EDF4(object);
}

extern "C" PutParticleObject* fn_16_7F70C(PutParticleObject* object, s16 flags)
{
	if (object != NULL) {
		fn_16_7EE30(object);
		fn_16_93BE8((u8*)object + 0x30, 0);
		dtor_8005BD3C((u8*)object + 0x28, 0);
		__dt__7TObjectFv(object, 0);
		if (flags > 0)
			__dl__10TObjSampleFPv(object);
	}
	return object;
}

extern "C" void fn_16_7F7A0(PutParticleObject* object)
{
	PutParticleParams* params = *(PutParticleParams**)((u8*)object->motion + 0x2C);
	for (s32 i = 0; i < object->count; ++i) {
		object->emitters[i] = params->emitters[i];
		if (object->emitters[i] >= 0)
			object->particles[i] = fn_16_528A4(
			    0, object->emitters[i] + 0x23, object->motion, (u8*)object->motion + 0xC, 0, 0, 0);
	}
}

extern "C" void fn_16_7F858(PutParticleObject* object)
{
	object->particles = NULL;
	object->count     = 0;
	object->emitters  = NULL;
}

extern "C" PutParticleObject* fn_16_7F874(PutParticleObject* object, void* owner)
{
	__ct__7TObjectFP7TObject(object, owner);
	fn_8005BE6C((u8*)object + 0x28);
	fn_16_93C3C((u8*)object + 0x30);
	fn_16_7F858(object);
	PutParticleParams* params = *(PutParticleParams**)((u8*)object->motion + 0x2C);
	fn_16_7EEE0(object, params->count == 0 ? 1 : params->count);
	fn_16_7F7A0(object);
	return object;
}

extern "C" void fn_16_7F990(void)
{
	PutParticleObject* object = (PutParticleObject*)__nw__10TObjSampleFUl(0x50);
	if (object != NULL)
		fn_16_7F874(object, lbl_8042C110);
}

extern "C" void fn_16_7F9E0(void)
{
	setupObjClass(putParticleRegistration, putParticleDisplayName, NULL, NULL, (void*)fn_16_7F990,
	    NULL, 0, 0, 0x32, 0x15EB, 2, 0, putParticleFieldTypes, putParticleFieldNames);
}

extern "C" void fn_16_7FA64(PutParticleObject* motionView)
{
	fn_16_7F48C((PutParticleObject*)((u8*)motionView - 0x28));
}

extern "C" void fn_16_7FA6C(void)
{
	fn_16_4E384(putParticleVtable);
}

__declspec(section ".ctors") void (*const putParticleCtorEntry)(void) = fn_16_7F9E0;
