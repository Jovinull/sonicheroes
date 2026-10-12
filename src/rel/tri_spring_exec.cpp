#include "types.h"

// TObjTriSpring::Exec (triSpringExec here). Out of range or marked to die, it
// hands its saved byte back to the placement's work byte and ends. While the
// editor moves it, it takes the placement (position, angles, the two springs'
// sizes, the launch value and the power picked from triSpringChoices) and sets
// the model. Otherwise it checks the player (triSpringCheckCollision, which
// starts the bounce, state 2). While bouncing, the phase advances and the
// amplitude decays by 0.987 a frame; once it is within 0.001 everything settles
// back to 1 and the state to 1, else the two scales swing around 1 with the
// phase's sine. It sets the model, counts its eight timers down and records the
// volume's position and angles before re-entering its collision.
//
// The unit owns the two constants only it reads (0.987 and 0.001); 1.0 is the
// module's shared triSpringOne.

typedef struct RwV3d {
	f32 x, y, z;
} RwV3d;

typedef struct TriSpringParams {
	f32 sizeA;  // 0x00
	f32 sizeB;  // 0x04
	s16 launch; // 0x08
	s8 power;   // 0x0A
} TriSpringParams;

typedef struct TriSpringSetData {
	RwV3d pos;               // 0x00
	s32 angX;                // 0x0C
	s32 angY;                // 0x10
	s32 angZ;                // 0x14
	u8 unk18[0x14];          // 0x18
	TriSpringParams* params; // 0x2C
	u8* work;                // 0x30
} TriSpringSetData;

typedef struct TriSpringChoice {
	const char* label; // 0x00
	s32 value;         // 0x04
} TriSpringChoice;

typedef struct TriSpring {
	u8 unk00[0x4];
	u16 signal;                // 0x04
	u8 unk06[0x22];            // 0x06
	TriSpringSetData* setdata; // 0x28
	void* setobjVtable;        // 0x2C
	u8 colli[0x60];            // 0x30
	RwV3d colliPos;            // 0x90
	s32 colliAngX;             // 0x9C
	s32 colliAngY;             // 0xA0
	s32 colliAngZ;             // 0xA4
	u8 unkA8[0x4];             // 0xA8
	RwV3d colliOldPos;         // 0xAC
	s32 state;                 // 0xB8
	s8 timers[8];              // 0xBC
	u8 saved;                  // 0xC4
	s8 power;                  // 0xC5
	s16 launch;                // 0xC6
	RwV3d pos;                 // 0xC8
	s32 angX;                  // 0xD4
	s32 angY;                  // 0xD8
	s32 angZ;                  // 0xDC
	s32 phase;                 // 0xE0
	f32 amplitude;             // 0xE4
	f32 scaleA;                // 0xE8
	f32 scaleB;                // 0xEC
	f32 sizeA;                 // 0xF0
	f32 sizeB;                 // 0xF4
} TriSpring;

extern "C" const f32 triSpringOne[1];
extern "C" TriSpringChoice triSpringChoices[];

extern "C" s32 CheckRangeOut__10TObjSetObjFv(void* setobj);
extern "C" s32 CheckMustKill__10TObjSetObjFv(void* setobj);
extern "C" s32 OnEdit__10TObjSetObjFv(void* setobj);
extern "C" void Entry__7C_COLLIFv(void* colli);
extern "C" f32 fn_800D7B00(s32 angle);
extern "C" double __fabs(double x);
extern "C" void triSpringCheckCollision(TriSpring* object);
extern "C" void triSpringSetPosition(TriSpring* object);

extern "C" void triSpringExec(TriSpring* object)
{
	TriSpringParams* params = object->setdata->params;
	TriSpringSetData* setdata;
	int i;

	if (CheckRangeOut__10TObjSetObjFv(&object->setdata)
	    || CheckMustKill__10TObjSetObjFv(&object->setdata)) {
		*object->setdata->work = object->saved;
		object->signal |= 1;
		return;
	}
	if (OnEdit__10TObjSetObjFv(&object->setdata)) {
		setdata        = object->setdata;
		object->pos.x  = setdata->pos.x;
		object->pos.y  = setdata->pos.y;
		object->pos.z  = setdata->pos.z;
		setdata        = object->setdata;
		object->angX   = setdata->angX;
		object->angY   = setdata->angY;
		object->angZ   = setdata->angZ;
		object->sizeA  = params->sizeA;
		object->sizeB  = triSpringOne[0] + params->sizeB;
		object->launch = params->launch;
		object->power  = triSpringChoices[params->power].value;
		triSpringSetPosition(object);
		return;
	}
	triSpringCheckCollision(object);
	if (object->state == 2) {
		object->phase += 0x800;
		object->amplitude = 0.987f * object->amplitude;
		if ((f32)__fabs(object->amplitude) <= 0.001f) {
			object->amplitude = triSpringOne[0];
			object->scaleB    = triSpringOne[0];
			object->scaleA    = triSpringOne[0];
			object->state     = 1;
		} else {
			object->scaleA = triSpringOne[0] + object->amplitude * fn_800D7B00(object->phase);
			object->scaleB = triSpringOne[0] - object->amplitude * fn_800D7B00(object->phase);
		}
	}
	triSpringSetPosition(object);
	for (i = 0; i < 8; i++) {
		if (object->timers[i] > 0) {
			object->timers[i]--;
		}
	}
	object->colliOldPos.x = object->colliPos.x;
	object->colliOldPos.y = object->colliPos.y;
	object->colliOldPos.z = object->colliPos.z;
	object->colliPos.x    = object->pos.x;
	object->colliPos.y    = object->pos.y;
	object->colliPos.z    = object->pos.z;
	object->colliAngX     = object->angX;
	object->colliAngY     = object->angY;
	object->colliAngZ     = object->angZ;
	Entry__7C_COLLIFv(object->colli);
}
