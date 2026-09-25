#ifndef CRI_SFXSET_H
#define CRI_SFXSET_H

#include "cri/sfxahn.h"

/* Reconstructed GameCube views and descriptive names, not recovered historical
 * type/member identities. Unknown field meanings remain unspecified. */
typedef struct SfxHandle {
	u32 unk_0x00;
	u32 unk_0x04;
	u32 unk_0x08;
	u32 unk_0x0C;
	s32 tag_valid;
	s32 tag_x;
	s32 tag_y;
	u32 unk_0x1C;
	void* convert_handle;
	u32 out_zoffset;
	u32 out_zscale;
	void* frame_handle;
	u32 output_mode;
	u32 max_alpha;
	void* tables[10];
	u32 unk_0x60;
	u32 unk_0x64;
} SfxHandle;

/* Only the frame prefix needed by this interface is described here. */
typedef struct SfxFrameInfo {
	u8 unk_0x00[0x4C];
	s32 index;
} SfxFrameInfo;

typedef struct SfxPlane {
	u8* address;
	s32 stride;
	s32 remaining;
} SfxPlane;

typedef struct SfxPlanes {
	u32 unk_0x00;
	SfxPlane y;
	u32 unk_0x10;
	SfxPlane u;
	u32 unk_0x20;
	SfxPlane v;
} SfxPlanes;

#ifdef __cplusplus
extern "C" {
#endif

void fn_17_8B98(SfxPlanes*, s32);
void fn_17_8BC4(SfxPlane*, s32);
void fn_17_8BE8(SfxPlanes*, s32);
u32 fn_17_8C68(SfxHandle*);
void fn_17_8C70(SfxHandle*, u32);
u32 fn_17_8C78(SfxHandle*);
void fn_17_8C80(SfxHandle*, u32);
u32 fn_17_8C88(SfxHandle*);
void fn_17_8C90(SfxHandle*, u32);
void fn_17_8C98(SfxHandle*, s32*, s32*, s32*);
void fn_17_8CBC(SfxHandle*, s32, s32, s32);
void fn_17_8CE0(SfxHandle*, SfxFrameInfo*, s32*, s32*);
void fn_17_8D08(SfxHandle*, float*, float*);
void fn_17_8D2C(SfxHandle*, float, float);
u32 fn_17_8D50(SfxHandle*);
void fn_17_8D58(SfxHandle*, u32);
u32 fn_17_8D60(SfxHandle*);
void fn_17_8D68(SfxHandle*, u32);
void fn_17_8D70(SfxHandle*, s32*, s32*);
void fn_17_8DA0(SfxHandle*, s32, s32);
u32 fn_17_8E3C(SfxHandle*);
void fn_17_8E44(SfxHandle*, u32);
void* fn_17_8E4C(SfxHandle*, s32);
void fn_17_8E5C(SfxHandle*, s32, void*);
void fn_17_8E74(SfxHandle*, u32*, u32*);
void fn_17_8E88(SfxHandle*, u32, u32);
u32 fn_17_8E94(SfxHandle*);
void fn_17_8E9C(SfxHandle*, u32);
void fn_17_8EA4(void);

/* Imported vendor entry points, including all forwarded argument registers. */
void fn_17_10664(void*, s32, s32*, s32*);
void fn_17_EB0C(void*, float*, float*);
void fn_17_EB50(void*, float, float);
void fn_17_108A8(void*, s32, s32);
void* fn_80221610(void*, const char*, const char*, void*);

#ifdef __cplusplus
}
#endif

#endif
