// Registers a custom RtAnim interpolation scheme once (HYPOTHESIS: an RtAnimInterpolatorInfo set
// up for the game's own key frames; names follow RenderWare): type 0x14 with 0x1C-byte key frames
// and 0x40 bytes of custom data. After RtAnimRegisterInterpolationScheme (fn_8020C088) accepts it,
// keeps a copy in lbl_803E7ED0. Returns 1 when registered now, 0 otherwise.
#include "types.h"

struct RtAnimInterpolatorInfofn_8011BC20 {
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
extern s32 lbl_8042C6C8;
extern RtAnimInterpolatorInfofn_8011BC20 lbl_803E7ED0;
// HYPOTHESIS: RtAnimRegisterInterpolationScheme.
s32 fn_8020C088(RtAnimInterpolatorInfofn_8011BC20* info);
void fn_8011C01C(void);
void fn_8011BF98(void);
void fn_8011BF00(void);
void fn_8011BEFC(void);
void fn_8011BEF8(void);
void fn_8011BE00(void);
void fn_8011BD58(void);
void fn_8011BEEC(void);

s32 fn_8011BC20(void)
{
	RtAnimInterpolatorInfofn_8011BC20 info;

	if (lbl_8042C6C8 == 0) {
		lbl_8042C6C8                 = 1;
		info.typeID                  = 0x14;
		info.interpKeyFrameSize      = 0x1C;
		info.animKeyFrameSize        = 0x1C;
		info.keyFrameApplyCB         = (void*)fn_8011C01C;
		info.keyFrameBlendCB         = (void*)fn_8011BF98;
		info.keyFrameInterpolateCB   = (void*)fn_8011BF00;
		info.keyFrameAddCB           = (void*)fn_8011BEFC;
		info.keyFrameMulRecipCB      = (void*)fn_8011BEF8;
		info.keyFrameStreamReadCB    = (void*)fn_8011BE00;
		info.keyFrameStreamWriteCB   = (void*)fn_8011BD58;
		info.keyFrameStreamGetSizeCB = (void*)fn_8011BEEC;
		info.customDataSize          = 0x40;
		if (fn_8020C088(&info) == 0) {
			return 0;
		}
		lbl_803E7ED0 = info;
		return 1;
	}
	return 0;
}
}
