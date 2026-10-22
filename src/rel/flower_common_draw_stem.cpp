#include "types.h"

// TObjFlowerCommon::Draw_Stem (the PS2 build's name, by its place in the PS2
// order): rel/flower_common.inc has the body, which Disp inlines.

#include "src/rel/flower_common.inc"

extern "C" void Draw_Stem__16TObjFlowerCommonFv(FlowerCommon* flower)
{
	flowerDrawStem(flower);
}
