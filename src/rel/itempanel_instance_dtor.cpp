#include "types.h"

// ItempanelInstance's destructor (the PS2 build's name), the same in the
// thirteen stage modules that share the engine core: the panel takes itself out
// of its control's chain (TObjItempanelControl::UnlinkInstance on PS2, written
// out here; the chain's first panel keeps the last one as its own last),
// counting itself out when it is a counted one.

class ItempanelInstance;

class TObjItempanelControl
{
public:
	u8 unk00[0x38];
	s32 instanceNum;          // 0x38
	ItempanelInstance* first; // 0x3C
};

class ItempanelInstance
{
public:
	~ItempanelInstance();

	u8 unk00[0x20];
	TObjItempanelControl* control; // 0x20
	ItempanelInstance* last;       // 0x24
	ItempanelInstance* next;       // 0x28
	s32 counted;                   // 0x2C
};

ItempanelInstance::~ItempanelInstance()
{
	TObjItempanelControl* owner = control;

	if (counted == 1) {
		owner->instanceNum--;
	}
	if (owner->first == this) {
		owner->first = next;
		if (owner->first != NULL) {
			owner->first->last = last;
		}
		last = next = NULL;
		return;
	}
	if (owner->first->last == this) {
		ItempanelInstance* prev = last;

		prev->next         = NULL;
		owner->first->last = prev;
		last = next = NULL;
		return;
	}
	ItempanelInstance* prev  = last;
	ItempanelInstance* after = next;

	prev->next  = after;
	after->last = prev;
	last = next = NULL;
}
