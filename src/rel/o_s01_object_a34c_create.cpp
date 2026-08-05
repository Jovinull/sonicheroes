#include "types.h"

// The factory of the object class whose destructor is in
// rel/o_s01_object_a34c_dtor.cpp. It takes the object off the stage heap and
// builds it against the current parent, and does nothing when the heap is
// exhausted.
//
// The claim is .text 0x0007D874 to 0x0007D8BC and nothing else. It reads no
// constant, so it owns no rodata.
//
// The allocation size confirms the layout inferred from the destructor
// independently: the original passes 60, and TObject plus the motion base plus
// the three trailing fields is exactly 0x3C.
//
// The constructor it calls, at 0x0007D1A4, is still assembly and keeps its
// placeholder name here. That name carries the module id, which is safe only
// because this source belongs to stage01D alone, like the other o_s01_* units;
// rel/o_s01_ciseki.cpp and rel/o_s01_shachicolli.cpp reference their own
// placeholders the same way.
//
// Same shape as the factory at the end of rel/o_s01_ciseki.cpp. Unlike the
// factories noted in rel/o_sample.cpp, this one keeps the allocator's result in
// place instead of copying it through a second register, so it reproduces from
// source.

typedef struct TObject TObject;

typedef struct Frame Frame;

typedef struct Motion {
	Frame* frame;  // 0x00
	void** vtable; // 0x04
} Motion;          // 0x08

typedef struct S01ObjectA34C {
	u8 base[0x28]; // 0x00
	Motion motion; // 0x28
	u32 unk30;     // 0x30
	void* mesh;    // 0x34
	void* handle;  // 0x38
} S01ObjectA34C;   // 0x3C

extern "C" void* lbl_8042C110;
extern "C" void* lbl_8042C148;

extern "C" void* fn_80018A34(void* heap, u32 size);
extern "C" void fn_3_7D1A4(S01ObjectA34C* object, void* parent);

extern "C" void s01ObjectA34CCreate(void)
{
	S01ObjectA34C* object = (S01ObjectA34C*)fn_80018A34(lbl_8042C148, sizeof(S01ObjectA34C));

	if (object != NULL) {
		fn_3_7D1A4(object, lbl_8042C110);
	}
}
