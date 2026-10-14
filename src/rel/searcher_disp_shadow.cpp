#include "types.h"

// TObjEnemySearcher::DispShadow (the PS2 build's name): draws the shadow
// (scale 12 x 1 x 12) on the ground under the searcher, fading with its height
// (1 - fade * height, held between 0.2 and 1 by the PS2 build's
// nVariable::Limit). Built without fused multiply-add, as the retail is.

#include "src/rel/searcher.inc"

namespace nVariable
{

template <class T> inline const T& Limit(const T& value, const T& min, const T& max)
{
	if (value < min) {
		return min;
	}
	if (value > max) {
		return max;
	}
	return value;
}

} // namespace nVariable

extern "C" const RwV3d searcherShadowScale;
extern "C" const f32 searcherOne;
extern "C" const f32 searcherShadowAlphaMin;
extern "C" const f32 searcherShadowAlphaMax;

extern "C" void fn_800B7864(s32 kind);
extern "C" void fn_800B719C(RwV3d* pos, RwV3d* normal, RwV3d* scale, f32 alpha);
extern "C" void fn_800B7820(void);

extern "C" void DispShadow__17TObjEnemySearcherFv(Searcher* searcher)
{
	f32 alpha;

	fn_800B7864(3);
	RwV3d scale = searcherShadowScale;

	alpha = searcherOne - searcher->shadowFade * (searcher->pos.y - searcher->shadowPos.y);
	alpha = nVariable::Limit(alpha, searcherShadowAlphaMin, searcherShadowAlphaMax);
	fn_800B719C(&searcher->shadowPos, &searcher->shadowNormal, &scale, alpha);
	fn_800B7820();
}
