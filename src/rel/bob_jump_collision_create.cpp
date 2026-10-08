#include "game/effect/eff_bomb.h"
#include "game/setObj.h"

// bobJumpCollisionObjectCreate, the factory the editor record for
// TObjBobJumpCollision points at.
//
// It is the same 143 instructions in twelve of the stage modules that share the
// engine core, at their own address in each, so each module's splits.txt names
// its own range.
//
// Both allocations are real new-expressions of C++ classes with inline
// constructors, which is what gives the original's `mr r0, r3` and then a copy
// into the register the construction runs on; rel/sample1_create.cpp has the
// long form. The jump collision is a placed object with the collision block as
// its third base, as in rel/warp_create.cpp. Its constructor builds a second
// object, TObjBobPreJumpCollision, which has no placement and so only two
// bases, and keeps the result at 0xF4, null or not. The PS2 build gives the
// pre-jump constructor a TObject parameter, so the owner is cast back.
//
// The placement's parameter block gives the box: two extents, then a depth the
// pre-jump box mirrors forward of the jump, then a third extent. Each shape is
// sized from them once the collision base has one.

struct BobJumpParam {
	f32 a;     // 0x00
	f32 b;     // 0x04
	f32 depth; // 0x08
	f32 c;     // 0x0C
};

class TObjBobJumpCollision;

extern "C" char* CL_TObjBobJumpCollision;
extern "C" char* CL_TObjBobPreJumpCollision;
extern "C" CCL_INFO bobJumpCclInfo;
extern "C" CCL_INFO bobPreJumpCclInfo;
extern "C" TObject* lbl_8042C110;

class TObjBobPreJumpCollision : public TObject, public C_COLLI
{
public:
	TObjBobJumpCollision* owner; // 0xB0

	inline TObjBobPreJumpCollision(TObject* parent);
	virtual ~TObjBobPreJumpCollision();
	virtual void Exec();
};

class TObjBobJumpCollision : public TObject, public TObjSetObj, public C_COLLI
{
public:
	s32 unkB8;                        // 0xB8
	RwV3d pos;                        // 0xBC
	sAngle ang;                       // 0xC8
	f32 a;                            // 0xD4
	f32 b;                            // 0xD8
	f32 c;                            // 0xDC
	f32 depth;                        // 0xE0
	s32 unkE4;                        // 0xE4
	s32 unkE8;                        // 0xE8
	s32 unkEC;                        // 0xEC
	s32 unkF0;                        // 0xF0
	TObjBobPreJumpCollision* preJump; // 0xF4

	TObjBobJumpCollision(TObject* parent)
	    : TObject(parent)
	{
		ClassName = CL_TObjBobJumpCollision;
		DispTime  = 0xF8;

		BobJumpParam* param = (BobJumpParam*)ObjParam->setData.setBuffer;
		pos                 = ObjParam->setData.pos;
		ang                 = ObjParam->setData.ang;

		a     = param->a;
		b     = param->b;
		c     = param->c;
		depth = param->depth;
		unkB8 = 1;

		Init(&bobJumpCclInfo, 1, 4);
		if (info != NULL) {
			info->a        = a;
			info->b        = b;
			info->c        = c;
			info->center.z = c;
			CalcRange();
		}

		unkE4 = unkE8 = 0;
		unkEC = unkF0 = 0;

		preJump = new TObjBobPreJumpCollision(this);
	}
	virtual ~TObjBobJumpCollision();
	virtual void Exec();
	virtual void EditOnChange(SETDATA_PARAM*);
};

inline TObjBobPreJumpCollision::TObjBobPreJumpCollision(TObject* parent)
    : TObject(parent)
{
	ClassName = CL_TObjBobPreJumpCollision;
	DispTime  = 0xB4;
	owner     = (TObjBobJumpCollision*)parent;

	Init(&bobPreJumpCclInfo, 1, 4);
	if (info != NULL) {
		info->a        = owner->a;
		info->b        = owner->b;
		info->c        = owner->depth;
		info->center.z = -owner->depth;
		CalcRange();
	}
}

extern "C" void bobJumpCollisionObjectCreate(void)
{
	new TObjBobJumpCollision(lbl_8042C110);
}
