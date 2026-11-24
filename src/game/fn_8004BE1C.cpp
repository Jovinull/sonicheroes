// Static initializer of the global stage object lbl_802B039C (HYPOTHESIS; its class is UNKNOWN,
// its destructor is fn_8004BDC0): publishes it through lbl_8042C1D0, clears its three blocks at
// 0x7250, 0x72B4 and 0xB0C and a few words, sets 0x8C20 and both words of lbl_8042AF50 to 1, and
// registers it so its destructor runs at shutdown (chain node lbl_802B0390). The inlined
// constructor and the hand-written .ctors entry follow game/fn_80052150.cpp.
#include "types.h"
#include "MSL_C/string.h"

struct Stage8004BE1C {
	u8 pad0[0xB08];
	s32 fB08;         // 0x0B08
	u8 fB0C[0x673C];  // 0x0B0C
	s32 f7248;        // 0x7248
	s32 f724C;        // 0x724C
	u8 f7250[0x64];   // 0x7250
	u8 f72B4[0x1964]; // 0x72B4
	s32 f8C18;        // 0x8C18
	u8 pad8C1C[0x8C20 - 0x8C1C];
	s32 f8C20; // 0x8C20
};

struct Flags8004BE1C {
	s32 a;
	s32 b;
};

extern "C" {
void __register_global_object(void* object, void* destructor, void* node);
void* fn_8004BDC0(void* p, s16 flags);

extern Stage8004BE1C lbl_802B039C;
extern u8 lbl_802B0390[12];
extern Stage8004BE1C* lbl_8042C1D0;
extern Flags8004BE1C lbl_8042AF50;

void fn_8004BE1C(void)
{
	lbl_8042C1D0 = &lbl_802B039C;
	memset(lbl_802B039C.f7250, 0, sizeof(lbl_802B039C.f7250));
	memset(lbl_802B039C.f72B4, 0, sizeof(lbl_802B039C.f72B4));
	memset(lbl_802B039C.fB0C, 0, sizeof(lbl_802B039C.fB0C));
	lbl_802B039C.f8C18 = 0;
	lbl_802B039C.fB08  = 0;
	lbl_802B039C.f7248 = 0;
	lbl_802B039C.f724C = 0;
	lbl_802B039C.f8C20 = 1;
	lbl_8042AF50.a     = 1;
	lbl_8042AF50.b     = 1;
	__register_global_object(&lbl_802B039C, (void*)fn_8004BDC0, lbl_802B0390);
}
}

__declspec(section ".ctors") void (*const fn8004BE1CCtorEntry)(void) = fn_8004BE1C;
