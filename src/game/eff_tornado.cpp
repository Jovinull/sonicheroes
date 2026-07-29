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
void* fn_8005EA04(const char*);
void* fn_8005E410(void*, s32, void*);
void* fn_8005E1DC(void*, s32, void*);
void fn_8005DA34(void*);
void fn_8005D9F4(void*);
void fn_8005D6DC(void*);
void fn_8005C014(void*);
void fn_800BD02C(void*, void*, void*);
void* fn_800BD0AC(void*, void*);
void fn_8020C72C(void*, void*);
void fn_8013F3A4(void*);
void fn_801491A8(void*);
void __dt__7C_COLLIFv(C_COLLI*, s32);
void __dt__7TObjectFv(TObject*, s32);
TObjEffTornado* __dt__14TObjEffTornadoFv(TObjEffTornado*, s32);
void fn_800189A4(void*, void*);

extern TObject* lbl_8042C2A0;
extern TObject* lbl_8042C110;
extern void* lbl_8042C350;
extern void* lbl_8042C354;
extern void* lbl_8042C358;
extern void* lbl_8042C35C;
extern void* lbl_8042C368;
extern void* lbl_8042C36C;
extern void* lbl_8042C370;
extern void* lbl_8042C374;
extern void* lbl_8042C360;
extern void* lbl_8042C364;
extern u8 lbl_8042C3D0[];
extern u8 lbl_8042B364[];
extern u8 lbl_8042B36C[];
extern void* lbl_80303F98;
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

void* lbl_802532E8[3] = { 0, 0, 0 };
void* lbl_802532F4[3] = { 0, 0, 0 };
char lbl_80253300[]   = "EF_TORNADE.DFF";
char lbl_80253310[]   = "EF_TORNADEB.DFF";
char lbl_80253320[]   = "EF_TORNADEC.DFF";
char* lbl_80253330[3] = { lbl_80253300, lbl_80253310, lbl_80253320 };
u8 lbl_8025333C[0x30] = {
	0x0a,
	0x0a,
	0xf0,
	0xe2,
	0x00,
	0x20,
	0x20,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x42,
	0x70,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x41,
	0xa0,
	0x00,
	0x00,
	0x42,
	0x70,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
};
char lbl_80253568[] = "EF_TORNADO.DFF";
char lbl_80253578[] = "EF_TORNADO_RING.DFF";
char lbl_8025358C[] = "EF_TORNADO_RINGB.DFF";
char lbl_802535A4[] = "EF_TORNADO.ANM";
char lbl_802535B4[] = "EF_TORNADO.UVB";
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

extern "C" TObjEffTornado* __dt__14TObjEffTornadoFv(TObjEffTornado* effect, s32 shouldDelete)
{
	if (effect != 0) {
		effect->vtable = lbl_8025361C;
		__dt__7C_COLLIFv(&effect->effectModel, 0);
		__dt__7TObjectFv(effect, 0);
		if ((s16)shouldDelete > 0) {
			fn_800189A4(lbl_8042C148, effect);
		}
	}
	return effect;
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

extern "C" void SetEffectTornado__FP7TObjectiP5RwV3dP6sAngle(
    TObject* parent, s32 kind, RwV3d* position, sAngle* rotation)
{
	if (parent == 0) {
		parent = lbl_8042C2A0;
		if (parent == 0) {
			parent = lbl_8042C110;
		}
	}

	new TObjEffTornado(parent, kind, position, rotation);
}

extern "C" void EndEffTornado__Fv()
{
	lbl_802532E8[0] = 0;
	lbl_802532F4[0] = 0;
	lbl_802532E8[1] = 0;
	lbl_802532F4[1] = 0;
	lbl_802532E8[2] = 0;
	lbl_802532F4[2] = 0;
	lbl_8042C350    = 0;
	lbl_8042C354    = 0;
	lbl_8042C358    = 0;
	lbl_8042C35C    = 0;
	lbl_8042C36C    = 0;
	lbl_8042C368    = 0;
	lbl_8042C370    = 0;
	lbl_8042C374    = 0;
}

extern "C" void InitEffTornado__Fv()
{
	for (s32 i = 0; i < 3; ++i) {
		if (lbl_802532E8[i] == 0) {
			lbl_802532E8[i] = fn_8005EA04(lbl_80253330[i]);
			if (lbl_802532E8[i] != 0) {
				lbl_802532F4[i] = fn_8005E410(lbl_802532E8[i], 0, lbl_8042B364);
			}
		}
	}

	lbl_8042C350 = fn_8005EA04(lbl_80253568);
	if (lbl_8042C350 != 0) {
		lbl_8042C354 = fn_8005E410(lbl_8042C350, 0, lbl_8042B36C);
		lbl_8042C370 = lbl_8042C354;
		lbl_8042C368 = fn_800BD0AC(lbl_8042C3D0, lbl_8042C350);
		fn_8005D9F4(lbl_8042C350);
		fn_8005D6DC(lbl_8042C350);
	}

	lbl_8042C358 = fn_8005EA04(lbl_80253578);
	if (lbl_8042C358 != 0) {
		lbl_8042C35C = fn_8005E410(lbl_8042C358, 0, lbl_8042B36C);
		fn_8005DA34(lbl_8042C358);
		fn_8005D9F4(lbl_8042C358);
		fn_8005D6DC(lbl_8042C358);
	}

	lbl_8042C360 = fn_8005EA04(lbl_8025358C);
	if (lbl_8042C360 != 0) {
		lbl_8042C364 = fn_8005E410(lbl_8042C360, 0, lbl_8042B36C);
		fn_8005DA34(lbl_8042C360);
		fn_8005D9F4(lbl_8042C360);
		fn_8005D6DC(lbl_8042C360);
	}

	lbl_8042C36C = fn_8005EA04(lbl_802535A4);
	if (lbl_8042C36C != 0 && lbl_8042C368 != 0) {
		fn_800BD02C(lbl_8042C3D0, lbl_8042C350, lbl_8042C368);
		*(u32*)lbl_8042C368 |= 0x3000;
		fn_8020C72C(*(void**)((u8*)lbl_8042C368 + 0x20), lbl_8042C36C);
		fn_8013F3A4(lbl_8042C368);
	}

	lbl_8042C374 = fn_8005EA04(lbl_802535B4);
	if (lbl_8042C374 != 0 && lbl_8042C370 != 0) {
		void* material = fn_8005E1DC(lbl_8042C350, 0, lbl_8042B36C);
		lbl_80303F98   = lbl_8042C374;
		fn_8005C014(material);
		fn_801491A8(material);
	}
}
