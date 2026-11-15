// Writes a frame's HAnim plugin data to a stream (HYPOTHESIS: the HAnim frame stream-write
// callback): the version 0x100, the frame's node id, then for a hierarchy that is not a
// sub-hierarchy its node count, flags, interpolator key-frame size and every node's id, index and
// flags, or a zero node count otherwise. Returns the stream, or null when a write fails.
// NonMatching: instruction stream matches; retail gives the hierarchy the frame's register (r29)
// and the node counter the frame data's (r31), where this source swaps them (11 words).
// Declaration orders and a macro for the frame data do not reproduce it.
#include "game/rw_engine.h"

#define RP_HANIM_STREAM_VERSION 0x100
#define RP_HANIM_SUB_HIERARCHY  0x1

struct Interpolator8013E87C {
	u8 pad0[0x20];
	s32 maxKeyFrameSize; // 0x20
};

struct FrameData8013E87C {
	s32 id;                      // 0x0
	RpHAnimHierarchy* hierarchy; // 0x4
};

extern "C" {
// HAnim plugin globals: the frame data offset is the first word (HYPOTHESIS).
extern s32 lbl_8042C828;
// HYPOTHESIS: RwStreamWriteInt32.
void* fn_80193474(void* stream, const void* ints, u32 numBytes);

void* fn_8013E87C(void* stream, s32 length, RwFrame* frame)
{
	s32 version = RP_HANIM_STREAM_VERSION;
	FrameData8013E87C* data;
	RpHAnimHierarchy* hierarchy;

	if (fn_80193474(stream, &version, sizeof(version)) == 0) {
		return 0;
	}
	data = (FrameData8013E87C*)((u8*)frame + lbl_8042C828);
	if (fn_80193474(stream, &data->id, sizeof(data->id)) == 0) {
		return 0;
	}
	hierarchy = data->hierarchy;
	if (hierarchy != 0 && !(hierarchy->flags & RP_HANIM_SUB_HIERARCHY)) {
		RpHAnimNodeInfo* node;
		s32 i;

		if (fn_80193474(stream, &hierarchy->numNodes, sizeof(s32)) == 0) {
			return 0;
		}
		if (fn_80193474(stream, &hierarchy->flags, sizeof(s32)) == 0) {
			return 0;
		}
		if (fn_80193474(stream, &((Interpolator8013E87C*)hierarchy->currentAnim)->maxKeyFrameSize,
		        sizeof(s32))
		    == 0) {
			return 0;
		}
		node = hierarchy->pNodeInfo;
		for (i = 0; i < hierarchy->numNodes; i++) {
			if (fn_80193474(stream, &node->nodeID, sizeof(s32)) == 0) {
				return 0;
			}
			if (fn_80193474(stream, &node->nodeIndex, sizeof(s32)) == 0) {
				return 0;
			}
			if (fn_80193474(stream, &node->flags, sizeof(s32)) == 0) {
				return 0;
			}
			node++;
		}
	} else {
		s32 numNodes = 0;
		if (fn_80193474(stream, &numNodes, sizeof(numNodes)) == 0) {
			return 0;
		}
	}
	return stream;
}
}
