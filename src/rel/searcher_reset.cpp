#include "types.h"

// TObjEnemySearcher::ResetVariable (the PS2 build's name): the searcher's
// starting values: no clumps, gadget or icons, walking, a walking speed of 0.5,
// 180-frame waits, no ground under the shadow yet, the shadow on (fading
// 0.004 a unit of height), 3 hit points shown.

#include "src/rel/searcher.inc"

extern "C" const f32 searcherZero;
extern "C" const f32 searcherDefaultWalkSpeed;
extern "C" const f32 searcherNoGround;
extern "C" const f32 searcherDefaultShadowFade;
extern "C" const f32 searcherIconShowTime;

extern "C" void ResetVariable__17TObjEnemySearcherFv(Searcher* searcher)
{
	searcher->field258  = -1;
	searcher->bodyClump = NULL;
	searcher->spin.x = searcher->spin.y = searcher->spin.z = searcherZero;
	searcher->bobAngle                                     = 0;
	searcher->walking                                      = 1;
	searcher->spinSpeed                                    = searcherZero;
	searcher->gadget                                       = NULL;
	searcher->kind                                         = 0;
	searcher->shotSpeed = searcher->walkSpeed = searcherDefaultWalkSpeed;
	searcher->field260                        = 0;
	searcher->attackWait = searcher->readyWait = 180;
	searcher->shadowPos.x                      = searcherZero;
	searcher->shadowPos.y                      = searcherNoGround;
	searcher->shadowPos.z                      = searcherZero;
	searcher->shadowNormal.x = searcher->shadowNormal.y = searcher->shadowNormal.z = searcherZero;
	searcher->request                                                              = 0;
	searcher->clumps[0]                                                            = NULL;
	searcher->clumps[1]                                                            = NULL;
	searcher->clumps[2]                                                            = NULL;
	searcher->clumps[3]                                                            = NULL;
	searcher->leanX = searcher->leanZ = searcherZero;
	searcher->shadowFade              = searcherDefaultShadowFade;
	searcher->shadowOn                = 1;
	searcher->field2A0                = 0;
	searcher->jetFrame                = NULL;
	searcher->maxHitPoint             = searcherIconShowTime;
	searcher->shownHitPoint           = searcher->maxHitPoint;
	searcher->field340                = NULL;
	searcher->field344                = NULL;
	searcher->gauge                   = NULL;
	searcher->icon                    = NULL;
	searcher->turning                 = 1;
	searcher->field2C8                = 1;
	searcher->field30C                = 0;
	searcher->partsClump              = NULL;
	searcher->motion                  = NULL;
	searcher->lit                     = 0;
}
