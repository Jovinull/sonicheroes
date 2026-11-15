// Registers a custom RtAnim interpolation scheme once (HYPOTHESIS: an RtAnimInterpolatorInfo set
// up for the game's own key frames; names follow RenderWare): type 0x15 with 0x1C-byte key frames
// and 0x40 bytes of custom data. After RtAnimRegisterInterpolationScheme (fn_8020C088) accepts it,
// keeps a copy in lbl_803E7EA0. Returns 1 when registered now, 0 otherwise.
#include "types.h"

struct RtAnimInterpolatorInfofn_8011B874 {
	s32 typeID;                    // 0x0
	s32 interpKeyFrameSize;        // 0x4
	s32 animKeyFrameSize;          // 0x8
	void* keyFrameApplyCB;         // 0xC
	void* keyFrameBlendCB;         // 0x10
	void* keyFrameInterpolateCB;   // 0x14
	void* keyFrameAddCB;           // 0x18
	void* keyFrameMulRecipCB;      // 0x1C
	void* keyFrameStreamReadCB;    // 0x20
	void* keyFrameStreamWriteCB;   // 0x24
	void* keyFrameStreamGetSizeCB; // 0x28
	s32 customDataSize;            // 0x2C
};

extern "C" {
extern s32 lbl_8042C6C0;
extern RtAnimInterpolatorInfofn_8011B874 lbl_803E7EA0;
// HYPOTHESIS: RtAnimRegisterInterpolationScheme.
s32 fn_8020C088(RtAnimInterpolatorInfofn_8011B874* info);
void fn_8011BB98(void);
void fn_8011BB6C(void);
void fn_8011BB40(void);
void fn_8011BB3C(void);
void fn_8011BB38(void);
void fn_8011BA54(void);
void fn_8011B9AC(void);
void fn_8011BB2C(void);

s32 fn_8011B874(void)
{
	RtAnimInterpolatorInfofn_8011B874 info;

	if (lbl_8042C6C0 == 0) {
		lbl_8042C6C0                 = 1;
		info.typeID                  = 0x15;
		info.interpKeyFrameSize      = 0x1C;
		info.animKeyFrameSize        = 0x1C;
		info.keyFrameApplyCB         = (void*)fn_8011BB98;
		info.keyFrameBlendCB         = (void*)fn_8011BB6C;
		info.keyFrameInterpolateCB   = (void*)fn_8011BB40;
		info.keyFrameAddCB           = (void*)fn_8011BB3C;
		info.keyFrameMulRecipCB      = (void*)fn_8011BB38;
		info.keyFrameStreamReadCB    = (void*)fn_8011BA54;
		info.keyFrameStreamWriteCB   = (void*)fn_8011B9AC;
		info.keyFrameStreamGetSizeCB = (void*)fn_8011BB2C;
		info.customDataSize          = 0x40;
		if (fn_8020C088(&info) == 0) {
			return 0;
		}
		lbl_803E7EA0 = info;
		return 1;
	}
	return 0;
}
}
