// TObjS13Cloud1's TDisp: placed in the editor (the original asks twice), it
// switches the scene light to set 0x10 and back to the default set through
// CLIGHT's own calls on the global light object. The class is shared through
// s13_cloud1_class.inc.

#define S13_CLOUD1_CTOR inline
#include "src/rel/s13_cloud1_class.inc"

// The part of the scene light (game/light.h's CLIGHT, whose header clashes
// with the object headers here) these calls use.
class CLIGHT
{
public:
	u8 unk000[0x4BE];
	s8 default_num; // 0x4BE
	void SetLightRegular(s8 num);
	void SetCurrentNum(s8 num);
};

extern "C" CLIGHT lbl_802D5E80;

void TObjS13Cloud1::TDisp()
{
	if (OnEdit()) {
		if (OnEdit()) {
			lbl_802D5E80.SetCurrentNum(0x10);
			lbl_802D5E80.SetLightRegular(lbl_802D5E80.default_num);
		}
	}
}
