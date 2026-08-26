#include "types.h"

// Complete stage40 formation-gate subordinate object and registration TU.
f32 formGateSubConstants[46];
char formGateSubData[0x130];
u8 formGateSubRegistration[0x30];
extern "C" void fn_16_8AA54() { }
extern "C" void fn_16_8AE38() { }
extern "C" void fn_16_8AE3C() { }
extern "C" void fn_16_8B080() { }
extern "C" void fn_16_8B2C4() { }
extern "C" void fn_16_8B588() { }
extern "C" void fn_16_8B630() { }
extern "C" void fn_16_8B820() { }
extern "C" void fn_16_8B8B0() { }
extern "C" void fn_16_8B8D8() { }
extern "C" void fn_16_8B954() { }
extern "C" void fn_16_8B9A4() { }
extern "C" void fn_16_8BA30() { }
__declspec(section ".ctors") void (*const formGateSubCtor)(void) = fn_16_8B9A4;
