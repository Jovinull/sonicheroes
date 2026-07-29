#include "types.h"

inline void* operator new(unsigned long, void* address)
{
	return address;
}

extern "C" void* fn_80018A34(void*, u32);
extern "C" void* lbl_8042C148;

struct RwV3d {
	f32 x;
	f32 y;
	f32 z;
};

struct sAngle {
	s32 x;
	s32 y;
	s32 z;
};

struct TObject {
	const char* className;
	u16 flags;
	u8 pad6[0x12];
	void** vtable;
	u8 pad1c[0xc];

	TObject(TObject*);
	~TObject();
	static void* operator new(unsigned long size) { return fn_80018A34(lbl_8042C148, size); }
};

struct C_COLLI {
	u8 data[0x78];

	C_COLLI();
	~C_COLLI();
};

struct TObjEffTornado : TObject {
	C_COLLI effectModel;
	s32 effectType;
	u8 padA4[0xc];
	s32 active;
	s8 kind;
	u8 padB5;
	u16 state;
	RwV3d position;
	sAngle rotation;
	f32 scale;
	u32 timer;
	f32 alpha;

	inline TObjEffTornado(TObject*, s32, RwV3d*, sAngle*);
	~TObjEffTornado();
};

struct TObjEffTyphoon : TObjEffTornado {
	RwV3d velocity;
	void* particle;

	TObjEffTyphoon(TObject*, s32, RwV3d*, sAngle*, RwV3d*);
};

struct TObjEffTornado2 : TObjEffTornado {
	u8 extra[0x10];

	TObjEffTornado2(TObject*, s32, RwV3d*, sAngle*, RwV3d*);
};

extern "C" {
void TDisp__14TObjEffTornadoFv(TObjEffTornado*);
void Exec__14TObjEffTornadoFv(TObjEffTornado*);
int fn_80017800(void*);
void fn_8003C200(void*, void*, s32, s32);
void fn_80021384(void*);
void* fn_8006298C(s32, RwV3d*, sAngle*);
void __dt__7C_COLLIFv(C_COLLI*, s32);
void __dt__7TObjectFv(TObject*, s32);
void __dt__14TObjEffTornadoFv(TObjEffTornado*, s32);
void fn_800189A4(void*, void*);

extern TObject* lbl_8042C2A0;
extern TObject* lbl_8042C110;
extern const char* lbl_8042B350;
extern const char* lbl_8042B360;
extern u8 lbl_8025333C[];
extern void* lbl_8025361C[];
extern f32 lbl_8042DBB0;
extern f32 lbl_8042DBB4;
extern f32 lbl_8042DBB8;

void TDisp__14TObjEffTyphoonFv(TObjEffTyphoon*);
void Exec__14TObjEffTyphoonFv(TObjEffTyphoon*);
TObjEffTyphoon* __dt__14TObjEffTyphoonFv(TObjEffTyphoon*, s32);
void fn_8001898C();
void fn_80018988();
void fn_80018950();
void fn_80018954();
void fn_80017854();
void fn_80018958();
void __ct__15TObjEffTornado2FP7TObjectiP5RwV3dP6sAngleP5RwV3d(
    TObjEffTornado2*, TObject*, s32, RwV3d*, sAngle*, RwV3d*);
}

u32 lbl_802534C0[5] = {
	0xffffffff,
	0x005aaaff,
	0x000000ff,
	0x00a000ff,
	0xff0060ff,
};
char lbl_802534D4[16]  = "TObjEffTyphoon";
void* lbl_802534E4[11] = {
	0,
	0,
	(void*)__dt__14TObjEffTyphoonFv,
	(void*)Exec__14TObjEffTyphoonFv,
	(void*)fn_8001898C,
	(void*)TDisp__14TObjEffTyphoonFv,
	(void*)fn_80018988,
	(void*)fn_80018950,
	(void*)fn_80018954,
	(void*)fn_80017854,
	(void*)fn_80018958,
};

static inline void copyVec(RwV3d* destination, const RwV3d* source)
{
	if (source != 0) {
		destination->x = source->x;
		destination->y = source->y;
		destination->z = source->z;
	}
}

static inline void copyAngle(sAngle* destination, const sAngle* source)
{
	if (source != 0) {
		destination->x = source->x;
		destination->y = source->y;
		destination->z = source->z;
	}
}

extern "C" void TDisp__14TObjEffTyphoonFv(TObjEffTyphoon* effect)
{
	TDisp__14TObjEffTornadoFv(effect);
}

extern "C" void Exec__14TObjEffTyphoonFv(TObjEffTyphoon* effect)
{
	Exec__14TObjEffTornadoFv(effect);
	effect->position.x += effect->velocity.x;
	effect->position.y += effect->velocity.y;
	effect->position.z += effect->velocity.z;
	f32 damping        = lbl_8042DBB0;
	effect->velocity.x = damping * effect->velocity.x;
	effect->velocity.y = damping * effect->velocity.y;
	effect->velocity.z = damping * effect->velocity.z;

	void* particle = effect->particle;
	if (particle != 0) {
		if (fn_80017800(particle) != 0) {
			particle = effect->particle;
			copyVec((RwV3d*)((u8*)particle + 0x80), &effect->position);
			copyAngle((sAngle*)((u8*)particle + 0x8c), &effect->rotation);
		} else {
			effect->particle = 0;
		}
	}
}

extern "C" TObjEffTyphoon* __dt__14TObjEffTyphoonFv(TObjEffTyphoon* effect, s32 shouldDelete)
{
	if (effect != 0) {
		effect->vtable = lbl_802534E4;
		if (effect != 0) {
			effect->vtable = lbl_8025361C;
			__dt__7C_COLLIFv(&effect->effectModel, 0);
			__dt__7TObjectFv(effect, 0);
		}
		if ((s16)shouldDelete > 0) {
			fn_800189A4(lbl_8042C148, effect);
		}
	}
	return effect;
}

#pragma opt_common_subs off
TObjEffTyphoon::TObjEffTyphoon(
    TObject* parent, s32 kind, RwV3d* position, sAngle* rotation, RwV3d* velocity)
    : TObjEffTornado(parent, kind, position, rotation)
{
	TObjEffTyphoon* result = this;

	result->vtable              = lbl_802534E4;
	result->className           = lbl_8042B360;
	*(u16*)((u8*)result + 0x1e) = 0xec;
	if (velocity != 0) {
		result->velocity.x = velocity->x;
		result->velocity.y = velocity->y;
		result->velocity.z = velocity->z;
	} else {
		f32 zeroVelocity   = lbl_8042DBB4;
		result->velocity.z = zeroVelocity;
		result->velocity.y = zeroVelocity;
		result->velocity.x = zeroVelocity;
	}
	result->particle = fn_8006298C(14, &result->position, &result->rotation);
}
#pragma opt_common_subs reset

extern "C" void SetEffectTyphoon__FP7TObjectiP5RwV3dP6sAngleP5RwV3d(
    TObject* parent, s32 kind, RwV3d* position, sAngle* rotation, RwV3d* velocity)
{
	if (parent == 0) {
		parent = lbl_8042C2A0;
		if (parent == 0) {
			parent = lbl_8042C110;
		}
	}

	new TObjEffTyphoon(parent, kind, position, rotation, velocity);
}

extern "C" void SetEffectTornado2__FP7TObjectiP5RwV3dP6sAngleP5RwV3d(
    TObject* parent, s32 kind, RwV3d* position, sAngle* rotation, RwV3d* velocity)
{
	if (parent == 0) {
		parent = lbl_8042C2A0;
		if (parent == 0) {
			parent = lbl_8042C110;
		}
	}

	new TObjEffTornado2(parent, kind, position, rotation, velocity);
}

TObjEffTornado::TObjEffTornado(TObject* parent, s32 kind, RwV3d* position, sAngle* rotation)
    : TObject(parent)
{
	TObjEffTornado* base      = this;
	base->vtable              = lbl_8025361C;
	base->className           = lbl_8042B350;
	*(u16*)((u8*)base + 0x1e) = 0xdc;
	base->position.x          = position->x;
	base->position.y          = position->y;
	base->position.z          = position->z;
	if (rotation != 0) {
		base->rotation.x = rotation->x;
		base->rotation.y = rotation->y;
		base->rotation.z = rotation->z;
	} else {
		base->rotation.z = 0;
		base->rotation.y = 0;
		base->rotation.x = 0;
	}
	base->state      = 0;
	f32 initialValue = lbl_8042DBB4;
	base->alpha      = initialValue;
	base->scale      = initialValue;
	base->kind       = kind;
	base->active     = 1;
	base->timer      = 0;
	fn_8003C200(&base->effectModel, lbl_8025333C, 1, 1);

	s32 effectType;
	switch (base->kind) {
		case 0:
			effectType = 7;
			break;
		case 1:
			effectType = 8;
			break;
		case 2:
			effectType = 9;
			break;
		case 3:
			effectType = 10;
			break;
		default:
			effectType = 0;
			break;
	}
	base->effectType = effectType;
	if (base->effectType == 0) {
		u8* model = *(u8**)&base->effectModel.data[0x10];
		u32 flags = model[3];
		flags &= ~3;
		model[3] = flags;
	}
	*(u16*)&base->effectModel.data[4] = 0;
	void* model                       = *(void**)&base->effectModel.data[0x10];
	if (model != 0) {
		((RwV3d*)((u8*)model + 8))->x = base->position.x;
		((RwV3d*)((u8*)model + 8))->y = base->position.y;
		((RwV3d*)((u8*)model + 8))->z = base->position.z;
		model                         = *(void**)&base->effectModel.data[0x10];
		((RwV3d*)((u8*)model + 8))->y += lbl_8042DBB8;
		fn_80021384(&base->effectModel);
	}
}
