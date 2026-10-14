#include "types.h"

// TObjEnemySearcher::DispTrans and DispOpaq (the PS2 build's names): the
// searcher draws nothing transparent; opaque, it sets the scene's light count,
// prepares its two texture sets for its kind (unless it keeps the plain
// textures) and draws its clumps.

#include "src/rel/searcher.inc"

namespace nRender
{
void SetLightNum(u32 count);
}

class TEnemyMatTexture
{
public:
	void PreDisp(s32 kind);
};

extern "C" TEnemyMatTexture searcherObjectGlobalA;
extern "C" TEnemyMatTexture searcherObjectGlobalB;

extern "C" void fn_8014FF2C(RpClump* clump);

extern "C" void DispTrans__17TObjEnemySearcherFv(Searcher* searcher) { }

extern "C" void DispOpaq__17TObjEnemySearcherFv(Searcher* searcher)
{
	nRender::SetLightNum(searcherEnemy(searcher)->GetCurrentLightNum());
	if (searcher->plainTexture == 0) {
		searcherObjectGlobalA.PreDisp(searcher->kind);
		searcherObjectGlobalB.PreDisp(searcher->kind);
	}
	fn_8014FF2C(searcher->clump);
	if (searcher->partsClump != NULL) {
		fn_8014FF2C(searcher->partsClump);
	}
}
