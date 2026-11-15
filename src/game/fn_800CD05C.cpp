// Deletes every sound stream object of the two-entry tables lbl_8042B624 and lbl_8042B634 (virtual
// destructor) and clears the entries.
#include "types.h"

struct Header800CD05C {
	u8 pad00[0x18];
};

// Local view: the stream objects are TObjects (virtual destructor first in the vtable at +0x18).
class Stream800CD05C : public Header800CD05C
{
public:
	virtual ~Stream800CD05C();
};

extern "C" {
extern Stream800CD05C* lbl_8042B624[2];
extern Stream800CD05C* lbl_8042B634[2];
}

extern "C" void fn_800CD05C(void)
{
	u8 i;
	u8 j;

	for (i = 0; i < 2; i++) {
		if (lbl_8042B624[i] != NULL) {
			delete lbl_8042B624[i];
			lbl_8042B624[i] = NULL;
		}
	}
	for (j = 0; j < 2; j++) {
		if (lbl_8042B634[j] != NULL) {
			delete lbl_8042B634[j];
			lbl_8042B634[j] = NULL;
		}
	}
}
