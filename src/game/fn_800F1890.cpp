// Resets a 0x6E-byte record: the floats at +0x14..+0x24 to 0, the words and half-words to 0, the
// half-words at +0xE/+0x10 to -1, and its 14 slots (a half-word id at +0x44, -1 = empty, and a byte
// at +0x60 each) to empty. Called by the player setup code; the record's role and field names are
// UNKNOWN.
#include "types.h"

struct Record800F1890 {
	s16 unknown0;  // 0x0
	s16 unknown2;  // 0x2
	s16 unknown4;  // 0x4
	s16 unknown6;  // 0x6
	s16 unknown8;  // 0x8
	s16 unknownA;  // 0xA
	s16 unknownC;  // 0xC
	s16 unknownE;  // 0xE
	s16 unknown10; // 0x10
	u8 pad12[2];
	f32 unknown14;    // 0x14
	f32 unknown18;    // 0x18
	f32 unknown1C;    // 0x1C
	f32 unknown20;    // 0x20
	f32 unknown24;    // 0x24
	s32 unknown28;    // 0x28
	s32 unknown2C;    // 0x2C
	s32 unknown30;    // 0x30
	s32 unknown34;    // 0x34
	s32 unknown38;    // 0x38
	s32 unknown3C;    // 0x3C
	s32 unknown40;    // 0x40
	s16 slotIds[14];  // 0x44
	u8 slotBytes[14]; // 0x60
};

extern "C" {
extern f32 lbl_8042E480; // 0.0f

void fn_800F1890(Record800F1890* r)
{
	f32 zero = lbl_8042E480;
	long i; // long, not int: with int MWCC drops the loop-entry test the retail code keeps

	r->unknown14 = r->unknown18 = r->unknown1C = zero;
	r->unknown28 = r->unknown2C = 0;
	r->unknown10 = r->unknownE = -1;
	r->unknown20 = r->unknown24 = zero;
	r->unknown0 = r->unknown4 = r->unknown2 = r->unknown6 = r->unknown8 = r->unknownA = r->unknownC
	    = 0;
	r->unknown30 = 0;
	r->unknown34 = 0;
	r->unknown38 = r->unknown3C = r->unknown40 = 0;
	for (i = 0; i < 14; i++) {
		r->slotIds[i]   = -1;
		r->slotBytes[i] = 0;
	}
}
}
