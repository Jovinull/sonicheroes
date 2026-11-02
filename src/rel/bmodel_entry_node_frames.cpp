#include "types.h"

// BMODEL::EntryNodeFrames (the PS2 build's name, from STAGE.BIN), the same in
// the four stage modules that carry BMODEL: each frame slot takes the frame
// of the hierarchy node with the matching bone ID, when there is one.

struct RwFrame;

struct RpHAnimNodeInfo {
	u8 unk00[0xC];
	RwFrame* frame; // 0x0C
}; // 0x10

struct RpHAnimHierarchy {
	u8 unk00[0x10];
	RpHAnimNodeInfo* nodes; // 0x10
};

class BMODEL
{
public:
	static void EntryNodeFrames(RpHAnimHierarchy* hierarchy, RwFrame** frames, s32* ids, s32 count);
};

s32 objRpHAnimHierarchyFindFrameFromBoneID(RpHAnimHierarchy* hierarchy, s32 bone);

void BMODEL::EntryNodeFrames(RpHAnimHierarchy* hierarchy, RwFrame** frames, s32* ids, s32 count)
{
	RwFrame** frame;
	RwFrame** end;
	s32* id = ids;

	frame = frames;
	end   = frames + count;
	for (; frame < end; frame++, id++) {
		s32 index = objRpHAnimHierarchyFindFrameFromBoneID(hierarchy, *id);

		if (index >= 0) {
			*frame = hierarchy->nodes[index].frame;
		}
	}
}
