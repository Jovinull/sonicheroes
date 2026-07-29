#include "types.h"

// The PS2 beta symbols identify this original C++ translation unit as
// e_paralysis.cpp and provide the TEnemyParalysis and sParalysisParam names.
// The GameCube vtable, constructor, destructor, static initializer, and
// exception cleanup establish the same class boundary in the retail build.
//
// This file requires deferred inlining. It emits the out-of-line methods in
// the retail order and keeps the two TObject cleanup records attached to the
// derived constructor and destructor.

struct RwV3d {
	f32 x, y, z;
};

struct sAngle {
	s32 x, y, z;
};

struct RawV3d {
	u32 v[3];
};

struct RwFrame;
extern "C" void fn_800189A4(void*, void*);
extern "C" void* lbl_8042C148;
enum RwOpCombineType {
	rwCOMBINEREPLACE    = 0,
	rwCOMBINEPRECONCAT  = 1,
	rwCOMBINEPOSTCONCAT = 2,
};

struct sParalysisParam {
	s32 activeFrames;
	s32 recoveryFrames;
	RawV3d offset;

	sParalysisParam();
};

struct TObject {
	u8 base[0x28];

	TObject(TObject* parent);
	~TObject();
	static void operator delete(void* ptr) { fn_800189A4(lbl_8042C148, ptr); }
};

struct TEnemyParalysis : TObject {
	s32 activeFrames;
	s32 recoveryFrames;
	RwV3d offset;
	void* effect;
	RwV3d position;
	RwV3d velocity;
	sAngle angle;
	s32 frame;
	s32 enabled;
	s32 state;
	s32 timer;

	TEnemyParalysis(TObject* parent, sParalysisParam* param);
	~TEnemyParalysis();
	void Initialize();
	void Finalize();
	void Exec();
	void TDisp();
	void Vibrate(RwFrame* frame, RwOpCombineType combine);
	void SetPosAng(const RwV3d* position, const sAngle* angle);
};

extern "C" {
void fn_8001898C();
void fn_80018988();
void fn_80018950();
void fn_80018954();
void fn_80017854();
void fn_80018958();
void __dt__15TEnemyParalysisFv();
void Exec__15TEnemyParalysisFv();
void TDisp__15TEnemyParalysisFv();
void fn_80150958(void*);
void* fn_80150588(void*);
void fn_8019EB94(void*, const void*, s32);
void fn_8019EC30(void*, const void*, s32);
void fn_8019ED68(void*, const void*, f32, s32);
s32 fn_8019CE34(void*, const void*);
s32 fn_801C28D8();
void fn_800B4A38(void*, s32, const void*, s32, s32, s32, s32);
void fn_80113940();
void fn_801138B4();
void fn_801137FC(s32);
void fn_801137AC();
void fn_8011398C(void*, s32);
void fn_8011B844(void*, f32);
void fn_8014FFBC(void*, void*, void*);
void fn_8014FF2C(void*);
void fn_80113838(s32);
void fn_801138F4();
void* fn_8005EC0C();
void* fn_8005EA04(char*);
void fn_8005BF5C(void*);
void fn_8005BF88();
void fn_80113AA8(void*, void*, void*, void*, s32);
void fn_80113A68(void*);
void* fn_80113C7C(void*);
void fn_80113C2C(void*, s16);
void __register_global_object(void*, void*, void*);
f64 __fabs(f64);

extern void* lbl_8042C180;
extern void* lbl_8042C388;
extern void** lbl_8042C9A4;
extern u8 lbl_80239978[];
extern u8 lbl_80239984[];
extern u8 lbl_80239990[];
extern u8 lbl_80288C24[];
}

char lbl_80288C90[]              = "TEnemyParalysis";
extern "C" void* lbl_8042B810[2] = { lbl_80288C90, NULL };

extern "C" void* lbl_80288CA0[] = {
	NULL,
	NULL,
	(void*)__dt__15TEnemyParalysisFv,
	(void*)Exec__15TEnemyParalysisFv,
	(void*)fn_8001898C,
	(void*)TDisp__15TEnemyParalysisFv,
	(void*)fn_80018988,
	(void*)fn_80018950,
	(void*)fn_80018954,
	(void*)fn_80017854,
	(void*)fn_80018958,
};

char lbl_80288CCC[] = "EF_SIBIRE.DFF";
char lbl_80288CDC[] = "EF_SIBIRE.UVB";

extern "C" {
void* lbl_8042C648;
void* lbl_8042C64C;
s32 lbl_8042C650[2];
u8 lbl_803E7538[0x44];
u8 lbl_803E757C[0xC];
u8 lbl_803E7588[0x18];
}

static const f32 lbl_8042E980 = 20.0f;
static const f32 lbl_8042E984 = 1.0f;
static const f32 lbl_8042E988 = 2.5f;
static const f32 lbl_8042E98C = 0.000030517578125f;
static const f32 lbl_8042E990 = 0.0f;
static const f32 lbl_8042E994 = 0.001f;
static const f32 lbl_8042E998 = 0.95f;
static const f32 lbl_8042E99C = -1.0f;
static const f32 lbl_8042E9A0 = 0.0054931640625f;
static const f64 lbl_8042E9A8 = 4503601774854144.0;
static const f32 lbl_8042E9B0 = 8.0f;

void __sinit_e_paralysis_cpp()
{
	void* object = fn_80113C7C(lbl_803E7588);
	__register_global_object(object, (void*)fn_80113C2C, lbl_803E757C);
}
// An explicit .ctors entry rather than #pragma startup: the pragma leaves the
// static initializer out of the section, which drops the 4-byte slot the retail
// .ctors reserves at 0x802398FC and shifts every later entry down. perf.cpp
// carries the same explicit entry for the same reason.
__declspec(section ".ctors") void (*const eParalysisCtorEntry)(void) = __sinit_e_paralysis_cpp;

sParalysisParam::sParalysisParam()
{
	activeFrames        = 50;
	recoveryFrames      = 20;
	*(f32*)&offset.v[0] = *(f32*)&offset.v[1] = *(f32*)&offset.v[2] = lbl_8042E9B0;
}

void TEnemyParalysis::Initialize()
{
	void* heap   = fn_8005EC0C();
	lbl_8042C648 = fn_8005EA04(lbl_80288CCC);
	lbl_8042C64C = fn_8005EA04(lbl_80288CDC);
	if (lbl_8042C648 != NULL && lbl_8042C64C != NULL) {
		*(void**)lbl_803E7538 = lbl_8042C64C;
		fn_8005BF5C(lbl_8042C648);
	}
	fn_80113AA8(lbl_803E7588, heap, lbl_8042C648, lbl_80288C24, 9);
	lbl_8042C650[0] = 0;
}

void TEnemyParalysis::Finalize()
{
	fn_80113A68(lbl_803E7588);
}

TEnemyParalysis::TEnemyParalysis(TObject* parent, sParalysisParam* param)
    : TObject(parent)
{
	*(void**)(base + 0x18) = lbl_80288CA0;
	activeFrames           = 50;
	recoveryFrames         = 20;
	offset.x = offset.y = offset.z = lbl_8042E9B0;
	*(void**)this                  = lbl_8042B810[0];
	*(u16*)(base + 0x1E)           = 0x74;
	effect                         = NULL;
	position.x = position.y = position.z = lbl_8042E990;
	velocity.x = velocity.y = velocity.z = lbl_8042E990;
	angle.x = angle.y = angle.z = 0;
	state                       = 0;
	frame                       = 0;
	enabled                     = 0;
	if (param != NULL) {
		activeFrames      = param->activeFrames;
		recoveryFrames    = param->recoveryFrames;
		*(RawV3d*)&offset = param->offset;
	} else {
		activeFrames   = 50;
		recoveryFrames = 20;
	}
	if (lbl_8042C648 != NULL)
		effect = fn_80150588(lbl_8042C648);
}

TEnemyParalysis::~TEnemyParalysis()
{
	*(void**)(base + 0x18) = lbl_80288CA0;
	if (effect != NULL) {
		fn_80150958(effect);
		effect = NULL;
	}
}

void TEnemyParalysis::Exec()
{
	switch (state) {
		case 0:
			if (enabled != 0) {
				velocity.x = lbl_8042E988 * (lbl_8042E98C * fn_801C28D8());
				velocity.y = lbl_8042E988 * (lbl_8042E98C * fn_801C28D8());
				velocity.z = lbl_8042E990;
				state      = 1;
				timer      = activeFrames;
				if (lbl_8042C388 != NULL)
					fn_800B4A38(lbl_8042C388, 0x405C, &position, 0, 1, 0, 0);
			}
			break;
		case 1:
			if ((f32)__fabs(velocity.x) > lbl_8042E994)
				velocity.x *= lbl_8042E998;
			else
				velocity.x = lbl_8042E990;
			if ((f32)__fabs(velocity.y) > lbl_8042E994)
				velocity.y *= lbl_8042E998;
			else
				velocity.y = lbl_8042E990;
			velocity.x *= lbl_8042E99C;
			velocity.y *= lbl_8042E99C;
			if (--timer < 0) {
				timer = recoveryFrames;
				state = 2;
			}
			break;
		case 2:
			if (--timer < 0) {
				state   = 0;
				enabled = 0;
			}
			break;
	}

	if (enabled != 0 && effect != NULL && state == 1) {
		void* frame = *(void**)((u8*)effect + 4);
		fn_8019EC30(frame, &offset, 0);
		fn_8019ED68(frame, lbl_80239990, lbl_8042E9A0 * angle.z, 2);
		fn_8019ED68(frame, lbl_80239978, lbl_8042E9A0 * angle.x, 2);
		fn_8019ED68(frame, lbl_80239984, lbl_8042E9A0 * angle.y, 2);
		fn_8019EB94(frame, &position, 2);
		++this->frame;
		if (this->frame > 8)
			this->frame = 0;
	}
}

void TEnemyParalysis::TDisp()
{
	if (effect != NULL && state == 1) {
		struct {
			RwV3d pos;
			f32 radius;
		} sphere;
		sphere.pos    = position;
		sphere.radius = lbl_8042E980;
		if (fn_8019CE34(*lbl_8042C9A4, &sphere)) {
			fn_80113940();
			fn_801138B4();
			fn_801137FC(0x15);
			fn_801137AC();
			fn_8011398C(lbl_803E7588, frame);
			s32 value = *(s32*)((u8*)lbl_8042C180 + 0x30);
			if (lbl_8042C650[0] != value) {
				fn_8011B844(lbl_8042C64C, lbl_8042E984);
				fn_8014FFBC(lbl_8042C648, (void*)fn_8005BF88, lbl_803E7538);
				lbl_8042C650[0] = value;
			}
			fn_8014FF2C(effect);
			fn_80113838(0x15);
			fn_801138F4();
		}
	}
}

void TEnemyParalysis::Vibrate(RwFrame* frame, RwOpCombineType combine)
{
	if (frame != NULL) {
		fn_8019EB94(frame, &velocity, combine);
		enabled = 1;
	}
}

void TEnemyParalysis::SetPosAng(const RwV3d* pos, const sAngle* ang)
{
	if (pos != NULL)
		position = *pos;
	if (ang != NULL)
		angle = *ang;
}
