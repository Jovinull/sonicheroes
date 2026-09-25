#ifndef DOLPHIN_MTX_H
#define DOLPHIN_MTX_H

#include "types.h"

// The matrix library types and the paired-single matrix concatenation, as
// declared by the Dolphin SDK (after doldecomp/dolsdk2004
// include/dolphin/mtx.h). Only what this DOL links is declared.

#ifdef __cplusplus
extern "C" {
#endif

typedef f32 Mtx[3][4];
typedef f32 (*MtxPtr)[4];

void PSMTXConcat(const Mtx a, const Mtx b, Mtx ab);

#ifdef __cplusplus
}
#endif

#endif
