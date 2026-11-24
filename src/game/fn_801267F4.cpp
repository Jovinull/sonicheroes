#include "types.h"
#include "MSL_C/string.h"

// Constructor of a memory card save-file layout (HYPOTHESIS; the class name is UNKNOWN, see
// fn_8012695C): stores the parameters, allocates the 0x40-byte comment block and copies the two
// 32-byte comment strings into it, then computes the offsets of the banner and the icons and the
// header size. The sizes are those of the GameCube card formats: a 96x32 banner is 0x1800 bytes in
// RGB5A3 or 0xC00 bytes plus a 0x200-byte palette (0xE00) in C8; each 32x32 icon is 0x800 bytes in
// RGB5A3 or 0x400 bytes in C8 with one shared 0x200-byte palette. Without icons (or with a
// non-positive count) one RGB5A3 icon is assumed; at most eight icons are kept, but the C8 size
// uses the count as passed, before that clamp (retail reads the parameter register). The meaning
// of the two words at 0x28 and 0x2C is UNKNOWN. Returns the object.

struct SaveLayout801267F4 {
	s32 size;          // 0x00: comment + banner + icons
	char* comments;    // 0x04: two 32-byte strings
	u32 hasBanner;     // 0x08
	u32 bannerC8;      // 0x0C
	u32 hasIcons;      // 0x10
	u32 iconsC8;       // 0x14
	s32 commentOffset; // 0x18
	s32 bannerOffset;  // 0x1C
	s32 iconOffset;    // 0x20
	s32 iconCount;     // 0x24
	s32 f28;           // 0x28
	s32 f2C;           // 0x2C
};

extern "C" SaveLayout801267F4* fn_801267F4(SaveLayout801267F4* o, u32 hasBanner, u32 bannerC8,
    u32 hasIcons, u32 iconsC8, s32 iconCount, s32 f28, s32 f2C, const char* comment0,
    const char* comment1)
{
	char* comments;

	o->hasBanner = hasBanner;
	o->bannerC8  = bannerC8;
	o->hasIcons  = hasIcons;
	o->iconsC8   = iconsC8;
	o->iconCount = iconCount;
	o->f28       = f28;
	o->f2C       = f2C;
	o->comments  = new char[0x40];
	memset(o->comments, 0, 0x40);
	comments = o->comments;
	strncpy(comments, comment0, 0x20);
	strncpy(comments + 0x20, comment1, 0x20);
	o->commentOffset = 0;
	o->size          = 0x40;
	o->bannerOffset  = o->size;
	if (o->hasBanner != 0) {
		if (o->bannerC8 == 0) {
			o->size += 0x1800;
		} else {
			o->size += 0xE00;
		}
	}
	o->iconOffset = o->size;
	if (o->iconCount <= 0 || o->hasIcons == 0) {
		o->iconCount = 1;
		o->hasIcons  = 0;
		o->iconsC8   = 0;
	}
	if (o->iconCount > 8) {
		o->iconCount = 8;
	}
	if (o->iconsC8 == 0) {
		o->size += o->iconCount * 0x800;
	} else {
		o->size += 0x200 + iconCount * 0x400;
	}
	return o;
}
