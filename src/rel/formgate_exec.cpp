#include "types.h"

// TObjFormGate::Exec (the PS2 build's name). Out of range or killed, it ends
// itself. While the editor changes it, it takes the placement again
// (SetParameter, inlined), places itself and gives both gate models' atomics
// its kind as user data. Otherwise it places itself and moves its collision
// to its position and angles, keeping the last position, and enters it.

#include "src/rel/formgate_class.inc"

struct RpAtomic;

RpAtomic* objRpClumpGetAtomic(RpClump* clump, RpAtomic* after);
extern "C" void RpAtomicMCCSetUsrData(RpAtomic* atomic, void* data, s32 size);

void TObjFormGate::Exec()
{
	if (CheckRangeOut() || CheckMustKill()) {
		Signal |= 1;
		return;
	}
	if (OnEdit()) {
		SetParameter();
		SetPosition();
		state = kind;
		RpAtomicMCCSetUsrData(objRpClumpGetAtomic(models[1], NULL), &state, 4);
		RpAtomicMCCSetUsrData(objRpClumpGetAtomic(models[2], NULL), &state, 4);
	} else {
		SetPosition();
		pre_pos      = C_COLLI::pos;
		C_COLLI::pos = pos;
		C_COLLI::ang = ang;
		Entry();
	}
}
