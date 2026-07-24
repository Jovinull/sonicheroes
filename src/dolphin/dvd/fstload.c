#include "dolphin/os.h"

typedef struct DVDDiskID {
	char game_name[4];
	char company[2];
	u8 disk_number;
	u8 game_version;
	u8 is_streaming;
	u8 stream_buffer_size;
	u8 padding[22];
} DVDDiskID;

typedef struct DVDBB2 {
	u32 bootFilePosition;
	u32 FSTPosition;
	u32 FSTLength;
	u32 FSTMaxLength;
	void* FSTAddress;
	u32 userPosition;
	u32 userLength;
	u32 padding;
} DVDBB2;

typedef struct DVDCommandBlock {
	u8 data[0x30];
} DVDCommandBlock;

typedef struct OSBootInfo {
	DVDDiskID disk_info;
	u8 padding[0x18];
	void* fst_location;
	u32 fst_max_length;
} OSBootInfo;

typedef void (*DVDCallback)(long result, DVDCommandBlock* block);

#define OSPhysicalToCached(address) ((void*)((u32)(address) + 0x80000000))
#define OSRoundUp32B(address)       (((u32)(address) + 31) & ~31)

#define DVD_STATE_FATAL_ERROR   -1
#define DVD_STATE_BUSY          1
#define DVD_STATE_WAITING       2
#define DVD_STATE_COVER_CLOSED  3
#define DVD_STATE_NO_DISK       4
#define DVD_STATE_COVER_OPEN    5
#define DVD_STATE_MOTOR_STOPPED 6

extern BOOL DVDReadAbsAsyncForBS(
    DVDCommandBlock* block, void* addr, u32 length, u32 offset, DVDCallback callback);
extern BOOL DVDReadDiskID(DVDCommandBlock* block, DVDDiskID* id, DVDCallback callback);
extern long DVDGetDriveStatus(void);
extern void DVDReset(void);
extern void* OSGetArenaHi(void);
extern void OSSetArenaHi(void* arenaHi);
extern void* memcpy(void* dst, const void* src, u32 size);

// .bss
static unsigned char bb2Buf[63]; // size: 0x3F, address: 0x0

// .sbss
static unsigned long lbl_8042CC68; // size: 0x4, address: 0x0
static struct DVDBB2* bb2;         // size: 0x4, address: 0x4
static struct DVDDiskID* idTmp;    // size: 0x4, address: 0x8

#define status lbl_8042CC68

// functions
static void cb(long result, struct DVDCommandBlock* block);
void __fstLoad();

static void cb(long result, struct DVDCommandBlock* block)
{
	if (result > 0) {
		switch (status) {
			case 0:
				status = 1;
				DVDReadAbsAsyncForBS(block, bb2, 0x20, 0x420, cb);
				return;
			case 1:
				status = 2;
				DVDReadAbsAsyncForBS(block, bb2->FSTAddress, (bb2->FSTLength + 0x1F) & 0xFFFFFFE0,
				    bb2->FSTPosition, cb);
			default:
				return;
		}
	}
	if (result == -1) {
		return;
	} else if (result == -4) {
		status = 0;
		DVDReset();
		DVDReadDiskID(block, idTmp, cb);
	}
}

void __fstLoad()
{
	struct OSBootInfo* bootInfo;
	struct DVDDiskID* id;
	unsigned char idTmpBuf[63];
	long state;
	void* arenaHi;
	static struct DVDCommandBlock block;

	arenaHi  = OSGetArenaHi();
	bootInfo = (void*)OSPhysicalToCached(0);
	idTmp    = (void*)OSRoundUp32B(idTmpBuf);
	bb2      = (void*)OSRoundUp32B(bb2Buf);
	DVDReset();
	DVDReadDiskID(&block, idTmp, cb);
	while (1) {
		state = DVDGetDriveStatus();
		if (state == 0) {
			break;
		}

		// weird switch that seemingly wont do anything but break out of its own switch. What was this for? Early DVD development pre-hardware?
		switch (state) {
			case DVD_STATE_FATAL_ERROR:
				break;
			case DVD_STATE_BUSY:
				break;
			case DVD_STATE_WAITING:
				break;
			case DVD_STATE_COVER_CLOSED:
				break;
			case DVD_STATE_NO_DISK:
				break;
			case DVD_STATE_COVER_OPEN:
				break;
			case DVD_STATE_MOTOR_STOPPED:
				break;
		}
	}
	bootInfo->fst_location   = (void*)bb2->FSTAddress;
	bootInfo->fst_max_length = bb2->FSTMaxLength;
	id                       = &bootInfo->disk_info;
	memcpy(id, idTmp, sizeof(DVDDiskID));
	OSReport("\n");
	OSReport("  Game Name ... %c%c%c%c\n", id->game_name[0], id->game_name[1], id->game_name[2],
	    id->game_name[3]);
	OSReport("  Company ..... %c%c\n", id->company[0], id->company[1]);
	OSReport("  Disk # ...... %d\n", id->disk_number);
	OSReport("  Game ver .... %d\n", id->game_version);
	OSReport("  Streaming ... %s\n", !(id->is_streaming) ? "OFF" : "ON");
	OSReport("\n");
	OSSetArenaHi(bb2->FSTAddress);
}
