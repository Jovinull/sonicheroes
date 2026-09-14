#ifndef CRI_RNARES_H
#define CRI_RNARES_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

// Field names describe the GameCube accessors and allocation loop.
typedef struct RnaResHandle {
	s32 used;
	u32 address;
	u32 size;
} RnaResHandle;

u32 fn_80224CD0(RnaResHandle* handle);
u32 fn_80224CE8(RnaResHandle* handle);
void fn_80224D00(RnaResHandle* handle);
RnaResHandle* fn_80224D14(void);
void fn_80224E1C(void);
void fn_80224F88(void);

#ifdef __cplusplus
}
#endif

#endif
