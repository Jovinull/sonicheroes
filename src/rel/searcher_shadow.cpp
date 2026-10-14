#include "types.h"

// TObjEnemySearcher::CheckCameraFrustumTestForShadow (the PS2 build's name):
// the shadow is drawn while it is on, the searcher lives (enemy mode 0x5E is
// its end) and has ground under it, and a sphere of radius 20 around the
// shadow is in the camera.

#include "src/rel/searcher.inc"

struct RwCamera;
struct RwSphere {
	RwV3d center;
	f32 radius;
};
struct CurrentCameraView {
	RwCamera* currentCamera;
};

extern "C" CurrentCameraView* lbl_8042C9A4;
extern "C" const f32 searcherNoGround;
extern "C" const f32 searcherShadowRadius;

extern "C" s32 fn_8019CE34(RwCamera* camera, const RwSphere* sphere);

extern "C" s32 CheckCameraFrustumTestForShadow__17TObjEnemySearcherFPC5RwV3df(
    Searcher* searcher, const RwV3d* pos, f32 radius)
{
	RwSphere sphere;

	if (searcher->shadowOn == 0) {
		return 0;
	}
	if (searcher->mode == 0x5E) {
		return 0;
	}
	if (searcher->state == 2) {
		return 0;
	}
	if (searcherNoGround != searcher->shadowPos.y) {
		sphere.center = searcher->shadowPos;
		sphere.radius = searcherShadowRadius;
		return fn_8019CE34(lbl_8042C9A4->currentCamera, &sphere) != 0;
	}
	return 0;
}
