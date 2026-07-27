#include "types.h"

// Four leaf accessors over one object, from fn_80013398 through 0x800133D0.
//
// The end of the range is exact: fn_800133D0, the function immediately after
// it, has its own extab entry at 0x800057A8 and extabindex entry at
// 0x8000BD7C, so it belongs to a different translation unit. The start is
// weaker, since this unit owns no data of its own to argue from. What supports
// it is that dtk's own analysis, run before this file was carved, placed a
// split at exactly 0x80013398..0x800133D0 without being told to. Two of the
// four functions ignore their argument entirely, so the run being one unit
// rests on the two that do share the object, not on all four.
//
// Two things here are load bearing for the match and must not be tidied:
//
//   The functions are declared in reverse address order under
//   `#pragma force_active on`. Written in address order the compiler emits
//   them in the other order and nothing lines up.
//
//   fn_800133A8 is written as `>=`, not `<`. CodeWarrior turns the unsigned
//   compare into the branchless Hacker's Delight sequence, and the operands
//   have to be in this order for field_283C to be the one that lands in r4.

extern "C" {

// Every name here is a guess. The object has no string, assert or SDK symbol
// in the binary to name it from, and only two of its fields are ever touched,
// 0x283C and 0x2840, so the rest is padding of unknown shape. Both fields are
// only ever loaded and compared against each other, which is what a pointer
// and its limit look like, but nothing in the binary confirms they are
// pointers rather than two plain words.
typedef struct Unknown {
	u8 padding[0x283C];
	void* field_283C;
	void* field_2840;
} Unknown;

#pragma force_active on

s32 fn_800133C8(void)
{
	return -1;
}

bool fn_800133A8(Unknown* obj)
{
	return obj->field_283C >= obj->field_2840;
}

u32 fn_800133A0(void)
{
	return 0;
}

u32 fn_80013398(Unknown* obj)
{
	return (u32)obj->field_283C;
}
}
