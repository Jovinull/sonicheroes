// TObjEnemy::Disp (symbol name from the retail map): draws the opaque part of an awake enemy whose
// position (+0x140, with the radius at +0x220) passes the camera frustum test.
#include "game/enemy/e_obj_enemy.h"

void TObjEnemy::Disp()
{
	if (!IsSleep()) {
		RwV3d pos = position;

		if (CheckCameraFrustumTest(&pos, radius)) {
			DispOpaq();
		}
	}
}
