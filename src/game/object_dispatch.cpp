#include "types.h"

// Reconstruction fragment for fn_80012E5C, whose exact code range ends at
// 0x80012EA0. Its extab/extabindex entries prove the function range, not an
// original translation-unit boundary.
//
// This is the GameCube counterpart of the RenderWare platform pathname
// destroy callback. The PS2 counterpart retains C linkage inside a unit that
// also contains a C++-mangled private callback, so this fragment is compiled
// as C++ while preserving the callback's C ABI.

typedef struct ObjectDispatch {
	void* unk0;
	void (*destroy)(void*);
} ObjectDispatch;

extern "C" ObjectDispatch* fn_801971A4(void);

extern "C" void fn_80012E5C(void* object)
{
	if (object != NULL) {
		fn_801971A4()->destroy(object);
	}
}
