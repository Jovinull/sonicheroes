// TObjCaptureCollision, shared by rel/capture_collision_create.cpp, which defines CAPTURE_COLLISION_CTOR
// as inline so its factory inlines the constructor, and rel/capture_collision_ctor.cpp,
// which defines it empty to emit the out-of-line copy the module also keeps.

#include "game/effect/eff_bomb.h"
#include "game/setObj.h"

extern "C" char* CL_TObjCaptureCollision;
extern "C" const f32 captureCollisionZero[1];
extern "C" TObject* lbl_8042C10C;

class TObjCaptureCollision : public TObject, public TObjSetObj
{
public:
	RwV3d pos;  // 0x30
	sAngle ang; // 0x3C

	TObjCaptureCollision(TObject* parent);

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

	// Out of range or due to be killed (TObjSetObj's two tests, as one answer).
	s32 CheckKill()
	{
		if (CheckRangeOut() || CheckMustKill()) {
			return 1;
		}
		return 0;
	}

	// The first virtual declared is the key function, and the unit that defines
	// it emits the vtable. These are all overrides, whose order does not move
	// their slots, so each fragment unit can put first one it does not define:
	// rel/capture_collision_exec.cpp (Exec) declares EditOnChange first.
#ifdef CAPTURE_EDIT_FIRST
	virtual void EditOnChange(SETDATA_PARAM*);
#endif
	virtual void Exec();
	virtual ~TObjCaptureCollision();
	virtual void TDisp();
#ifndef CAPTURE_EDIT_FIRST
	virtual void EditOnChange(SETDATA_PARAM*);
#endif
};

CAPTURE_COLLISION_CTOR TObjCaptureCollision::TObjCaptureCollision(TObject* parent)
    : TObject(parent)
{
	ClassName = CL_TObjCaptureCollision;
	DispTime  = 0x48;
	ResetVariable();
	SetParameter();
}
