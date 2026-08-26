#include "types.h"

// CRI RNARES for GameCube: .text 0x80224D14-0x80225100, .rodata
// 0x802405F8-0x80240648, and .bss 0x8042A9D0-0x8042AB68. AXRNA identifies
// these same boundaries from the adjacent side.

typedef struct RnaResHandle {
	s32 used;
	u32 address;
	u32 size;
} RnaResHandle;

extern void fn_80223424(const char* message);
extern u32 ARAlloc(u32 size);
extern void ARFree(u32* size);
extern void* memset(void* dst, int value, u32 size);

typedef struct RnaResBase {
	u32 referenceCount;
	u32 externallyAllocated;
	u32 handleCount;
	u32 aramSize;
	u32 aramAddress;
} RnaResBase;

static RnaResBase lbl_8042A9D0;
static RnaResHandle lbl_8042A9E4[32];
static u8 rnares_pad[4];

#define rnares_reference_count      lbl_8042A9D0.referenceCount
#define rnares_externally_allocated lbl_8042A9D0.externallyAllocated
#define rnares_handle_count         lbl_8042A9D0.handleCount
#define rnares_aram_size            lbl_8042A9D0.aramSize
#define rnares_aram_address         lbl_8042A9D0.aramAddress
#define rnares_handles              lbl_8042A9E4

const char lbl_802405F8[]       = "E1070313:Not enough RNARES handle.\n";
const char lbl_8024061C[]       = "E1090601:Free area other than ADX buffer.\n";
const u8 gap_06_80240647_rodata = 0;

RnaResHandle* fn_80224D14(void)
{
	s32 count            = 0;
	RnaResHandle* handle = rnares_handles;
	while (handle->used != 0) {
		handle++;
		count++;
		if (count == 32) {
			fn_80223424(lbl_802405F8);
			return NULL;
		}
	}
	handle->used = 1;
	return handle;
}

void fn_80224E1C(void)
{
	s32 i;
	u32 freeSize;
	if (--rnares_reference_count != 0) {
		return;
	}
	for (i = 0; i < 32; i++) {
		if (rnares_handles[i].used == 1 && &rnares_handles[i] != NULL) {
			rnares_handles[i].used = 0;
		}
	}
	memset(rnares_handles, 0, sizeof(rnares_handles));
	if (rnares_externally_allocated == 0) {
		ARFree(&freeSize);
		if (freeSize != rnares_aram_size) {
			fn_80223424(lbl_8024061C);
		}
		rnares_handle_count = 0;
		rnares_aram_size    = 0;
		rnares_aram_address = 0;
	}
}

void fn_80224F88(void)
{
	u32 count;
	u32 offset;
	RnaResHandle* handle;
	if (rnares_reference_count == 0) {
		if (rnares_externally_allocated == 0) {
			rnares_handle_count = 32;
			rnares_aram_size    = 0x40000;
			rnares_aram_address = ARAlloc(0x40000);
		}
		memset(rnares_handles, 0, sizeof(rnares_handles));
		offset = 0;
		count  = rnares_handle_count;
		handle = rnares_handles;
		while (count > 0) {
			handle->address = (rnares_aram_address + offset) >> 1;
			handle->size    = 0x1000;
			offset += 0x2000;
			handle++;
			count--;
		}
	}
	rnares_reference_count++;
}
