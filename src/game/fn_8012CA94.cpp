// Releases the models of a menu scene (HYPOTHESIS; names inferred): for each of its 0x68-byte model
// entries, destroys the object at 0xC (fn_80203998), clears the second word of every 0xC-byte part
// record and resets the entry's time to lbl_8042EDC8; then destroys the scene's texture dictionary
// at 0xC (fn_801A46D0). Built with the game-unit flags (-opt noschedule,nopeephole).
// NonMatching: retail derives the part offset and the stored zero from the part counter's register
// (mr from r5); this source gives the offset its own load and swaps the two registers (6 words).
// Tried for, while and pointer-offset forms of the part loop and several declaration orders.
#include "types.h"

struct Part8012CA94 {
	s32 value0;   // 0x0
	void* object; // 0x4
	s32 value8;   // 0x8
};

struct Model8012CA94 {
	u8 pad0[0xC];
	void* object;        // 0xC
	f32 time;            // 0x10
	s32 numParts;        // 0x14
	Part8012CA94* parts; // 0x18
	u8 pad1C[0x68 - 0x1C];
};

struct Scene8012CA94 {
	u8 pad0[0x4];
	Model8012CA94* models;              // 0x4
	s32 numModels;                      // 0x8
	struct RwTexDictionary* dictionary; // 0xC
};

extern "C" {
extern const f32 lbl_8042EDC8;
// HYPOTHESIS: the object destructor of the 0x802038AC module and RwTexDictionaryDestroy.
void fn_80203998(void* object);
void fn_801A46D0(struct RwTexDictionary* dictionary);

void fn_8012CA94(Scene8012CA94* scene)
{
	if (scene != 0) {
		Model8012CA94* model;
		s32 count;

		count = scene->numModels;
		model = scene->models;
		while (count != 0) {
			s32 i;
			if (model->object != 0) {
				fn_80203998(model->object);
				model->object = 0;
			}
			for (i = 0; i != model->numParts; i++) {
				model->parts[i].object = 0;
			}
			model->object = 0;
			model->time   = lbl_8042EDC8;
			count--;
			model++;
		}
		if (scene->dictionary != 0) {
			fn_801A46D0(scene->dictionary);
			scene->dictionary = 0;
		}
	}
}
}
