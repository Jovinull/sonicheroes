#include "types.h"

// fn_80057524 has no callers or data references and consists solely of the
// EABI register-save area emitted for a variadic function.  Like the adjacent
// leaf-function carves, this records only its proven data-free range; it does
// not assert a translation-unit boundary.
extern "C" void fn_80057524(s32 first, ...)
{
}
