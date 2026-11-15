// Shuts the sound streams down: deletes every stream object of the two-entry tables lbl_8042B624
// and lbl_8042B634 (virtual destructor), clears the entries, resets lbl_8042B644 to -1 and finishes
// the ADX library (ADXT_Finish). See fn_800CD05C for the same deletion without the shutdown.
#include "types.h"

struct Header800CD548 {
	u8 pad00[0x18];
};

// Local view: the stream objects are TObjects (virtual destructor first in the vtable at +0x18).
class Stream800CD548 : public Header800CD548
{
public:
	virtual ~Stream800CD548();
};

extern "C" {
extern Stream800CD548* lbl_8042B624[2];
extern Stream800CD548* lbl_8042B634[2];
extern s8 lbl_8042B644;
void ADXT_Finish(void);
}

// Deletes the two stream objects of a table and clears it.
static inline void DeleteStreams(Stream800CD548** table)
{
	u8 i;

	for (i = 0; i < 2; i++) {
		if (table[i] != NULL) {
			delete table[i];
			table[i] = NULL;
		}
	}
}

extern "C" void fn_800CD548(void)
{
	DeleteStreams(lbl_8042B624);
	DeleteStreams(lbl_8042B634);
	lbl_8042B644 = -1;
	ADXT_Finish();
}
