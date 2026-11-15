// Prepares the set-object file of a TObjSetGen-sized object (HYPOTHESIS): unless it already has
// one (+0xA50) or a buffer (+0xA44), creates an unnamed ONEFILE (flag 1), waits for it, allocates a
// 1 MiB buffer (fn_80012994) and gives it to the file as its external buffer (+0x40). Field roles
// are HYPOTHESIS.
// NonMatching (one instruction short): after the second test the retail code branches into the
// body and jumps over it otherwise (beq body; b end); MWCC 1.3.2 emits a single bne for every
// spelling tried (&&, nested ifs, early returns, ||-else, inline predicate helpers).
#include "game/one.h"

struct Owner8005B2C4 {
	u8 pad0[0xA44];
	void* buffer; // 0xA44
	u8 padA48[0xA50 - 0xA48];
	ONEFILE* file; // 0xA50
};

extern "C" {
void* fn_80012994(u32 size);

void fn_8005B2C4(Owner8005B2C4* o)
{
	if (o->file == NULL && o->buffer == NULL) {
		o->file = new ONEFILE(NULL, 1);
		while (o->file == NULL) {
		}
		o->buffer         = fn_80012994(0x100000);
		o->file->exBuffer = o->buffer;
	}
}
}
