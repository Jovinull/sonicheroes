// TObjEnemy::TDisp (symbol name from the retail map): for an awake enemy, draws the translucent
// part when its position passes the camera frustum test, and the shadow (with fog off, inside a
// saved render state) when it passes the shadow frustum test.
#include "game/enemy/e_obj_enemy.h"
#include "game/enemy/e_utility_render.h"

void TObjEnemy::TDisp()
{
	if (!IsSleep()) {
		RwV3d pos = position;

		if (CheckCameraFrustumTest(&pos, radius)) {
			DispTrans();
		}
		if (CheckCameraFrustumTestForShadow(&pos, radius)) {
			nRender::SaveRenderState();
			nRender::FogDisable();
			DispShadow();
			nRender::LoadRenderState();
		}
	}
}
