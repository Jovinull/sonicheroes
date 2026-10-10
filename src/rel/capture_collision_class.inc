// TObjCaptureCollision, shared by rel/capture_collision_create.cpp, which defines CAPTURE_COLLISION_CTOR
// as inline so its factory inlines the constructor, and rel/capture_collision_ctor.cpp,
// which defines it empty to emit the out-of-line copy the module also keeps.

#include "game/effect/eff_bomb.h"
#include "game/setObj.h"

extern "C" char* CL_TObjCaptureCollision;
extern "C" const f32 captureCollisionZero[1];
extern "C" TObject* lbl_8042C10C;

// KillMyself and the constructor's two steps are inline (Exec and the
// factories inline them); rel/capture_collision_kill.cpp defines
// CAPTURE_KILL_INLINE empty, and rel/capture_collision_parameter.cpp
// CAPTURE_PARAM_INLINE, to emit the out-of-line copies each module also keeps.
#ifndef CAPTURE_KILL_INLINE
#define CAPTURE_KILL_INLINE inline
#endif
#ifndef CAPTURE_PARAM_INLINE
#define CAPTURE_PARAM_INLINE inline
#endif

class TObjCaptureCollision : public TObject, public TObjSetObj
{
public:
	RwV3d pos;  // 0x30
	sAngle ang; // 0x3C

	TObjCaptureCollision(TObject* parent);

	// Out of range or due to be killed (TObjSetObj's two tests, as one answer).
	CAPTURE_KILL_INLINE s32 KillMyself();
	CAPTURE_PARAM_INLINE void SetParameter();
	CAPTURE_PARAM_INLINE void ResetVariable();
	static TObjCaptureCollision* CreateInstance();

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

CAPTURE_KILL_INLINE s32 TObjCaptureCollision::KillMyself()
{
	if (CheckRangeOut() || CheckMustKill()) {
		return 1;
	}
	return 0;
}

CAPTURE_PARAM_INLINE void TObjCaptureCollision::SetParameter()
{
	pos = ObjParam->setData.pos;
	ang = ObjParam->setData.ang;
}

CAPTURE_PARAM_INLINE void TObjCaptureCollision::ResetVariable()
{
	pos.x = pos.y = pos.z = captureCollisionZero[0];
	ang.x = ang.y = ang.z = 0;
}

CAPTURE_COLLISION_CTOR TObjCaptureCollision::TObjCaptureCollision(TObject* parent)
    : TObject(parent)
{
	ClassName = CL_TObjCaptureCollision;
	DispTime  = 0x48;
	ResetVariable();
	SetParameter();
}
