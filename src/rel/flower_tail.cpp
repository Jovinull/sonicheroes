#include "types.h"

// Six small functions between each module's flower registration and
// TObjChao::SearchCage (the PS2 build's names), the same in the thirteen stage
// modules that share the engine core. Nothing calls them; they are kept with
// force_active.
//
// Two return the flower's bound (flowerBound2). The other four work an object
// whose virtual table sits at 0x18: two call a virtual (slot 0x40 or 0x44) and
// then clear a word to -1, and two set the object's state to 2 or 3 and clear
// or fill the top byte of its colour, hiding or showing it.

extern "C" const f32 flowerBound2[1];

class FlowerTailObject
{
public:
	u8 unk00[0x18];
	virtual void Virtual08();
	virtual void Virtual0C();
	virtual void Virtual10();
	virtual void Virtual14();
	virtual void Virtual18();
	virtual void Virtual1C();
	virtual void Virtual20();
	virtual void Virtual24();
	virtual void Virtual28();
	virtual void Virtual2C();
	virtual void Virtual30();
	virtual void Virtual34();
	virtual void Virtual38();
	virtual void Virtual3C();
	virtual void Virtual40();
	virtual void Virtual44();
	u8 unk1C[0xC];
	s32 state;  // 0x28
	u32 colour; // 0x2C
	s32 unk30;  // 0x30
};

extern "C" f32 flowerTailBoundA(void)
{
	return flowerBound2[0];
}

extern "C" f32 flowerTailBoundB(void)
{
	return flowerBound2[0];
}

extern "C" void flowerTailResetA(FlowerTailObject* object)
{
	object->Virtual40();
	object->unk30 = -1;
}

extern "C" void flowerTailHide(FlowerTailObject* object)
{
	object->state = 2;
	object->colour &= 0xFFFFFF;
}

extern "C" void flowerTailResetB(FlowerTailObject* object)
{
	object->Virtual44();
	object->colour = -1;
}

extern "C" void flowerTailShow(FlowerTailObject* object)
{
	object->state  = 3;
	object->colour = (object->colour & 0xFFFFFF) | 0xFF000000;
}
