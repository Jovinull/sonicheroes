#include "types.h"

// Retained PS2 symbols name this object TObjS11Key and give its method family
// in the order the GameCube text keeps: SearchCage, Disappear,
// CheckTouchedByLeader, TDisp, Disp, Exec, GetWaitAngY, GetWaitPosY,
// SetPosition, the destructor, the TObject* constructor and the
// initObj/endObj/startObj lifecycle functions. The "TObjS11Key" class-name
// string in this unit's .data correlates the GameCube object with it.
//
// Exec inlines SetPosition, GetWaitPosY and GetWaitAngY although all three are
// emitted after it, and the constructor is inlined into startObjS11Key before
// its own body; only deferred inlining lets a caller inline a later body. With
// it the compiler emits the unit's functions in reverse definition order, so
// the source below runs from the lifecycle functions back to SearchCage.

struct Vec3 {
	f32 x;
	f32 y;
	f32 z;
};

struct sAngle {
	s32 x;
	s32 y;
	s32 z;
};

/* The goal cage record a key leaves on its set data once it has found one. */
struct KeyCage {
	u32 magic;
	Vec3 position;
};

struct SETDATA_PARAM {
	Vec3 position;
	s32 angleX;
	s32 angleY;
	s32 angleZ;
	u32 flags;
	u8 pad1C[0xE];
	u8 group;
	u8 pad2B[5];
	KeyCage* cage;
};

/* One entry of the stage's per-group set-object lists. */
struct SetObjNode {
	u8 pad00[0x28];
	u16 type;
	u8 pad2A[0xE];
	SetObjNode* next;
};

struct ObjectManager {
	u8 pad000[0x30];
	SetObjNode* lists[1];
};

struct GameState {
	u8 pad00[0x1F];
	s8 paused;
	s8 editMode;
	u8 pad21[3];
	s8 stageMode;
	u8 pad25[0xB];
	s32 frame;
};

struct TeamInfo {
	u8 pad000[0x3A];
	s8 partner;
	s8 leader;
	u8 pad03C[0xD4];
	s8 members[1];
};

struct PlayerInfo {
	u8 pad000[0x25C];
	s8 team;
};

struct HitNode {
	u8 pad00[4];
	struct HitObject* object;
};

struct HitObject {
	u8 pad00[0x78];
	s32 character;
};

static inline HitObject* HitObjectOf(HitNode* node)
{
	return node != NULL ? node->object : NULL;
}

class TObject
{
public:
	const char* className;
	u16 signal;
	u8 pad06[0x12];
	void** vtable;
	s16 pad1C;
	s16 objectSize;
	u8 pad20[8];

	TObject(TObject*);
	~TObject();
};

struct Motion;

extern "C" {
void fn_8005BE6C(void*);
void fn_8003C618(void*);
s32 fn_8005B8BC(Motion*);
s32 fn_8005B8D8(Motion*);
s32 fn_8005B9F0(Motion*);
}

struct Motion {
	SETDATA_PARAM* frame;
	void** vtable;

	Motion() { fn_8005BE6C(this); }
	s32 CheckMustKill() { return fn_8005B9F0(this); }
	s32 CheckRangeOut() { return fn_8005B8BC(this); }
	s32 OnEdit() { return fn_8005B8D8(this); }
};

/* The key's collision body. Its position history sits at 0x60. */
struct KeyCollision {
	u8 pad00[0x60];
	Vec3 position;
	sAngle angle;
	u8 pad78[4];
	Vec3 previous;

	KeyCollision() { fn_8003C618(this); }
};

extern "C" {
extern void* lbl_8042C110;
extern void* lbl_8042C148;
extern GameState* lbl_8042C180;
extern u8 lbl_8042C1A4;
extern void* lbl_8042C1D0;
extern ObjectManager* lbl_8042C298;
extern void* lbl_8042C388;
extern u8 AxisY;
extern u8 lbl_802FF5A0;
extern PlayerInfo* lbl_802AD0D0[];
extern TeamInfo* lbl_80303DC8[];

void dtor_8003C52C(void*, s16);
void dtor_8005BD3C(void*, s16);
void* fn_80018A34(void*, u32);
void fn_800189A4(void*, void*);
HitNode* fn_80020BD8(void*, s32);
HitNode* fn_800211A8(void*);
void fn_80021824(void*);
void fn_8003BC38(void*);
void fn_8003BF04(void*, void*, s32, s32);
void* fn_80057644(u32);
void fn_8005BC04(Motion*);
void fn_8005D5C8(void*, u32);
void fn_800628D0(s32, Vec3*, s32);
void fn_80066988(void*, s32, s32);
void fn_80090B00(TeamInfo*);
void fn_800B52E8(void*, s32, s32, s32);
void* fn_800BB92C(void*, s32, void*);
s32 fn_800BC6CC(void*, const char*);
void fn_800BC9F4(void*, void*);
f32 fn_800D71DC(SETDATA_PARAM*, SetObjNode*);
f32 fn_800D7AE4(s32);
f32 fn_800D7B00(s32);
void fn_80119618(void*);
void fn_8011967C(void*, f32*);
void fn_801197F4(void*, s32);
void* fn_80119A18(void*, void*);
void fn_801379A0(s32, s32);
void fn_8014FF2C(void*);
void* fn_80150588(void*);
void fn_80150958(void*);
void fn_80194234(s32, s32);
void fn_80194294(s32, s32*);
void fn_80195790(void*, void*, f32, f32, s32);
void fn_8019E880(void*);
void fn_8019EB94(void*, Vec3*, s32);
void fn_8019EC30(void*, Vec3*, s32);
void fn_801A4C84(void*);

void fn_8005B8B8();
void PDisp__7TObjectFv();
void ImmAftSetRaster__7TObjectFv();
void Debug__7TObjectFv();
void Error__7TObjectFPc();
void Render__7TObjectFv();
}

class TObjS11Key : public TObject, public Motion
{
public:
	KeyCollision collision;
	Vec3 position;
	s32 angle;
	s32 angleSpeed;
	f32 scale;
	f32 alpha;
	s32 state;
	void* model;
	void* uvAnim;
	s32 unkE0;

	void SearchCage();
	void Disappear();
	s32 CheckTouchedByLeader();
	void TDisp();
	void Disp();
	void Exec();
	s32 GetWaitAngY();
	f32 GetWaitPosY();
	void SetPosition();
	TObjS11Key();
	TObjS11Key(TObject*);
	~TObjS11Key();

	static void* operator new(unsigned long size, void* heap) { return fn_80018A34(heap, size); }
	static void operator delete(void* object) { fn_800189A4(lbl_8042C148, object); }
};

// The s11key* data names and CL_TObjS11Key are descriptive guesses.
extern "C" {
TObjS11Key* __dt__10TObjS11KeyFv(TObjS11Key*, s16);
void Exec__10TObjS11KeyFv(TObjS11Key*);
void Disp__10TObjS11KeyFv(TObjS11Key*);
void TDisp__10TObjS11KeyFv(TObjS11Key*);
void endObjS11Key();
void initObjS11Key();
void startObjS11Key();
}

static const sAngle lbl_8_rodata_1FB8 = { 0, 0, 0 };

extern "C" {
f32 lbl_8_data_18DF0     = 0.05f;
s32 lbl_8_data_18DF4     = 0x40;
f32 lbl_8_data_18DF8     = 0.015f;
f32 lbl_8_data_18DFC     = 0.015f;
f32 lbl_8_data_18E00     = 10.0f;
u32 lbl_8_data_18E04[12] = { 0x0000F0E0, 0x00000402, 0x00000000, 0x40F00000, 0x00000000, 0x40F00000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000 };
char TObjS11KeyClassName[] = "TObjS11Key";
char* CL_TObjS11Key        = TObjS11KeyClassName;
void* s11keyVtable[14]     = {
	0,
	0,
	(void*)__dt__10TObjS11KeyFv,
	(void*)Exec__10TObjS11KeyFv,
	(void*)Disp__10TObjS11KeyFv,
	(void*)TDisp__10TObjS11KeyFv,
	(void*)PDisp__7TObjectFv,
	(void*)ImmAftSetRaster__7TObjectFv,
	(void*)Debug__7TObjectFv,
	(void*)Error__7TObjectFPc,
	(void*)Render__7TObjectFv,
	0,
	0,
	(void*)fn_8005B8B8,
};
char s11keyModelName[]         = "s11_o_goalkey.dff";
char s11keyObjectDisplayName[] = "S11KEY OBJECT";
}

struct SETOBJ_PARAM {
	char* displayName;
	void (*init)();
	void (*end)();
	void (*create)();
	u32 field10;
	u32 flags;
	u32 field18;
	u16 id;
	u16 count;
	u8 field20;
	u8 field21;
	u8 pad22[2];
	char* fieldTypes;
	void* fields;
};

extern "C" {
void* s11keyModel;
SETOBJ_PARAM s11keyObjectEntry;
}

extern "C" void s11keyObjectRegister()
{
	s11keyObjectEntry.flags       = 0;
	s11keyObjectEntry.field18     = 0;
	s11keyObjectEntry.displayName = s11keyObjectDisplayName;
	s11keyObjectEntry.init        = initObjS11Key;
	s11keyObjectEntry.end         = endObjS11Key;
	s11keyObjectEntry.create      = startObjS11Key;
	s11keyObjectEntry.field10     = 0;
	s11keyObjectEntry.flags       = 0x20000;
	s11keyObjectEntry.field18     = 0;
	s11keyObjectEntry.field20     = 0x1E;
	s11keyObjectEntry.id          = 0x1109;
	s11keyObjectEntry.count       = 2;
	s11keyObjectEntry.field21     = 0;
	s11keyObjectEntry.fieldTypes  = NULL;
	s11keyObjectEntry.fields      = NULL;
	if (s11keyObjectEntry.fieldTypes != NULL)
		s11keyObjectEntry.flags |= 8;
	else
		s11keyObjectEntry.flags &= ~8;
}

__declspec(section ".ctors") void (*const s11keyObjectCtorEntry)() = s11keyObjectRegister;

extern "C" void startObjS11Key()
{
	new (lbl_8042C148) TObjS11Key();
}

extern "C" void initObjS11Key()
{
	void* stage = *(void**)((u8*)lbl_8042C1D0 + 0x8C18);
	if (!(stage != NULL && (fn_801A4C84(stage), 1)))
		return;

	void* archive = *(void**)((u8*)lbl_8042C298 + 0xA50);
	fn_800BC9F4(archive, &lbl_802FF5A0);
	s32 id      = fn_800BC6CC(archive, s11keyModelName);
	s11keyModel = fn_800BB92C(archive, id, &lbl_802FF5A0);
}

extern "C" void endObjS11Key()
{
	if (s11keyModel != NULL) {
		fn_80150958(s11keyModel);
		s11keyModel = NULL;
	}
}

static inline void constructKey(TObjS11Key* object)
{
	object->TObject::vtable = s11keyVtable;
	object->Motion::vtable  = s11keyVtable + 11;
	object->className       = CL_TObjS11Key;
	object->objectSize      = sizeof(TObjS11Key);
	object->position        = object->frame->position;
	object->state           = 0;
	object->scale           = 0.0f;
	object->alpha           = 1.0f;
	object->uvAnim          = NULL;
	object->unkE0           = 0;
	object->model           = fn_80150588(s11keyModel);
	if (object->model != NULL) {
		fn_8005D5C8(object->model, ((object->frame->flags & 0x1C0000) >> 18) + 4);
		void* anim = fn_80057644(0x14);
		if (anim != NULL) {
			anim = fn_80119A18(anim, object->model);
		}
		object->uvAnim = anim;
	}
	if (fn_8005B8D8((Motion*)((u8*)object + 0x28)) == 0) {
		fn_8003BF04(&object->collision, lbl_8_data_18E04, 1, 4);
		object->SearchCage();
	}
	if (lbl_8042C180->stageMode == 8) {
		object->frame->flags |= 0x10000000;
	}
}

TObjS11Key::TObjS11Key(TObject* parent)
    : TObject(parent)
    , Motion()
{
	constructKey(this);
}

inline TObjS11Key::TObjS11Key()
    : TObject((TObject*)lbl_8042C110)
    , Motion()
{
	constructKey(this);
}

TObjS11Key::~TObjS11Key()
{
	TObject::vtable = s11keyVtable;
	Motion::vtable  = s11keyVtable + 11;
	if (model != NULL) {
		if (uvAnim != NULL) {
			fn_801197F4(uvAnim, 1);
			uvAnim = NULL;
		}
		fn_80150958(model);
		model = NULL;
	}
	if (frame->flags & 0x10000) {
		fn_8005BC04((Motion*)((u8*)this + 0x28));
	}
	dtor_8003C52C(&collision, 0);
	dtor_8005BD3C((u8*)this + 0x28, 0);
}

void TObjS11Key::SetPosition()
{
	if (model != NULL) {
		KeyCage* cage;
		s32 onCage = 0;
		cage       = frame->cage;
		if (cage != NULL && cage->magic == 0x12345678) {
			position = cage->position;
			onCage   = 1;
		}
		void* atomic = *(void**)((u8*)model + 4);
		if (state == 1) {
			Vec3 pos = position;
			if (onCage == 0) {
				pos.y = GetWaitPosY();
			}
			fn_8019EB94(atomic, &pos, 0);
			s32 angY = GetWaitAngY();
			f32 sine = fn_800D7B00(angY);
			fn_80195790((u8*)atomic + 0x10, &AxisY, 1.0f - fn_800D7AE4(angY), sine, 1);
			fn_8019E880(atomic);
		} else {
			Vec3 size;
			size.x = size.y = size.z = 1.0f + scale;
			fn_8019EB94(atomic, &position, 0);
			f32 sine = fn_800D7B00(angle);
			fn_80195790((u8*)atomic + 0x10, &AxisY, 1.0f - fn_800D7AE4(angle), sine, 1);
			fn_8019E880(atomic);
			fn_8019EC30(atomic, &size, 1);
		}
	}
}

f32 TObjS11Key::GetWaitPosY()
{
	return position.y + 2.5f * (1.0f + fn_800D7AE4(GetWaitAngY()));
}

s32 TObjS11Key::GetWaitAngY()
{
	return 182.04445f * (lbl_8042C180->frame % 360);
}

void TObjS11Key::Exec()
{
	if (CheckMustKill() != 0 || CheckRangeOut() != 0) {
		Disappear();
		return;
	}
	if (OnEdit() != 0) {
		position = frame->position;
		SetPosition();
		return;
	}
	SetPosition();
	switch (state) {
		case 0:
			state = 1;
			break;
		case 1: {
			s32 team = CheckTouchedByLeader();
			if (team != -1) {
				state = 2;
				frame->flags |= 0x10000;
				s32 leader = lbl_80303DC8[team]->members[lbl_80303DC8[team]->leader];
				fn_80066988(&collision, leader, 100);
				if (lbl_8042C388 != NULL) {
					fn_800B52E8(lbl_8042C388, 0x1020, 0, 0);
				}
				fn_80090B00(lbl_80303DC8[team]);
				fn_801379A0(0x2C, leader);
				position.y = GetWaitPosY();
				angle      = GetWaitAngY();
				angleSpeed = 0xB6;
			} else {
				sAngle zero        = lbl_8_rodata_1FB8;
				collision.previous = collision.position;
				collision.position = position;
				collision.angle    = zero;
				fn_8003BC38(&collision);
			}
			break;
		}
		case 2:
			position.y += lbl_8_data_18DF0;
			angleSpeed += lbl_8_data_18DF4;
			angle += angleSpeed;
			scale += lbl_8_data_18DF8;
			alpha -= lbl_8_data_18DFC;
			if (lbl_8042C180->paused == 0 && lbl_8042C180->frame % 20 == 0) {
				Vec3 pos = position;
				pos.y += lbl_8_data_18E00 * (1.0f + scale);
				fn_800628D0(0xD, &pos, 0);
			}
			if (alpha < 0.0f) {
				alpha = 0.0f;
				Disappear();
			}
			break;
		case 3:
			break;
	}
}

void TObjS11Key::Disp()
{
	if (model != NULL && lbl_8042C180->editMode == 0 && state == 1) {
		fn_8014FF2C(model);
	}
}

void TObjS11Key::TDisp()
{
	if (model != NULL && lbl_8042C180->editMode == 0 && state == 2 && uvAnim != NULL) {
		f32 color[4];
		s32 srcBlend;
		s32 dstBlend;
		color[0] = color[1] = color[2] = 1.0f;
		color[3]                       = alpha;
		fn_80194294(10, &srcBlend);
		fn_80194294(11, &dstBlend);
		fn_80194234(10, 5);
		fn_80194234(11, 2);
		fn_8011967C(uvAnim, color);
		fn_8014FF2C(model);
		fn_80119618(uvAnim);
		fn_80194234(10, srcBlend);
		fn_80194234(11, dstBlend);
	}
}

s32 TObjS11Key::CheckTouchedByLeader()
{
	s32 character = -1;
	HitObject* hit;

	if (HitObjectOf((fn_80021824(&lbl_8042C1A4), fn_80020BD8(&collision, 0x13))) != NULL) {
		return -1;
	}
	if (HitObjectOf((fn_80021824(&lbl_8042C1A4), fn_80020BD8(&collision, 1))) != NULL) {
		return -1;
	}
	fn_80021824(&collision);
	while ((hit = HitObjectOf(fn_800211A8(&collision))) != NULL) {
		switch (hit->character) {
			case 1:
				character = 0;
				break;
			case 2:
				character = 1;
				break;
			case 3:
				character = 2;
				break;
			case 4:
				character = 3;
				break;
			case 5:
				character = 4;
				break;
			case 6:
				character = 5;
				break;
		}
		if (character != -1) {
			TeamInfo* info;
			PlayerInfo* player = lbl_802AD0D0[character];
			s32 team           = player->team;
			if (player != NULL) {
				info = lbl_80303DC8[team];
				if (character == info->members[info->leader]
				    || character == info->members[info->partner]) {
					return team;
				}
			}
		}
	}
	return -1;
}

void TObjS11Key::Disappear()
{
	signal |= 1;
}

void TObjS11Key::SearchCage()
{
	if (frame->cage == NULL) {
		SetObjNode* node = lbl_8042C298->lists[frame->group];
		f32 range        = 100.0f;
		for (; node != NULL; node = node->next) {
			if (node->type == 0x24 && fn_800D71DC(frame, node) < range) {
				frame->cage           = (KeyCage*)fn_80057644(0x14);
				frame->cage->magic    = 0x12345678;
				frame->cage->position = frame->position;
				return;
			}
		}
	}
}
