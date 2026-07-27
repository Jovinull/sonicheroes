#include "types.h"

extern "C" {

extern s32 DVDGetDriveStatus(void);
extern void* lbl_8042C0D4;
extern s32 DVDGetCommandBlockStatus(void* block);

s32 fn_80013044(void)
{
	switch (DVDGetDriveStatus()) {
		case 0: return 7;
		case 5: return 0;
		case 4: return 1;
		case 6: return 2;
		case -1: return 3;
		case 11: return 4;
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
		case 0: return 7;
		case 5: return 0;
		case 4: return 1;
		case 6: return 2;
		case -1: return 3;
		case 11: return 4;
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
