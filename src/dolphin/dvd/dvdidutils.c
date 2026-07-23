#include "types.h"

typedef struct DVDDiskID {
	char gameName[4];
	char company[2];
	u8 diskNumber;
	u8 gameVersion;
	u8 streaming;
	u8 streamBufSize;
	u8 padding[22];
} DVDDiskID;

extern int strncmp(const char* lhs, const char* rhs, u32 count);

int DVDCompareDiskID(DVDDiskID* id1, DVDDiskID* id2)
{
	if (id1->gameName[0] != '\0' && id2->gameName[0] != '\0'
	    && strncmp(id1->gameName, id2->gameName, 4) != 0) {
		return 0;
	}

	if (id1->company[0] == '\0' || id2->company[0] == '\0'
	    || strncmp(id1->company, id2->company, 2) != 0) {
		return 0;
	}

	if (id1->diskNumber != 0xFF && id2->diskNumber != 0xFF && id1->diskNumber != id2->diskNumber) {
		return 0;
	}

	if (id1->gameVersion != 0xFF && id2->gameVersion != 0xFF
	    && id1->gameVersion != id2->gameVersion) {
		return 0;
	}

	return 1;
}
