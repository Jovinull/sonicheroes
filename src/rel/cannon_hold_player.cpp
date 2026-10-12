#include "types.h"

#include "src/rel/cannon_class.inc"

// A TObjCannon member that holds a player at the cannon (cannonHoldPlayer here;
// the name is ours, the PS2 order does not pin it down), the out-of-line copy
// nothing calls. When the player is there, it works the barrel out at the
// cannon's own barrel angles (CalcBarrelPosition, inlined, keeping the matrix),
// turns the module's seat point by that matrix (the result is not used) and
// sets the player back at the position it was found at.

typedef struct sAngle sAngle;

extern "C" RwV3d cannonSeatPoint;

extern "C" s32 fn_8003E2E4(s32 player, s32 kind, RwV3d* position, s32 arg3);
extern "C" void objSetPlayerPosition__17OBJ_ReplacePlayerFiUcP5RwV3dP6sAngle(
    void* replace, s32 player, u8 flags, RwV3d* position, sAngle* angle);

extern "C" void cannonHoldPlayer(Cannon* object, s32 player)
{
	RwMatrixTag matrix;
	RwV3d seat;
	RwV3d found;

	if (fn_8003E2E4(player, 0, &found, 0)) {
		cannonCalcBarrelPosition(object, object->barrelPitch, object->barrelYaw, &matrix);
		fn_8019941C(&seat, &cannonSeatPoint, 1, &matrix);
		objSetPlayerPosition__17OBJ_ReplacePlayerFiUcP5RwV3dP6sAngle(
		    object->replace, player, 0, &found, NULL);
	}
}
