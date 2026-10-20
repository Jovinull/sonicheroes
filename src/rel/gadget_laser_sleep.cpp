#include "types.h"

// TEnemyGadgetLaser::Sleep and Resume (the PS2 build's names): the laser
// gadget stops and restarts its updates.

class TEnemyGadgetLaser
{
public:
	void Sleep();
	void Resume();

	u8 unk000[0xF4]; // 0x00
	s32 awake;       // 0xF4
};

void TEnemyGadgetLaser::Sleep()
{
	awake = 0;
}

void TEnemyGadgetLaser::Resume()
{
	awake = 1;
}
