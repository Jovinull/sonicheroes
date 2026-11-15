// Allocates and constructs a 0x30-byte object (HYPOTHESIS: a factory for the class whose
// constructor is fn_801267F4; the class and its nine parameters are UNKNOWN). Returns the object,
// or null when the allocation fails. Built with the game-unit flags (-opt noschedule,nopeephole).
// NonMatching: retail is a C++ new-expression, whose temporary takes the last saved register (r22)
// after the parameters; this source's local takes r31 first (21 register-only words). A real
// new-expression needs the class, whose constructor symbol is only known as fn_801267F4.
#include "types.h"

void* operator new(unsigned long size);

extern "C" {
void* fn_801267F4(void* self, s32 a, s32 b, s32 c, s32 d, s32 e, s32 f, s32 g, s32 h, s32 i);

void* fn_8012695C(s32 a, s32 b, s32 c, s32 d, s32 e, s32 f, s32 g, s32 h, s32 i)
{
	void* object = operator new(0x30);
	if (object != 0) {
		fn_801267F4(object, a, b, c, d, e, f, g, h, i);
	}
	return object;
}
}
