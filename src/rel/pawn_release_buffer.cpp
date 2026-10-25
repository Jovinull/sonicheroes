#include "types.h"

// pawnReleaseBuffer, which TEnemyGadgetMGun's destructor calls on its machine
// gun: the gun's object is switched off when it has one, then the gun is
// cleared and put in its second state.

class ENEMY_MGUN
{
public:
	void Off();
};

typedef struct MachineGun {
	u8 unk00[0x28];
	ENEMY_MGUN* object; // 0x28
	s32 unk2C;          // 0x2C
	u8 unk30[0x28];
	s32 state; // 0x58
} MachineGun;

extern "C" void pawnReleaseBuffer(MachineGun* gun)
{
	if (gun->object != NULL) {
		gun->object->Off();
	}
	gun->unk2C = 0;
	gun->state = 2;
}
