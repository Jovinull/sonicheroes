#include "game/effect/eff_bomb.h"
#include "game/setObj.h"

// rinoColObjectCreate, the factory the editor record for
// TObjColliCommunication points at: the trigger volumes that steer the
// Rinoliner, in stage05D and stage07D.
//
// The allocation is a real new-expression of the C++ class, which is what
// gives the original's `mr r0, r3` and then `mr r31, r0`; rel/sample1_create.cpp
// has the long form. The bases are in the order rel/flyer_collision_create.cpp
// has them, collision block second and placement base third, and the object
// hangs off the task at lbl_8042C10C.
//
// The constructor is that class's without the reset step: copy the
// placement's kind, extents, position and angle, then give the collision base
// its shape, centred on the placement, with the radius from the parameter
// block.

struct ColliCommunicationParam {
	u8 kind;      // 0x00
	f32 radius;   // 0x04
	RwV3d extent; // 0x08
};

extern "C" char* CL_TObjColliCommunication;
extern "C" CCL_INFO colliCommunicationCclInfo;
extern "C" TObject* lbl_8042C10C;

class TObjColliCommunication : public TObject, public C_COLLI, public TObjSetObj
{
public:
	RwV3d pos;    // 0xB8
	sAngle ang;   // 0xC4
	u8 kind;      // 0xD0
	RwV3d extent; // 0xD4

	TObjColliCommunication(TObject* parent)
	    : TObject(parent)
	{
		ClassName = CL_TObjColliCommunication;
		DispTime  = 0xE0;
		SetParameter();
		SetColliParameter();
	}

	void SetParameter()
	{
		ColliCommunicationParam* param = (ColliCommunicationParam*)ObjParam->setData.setBuffer;

		kind   = param->kind;
		extent = param->extent;
		pos    = ObjParam->setData.pos;
		ang    = ObjParam->setData.ang;
	}

	void SetColliParameter()
	{
		Init(&colliCommunicationCclInfo, 1, 4);
		if (info != NULL) {
			ColliCommunicationParam* param = (ColliCommunicationParam*)ObjParam->setData.setBuffer;

			C_COLLI::pos = pos;
			info->a      = param->radius;
		}
		CalcRange();
	}

	virtual ~TObjColliCommunication();
	virtual void Exec();
	virtual void TDisp();
	virtual void EditOnChange(SETDATA_PARAM*);
};

extern "C" void rinoColObjectCreate(void)
{
	new TObjColliCommunication(lbl_8042C10C);
}
