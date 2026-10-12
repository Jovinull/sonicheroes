#include "game/effect/eff_bomb.h"
#include "game/object.h"
#include "game/setObj.h"

// TObjCage (the PS2 build's class): a cage that swings on its placement and
// holds what was placed inside it. The members below are inline here and also
// have out-of-line copies, each in its own unit (rel/cage_*.cpp), which defines
// its macro empty before including this file.

struct CageParams {
	s32 kind;    // 0x00
	f32 period;  // 0x04
	f32 rangeX;  // 0x08
	f32 rangeY;  // 0x0C
};

struct sParalysisParam;

class TEnemyParalysis : public TObject
{
public:
	u8 pad28[0x4C];

	TEnemyParalysis(TObject* parent, sParalysisParam* param);
	~TEnemyParalysis();
}; // 0x74

class TObjCage : public TObject, public TObjSetObj, public C_COLLI, public OBJ_MoveOnGround
{
public:
	s32 state;                  // 0xF0
	s8 kind;                    // 0xF4
	u8 padF5;
	s16 unkF6;                  // 0xF6
	s16 unkF8;                  // 0xF8
	u8 padFA[0x2];
	RwV3d startPos;             // 0xFC
	RwV3d pos;                  // 0x108
	sAngle ang;                 // 0x114
	RwV3d spd;                  // 0x120
	f32 unk12C;                 // 0x12C
	f32 unk130;                 // 0x130
	s32 swingStep;              // 0x134
	f32 rangeX;                 // 0x138
	f32 rangeY;                 // 0x13C
	f32 radius;                 // 0x140
	RpClump* models[2];         // 0x144
	SETOBJ_PARAM* inside;       // 0x14C
	f32 baseY;                  // 0x150
	TEnemyParalysis* paralysis; // 0x154

	TObjCage(TObject* parent);
	// Exec comes first so that it is the key function: no unit of ours emits
	// the vtable, which stays in each module's data.
	virtual void Exec();
	virtual ~TObjCage();
	void SetPosition();
	void SetParameter();
	void DestroyClump();
	void CloneClump();
	s32 SearchInsideObject();
}; // 0x158

extern "C" u8* lbl_8042C1D0;
extern "C" void* cageModels[3];
struct CageObjectLists {
	u8 pad00[0x30];
	SETOBJ_PARAM* lists[1]; // 0x30, by group
};

extern "C" CageObjectLists* lbl_8042C298;
extern "C" const f32 cageZero[1];
extern "C" const f32 cageSwingScale[1];
extern "C" const f32 cageSwingRate[1];
extern "C" const f32 cageRangeYScale[1];
extern "C" const f64 cageHalf[1];
extern "C" const f64 cageThree[1];
extern "C" const f32 cageRadiusScale[1];
extern "C" const f32 cageInsideReach[1];

extern "C" f32 fn_800D7B00(s32 angle);
extern "C" RpClump* fn_80150588(void* model);
extern "C" void fn_80150958(RpClump* clump);
extern "C" void fn_8015BB08(void* world, RpClump* clump);
extern "C" void fn_8015BBF8(void* world, RpClump* clump);
double __frsqrte(double x);
void objRpClumpForAllAtomicsToSetRenderCallbackToUseLight(RpClump* clump, u32 light);
f32 Distance2P2P(const RwV3d* a, const RwV3d* b);

// MSL's sqrtf, with the TU's pooled constants named (0.0f, 0.5 and 3.0). The
// constants are read into locals as the retail schedules them: 3.0 after the
// first 0.5 * guess.
static inline f32 cageSqrtf(f32 x)
{
	volatile f32 y;

	if (x > cageZero[0]) {
		double guess = __frsqrte((double)x);
		double half  = cageHalf[0];
		double three;
		guess        = half * guess * ((three = cageThree[0]) - guess * guess * x);
		guess        = half * guess * (three - guess * guess * x);
		guess        = half * guess * (three - guess * guess * x);
		y            = (f32)(x * guess);
		return y;
	}
	return x;
}

#ifndef CAGE_SET_PARAMETER_INLINE
#define CAGE_SET_PARAMETER_INLINE inline
#endif

// The placement: position (also kept as the start), angles, kind, the two
// swing ranges, the swing step from the period and the radius the swing spans.
CAGE_SET_PARAMETER_INLINE void TObjCage::SetParameter()
{
	CageParams* params = (CageParams*)ObjParam->setData.setBuffer;

	pos       = ObjParam->setData.pos;
	startPos  = pos;
	ang       = ObjParam->setData.ang;
	kind      = params->kind;
	rangeX    = params->rangeX;
	rangeY    = params->rangeY;
	swingStep = cageSwingScale[0] / (cageSwingRate[0] * params->period);
	f32 x     = rangeX * fn_800D7B00(swingStep);
	f32 y     = cageRangeYScale[0] * (rangeY * fn_800D7B00(swingStep));
	radius    = cageRadiusScale[0] * cageSqrtf(x * x + y * y);
}

#ifndef CAGE_DESTROY_CLUMP_INLINE
#define CAGE_DESTROY_CLUMP_INLINE inline
#endif

// Takes both models out of the world and frees them.
CAGE_DESTROY_CLUMP_INLINE void TObjCage::DestroyClump()
{
	for (int i = 0; i < 2; i++) {
		if (models[i] != NULL) {
			fn_8015BBF8(*(void**)(lbl_8042C1D0 + 0x7274), models[i]);
			fn_80150958(models[i]);
			models[i] = NULL;
		}
	}
}

#ifndef CAGE_CLONE_CLUMP_INLINE
#define CAGE_CLONE_CLUMP_INLINE inline
#endif

// Makes the models again for the kind: the cage (the second model for kinds 2
// and 3) and, for kinds 1 and 3, the third model, lit by the placement's light
// bits.
CAGE_CLONE_CLUMP_INLINE void TObjCage::CloneClump()
{
	DestroyClump();
	if (kind == 2 || kind == 3) {
		models[0] = fn_80150588(cageModels[1]);
	} else {
		models[0] = fn_80150588(cageModels[0]);
	}
	fn_8015BB08(*(void**)(lbl_8042C1D0 + 0x7274), models[0]);
	if (kind == 1 || kind == 3) {
		models[1] = fn_80150588(cageModels[2]);
		fn_8015BB08(*(void**)(lbl_8042C1D0 + 0x7274), models[1]);
	} else {
		models[1] = NULL;
	}
	objRpClumpForAllAtomicsToSetRenderCallbackToUseLight(
	    models[0], ((ObjParam->setData.condition.Flag & 0x1C0000) >> 18) + 4);
	if (models[1] != NULL) {
		objRpClumpForAllAtomicsToSetRenderCallbackToUseLight(
		    models[1], ((ObjParam->setData.condition.Flag & 0x1C0000) >> 18) + 4);
	}
}

#ifndef CAGE_SEARCH_INSIDE_INLINE
#define CAGE_SEARCH_INSIDE_INLINE inline
#endif

// The first object of the placement's group, of one of the kinds a cage can
// hold, near enough to the cage.
CAGE_SEARCH_INSIDE_INLINE s32 TObjCage::SearchInsideObject()
{
	SETOBJ_PARAM* obj = lbl_8042C298->lists[ObjParam->setData.communicateId];

	inside = NULL;
	for (; obj != NULL; obj = obj->next) {
		u16 id = obj->setData.uniqueId;

		if (id == 0x5 || id == 0x18 || id == 0x67 || id == 0x10B || id == 0x511 || id == 0x140A
		    || id == 0x1109 || id == 0x23) {
			if (Distance2P2P(&ObjParam->setData.pos, &obj->setData.pos) < cageInsideReach[0]) {
				inside = obj;
				return 1;
			}
		}
	}
	return 0;
}
