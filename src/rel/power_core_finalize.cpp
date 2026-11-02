#include "types.h"

// TEnemyPowerCore::Finalize (the PS2 build's name), the same in the bonus
// stages (31D-33D): the loaded power core models and the UV animation are
// forgotten.

struct RpClump;
struct RpUVAnimAnimation;

extern "C" RpClump* powerCoreModels[2];
extern "C" RpUVAnimAnimation* powerCoreUVAnim;

extern "C" void Finalize__15TEnemyPowerCoreFv(void)
{
	powerCoreModels[0] = NULL;
	powerCoreModels[1] = NULL;
	powerCoreUVAnim    = NULL;
}
