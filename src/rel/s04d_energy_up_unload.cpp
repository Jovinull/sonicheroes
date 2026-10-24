#include "types.h"

// The energy booster's Unload hook (s04dEnergyUpUnload here): each of its
// models is released, with fn_800B8ADC called on it first when bit 0 of its
// flags is set.

// one of the family's models: its flags and the model once loaded
typedef struct S04dEnergyUpModel {
	u8 unk00[0x1];
	u8 flags; // 0x01
	u8 unk02[0x6];
	void* model; // 0x08
	u8 unk0C[0xC];
} S04dEnergyUpModel; // 0x18

extern "C" u8 s04dEnergyUpModels[];

extern "C" void fn_800B8ADC(void* clump);
extern "C" void fn_80150958(void* clump);

extern "C" void s04dEnergyUpUnload(void)
{
	S04dEnergyUpModel* model = (S04dEnergyUpModel*)s04dEnergyUpModels;

	for (u8 i = 0; i < 2; i++) {
		if (model->model != NULL) {
			if (model->flags & 1) {
				fn_800B8ADC(model->model);
			}
			fn_80150958(model->model);
			model->model = NULL;
		}
		model++;
	}
}
