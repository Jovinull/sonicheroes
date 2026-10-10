//
#ifndef GAME_OBJ_FLYER_COLLISION_H
#define GAME_OBJ_FLYER_COLLISION_H
#include "game/effect/eff_bomb.h"
#include "game/setObj.h"

// TObjFlyerCollision, the trigger volumes of the flyer enemies, in the five
// stage modules that carry the class: stage05D, 07D, 09D, 13D and 26D. The
// bases are in another order than the usual placed object: the collision block
// second, at 0x28, and the placement base third, at 0xB0, which is why the
// second vtable pointer is at 0xB4 and the PS2 build's EditOnChange thunk
// adjusts by 176. Objects hang off the task at lbl_8042C10C.
//
// The constructor is the three steps the PS2 build names: ResetVariable clears
// the fields, SetParameter copies the placement's, and SetColliParameter (after
// the collision base's Init) gives the collision its shape, centred on the
// placement, with the radius from the parameter block. It is inlined into both
// rel/flyer_collision_create.cpp and rel/flyer_collision_instance.cpp.

struct FlyerColParam {
	u8 kind;      // 0x00
	f32 radius;   // 0x04
	RwV3d extent; // 0x08
	s32 unk14;    // 0x14
};

extern "C" char* CL_TObjFlyerCollision;
extern "C" CCL_INFO flyerColCclInfo;
extern "C" const f32 flyerColZero[1];
extern "C" TObject* lbl_8042C10C;

// The constructor and its three steps are inline (the factories inline them);
// rel/flyer_collision_ctor.cpp defines FLYER_COL_CTOR empty, and
// rel/flyer_collision_parameter.cpp FLYER_COL_INLINE, to emit the out-of-line
// copies each module also keeps.
#ifndef FLYER_COL_CTOR
#define FLYER_COL_CTOR inline
#endif
#ifndef FLYER_COL_INLINE
#define FLYER_COL_INLINE inline
#endif

class TObjFlyerCollision : public TObject, public C_COLLI, public TObjSetObj
{
public:
	RwV3d pos;    // 0xB8
	sAngle ang;   // 0xC4
	u8 kind;      // 0xD0
	s32 unkD4;    // 0xD4
	RwV3d extent; // 0xD8

	FLYER_COL_CTOR TObjFlyerCollision(TObject* parent);
	FLYER_COL_INLINE void SetColliParameter();
	FLYER_COL_INLINE void SetParameter();
	FLYER_COL_INLINE void ResetVariable();
	s32 CheckCollision();
	void OnClose();

	static TObjFlyerCollision* CreateInstance();

	// The first virtual declared is the key function, and the unit that defines
	// it emits the vtable. Overrides, whose order does not move their slots:
	// the unit that defines Exec declares the destructor first, the others Exec.
#ifdef FLYER_COL_DTOR_FIRST
	virtual ~TObjFlyerCollision();
#endif
	virtual void Exec();
	virtual void TDisp();
	virtual void EditOnChange(SETDATA_PARAM*);
#ifndef FLYER_COL_DTOR_FIRST
	virtual ~TObjFlyerCollision();
#endif
};

FLYER_COL_INLINE void TObjFlyerCollision::SetColliParameter()
{
	if (info != NULL) {
		FlyerColParam* param = (FlyerColParam*)ObjParam->setData.setBuffer;

		C_COLLI::pos = pos;
		info->a      = param->radius;
	}
	CalcRange();
}

FLYER_COL_INLINE void TObjFlyerCollision::SetParameter()
{
	FlyerColParam* param = (FlyerColParam*)ObjParam->setData.setBuffer;

	kind   = param->kind;
	unkD4  = param->unk14;
	extent = param->extent;
	pos    = ObjParam->setData.pos;
	ang    = ObjParam->setData.ang;
}

FLYER_COL_INLINE void TObjFlyerCollision::ResetVariable()
{
	kind     = 0;
	unkD4    = 0;
	extent.x = extent.y = extent.z = flyerColZero[0];
}

FLYER_COL_CTOR TObjFlyerCollision::TObjFlyerCollision(TObject* parent)
    : TObject(parent)
{
	ClassName = CL_TObjFlyerCollision;
	DispTime  = 0xE4;
	ResetVariable();
	SetParameter();
	Init(&flyerColCclInfo, 1, 4);
	SetColliParameter();
}

#endif
