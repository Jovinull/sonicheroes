#include "types.h"

// TObjHintRing::IsThereAnySameCommunicateId (the PS2 build's name, by its
// place in the PS2 order): whether the ring's group (the list its placement's
// group byte picks) holds a placement other than the ring's own.

typedef struct HintParam {
	u8 unk00[0x2A];
	u8 group;               // 0x2A
	u8 unk2B[0xD];          // 0x2B
	struct HintParam* next; // 0x38
} HintParam;

typedef struct HintLists {
	u8 unk00[0x30];
	HintParam* groups[1]; // 0x30
} HintLists;

typedef struct HintRing {
	u8 unk00[0x28];
	HintParam* param; // 0x28
} HintRing;

extern "C" HintLists* lbl_8042C298;

extern "C" u8 IsThereAnySameCommunicateId__12TObjHintRingFv(HintRing* ring)
{
	HintParam* head = lbl_8042C298->groups[ring->param->group];

	return head != ring->param || head->next != NULL;
}
