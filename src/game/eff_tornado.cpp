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

struct Rgba {
	u8 red;
	u8 green;
	u8 blue;
	u8 alpha;
};

struct Material {
	u32 pad;
	u8 red;
	u8 green;
	u8 blue;
	u8 alpha;
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
	s16 state;
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
	u8 opacity;
	s8 direction;
	u8 padDE[2];
	f32 swirlScale;
	f32 verticalScale;
	u8 color[4];

	TObjEffTornado2(TObject*, s32, RwV3d*, sAngle*, RwV3d*);
	~TObjEffTornado2();
	void TDisp();
};

struct PlayerColorSource {
	u8 pad0[0x34];
	s32 team;
};

struct TObjEffTornadoSpin : TObject {
	s32 state;
	s16 timer;
	s16 angle;
	RwV3d position;
	RwV3d direction;
	void* model;
	f32 alpha;

	inline TObjEffTornadoSpin(TObject*, const RwV3d*, const RwV3d*);
};

struct CollisionSearchResult {
	u32 unknown;
	void* object;
};

struct RotationPair {
	f32 cosine;
	f32 sine;
};

struct Color {
	u8 red;
	u8 green;
	u8 blue;
	u8 alpha;
};

enum CHARACTER_ID {
	CHARACTER_ID_0 = 0,
	CHARACTER_ID_1,
	CHARACTER_ID_2,
	CHARACTER_ID_3,
	CHARACTER_ID_4,
	CHARACTER_ID_5,
	CHARACTER_ID_6,
	CHARACTER_ID_7,
	CHARACTER_ID_8,
	CHARACTER_ID_9,
	CHARACTER_ID_10,
};

extern "C" {
void TDisp__14TObjEffTornadoFv(TObjEffTornado*);
void Exec__14TObjEffTornadoFv(TObjEffTornado*);
int fn_80017800(void*);
void fn_8003C200(void*, void*, s32, s32);
void fn_80021384(void*);
void* fn_8006298C(s32, RwV3d*, sAngle*);
void* fn_8005EA04(const char*);
void* fn_8005E410(void*, s32, const void*);
void* fn_8005E1DC(void*, s32, const void*);
void fn_8005DA34(void*);
void fn_8005D9F4(void*);
void fn_8005D6DC(void*);
void fn_8005C014(void*);
void fn_800BD02C(void*, void*, void*);
void* fn_800BD0AC(void*, void*);
void fn_8020C72C(void*, void*);
void fn_8013F3A4(void*);
void fn_801491A8(void*);
int fn_801C28D8();
void* fn_80150588(void*);
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
extern s32 lbl_8042C378[2];
extern void* lbl_8042C360;
extern void* lbl_8042C364;
extern void* lbl_8042C180;
extern Rgba lbl_8042B35C;
extern u8 lbl_8042C3D0[4];
extern void* lbl_80303F98[3];
extern const char* lbl_8042B350;
extern const char* lbl_8042B358;
extern const char* lbl_8042B360;
extern const char* lbl_8042B354;
extern u8 lbl_8025333C[];
extern void* lbl_8025361C[];
extern void* lbl_802532E8[3];
extern void* lbl_802532F4[3];
extern char lbl_80253300[];
extern char lbl_80253310[];
extern char lbl_80253320[];
extern char* lbl_80253330[3];
extern char lbl_80253568[];
extern char lbl_80253578[];
extern char lbl_8025358C[];
extern char lbl_802535A4[];
extern char lbl_802535B4[];
extern char lbl_8025336C[];
extern char lbl_8025349C[];
extern char lbl_802534B0[];
extern char lbl_802534D4[];
extern f32 lbl_8042DBB0;
extern f32 lbl_8042DBB4;
extern f32 lbl_8042DBB8;
extern f32 lbl_8042DBBC;
extern f32 lbl_8042DBC0;
extern f32 lbl_8042DBC8;
extern f32 lbl_8042DBE0;
extern f32 lbl_8042DBE8;
extern f32 lbl_8042DBF0;
extern f32 lbl_8042DBF4;
extern f32 lbl_8042DBC4;
extern f32 lbl_8042DC08;
extern f32 lbl_8042DBE4;
extern f32 lbl_8042DBEC;
extern f32 lbl_8042DBF8;
extern f32 lbl_8042DBFC;
extern f32 lbl_8042DC00;
extern f32 lbl_8042DC04;
extern f32 lbl_8042DC0C;
extern f32 lbl_8042DC10;
extern f32 lbl_8042DC14;
extern f32 lbl_8042DC18;
extern f32 lbl_8042DC1C;
extern f32 lbl_8042DC20;
extern f32 lbl_8042DC24;

extern u8 lbl_8029C310[];
extern u8 lbl_802D5E80[];
extern void* lbl_802AD070[];
extern u8 lbl_8042C1A4;
extern RwV3d lbl_80239978;
extern RwV3d lbl_80239984;
extern void* lbl_802535F0[];
extern RwV3d lbl_8025337C[];
extern RwV3d lbl_802533DC[];
extern RotationPair lbl_8025343C[];
extern s32 lbl_8025347C[];
extern void* lbl_802535C4[];
extern PlayerColorSource* lbl_80303DC8[];

void fn_80194294(s32, u32*);
void fn_80194234(s32, u32);
void fn_80053660(void*, s32);
void fn_8005349C(void*, u8);
void fn_8014FF2C(void*);
int fn_8005BB20(RwV3d*, f32);
f32 fn_800D7328(f32, f32, f32);
void fn_80021824(void*);
CollisionSearchResult* fn_80020BD8(void*, s32);
void fn_80150958(void*);
void fn_8019EC30(void*, RwV3d*, s32);
f32 fn_800D7B00(s32);
f32 fn_800D7AE4(s32);
void fn_80195790(void*, RwV3d*, f32, f32, s32);
void fn_8019E880(void*);
void fn_8019EB94(void*, RwV3d*, s32);
void fn_8003BC38(C_COLLI*);
void fn_8003BE78(C_COLLI*);
void GXSetBlendMode(s32, s32, s32, s32);
void fn_8011B844(f32);
void fn_8014FFBC(void*, void*, void*);
void fn_8005BF88();
void fn_8020CC18(void*, f32);
void fn_8013FC30(void*);

void TDisp__18TObjEffTornadoSpinFv(TObjEffTornadoSpin*);
void Exec__18TObjEffTornadoSpinFv(TObjEffTornadoSpin*);
TObjEffTornadoSpin* __dt__18TObjEffTornadoSpinFv(TObjEffTornadoSpin*, s32);
void TDisp__15TObjEffTornado2Fv(TObjEffTornado2*);
void Exec__15TObjEffTornado2Fv(TObjEffTornado2*);
int SetPosition__18TObjEffTornadoSpinFv(TObjEffTornadoSpin*);
int CheckTornado__FP7C_COLLI(C_COLLI*);

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

extern "C" void TDisp__18TObjEffTornadoSpinFv(TObjEffTornadoSpin* effect)
{
	u32 state10;
	u32 state11;
	u32 state20;
	u32 state14;
	fn_80194294(10, &state10);
	fn_80194294(11, &state11);
	fn_80194294(20, &state20);
	fn_80194294(14, &state14);
	fn_80194234(10, 5);
	fn_80194234(11, 2);
	fn_80194234(20, 1);
	fn_80194234(14, 0);

	u8* material     = *(u8**)((u8*)lbl_802532F4 + 4);
	u32 saved        = *(u32*)(material + 4);
	((u8*)&saved)[3] = (u8)(effect->alpha * lbl_8042DC14);
	material[4]      = ((u8*)&saved)[0];
	material[5]      = ((u8*)&saved)[1];
	material[6]      = ((u8*)&saved)[2];
	material[7]      = ((u8*)&saved)[3];

	fn_80053660(lbl_802D5E80, 16);
	fn_8005349C(lbl_802D5E80, lbl_802D5E80[0x4be]);
	fn_8014FF2C(effect->model);

	fn_80194234(14, state14);
	fn_80194234(20, state20);
	fn_80194234(10, state10);
	fn_80194234(11, state11);
}

extern "C" void Exec__18TObjEffTornadoSpinFv(TObjEffTornadoSpin* effect)
{
	if (fn_8005BB20(&effect->direction, lbl_8042DBE0) != 0 || *(s32*)(lbl_8029C310 + 0x18) != 0) {
		effect->flags |= 1;
		return;
	}

	switch (effect->state) {
		case 1:
			effect->alpha = fn_800D7328(effect->alpha, lbl_8042DBC0, lbl_8042DBE8);
			if (effect->alpha >= lbl_8042DBC0) {
				effect->state = 2;
				effect->timer = 0;
			}
			break;
		case 2: {
			s16 timer = effect->timer;
			effect->timer++;
			if ((f32)timer >= lbl_8042DC18) {
				effect->state = 3;
			}
			break;
		}
		case 3:
			effect->alpha = fn_800D7328(effect->alpha, lbl_8042DBB4, lbl_8042DBE8);
			if (effect->alpha <= lbl_8042DBB4) {
				effect->state = 4;
			}
			break;
		case 4:
			effect->flags |= 1;
			return;
	}

	effect->angle += 0x1000;
	void* frame = *(void**)((u8*)effect->model + 4);
	fn_8019EC30(frame, &effect->position, 0);
	f32 sine   = fn_800D7B00(effect->angle);
	f32 cosine = lbl_8042DBC0 - fn_800D7AE4(effect->angle);
	fn_80195790((u8*)frame + 0x10, &lbl_80239984, cosine, sine, 2);
	fn_8019E880(frame);
	fn_8019EB94(frame, &effect->direction, 2);
}

extern "C" TObjEffTornadoSpin* __dt__18TObjEffTornadoSpinFv(
    TObjEffTornadoSpin* effect, s32 shouldDelete)
{
	if (effect != 0) {
		effect->vtable = lbl_802535F0;
		if (effect->model != 0) {
			fn_80150958(effect->model);
			effect->model = 0;
		}
		__dt__7TObjectFv(effect, 0);
		if ((s16)shouldDelete > 0) {
			fn_800189A4(lbl_8042C148, effect);
		}
	}
	return effect;
}

static inline s32 tornadoTeamFromObject(void* collision)
{
	CHARACTER_ID type = *(CHARACTER_ID*)((u8*)collision + 0x78);
	void* team;
	s32 teamNumber;
	team = 0;
	switch (type) {
		case 0:
			teamNumber = 0;
			break;
		case 1:
			teamNumber = 1;
			break;
		case 2:
			teamNumber = 2;
			break;
		case 3:
			teamNumber = 3;
			break;
		case 4:
			team = lbl_802AD070[0];
			break;
		case 5:
			team = lbl_802AD070[1];
			break;
		case 6:
			team = lbl_802AD070[2];
			break;
		case 7:
			team = lbl_802AD070[3];
			break;
		case 8:
			team = lbl_802AD070[4];
			break;
		case 9:
			team = lbl_802AD070[5];
			break;
		case 10:
		default:
			teamNumber = -1;
			break;
	}
	if (team != 0) {
		teamNumber = *(s8*)((u8*)team + 0x9bc);
	}
	return teamNumber;
}

extern "C" int SetPosition__18TObjEffTornadoSpinFv(TObjEffTornadoSpin* effect)
{
	fn_80021824(&lbl_8042C1A4);
	CollisionSearchResult* result = fn_80020BD8(effect, 10);
	void* object                  = result != 0 ? result->object : 0;
	if (object != 0) {
		return tornadoTeamFromObject(object);
	}
	result = fn_80020BD8(effect, 16);
	object = result != 0 ? result->object : 0;
	if (object != 0) {
		return tornadoTeamFromObject(object);
	}
	return -1;
}

extern "C" int CheckTornado__FP7C_COLLI(C_COLLI* collision)
{
	fn_80021824(&lbl_8042C1A4);
	if (fn_80020BD8(collision, 10) != 0) {
		return 1;
	}
	return fn_80020BD8(collision, 16) != 0;
}

TObjEffTornadoSpin::TObjEffTornadoSpin(
    TObject* parent, const RwV3d* directionValue, const RwV3d* positionValue)
    : TObject(parent)
{
	TObjEffTornadoSpin* result  = this;
	result->vtable              = lbl_802535F0;
	result->className           = lbl_8042B354;
	*(u16*)((u8*)result + 0x1e) = 0x50;
	result->direction.x         = directionValue->x;
	result->direction.y         = directionValue->y;
	result->direction.z         = directionValue->z;
	result->position.x          = positionValue->x;
	result->position.y          = positionValue->y;
	result->position.z          = positionValue->z;
	result->timer               = 0;
	result->alpha               = lbl_8042DBB4;
	result->angle               = (s16)(fn_801C28D8() * lbl_8042DC20 * lbl_8042DC1C);
	result->state               = 1;
	result->model               = fn_80150588(lbl_802532E8[1]);

	void* frame = *(void**)((u8*)result->model + 4);
	fn_8019EC30(frame, &result->position, 0);
	f32 sine   = fn_800D7B00(result->angle);
	f32 cosine = lbl_8042DBC0 - fn_800D7AE4(result->angle);
	fn_80195790((u8*)frame + 0x10, &lbl_80239984, cosine, sine, 2);
	fn_8019E880(frame);
	fn_8019EB94(frame, &result->direction, 2);
}

u32 lbl_802534C0[5] = {
	0xffffffff,
	0x005aaaff,
	0x000000ff,
	0x00a000ff,
	0xff0060ff,
};
char lbl_802534D4[]    = "TObjEffTyphoon";
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

static inline void copyColor(u8* destination, const u8* source)
{
	destination[0] = source[0];
	destination[1] = source[1];
	destination[2] = source[2];
	destination[3] = source[3];
}

static inline void copyAngle(sAngle* destination, const sAngle* source)
{
	if (source != 0) {
		destination->x = source->x;
		destination->y = source->y;
		destination->z = source->z;
	}
}

static inline void* tornadoModel(void** models, s32 index)
{
	return models[index];
}

static inline void* tornadoFrame(void* model)
{
	return *(void**)((u8*)model + 4);
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
extern "C" void TDisp__14TObjEffTornadoFv(TObjEffTornado* effect)
{
	u32 state10;
	u32 state11;
	u32 state20;
	u32 state14;
	fn_80194294(10, &state10);
	fn_80194294(11, &state11);
	fn_80194294(20, &state20);
	fn_80194294(14, &state14);
	fn_80194234(10, 5);
	fn_80194234(11, 2);
	fn_80194234(20, 1);
	fn_80194234(14, 0);

	f32 height       = lbl_8042DBB4;
	s8 index         = 0;
	void** resources = lbl_802532F4;
	u8* material     = (u8*)resources[0];
	Color color      = *(Color*)(material + 4);
	f32 multiplier;
	color.alpha = (u8)(effect->alpha * (multiplier = lbl_8042DBF4));
	material[4] = color.red;
	material[5] = color.green;
	material[6] = color.blue;
	material[7] = color.alpha;

	material    = (u8*)resources[1];
	color.red   = material[4];
	color.green = material[5];
	color.blue  = material[6];
	color.alpha = material[7];
	color.alpha = (u8)(effect->alpha * multiplier);
	material[4] = color.red;
	material[5] = color.green;
	material[6] = color.blue;
	material[7] = color.alpha;

	material    = (u8*)resources[2];
	color.red   = material[4];
	color.green = material[5];
	color.blue  = material[6];
	color.alpha = material[7];
	color.alpha = (u8)(effect->alpha * multiplier);
	material[4] = color.red;
	material[5] = color.green;
	material[6] = color.blue;
	material[7] = color.alpha;

	fn_80053660(lbl_802D5E80, 16);
	fn_8005349C(lbl_802D5E80, lbl_802D5E80[0x4be]);

	s32 angle = (s32)(lbl_8042DBC4 * effect->scale);
	void** models;
	RwV3d* positions;
	RwV3d* directions;
	RotationPair* rotations;
	RwV3d* firstAxis;
	s32* angleOffsets;
	RwV3d* secondAxis;
	{
		models       = lbl_802532E8;
		positions    = lbl_8025337C;
		directions   = lbl_802533DC;
		rotations    = lbl_8025343C;
		firstAxis    = &lbl_80239978;
		f32 one      = lbl_8042DBC0;
		angleOffsets = lbl_8025347C;
		secondAxis   = &lbl_80239984;
		f32 sine;
		f32 increment = lbl_8042DC24;
		f32 limit     = lbl_8042DBB8;
		while (height <= limit) {
			void* model = tornadoModel(models, 0);
			void* frame = tornadoFrame(model);
			s32 tableIndex;
			s32 vectorOffset;
			fn_8019EC30(frame,
			    (RwV3d*)((u8*)positions
			        + (vectorOffset = (tableIndex = index & 7) * sizeof(RwV3d))),
			    0);
			fn_8019EB94(frame, (RwV3d*)((u8*)directions + vectorOffset), 2);
			RotationPair* pair = &rotations[tableIndex];
			fn_80195790((u8*)frame + 0x10, firstAxis, one - pair->cosine, pair->sine, 2);
			s32 angleByteOffset = tableIndex * sizeof(s32);
			s32* angleEntry     = (s32*)((u8*)angleOffsets + angleByteOffset);
			sine                = fn_800D7B00(angle + *angleEntry);
			f32 cosine          = one - fn_800D7AE4(angle + *angleEntry);
			fn_80195790((u8*)frame + 0x10, secondAxis, cosine, sine, 2);
			fn_8019E880(frame);
			RwV3d position = effect->position;
			position.y += height;
			fn_8019EB94(frame, &position, 2);
			fn_8014FF2C(model);
			height += increment;
			index++;
			angle += 0x3b05;
		}
	}

	{
		models       = lbl_802532E8;
		positions    = lbl_8025337C;
		directions   = lbl_802533DC;
		rotations    = lbl_8025343C;
		firstAxis    = &lbl_80239978;
		f32 one      = lbl_8042DBC0;
		angleOffsets = lbl_8025347C;
		secondAxis   = &lbl_80239984;
		f32 sine;
		f32 limit;
		f32 increment = lbl_8042DC24;
		limit         = lbl_8042DBF0;
		while (height <= limit) {
			void* model = tornadoModel(models, 1);
			void* frame = tornadoFrame(model);
			s32 tableIndex;
			s32 vectorOffset;
			fn_8019EC30(frame,
			    (RwV3d*)((u8*)positions
			        + (vectorOffset = (tableIndex = index & 7) * sizeof(RwV3d))),
			    0);
			fn_8019EB94(frame, (RwV3d*)((u8*)directions + vectorOffset), 2);
			RotationPair* pair = &rotations[tableIndex];
			fn_80195790((u8*)frame + 0x10, firstAxis, one - pair->cosine, pair->sine, 2);
			s32 angleByteOffset = tableIndex * sizeof(s32);
			s32* angleEntry     = (s32*)((u8*)angleOffsets + angleByteOffset);
			sine                = fn_800D7B00(angle + *angleEntry);
			f32 cosine          = one - fn_800D7AE4(angle + *angleEntry);
			fn_80195790((u8*)frame + 0x10, secondAxis, cosine, sine, 2);
			RwV3d position = effect->position;
			position.y += height;
			fn_8019EB94(frame, &position, 2);
			fn_8014FF2C(model);
			height += increment;
			index++;
			angle += 0x127d;
		}
	}

	{
		s32 count  = 0;
		models     = lbl_802532E8;
		positions  = lbl_8025337C;
		directions = lbl_802533DC;
		rotations  = lbl_8025343C;
		firstAxis  = &lbl_80239978;
		f32 sine;
		f32 one      = lbl_8042DBC0;
		angleOffsets = lbl_8025347C;
		do {
			void* model = tornadoModel(models, 2);
			void* frame = tornadoFrame(model);
			s32 vectorOffset;
			s32 tableIndex;
			fn_8019EC30(frame,
			    (RwV3d*)((u8*)positions
			        + (vectorOffset = (tableIndex = index & 7) * sizeof(RwV3d))),
			    0);
			fn_8019EB94(frame, (RwV3d*)((u8*)directions + vectorOffset), 2);
			RotationPair* pair = &rotations[tableIndex];
			fn_80195790((u8*)frame + 0x10, firstAxis, one - pair->cosine, pair->sine, 2);
			vectorOffset = tableIndex * sizeof(s32);
			sine         = fn_800D7B00(angle + *(s32*)((u8*)angleOffsets + vectorOffset));
			f32 cosine   = one - fn_800D7AE4(angle + *(s32*)((u8*)angleOffsets + vectorOffset));
			fn_80195790((u8*)frame + 0x10, &lbl_80239984, cosine, sine, 2);
			RwV3d position = effect->position;
			position.y += height;
			fn_8019EB94(frame, &position, 2);
			fn_8014FF2C(model);
			index++;
			angle += 0x2666;
			count++;
		} while (count < 4);
	}

	fn_80194234(14, state14);
	fn_80194234(20, state20);
	fn_80194234(10, state10);
	fn_80194234(11, state11);
}
#pragma opt_common_subs reset

#pragma peephole on
void TObjEffTornado2::TDisp()
{
	u32 saved10;
	u32 saved11;
	u32 saved20;
	u32 saved14;
	void* model;
	s32 frame;
	u32 blue;
	u32 red;
	u32 green;
	u32 alpha;

	fn_80194294(10, &saved10);
	fn_80194294(11, &saved11);
	fn_80194294(20, &saved20);
	fn_80194294(14, &saved14);

	red = this->color[0], green = this->color[1], blue = this->color[2], alpha = this->color[3];
	if (red != 0 || green != 0 || blue != 0) {
		fn_80194234(10, 5);
		fn_80194234(11, 2);
		fn_80194234(20, 1);
	} else {
		fn_80194234(10, 5);
		fn_80194234(11, 2);
		GXSetBlendMode(3, 4, 1, 0);
		fn_80194234(20, 1);
		red   = (s32)((f32)lbl_8042B35C.red * this->alpha);
		green = (s32)((f32)lbl_8042B35C.green * this->alpha);
		blue  = (s32)((f32)lbl_8042B35C.blue * this->alpha);
	}

	fn_80194234(14, 0);
	Material* material = (Material*)lbl_8042C354;
	material->red      = red;
	material->green    = green;
	material->blue     = blue;
	material->alpha    = alpha;

	fn_80053660(lbl_802D5E80, 16);
	fn_8005349C(lbl_802D5E80, lbl_802D5E80[0x4be]);

	model = lbl_8042C350;
	frame = *(s32*)((u8*)lbl_8042C180 + 0x30);
	if (lbl_8042C378[0] != frame) {
		f32 elapsed = (f32)(frame - lbl_8042C378[0]);
		if (lbl_8042C370 != 0 && lbl_8042C374 != 0) {
			fn_8011B844(elapsed);
			fn_8014FFBC(model, (void*)fn_8005BF88, lbl_80303F98);
		}
		if (lbl_8042C368 != 0) {
			fn_8020CC18(*(void**)((u8*)lbl_8042C368 + 0x20), lbl_8042DBBC * elapsed);
			fn_8013FC30(lbl_8042C368);
		}
		lbl_8042C378[0] = frame;
	}

	void* primaryFrame = *(void**)((u8*)model + 4);
	RwV3d position     = this->position;
	fn_8019EB94(primaryFrame, &position, 0);
	fn_8014FF2C(model);

	model = lbl_8042C358;
	u32 opacity;
	if (model != 0 && (opacity = this->opacity) != 0) {
		material        = (Material*)lbl_8042C35C;
		material->red   = red;
		material->green = green;
		material->blue  = blue;
		material->alpha = opacity;

		void* frameObject = *(void**)((u8*)model + 4);
		RwV3d scale;
		scale.x = this->swirlScale;
		scale.y = this->swirlScale;
		scale.z = this->swirlScale;
		fn_8019EC30(frameObject, &scale, 0);

		s32 angle         = (s32)(lbl_8042DBC4 * this->scale);
		f32 sine          = fn_800D7B00(angle);
		f32 inverseCosine = lbl_8042DBC0 - fn_800D7AE4((s32)(lbl_8042DBC4 * this->scale));
		fn_80195790((u8*)frameObject + 0x10, &lbl_80239984, inverseCosine, sine, 2);
		fn_8019E880(frameObject);
		fn_8019EB94(frameObject, &position, 2);
		fn_8014FF2C(model);
	}

	model = lbl_8042C360;
	if (model != 0 && (opacity = this->opacity) != 0) {
		material        = (Material*)lbl_8042C364;
		material->red   = red;
		material->green = green;
		material->blue  = blue;
		material->alpha = opacity;

		void* frameObject = *(void**)((u8*)model + 4);
		RwV3d scale;
		scale.x = this->verticalScale;
		scale.y = this->verticalScale;
		scale.z = this->verticalScale;
		fn_8019EC30(frameObject, &scale, 0);

		s32 angle         = (s32)(lbl_8042DBC4 * this->scale);
		f32 sine          = fn_800D7B00(angle);
		f32 inverseCosine = lbl_8042DBC0 - fn_800D7AE4((s32)(lbl_8042DBC4 * this->scale));
		fn_80195790((u8*)frameObject + 0x10, &lbl_80239984, inverseCosine, sine, 2);
		fn_8019E880(frameObject);
		f32 height = lbl_8042DBC8 * (lbl_8042DBC0 - this->verticalScale);
		position.y = position.y + height;
		fn_8019EB94(frameObject, &position, 2);
		fn_8014FF2C(model);
	}

	fn_80194234(14, saved14);
	fn_80194234(20, saved20);
	fn_80194234(10, saved10);
	fn_80194234(11, saved11);
}
#pragma peephole reset

extern "C" void Exec__15TObjEffTornado2Fv(TObjEffTornado2* effect)
{
	if (fn_8005BB20(&effect->position, lbl_8042DBE0) != 0) {
		effect->flags |= 1;
		return;
	}

	switch (effect->active) {
		case 1:
			if (effect->direction != 0) {
				effect->alpha = fn_800D7328(effect->alpha, lbl_8042DBC0, lbl_8042DBE4);
			} else {
				effect->alpha = fn_800D7328(effect->alpha, lbl_8042DBC0, lbl_8042DBE8);
			}
			if (effect->alpha >= lbl_8042DBC0) {
				effect->active = 2;
				effect->state  = 0;
			}
			break;

		case 2: {
			if (effect->direction != 0) {
				s16 timer = effect->state++;
				if ((f32)timer >= lbl_8042DBEC) {
					effect->active = 3;
				}
			} else {
				s16 timer = effect->state++;
				if ((f32)timer >= lbl_8042DBF0) {
					effect->active = 3;
				}
			}

			CollisionSearchResult* collision = fn_80020BD8(&effect->effectModel, 11);
			void* hit                        = collision != 0 ? collision->object : 0;
			if (hit != 0) {
				effect->active = 3;
			}
			break;
		}

		case 3:
			if (effect->direction != 0) {
				effect->alpha = fn_800D7328(effect->alpha, lbl_8042DBB4, lbl_8042DBE4);
			} else {
				effect->alpha = fn_800D7328(effect->alpha, lbl_8042DBB4, lbl_8042DBE8);
			}
			if (effect->alpha <= lbl_8042DBB4) {
				effect->active = 4;
			}
			break;

		case 4: {
			TObject* parent = *(TObject**)((u8*)effect + 0x10);
			if (parent != lbl_8042C110 && parent != lbl_8042C2A0) {
				return;
			}
			effect->flags |= 1;
			return;
		}
	}

	effect->scale += lbl_8042DBF4;
	effect->swirlScale    = fn_800D7328(effect->swirlScale, lbl_8042DBC0, lbl_8042DBF8);
	effect->verticalScale = fn_800D7328(effect->verticalScale, lbl_8042DBFC, lbl_8042DC00);

	if (effect->swirlScale >= lbl_8042DC04) {
		s32 opacity = effect->opacity;
		if ((opacity -= 0x7f) < 0) {
			effect->opacity       = 0xff;
			effect->swirlScale    = lbl_8042DC08;
			effect->verticalScale = lbl_8042DBC0;
		} else {
			effect->opacity = opacity;
		}
	}

	effect->color[3] = (u8)(lbl_8042DC0C * effect->alpha);
	if (effect->alpha > lbl_8042DC10) {
		if (*(s32*)(lbl_8029C310 + 0x18) == 0) {
			*(RwV3d*)&effect->effectModel.data[0x7c]  = *(RwV3d*)&effect->effectModel.data[0x60];
			*(RwV3d*)&effect->effectModel.data[0x60]  = effect->position;
			*(sAngle*)&effect->effectModel.data[0x6c] = effect->rotation;
			fn_8003BC38(&effect->effectModel);
		} else {
			fn_8003BE78(&effect->effectModel);
		}
	}
}

extern "C" TObjEffTornado2* __dt__15TObjEffTornado2Fv(TObjEffTornado2* effect, s32 shouldDelete)
{
	if (effect != 0) {
		effect->vtable = lbl_802535C4;
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

extern "C" void Exec__14TObjEffTornadoFv(TObjEffTornado* effect)
{
	if (fn_8005BB20(&effect->position, lbl_8042DBE0) != 0) {
		effect->flags |= 1;
		return;
	}

	switch (effect->active) {
		case 1:
			effect->alpha = fn_800D7328(effect->alpha, lbl_8042DBC0, lbl_8042DBE8);
			if (effect->alpha >= lbl_8042DBC0) {
				effect->active = 2;
				effect->state  = 0;
			}
			break;
		case 2: {
			s16 timer = effect->state;
			effect->state++;
			if ((f32)timer >= lbl_8042DBF0) {
				effect->active = 3;
			}
			CollisionSearchResult* result = fn_80020BD8(&effect->effectModel, 11);
			void* object                  = result != 0 ? result->object : 0;
			if (object != 0) {
				effect->active = 3;
			}
			break;
		}
		case 3:
			effect->alpha = fn_800D7328(effect->alpha, lbl_8042DBB4, lbl_8042DBE8);
			if (effect->alpha <= lbl_8042DBB4) {
				effect->active = 4;
			}
			break;
		case 4: {
			TObject* parent = *(TObject**)((u8*)effect + 0x10);
			if (parent == lbl_8042C110 || parent == lbl_8042C2A0) {
				effect->flags |= 1;
			}
			return;
		}
	}

	effect->scale += lbl_8042DBF4;
	if (effect->alpha > lbl_8042DC10 && effect->active == 2) {
		if (*(s32*)(lbl_8029C310 + 0x18) == 0) {
			*(f32*)((u8*)effect + 0xa4) = *(f32*)((u8*)effect + 0x88);
			*(f32*)((u8*)effect + 0xa8) = *(f32*)((u8*)effect + 0x8c);
			*(f32*)((u8*)effect + 0xac) = *(f32*)((u8*)effect + 0x90);
			*(f32*)((u8*)effect + 0x88) = effect->position.x;
			*(f32*)((u8*)effect + 0x8c) = effect->position.y;
			*(f32*)((u8*)effect + 0x90) = effect->position.z;
			*(s32*)((u8*)effect + 0x94) = effect->rotation.x;
			*(s32*)((u8*)effect + 0x98) = effect->rotation.y;
			*(s32*)((u8*)effect + 0x9c) = effect->rotation.z;
			fn_8003BC38(&effect->effectModel);
		} else {
			fn_8003BE78(&effect->effectModel);
		}
	} else {
		fn_8003BE78(&effect->effectModel);
	}
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

#pragma opt_common_subs reset
#pragma opt_common_subs off
TObjEffTornado2::TObjEffTornado2(
    TObject* parent, s32 kind, RwV3d* position, sAngle* rotation, RwV3d* velocity)
    : TObjEffTornado(parent, kind, position, rotation)
{
	TObjEffTornado2* result = this;

	result->vtable              = lbl_802535C4;
	result->className           = lbl_8042B358;
	*(u16*)((u8*)result + 0x1e) = 0xec;

	if (kind < 0) {
		copyColor(result->color, (u8*)lbl_802534C0);
	} else {
		switch (lbl_80303DC8[kind]->team) {
			case 0:
				copyColor(result->color, (u8*)lbl_802534C0 + 4);
				break;
			case 1:
				copyColor(result->color, (u8*)lbl_802534C0 + 8);
				break;
			case 3:
				copyColor(result->color, (u8*)lbl_802534C0 + 12);
				break;
			case 2:
				copyColor(result->color, (u8*)lbl_802534C0 + 16);
				break;
		}
	}

	result->swirlScale    = lbl_8042DC08;
	result->verticalScale = lbl_8042DBC0;
	result->opacity       = 0xff;
	result->direction     = (s8)(u32)velocity;
}
#pragma opt_common_subs reset

TObjEffTyphoon::TObjEffTyphoon(
    TObject* parent, s32 kind, RwV3d* position, sAngle* rotation, RwV3d* velocity)
    : TObjEffTornado(parent, kind, position, rotation)
{
	TObjEffTyphoon* __restrict result = this;

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

extern "C" void SetEffectTornadoSpin__FP7TObjectPC5RwV3dPC5RwV3d(
    TObject* parent, const RwV3d* direction, const RwV3d* position)
{
	if (parent == 0) {
		parent = lbl_8042C2A0;
		if (parent == 0) {
			parent = lbl_8042C110;
		}
	}

	new TObjEffTornadoSpin(parent, direction, position);
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

const char* lbl_8042B350 = lbl_8025336C;
const char* lbl_8042B354 = lbl_8025349C;
const char* lbl_8042B358 = lbl_802534B0;
Rgba lbl_8042B35C        = { 0x60, 0x60, 0x60, 0xff };
const char* lbl_8042B360 = lbl_802534D4;

#pragma opt_common_subs off
extern "C" void InitEffTornado__Fv()
{
	for (s32 i = 0; i < 3; ++i) {
		if (lbl_802532E8[i] == 0) {
			lbl_802532E8[i] = fn_8005EA04(lbl_80253330[i]);
			if (lbl_802532E8[i] != 0) {
				lbl_802532F4[i] = fn_8005E410(lbl_802532E8[i], 0, "ef_tnd");
			}
		}
	}

	lbl_8042C350 = fn_8005EA04(lbl_80253568);
	if (lbl_8042C350 != 0) {
		lbl_8042C354 = fn_8005E410(lbl_8042C350, 0, "ef_chbl");
		lbl_8042C370 = lbl_8042C354;
		lbl_8042C368 = fn_800BD0AC(lbl_8042C3D0, lbl_8042C350);
		fn_8005D9F4(lbl_8042C350);
		fn_8005D6DC(lbl_8042C350);
	}

	lbl_8042C358 = fn_8005EA04(lbl_80253578);
	if (lbl_8042C358 != 0) {
		lbl_8042C35C = fn_8005E410(lbl_8042C358, 0, "ef_chbl");
		fn_8005DA34(lbl_8042C358);
		fn_8005D9F4(lbl_8042C358);
		fn_8005D6DC(lbl_8042C358);
	}

	lbl_8042C360 = fn_8005EA04(lbl_8025358C);
	if (lbl_8042C360 != 0) {
		lbl_8042C364 = fn_8005E410(lbl_8042C360, 0, "ef_chbl");
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
		void* material  = fn_8005E1DC(lbl_8042C350, 0, "ef_chbl");
		lbl_80303F98[0] = lbl_8042C374;
		fn_8005C014(material);
		fn_801491A8(material);
	}
}
#pragma opt_common_subs reset

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
char lbl_8025336C[]   = "TObjEffTornado";
RwV3d lbl_8025337C[8] = {
	{ 0.8f, 1.5f, 0.9f },
	{ 1.1f, 0.8f, 1.2f },
	{ 1.1f, 0.9f, 1.0f },
	{ 0.9f, 1.4f, 0.8f },
	{ 0.8f, 0.6f, 0.9f },
	{ 0.8f, 1.8f, 0.8f },
	{ 0.9f, 1.2f, 0.7f },
	{ 1.0f, 0.9f, 1.1f },
};
RwV3d lbl_802533DC[8] = {
	{ 4.0f, -1.5f, 4.5f },
	{ 5.5f, 0.0f, -6.0f },
	{ -5.5f, 2.5f, -5.0f },
	{ -4.5f, 1.0f, 4.0f },
	{ 4.0f, -0.5f, 4.5f },
	{ 4.0f, 0.8f, -4.0f },
	{ -4.5f, -0.9f, -3.5f },
	{ -5.0f, 0.3f, 5.5f },
};
RotationPair lbl_8025343C[8] = {
	{ 0.996195f, 0.087156f },
	{ 0.965926f, -0.258819f },
	{ 0.999391f, 0.034899f },
	{ 0.992546f, 0.121869f },
	{ 0.996195f, -0.087156f },
	{ 0.999848f, 0.017452f },
	{ 0.990268f, -0.139173f },
	{ 0.994522f, 0.104528f },
};
s32 lbl_8025347C[8]    = { 0, -0x4000, 0x1600, -0xc00, 0x3000, 0x1000, -0x1600, 0xa00 };
char lbl_8025349C[]    = "TObjEffTornadoSpin";
char lbl_802534B0[16]  = "TObjEffTornado2";
char lbl_80253568[]    = "EF_TORNADO.DFF";
char lbl_80253578[]    = "EF_TORNADO_RING.DFF";
char lbl_8025358C[]    = "EF_TORNADO_RINGB.DFF";
char lbl_802535A4[]    = "EF_TORNADO.ANM";
char lbl_802535B4[]    = "EF_TORNADO.UVB";
void* lbl_802535C4[11] = {
	0,
	0,
	(void*)__dt__15TObjEffTornado2Fv,
	(void*)Exec__15TObjEffTornado2Fv,
	(void*)fn_8001898C,
	(void*)TDisp__15TObjEffTornado2Fv,
	(void*)fn_80018988,
	(void*)fn_80018950,
	(void*)fn_80018954,
	(void*)fn_80017854,
	(void*)fn_80018958,
};
void* lbl_802535F0[11] = {
	0,
	0,
	(void*)__dt__18TObjEffTornadoSpinFv,
	(void*)Exec__18TObjEffTornadoSpinFv,
	(void*)fn_8001898C,
	(void*)TDisp__18TObjEffTornadoSpinFv,
	(void*)fn_80018988,
	(void*)fn_80018950,
	(void*)fn_80018954,
	(void*)fn_80017854,
	(void*)fn_80018958,
};
void* lbl_8025361C[11] = {
	0,
	0,
	(void*)__dt__14TObjEffTornadoFv,
	(void*)Exec__14TObjEffTornadoFv,
	(void*)fn_8001898C,
	(void*)TDisp__14TObjEffTornadoFv,
	(void*)fn_80018988,
	(void*)fn_80018950,
	(void*)fn_80018954,
	(void*)fn_80017854,
	(void*)fn_80018958,
};

void* lbl_8042C350;
void* lbl_8042C354;
void* lbl_8042C358;
void* lbl_8042C35C;
void* lbl_8042C360;
void* lbl_8042C364;
void* lbl_8042C368;
void* lbl_8042C36C;
void* lbl_8042C370;
void* lbl_8042C374;
s32 lbl_8042C378[2];
