#include "types.h"

// The flower (TObjFlower) EditOnChange (flowerEditOnChange here): its kind is cleared,
// a size at or under the small limit gets its default and one at or under the
// minimum is raised to it, and the record's draw distance is kept at 0x80 at
// least.

typedef struct FlowerParams {
	u8 unk00[0x4];
	f32 size; // 0x04
	s32 kind; // 0x08
} FlowerParams;

typedef struct FlowerEdit {
	u8 unk00[0x2A];
	u8 distance; // 0x2A
	u8 unk2B;
	FlowerParams* params; // 0x2C
} FlowerEdit;

extern "C" const f32 flowerEditSmall[1];
extern "C" const f32 flowerEditDefault[1];
extern "C" const f32 flowerEditMin[1];

extern "C" void flowerEditOnChange(void* object, FlowerEdit* edit)
{
	FlowerParams* params = edit->params;
	const f32* min;

	if (params->kind >= 1) {
		params->kind = 0;
	}
	if (params->kind <= 0) {
		params->kind = 0;
	}
	if (params->size <= *flowerEditSmall) {
		params->size = *flowerEditDefault;
	} else if (params->size <= *(min = flowerEditMin)) {
		params->size = *min;
	}
	if (edit->distance < 0x80) {
		edit->distance = 0x80;
	}
}
