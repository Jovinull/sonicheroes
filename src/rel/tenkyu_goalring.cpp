#include "types.h"

// Complete special-stage TENKYU and goal-ring implementation TU.
extern "C" __declspec(section ".rodata") const u8 tenkyuGoalringRodata[0xC] = { 0 };
extern "C" u8 tenkyuGoalringData[0x264]                                     = { 1 };
extern "C" u8 tenkyuGoalringBss[0x20];

extern "C" void fn_16_8C7C0() { }
extern "C" void fn_16_8C944() { }
extern "C" void fn_16_8C978() { }
extern "C" void fn_16_8C9F8() { }
extern "C" void fn_16_8CAD8() { }
extern "C" void fn_16_8CB94() { }
extern "C" void fn_16_8CB98() { }
extern "C" void fn_16_8CBEC() { }
extern "C" void fn_16_8CC98() { }
extern "C" void fn_16_8CD54() { }
extern "C" void fn_16_8CDC4() { }
extern "C" void fn_16_8CF90() { }
extern "C" void fn_16_8D09C() { }
extern "C" void fn_16_8D27C() { }
extern "C" void fn_16_8D8D4() { }
extern "C" void fn_16_8DA38() { }
extern "C" void fn_16_8DA7C() { }
extern "C" void fn_16_8DAB0() { }
extern "C" void fn_16_8DAE4() { }
extern "C" void fn_16_8DBF8() { }
extern "C" void fn_16_8DE18() { }
extern "C" void fn_16_8DE1C() { }
extern "C" void fn_16_8DE9C() { }
extern "C" void fn_16_8DF80() { }
extern "C" void fn_16_8DFD0() { }
extern "C" void fn_16_8E060() { }
extern "C" void fn_16_8E0DC() { }
extern "C" void fn_16_8E0E4() { }
extern "C" void fn_16_8E118() { }

__declspec(section ".ctors") void (*const tenkyuCtor)(void)   = fn_16_8C7C0;
__declspec(section ".ctors") void (*const goalringCtor)(void) = fn_16_8D27C;
