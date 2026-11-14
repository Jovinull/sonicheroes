// Refreshes the object's cached matrices when flag bit 2 of the word at +0x8 is set: with flag bit
// 1 (dirty) it multiplies the matrix stack by the local matrix at +0xC through fn_8016F5B0, copies
// the resulting top (fn_8016FB84) into +0x4C, stores its inverse at +0xC0 through fn_80195B5C
// (HYPOTHESIS: RwMatrixInvert) and clears the dirty flag; otherwise it pushes the cached matrix at
// +0x4C through fn_8016F728. Either way the stack is popped again through fn_8016F860. Names are
// UNKNOWN. Returns the object.
#include "types.h"

// A 0x40-byte matrix, copied as sixteen plain words.
struct Matrix8017377C {
	unsigned int w[16];
};

struct Object8017377C {
	unsigned char pad0[0x8];
	int flags;            // 0x8
	Matrix8017377C local; // 0xC
	Matrix8017377C world; // 0x4C
	unsigned char pad8C[0xC0 - 0x8C];
	Matrix8017377C inverse; // 0xC0
};

extern "C" {
void fn_8016F5B0(Matrix8017377C* matrix);
Matrix8017377C* fn_8016FB84(void);
Matrix8017377C* fn_80195B5C(Matrix8017377C* dst, const Matrix8017377C* src);
void fn_8016F728(Matrix8017377C* matrix);
void fn_8016F860(void);

Object8017377C* fn_8017377C(Object8017377C* object)
{
	if ((object->flags & 4) == 4) {
		if ((object->flags & 2) == 2) {
			fn_8016F5B0(&object->local);
			object->world = *fn_8016FB84();
			fn_80195B5C(&object->inverse, &object->world);
			object->flags &= ~2;
		} else {
			fn_8016F728(&object->world);
		}
		fn_8016F860();
	}
	return object;
}
}
