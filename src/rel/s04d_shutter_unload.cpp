#include "types.h"

// The shutter's Unload hook (s04dShutterUnload here): each of its models is
// released, with fn_800B8ADC called on it first when bit 0 of its flags is set.

// one of the family's models: its flags and the model once loaded
typedef struct S04dShutterModel {
	u8 flags; // 0x00
	u8 unk01[0x7];
	void* model; // 0x08
	u8 unk0C[0x4];
} S04dShutterModel; // 0x10

extern "C" u8 s04dShutterModels[];

extern "C" void fn_800B8ADC(void* clump);
extern "C" void fn_80150958(void* clump);

extern "C" void s04dShutterUnload(void)
{
	S04dShutterModel* model = (S04dShutterModel*)s04dShutterModels;

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
