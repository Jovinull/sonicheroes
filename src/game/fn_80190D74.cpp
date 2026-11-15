// Records a modification time in an info structure (HYPOTHESIS: libpng png_set_tIME): copies the
// 8-byte time value (HYPOTHESIS: png_time, sizeof 8 in this build) to info + 0x3C and flags tIME
// valid, unless the png structure or the info structure is null or the png mode says the chunk was
// already written (0x200 = PNG_WROTE_tIME). Fields used here are HYPOTHESIS: png_struct/png_info
// layout (mode at 0x28, valid at 0x8).
//
// The branch layout of the original is a switch test, not an if: mwcc emits the record-form
// `rlwinm.` followed by `beq body; b join` only for a one-case switch on the masked bit; every
// if/else/goto spelling of the same test folds to a single `bne join`.
#include "types.h"

struct Png80190D74 {
	u8 pad0[0x28];
	u32 mode; // 0x28
};

// HYPOTHESIS: png_time, 8 bytes (u16 year, five u8 fields, 2-byte aligned).
struct PngTime80190D74 {
	u16 year;  // 0x0
	u8 month;  // 0x2
	u8 day;    // 0x3
	u8 hour;   // 0x4
	u8 minute; // 0x5
	u8 second; // 0x6
};

struct PngInfo80190D74 {
	u8 pad0[0x8];
	u32 valid; // 0x8
	u8 padC[0x3C - 0xC];
	PngTime80190D74 modTime; // 0x3C
};

#define PNG_INFO_tIME  0x200
#define PNG_WROTE_tIME 0x200

extern "C" {
void* memcpy(void* destination, const void* source, u32 size);

void fn_80190D74(Png80190D74* png, PngInfo80190D74* info, PngTime80190D74* modTime)
{
	if (png == 0) {
		return;
	}
	if (info == 0) {
		return;
	}
	switch (png->mode & PNG_WROTE_tIME) {
		case 0:
			memcpy(&info->modTime, modTime, sizeof(PngTime80190D74));
			info->valid |= PNG_INFO_tIME;
			break;
		default:
			break;
	}
}
}
