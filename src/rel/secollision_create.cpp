// objSecollisionCreate, the factory of TObjSECollision (the PS2 build's name), the
// sound effect collision: an invisible collision shape that plays a sound effect
// when touched. The constructor is inline here. When the placement is being
// edited, its zero distances are put back to defaults (the sound kind 5, three
// reaches of 10); the shape takes the placement's position and the first
// reach, and kind 1 makes it the box form with all three reaches.
//
// The u16 reaches are converted with the module's shared int-to-float bias
// (secollisionBias), whose 8 bytes of .rodata this unit owns.

#include "game/effect/eff_bomb.h"
#include "game/setObj.h"

extern "C" char* CL_TObjSECollision;
extern "C" CCL_INFO secollisionInfo;
extern "C" TObject* lbl_8042C110;

struct SECollisionParams {
	u8 unk00[0x7];
	s8 kind; // 0x07
	s16 unk08;
	u16 reachA; // 0x0A
	u16 reachB; // 0x0C
	u16 reachC; // 0x0E
};

class TObjSECollision : public TObject, public TObjSetObj, public C_COLLI
{
public:
	RwV3d pos; // 0xB8

	TObjSECollision(TObject* parent);

	// Declared first and defined elsewhere: this unit emits no vtable.
	virtual void TDisp();
	virtual void Exec();
	virtual ~TObjSECollision();
	virtual void EditOnChange(SETDATA_PARAM*);
};

inline TObjSECollision::TObjSECollision(TObject* parent)
    : TObject(parent)
{
	SECollisionParams* params = (SECollisionParams*)ObjParam->setData.setBuffer;

	ClassName = CL_TObjSECollision;
	DispTime  = 0xC4;
	if (OnEdit()) {
		if (params->unk08 == 0) {
			params->unk08 = 5;
		}
		if (params->reachA == 0) {
			params->reachA = 10;
		}
		if (params->reachB == 0) {
			params->reachB = 10;
		}
		if (params->reachC == 0) {
			params->reachC = 10;
		}
	}
	pos = ObjParam->setData.pos;
	Init(&secollisionInfo, 1, 4);
	CCL_INFO* shape = info;
	if (params->kind == 1) {
		shape->form = 4;
		shape->a    = params->reachA;
		shape->b    = params->reachB;
		shape->c    = params->reachC;
	} else {
		shape->a = params->reachA;
	}
	CalcRange();
}

extern "C" void objSecollisionCreate(void)
{
	new TObjSECollision(lbl_8042C110);
}
