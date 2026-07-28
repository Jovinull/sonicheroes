#include "types.h"

// The game's own view of the disc: it folds the SDK's drive and command block
// status codes into one small set the rest of the game switches on. A
// one-function translation unit from fn_80013044 through 0x80013128.
//
// Its boundary is exact: the function has its own extab entry at 0x80005788
// and extabindex entry at 0x8000BD4C. It also owns the two jump tables in
// .data at 0x802406F0 and 0x80240724, which nothing outside this range
// references, so the private data test agrees with the extab evidence.
//
// Two things here are load bearing for the match and must not be tidied:
//
//   The case to return value mapping is not the identity it looks like it
//   ought to be. Both switches remap the SDK codes, and the values below are
//   the ones that reproduce the jump tables.
//
//   The case bodies are written in the order 0, 5, 4, 6, -1, 11 rather than
//   sorted. CodeWarrior preserves source order when emitting the labels, and
//   sorting them changes the tables.
//
// The returned codes are the game's, and nothing in the binary names them, so
// they are left as bare numbers rather than given invented names.

extern "C" {

extern s32 DVDGetDriveStatus(void);
extern void* lbl_8042C0D4;
extern s32 DVDGetCommandBlockStatus(void* block);

s32 fn_80013044(void)
{
	switch (DVDGetDriveStatus()) {
		case 0:
			return 7;
		case 5:
			return 0;
		case 4:
			return 1;
		case 6:
			return 2;
		case -1:
			return 3;
		case 11:
			return 4;
		case 1:
		case 2:
		case 3:
		case 7:
		case 8:
		case 9:
		case 10:
			break;
	}

	if (lbl_8042C0D4 == NULL) {
		return 6;
	}

	switch (DVDGetCommandBlockStatus(lbl_8042C0D4)) {
		case 0:
			return 7;
		case 5:
			return 0;
		case 4:
			return 1;
		case 6:
			return 2;
		case -1:
			return 3;
		case 11:
			return 4;
		case 1:
		case 2:
		case 3:
		case 7:
		case 8:
		case 9:
		case 10:
			break;
	}

	return 6;
}
}
