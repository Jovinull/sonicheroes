#ifndef DOLPHIN_DVD_H
#define DOLPHIN_DVD_H

#include "types.h"

// The disc identification block, 0x20 bytes, as the SDK declares it. The DVD
// units keep their own file-local copies; this header serves other clients.

typedef struct DVDDiskID {
	char gameName[4];    // 0x00
	char company[2];     // 0x04
	u8 diskNumber;       // 0x06
	u8 gameVersion;      // 0x07
	u8 streaming;        // 0x08
	u8 streamingBufSize; // 0x09
	u8 padding[22];      // 0x0A
} DVDDiskID;             // 0x20

#endif
