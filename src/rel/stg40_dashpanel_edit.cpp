#include "types.h"

// TObjDashpanel::EditOnChange in stage40D (the PS2 build's name; the class is the one
// whose vtable holds it): the module's ordinary TObjDashpanel, not the SPSTAGEOBJ one,
// with the body of SPSTAGEOBJ::TObjDashpanel's (rel/sp_dashpanel.cpp, whose
// flags it shares): the power is kept within its bounds and the no-control
// time within 0-32767.

struct EditMember {
	f32 Power;      // 0x00
	s16 nocon_time; // 0x04
};

struct SETDATA_PARAM {
	u8 pad00[0x2C];
	EditMember* member; // 0x2C
};

extern "C" const f32 plainDashpanelMinimumPower;
extern "C" const f32 plainDashpanelMaximumPower;

// built without optimisation, as in rel/sp_dashpanel.cpp
#pragma optimization_level 0

extern "C" void EditOnChange__13TObjDashpanelFP13SETDATA_PARAM(void* object, SETDATA_PARAM* setData)
{
	register EditMember* _member = setData->member;
	if (_member->Power < plainDashpanelMinimumPower)
		_member->Power = plainDashpanelMinimumPower;
	if (_member->Power > plainDashpanelMaximumPower)
		_member->Power = plainDashpanelMaximumPower;
	if (_member->nocon_time < 0)
		_member->nocon_time = 0;
	if (_member->nocon_time > 32767)
		_member->nocon_time = 32767;
}
