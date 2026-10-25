#include "types.h"

// The stage 14 UFO's Unload hook (s14dUfoUnload here): its lights table (the three light
// records the Load makes, each holding a material and its colour) is deleted
// with its records and forgotten, and its two model records are released.

// one of the lights the Load makes
typedef struct UfoLight {
	s8 index;       // 0x00
	s32 angle;      // 0x04
	void* material; // 0x08
	u8 colour[4];   // 0x0C
} UfoLight;         // 0x10

// the lights table
struct UfoLights {
	UfoLight* lights[3]; // 0x00
	s32 unk0C;           // 0x0C

	~UfoLights()
	{
		for (u8 i = 0; i < 3; i++) {
			// the record is tested twice, as the retail does
			if (lights[i] != NULL) {
				if (lights[i] != NULL) {
					delete lights[i];
				}
			}
		}
	}
}; // 0x10

// one of the stage's larger model records (fn_9_76448 releases them,
// fn_9_765CC loads them)
typedef struct S13ModelRecord {
	u8 unk00[0x2C];
} S13ModelRecord; // 0x2C

extern "C" S13ModelRecord s14dUfoModels[2];
extern "C" UfoLights* s14dUfoLights;

extern "C" void fn_9_76448(S13ModelRecord* record);

extern "C" void s14dUfoUnload(void)
{
	S13ModelRecord* record = (S13ModelRecord*)s14dUfoModels;

	if (s14dUfoLights != NULL) {
		delete s14dUfoLights;
		s14dUfoLights = NULL;
	}
	for (u8 i = 0; i < 2; i++) {
		fn_9_76448(record);
		record++;
	}
}
