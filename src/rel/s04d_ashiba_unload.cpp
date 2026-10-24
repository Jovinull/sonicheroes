#include "types.h"

// The scaffold's Unload hook (s04dAshibaUnload here): each of its models is
// released, with fn_800B8ADC called on it first when bit 0 of its flags is set.

// one of the family's models: its flags and the model once loaded
typedef struct S04dAshibaModel {
	u8 flags; // 0x00
	u8 unk01[0x7];
	void* model; // 0x08
	u8 unk0C[0x4];
} S04dAshibaModel; // 0x10

extern "C" u8 s04dAshibaModels[];

extern "C" void fn_800B8ADC(void* clump);
extern "C" void fn_80150958(void* clump);

extern "C" void s04dAshibaUnload(void)
{
	S04dAshibaModel* model = (S04dAshibaModel*)s04dAshibaModels;

	for (u8 i = 0; i < 4; i++) {
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
