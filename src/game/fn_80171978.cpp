// Turns the growable segment lists of a 2D path chain into plain arrays (HYPOTHESIS: the Rt2d path
// "lock"/flatten step): for each path whose count is -1 (segments still in an RwSList), the count
// becomes the list's entry count and the list is replaced by its array (fn_801946A4); the walk
// follows +0x14 and stops at the first path already flattened. The compiler inlines the
// recursion several levels deep. Returns the first path. Names follow fn_80171BFC.
// NonMatching: retail inlines the recursion seven levels before the out-of-line call, this
// source eight (one extra level, 132 vs 119 instructions); the inliner's size budget depends on a
// source detail not yet found. Early-return and guarded-call forms inline even deeper.
#include "game/rw_engine.h"

struct Path80171978 {
	void* segments;  // 0x0: RwSList while numSegments is -1
	s32 numSegments; // 0x4
	u8 pad8[0x14 - 0x8];
	Path80171978* next; // 0x14
};

extern "C" {
// HYPOTHESIS: _rwSListGetNumEntries and _rwSListToArray.
s32 fn_8019469C(RwSList* sList);
void* fn_801946A4(RwSList* sList);

Path80171978* fn_80171978(Path80171978* path)
{
	if (path != 0 && path->numSegments == -1) {
		s32 count         = fn_8019469C((RwSList*)path->segments);
		path->segments    = fn_801946A4((RwSList*)path->segments);
		path->numSegments = count;
		fn_80171978(path->next);
	}
	return path;
}
}
