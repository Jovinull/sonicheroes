#include "types.h"

// SetEffectFireBomb (CORROBORATED by PS2 metadata and the stored class name order): creates a TObjEffFireBomb
// (vtable lbl_8025A158) through TObject's task-heap operator new. Names are from PS2; the symbols keep their
// address-based names.
// The class's vtable is not defined in this unit yet, so the constructor stores it by its current name.

struct RwV3d {
	f32 x, y, z;
};
struct sAngle {
	s32 x, y, z;
};

struct THeapCtrl {
	void* Malloc(u32);
	void Free(void*);
};
extern "C" THeapCtrl* lbl_8042C148;

class TObject;
struct TObjectBase {
	char* ClassName;
	u16 Signal, Tag;
	TObject* Prev;
	TObject* Next;
	TObject* Parent;
	TObject* Child;
};
class TObject : public TObjectBase
{
public:
	TObject(TObject*);
	~TObject();
	void** vtable; // 0x18
	u16 ExecTime, DispTime, TDispTime, PDispTime, ImmAftSetRasterTime;
	static void* operator new(unsigned long size) { return lbl_8042C148->Malloc(size); }
	static void operator delete(void* p);
};

class C_COLLI;
struct CCL_HIT_INFO {
	s8 my_num, hit_num;
	u16 flag;
	C_COLLI* hit_ccl;
};
struct CCL_INFO {
	u8 kind, form, push, damage;
	u32 attr;
	RwV3d center;
	f32 a, b, c;
	void* pReactor;
	s32 angx, angy, angz;
};
class C_COLLI
{
public:
	C_COLLI();
	~C_COLLI();
	void Init(CCL_INFO*, int, u8);
	void CalcRange();
	u16 id;
	s16 nbHit, strength, vitality;
	u16 flag, nbInfo;
	f32 colli_range;
	CCL_INFO* info;
	CCL_HIT_INFO hit_info[8];
	RwV3d normal, pos;
	sAngle ang;
	s32 character_id;
	RwV3d pre_pos;
};

struct RpClump;
struct RpAtomic;

extern "C" {
extern TObject* lbl_8042C2A0;
extern TObject* lbl_8042C110;
extern char* lbl_8042B6EC;
extern f32 lbl_8042E584;
extern f32 lbl_8042E5B0;
extern CCL_INFO lbl_80259E98;
extern RpClump* lbl_8042C50C;
extern char lbl_8042B700;
extern char lbl_8025A158[];
RpClump* fn_80150588(RpClump*);
void objRpClumpForAllGeometrysToIgnoreLights__FP7RpClump(RpClump*);
void objRpClumpForAllGeometrysToModulateMaterialColor__FP7RpClump(RpClump*);
RpAtomic* objRpClumpGetAtomicWithTexture__FP7RpClumpP8RpAtomicPc(RpClump*, RpAtomic*, char*);
RpAtomic* fn_801491A8(RpAtomic*);
}
s32 GetCCLCharacterIdFromTeamNoOfBomb(s32);

class TObjEffFireBomb : public TObject, public C_COLLI
{
public:
	TObjEffFireBomb(TObject* parent, s32 teamNo_Current, RwV3d* pPosition0, sAngle* pAngle0)
	    : TObject(parent)
	{
		vtable         = (void**)lbl_8025A158;
		ClassName      = lbl_8042B6EC;
		DispTime       = sizeof(TObjEffFireBomb);
		teamNo         = (s8)teamNo_Current;
		unkB1          = 0xFF;
		unkB2          = 0xFF;
		scale          = lbl_8042E584;
		pos            = *pPosition0;
		ang            = *pAngle0;
		pClumpInstance = fn_80150588(lbl_8042C50C);
		if (pClumpInstance) {
			objRpClumpForAllGeometrysToIgnoreLights__FP7RpClump(pClumpInstance);
			objRpClumpForAllGeometrysToModulateMaterialColor__FP7RpClump(pClumpInstance);
			RpAtomic* pAtomic = objRpClumpGetAtomicWithTexture__FP7RpClumpP8RpAtomicPc(
			    pClumpInstance, 0, &lbl_8042B700);
			fn_801491A8(pAtomic);
			fn_801491A8(objRpClumpGetAtomicWithTexture__FP7RpClumpP8RpAtomicPc(
			    pClumpInstance, pAtomic, &lbl_8042B700));
		}
		Init(&lbl_80259E98, 1, 1);
		character_id = GetCCLCharacterIdFromTeamNoOfBomb(teamNo);
		if (info) {
			info->a = lbl_8042E5B0 * scale;
			CalcRange();
		}
		if (teamNo_Current != -1)
			strength = 3;
	}

private:
	s8 teamNo;
	u8 unkB1, unkB2, unkB3;
	f32 scale;
	RpClump* pClumpInstance;
	RwV3d pos;
	sAngle ang;
};

extern "C" void fn_800FA7CC(s32 teamNo_Current, RwV3d* pPosition0, sAngle* pAngle0)
{
	TObject* parent = lbl_8042C2A0;
	if (!parent)
		parent = lbl_8042C110;
	new TObjEffFireBomb(parent, teamNo_Current, pPosition0, pAngle0);
}
