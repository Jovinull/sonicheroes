#include "types.h"

// Complete special-stage Chao Beans object, helpers, lifecycle, and registration.
f32 chaoBeansConstants[12];
char chaoBeansData[0x9C];
u8 chaoBeansRegistration[0x30];

extern "C" void fn_16_8BA38() { }
extern "C" void fn_16_8BAC0() { }
extern "C" void fn_16_8BADC() { }
extern "C" void fn_16_8BB98() { }
extern "C" void fn_16_8BC9C() { }
extern "C" void fn_16_8BE40() { }
extern "C" void fn_16_8BF28() { }
extern "C" void fn_16_8BF8C() { }
extern "C" void fn_16_8BFE0() { }
extern "C" void fn_16_8C03C() { }
extern "C" void fn_16_8C04C() { }
extern "C" void fn_16_8C05C() { }
extern "C" void fn_16_8C0A0() { }
extern "C" void fn_16_8C138() { }
extern "C" void fn_16_8C1C8() { }
extern "C" void fn_16_8C20C() { }
extern "C" void fn_16_8C3A0() { }
extern "C" void fn_16_8C448() { }
extern "C" void fn_16_8C534() { }
extern "C" void fn_16_8C538() { }
extern "C" void fn_16_8C670() { }
extern "C" void fn_16_8C6C0() { }
extern "C" void fn_16_8C6E8() { }
extern "C" void fn_16_8C73C() { }

__declspec(section ".ctors") void (*const chaoBeansCtor)(void) = fn_16_8C73C;
