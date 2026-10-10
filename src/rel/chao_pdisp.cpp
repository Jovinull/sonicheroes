// TObjChao::PDisp: the chao's clump is drawn unless the stage is being edited
// (the state byte at 0x20). The class is in chao_class.inc.

#include "src/rel/chao_class.inc"

struct ChaoGameState {
	u8 pad00[0x20];
	s8 editMode; // 0x20
};

extern "C" ChaoGameState* lbl_8042C180;
extern "C" void fn_8014FF2C(RpClump* clump);

void TObjChao::PDisp()
{
	if (!lbl_8042C180->editMode && clump != NULL) {
		fn_8014FF2C(clump);
	}
}
