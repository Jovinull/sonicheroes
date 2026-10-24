#include "types.h"

// The energy cylinder's Unload hook (s04dECylinderUnload here): each of its
// models is released, with fn_800B8ADC called on it first when bit 0 of its
// flags is set.

// one of the family's models: its flags and the model once loaded
typedef struct S04dECylinderModel {
	u8 flags; // 0x00
	u8 unk01[0x7];
	void* model; // 0x08
	u8 unk0C[0x4];
} S04dECylinderModel; // 0x10

extern "C" u8 s04dECylinderModels[];

extern "C" void fn_800B8ADC(void* clump);
extern "C" void fn_80150958(void* clump);

extern "C" void s04dECylinderUnload(void)
{
	S04dECylinderModel* model = (S04dECylinderModel*)s04dECylinderModels;

	for (u8 i = 0; i < 12; i++) {
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
