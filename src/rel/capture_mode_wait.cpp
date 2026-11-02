#include "types.h"

// One of the capture enemy's mode hooks (captureModeWait here), the same in
// the seven stage modules that carry the capture: phase 0 hides the search
// icon and starts motion 0; the other phases do nothing.

class TEnemyIconMan
{
public:
	void Off();
};

typedef struct Capture {
	u8 unk000[0xD4];
	s32 motion; // 0x0D4
	u8 unk0D8[0x21C];
	TEnemyIconMan* searchIcon; // 0x2F4
} Capture;

extern "C" void captureModeWait(Capture* object, s32 phase)
{
	switch (phase) {
		case 0:
			if (object->searchIcon != NULL) {
				object->searchIcon->Off();
			}
			object->motion = 0;
			break;
		case 1:
		case 2:
		case 3:
			break;
	}
}
