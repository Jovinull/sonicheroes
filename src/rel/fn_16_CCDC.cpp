#include "types.h"
typedef struct RpClump RpClump;
typedef struct E {
	u8 unk00[0x30];
	RpClump* a;
	RpClump* b;
} E;
extern "C" void fn_80150958(RpClump* clump);
extern "C" void __dl__FPv(void* memory);
extern "C" E* fn_16_CCDC(E* e, s16 flags)
{
	if (e != NULL) {
		if (e->a != NULL) {
			fn_80150958(e->a);
			e->a = NULL;
		}
		if (e->b != NULL) {
			fn_80150958(e->b);
			e->b = NULL;
		}
		if (flags > 0) {
			__dl__FPv(e);
		}
	}
	return e;
}
