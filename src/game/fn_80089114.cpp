// Compares one 16-bit field of a small state record with an id. The only caller passes the record
// at player+0x14C after checking the half-word at +0x2 itself, so the record looks like a set of
// action ids (HYPOTHESIS: current/previous action); the roles of the fields are UNKNOWN.
// NonMatching (3 words): the retail code sign-extends the id in place (extsh r4,r4) before the
// load and subtracts the id from the field; MWCC 1.3.2 loads the field into r3 first and
// subtracts the other way. Tried: both operand orders, s16/s32 parameter with casts, locals,
// inline helper, if/return forms, ns/noschedule flags and compilers 1.2.5n-2.6.
#include "types.h"

struct ActionIds80089114 {
	s16 unknown0; // 0x0
	s16 unknown2; // 0x2 (checked directly by the caller)
	s16 unknown4; // 0x4
};

extern "C" bool fn_80089114(ActionIds80089114* ids, s16 id)
{
	return ids->unknown4 == id;
}
