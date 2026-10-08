#include "game/effect/eff_bomb.h"
#include "game/setObj.h"

// captureCollisionCreate, the factory rel/capture_collision_register.cpp puts
// in the editor record for TObjCaptureCollision, in the five stage modules
// whose revision of the class inlines the whole constructor: stage05D, 07D,
// 09D, 13D and 26D. rel/e_capture_collision.cpp is the other revision, where
// ResetVariable and SetParameter stay calls.
//
// The allocation is a real new-expression of the C++ class, which is what
// gives the original's `mr r0, r3` and then `mr r31, r0`; rel/sample1_create.cpp
// has the long form. The object hangs off the task at lbl_8042C10C rather than
// the usual one.
//
// ResetVariable clears the position and angle, the position from the module's
// zero, and SetParameter then copies the placement's over them.

extern "C" char* CL_TObjCaptureCollision;
extern "C" const f32 captureCollisionZero[1];
extern "C" TObject* lbl_8042C10C;

class TObjCaptureCollision : public TObject, public TObjSetObj
{
public:
	RwV3d pos;  // 0x30
	sAngle ang; // 0x3C

	TObjCaptureCollision(TObject* parent)
	    : TObject(parent)
	{
		ClassName = CL_TObjCaptureCollision;
		DispTime  = 0x48;
		ResetVariable();
		SetParameter();
	}

	void ResetVariable()
	{
		pos.x = pos.y = pos.z = captureCollisionZero[0];
		ang.x = ang.y = ang.z = 0;
	}

	void SetParameter()
	{
		pos = ObjParam->setData.pos;
		ang = ObjParam->setData.ang;
	}

	virtual ~TObjCaptureCollision();
	virtual void Exec();
	virtual void EditOnChange(SETDATA_PARAM*);
};

extern "C" void captureCollisionCreate(void)
{
	new TObjCaptureCollision(lbl_8042C10C);
}
