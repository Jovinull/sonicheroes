#ifndef DOLPHIN_TYPES_H
#define DOLPHIN_TYPES_H

// Shim: the GX library headers were ported from the Dolphin SDK, where they
// include <dolphin/types.h>. This tree owns its scalar types in the top-level
// types.h; reroute to it and add the two SDK macros the GX headers rely on.

#include <types.h>

#if defined(__MWERKS__)
#define AT_ADDRESS(addr) : (addr)
#else
#define AT_ADDRESS(addr)
#endif

#define ATTRIBUTE_ALIGN(num) __attribute__((aligned(num)))

#endif
