#include "types.h"

// Destructor of a memory card controller (HYPOTHESIS; the class name is UNKNOWN): unmounts the
// card when bit 0 of the state flags (0x20) is set, closes the open file when bit 1 is set,
// clears the flags and deletes the work block at 0x0 (whose inlined destructor deletes its data
// buffer), then frees the object when the delete flag is positive. Returns the object.

// dolphin/card.h does not parse as C++ (a parameter is named new), so the two calls and the file
// handle (CARDFileInfo) are declared here.
struct CardFileInfo8012823C {
	s32 chan;
	s32 fileNo;
	s32 offset;
	s32 length;
	u16 iBlock;
};

extern "C" {
s32 CARDUnmount(s32 chan);
s32 CARDClose(CardFileInfo8012823C* fileInfo);
}

struct CardWork8012823C {
	~CardWork8012823C()
	{
		if (buffer != NULL) {
			delete[] buffer;
		}
	}

	u8* buffer; // 0x0
	u8 pad4[0x24 - 0x4];
	CardFileInfo8012823C fileInfo; // 0x24
};

struct Card8012823C {
	CardWork8012823C* work; // 0x0
	s32 chan;               // 0x4
	u8 pad8[0x20 - 0x8];
	u32 flags; // 0x20
};

extern "C" Card8012823C* fn_8012823C(Card8012823C* card, s16 deleteFlag)
{
	if (card != NULL) {
		if (card->flags & 1) {
			CARDUnmount(card->chan);
		}
		if (card->flags & 2) {
			CARDClose(&card->work->fileInfo);
		}
		card->flags = 0;
		if (card->work != NULL) {
			delete card->work;
		}
		if (deleteFlag > 0) {
			operator delete(card);
		}
	}
	return card;
}
