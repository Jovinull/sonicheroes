#include "types.h"

// TObjFlowerCommon::SetCollisionParameter (the PS2 build's name, by its place
// in the PS2 order): the five collision shapes are the template's scaled by
// the flower's scale, the first three raised by its height and the fifth by
// half of it (centre and second size); then the range is worked out again.

#include "src/rel/flower_common.inc"

extern "C" FlowerShape flowerCommonCclInfo[5];
extern "C" const f32 flowerCommonHalf[1];

extern "C" void CalcRange__7C_COLLIFv(void* colli);

extern "C" void SetCollisionParameter__16TObjFlowerCommonFv(FlowerCommon* flower)
{
	if (flower->info != NULL) {
		for (int i = 0; i < 5; i++) {
			flower->info[i].center.x = flower->scale * flowerCommonCclInfo[i].center.x;
			flower->info[i].center.y = flower->scale * flowerCommonCclInfo[i].center.y;
			flower->info[i].center.z = flower->scale * flowerCommonCclInfo[i].center.z;
			flower->info[i].a        = flower->scale * flowerCommonCclInfo[i].a;
			flower->info[i].b        = flower->scale * flowerCommonCclInfo[i].b;
			flower->info[i].c        = flower->scale * flowerCommonCclInfo[i].c;
		}
		flower->info[0].center.y += flower->height;
		flower->info[1].center.y += flower->height;
		flower->info[2].center.y += flower->height;
		flower->info[4].center.y += flowerCommonHalf[0] * flower->height;
		flower->info[4].b += flowerCommonHalf[0] * flower->height;
		CalcRange__7C_COLLIFv(flower->colli);
	}
}
