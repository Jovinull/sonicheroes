#include "types.h"

// Complete special-stage dash-effect engine: object lifecycle, resources,
// animation, geometry, transforms, rendering, and effect instance controls.
f32 spEffDashConstants[3] = { 0.0f, 1.0f, -1.0f };
char spEffDashClassName[] = "TSPEffDash";
char spEffDashOwnedData[0xB4];
u8 spEffDashResources[0x50];

extern "C" void fn_16_86310() { }
extern "C" void fn_16_86380() { }
extern "C" void fn_16_86484() { }
extern "C" void fn_16_86528() { }
extern "C" void fn_16_8652C() { }
extern "C" void fn_16_869DC() { }
extern "C" void fn_16_86A18() { }
extern "C" void fn_16_86A94() { }
extern "C" void fn_16_86CB4() { }
extern "C" void fn_16_86CF4() { }
extern "C" void fn_16_86D5C() { }
extern "C" void fn_16_86DF8() { }
extern "C" void fn_16_86E2C() { }
extern "C" void fn_16_86F40() { }
extern "C" void fn_16_87244() { }
extern "C" void fn_16_87270() { }
extern "C" void fn_16_87308() { }
extern "C" void fn_16_87674() { }
extern "C" void fn_16_87744() { }
extern "C" void fn_16_87794() { }
extern "C" void fn_16_87910() { }
extern "C" void fn_16_87A7C() { }
extern "C" void fn_16_87B2C() { }
extern "C" void fn_16_87C00() { }
extern "C" void fn_16_87D24() { }
extern "C" void fn_16_87E38() { }
extern "C" void fn_16_8817C() { }
extern "C" void fn_16_881BC() { }
extern "C" void fn_16_881FC() { }
extern "C" void fn_16_88230() { }
extern "C" void fn_16_882CC() { }
extern "C" void fn_16_883B4() { }
extern "C" void fn_16_884A4() { }
extern "C" void fn_16_8867C() { }
extern "C" void fn_16_88738() { }
extern "C" void fn_16_887B4() { }
extern "C" void fn_16_88878() { }
extern "C" void fn_16_889F0() { }
extern "C" void fn_16_88C1C() { }
extern "C" void fn_16_88C68() { }
extern "C" void fn_16_88CA4() { }
extern "C" void fn_16_88D38() { }
extern "C" void fn_16_88DFC() { }
extern "C" void fn_16_88E88() { }
extern "C" void fn_16_88F14() { }
extern "C" void fn_16_88FA0() { }
extern "C" void fn_16_88FD0() { }
extern "C" void fn_16_8902C() { }
extern "C" void fn_16_8909C() { }
extern "C" void fn_16_890F8() { }
extern "C" void fn_16_8910C() { }
extern "C" void fn_16_891A0() { }
extern "C" void fn_16_892E0() { }
extern "C" void fn_16_89350() { }
extern "C" void fn_16_89424() { }
extern "C" void fn_16_8944C() { }
extern "C" void fn_16_89480() { }
extern "C" void fn_16_89560() { }
extern "C" void fn_16_89600() { }
extern "C" void fn_16_89814() { }
extern "C" void fn_16_89968() { }
extern "C" void fn_16_89EB4() { }
extern "C" void fn_16_89F3C() { }
extern "C" void fn_16_89FEC() { }
extern "C" void fn_16_8A3BC() { }
extern "C" void fn_16_8A454() { }
extern "C" void fn_16_8A494() { }
extern "C" void fn_16_8A82C() { }
extern "C" void fn_16_8A87C() { }
extern "C" void fn_16_8A9C0() { }
extern "C" void fn_16_8AA4C() { }

__declspec(section ".ctors") void (*const spEffDashCtor)(void) = fn_16_8A9C0;
