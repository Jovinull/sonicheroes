//
#ifndef GAME_OBJ_COLLI_COMMUNICATION_H
#define GAME_OBJ_COLLI_COMMUNICATION_H
#include "game/effect/eff_bomb.h"
#include "game/setObj.h"

// TObjColliCommunication, the trigger volumes that steer the Rinoliner, in
// stage05D and stage07D. The bases are in the order game/obj_flyer_collision.h
// has them, collision block second and placement base third, and objects hang
// off the task at lbl_8042C10C.
//
// The constructor is the flyer collision's with an empty reset step: copy the
// placement's kind, extents, position and angle, then (after the collision
// base's Init) give the collision its shape, centred on the placement, with
// the radius from the parameter block. It is inlined into both
// rel/colli_communication_create.cpp and rel/colli_communication_instance.cpp.

struct ColliCommunicationParam {
	u8 kind;      // 0x00
	u8 action;    // 0x01: names the editor's second field
	f32 radius;   // 0x04
	RwV3d extent; // 0x08
};

extern "C" char* CL_TObjColliCommunication;
extern "C" CCL_INFO colliCommunicationCclInfo;
extern "C" TObject* lbl_8042C10C;

// The constructor and its steps are inline (the factories inline them);
// rel/colli_communication_ctor.cpp defines COLLI_COMM_CTOR empty, and
// rel/colli_communication_parameter.cpp COLLI_COMM_INLINE, to emit the
// out-of-line copies each module also keeps.
#ifndef COLLI_COMM_CTOR
#define COLLI_COMM_CTOR inline
#endif
#ifndef COLLI_COMM_INLINE
#define COLLI_COMM_INLINE inline
#endif

class TObjColliCommunication : public TObject, public C_COLLI, public TObjSetObj
{
public:
	RwV3d pos;    // 0xB8
	sAngle ang;   // 0xC4
	u8 kind;      // 0xD0
	RwV3d extent; // 0xD4

	COLLI_COMM_CTOR TObjColliCommunication(TObject* parent);
	COLLI_COMM_INLINE void SetColliParameter();
	COLLI_COMM_INLINE void SetParameter();
	COLLI_COMM_INLINE void ResetVariable();
	s32 CheckCollision();
	void OnClose();

	static TObjColliCommunication* CreateInstance();

	// The first virtual declared is the key function, and the unit that defines
	// it emits the vtable. Overrides, whose order does not move their slots:
	// the unit that defines Exec declares the destructor first, the others Exec.
#ifdef COLLI_COMM_DTOR_FIRST
	virtual ~TObjColliCommunication();
#endif
	virtual void Exec();
	virtual void TDisp();
	virtual void EditOnChange(SETDATA_PARAM*);
#ifndef COLLI_COMM_DTOR_FIRST
	virtual ~TObjColliCommunication();
#endif
};

COLLI_COMM_INLINE void TObjColliCommunication::SetColliParameter()
{
	if (info != NULL) {
		ColliCommunicationParam* param = (ColliCommunicationParam*)ObjParam->setData.setBuffer;

		C_COLLI::pos = pos;
		info->a      = param->radius;
	}
	CalcRange();
}

COLLI_COMM_INLINE void TObjColliCommunication::SetParameter()
{
	ColliCommunicationParam* param = (ColliCommunicationParam*)ObjParam->setData.setBuffer;

	kind   = param->kind;
	extent = param->extent;
	pos    = ObjParam->setData.pos;
	ang    = ObjParam->setData.ang;
}

COLLI_COMM_INLINE void TObjColliCommunication::ResetVariable() { }

COLLI_COMM_CTOR TObjColliCommunication::TObjColliCommunication(TObject* parent)
    : TObject(parent)
{
	ClassName = CL_TObjColliCommunication;
	DispTime  = 0xE0;
	ResetVariable();
	SetParameter();
	Init(&colliCommunicationCclInfo, 1, 4);
	SetColliParameter();
}

#endif
