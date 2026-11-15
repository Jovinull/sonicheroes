// Walks the atomics of a clump that fn_800F47B0 selects (fn_8014FFBC with a search record: the
// result, the previous match and the name table lbl_80259C08) and, for each match, applies
// fn_80146BC8(atomic, 6) and fn_80145EF8(..., fn_800F474C, 0, 0). HYPOTHESIS: sets a render
// callback on the named atomics of a model; the RenderWare names are UNKNOWN.
// NonMatching (4 words): the retail code loads the search result straight into the saved
// register (lwz r27; cmplwi r27; mr r3, r27); MWCC 1.3.2 loads it into r3 and copies it.
// Tried: assignment inside the test, one variable for the current and previous match, an inline
// helper for the two calls, declaration orders.
#include "types.h"

struct Search800F46B0 {
	void* found;    // 0x0
	void* previous; // 0x4
	u8* names;      // 0x8
};

extern "C" {
extern u8 lbl_80259C08[];
void fn_8014FFBC(void* clump, void* (*callback)(void*, void*), Search800F46B0* search);
void* fn_80146BC8(void* atomic, s32 value);
void fn_80145EF8(void* object, void* callback, s32 a, s32 b);
void* fn_800F47B0(void* atomic, void* data);
void fn_800F474C(void);

void fn_800F46B0(void* clump)
{
	Search800F46B0 search;
	void* previous = NULL;

	for (;;) {
		void* atomic;

		search.found    = NULL;
		search.previous = previous;
		search.names    = lbl_80259C08;
		fn_8014FFBC(clump, fn_800F47B0, &search);
		atomic = search.found;
		if (atomic == NULL) {
			break;
		}
		fn_80145EF8(fn_80146BC8(atomic, 6), (void*)fn_800F474C, 0, 0);
		previous = atomic;
	}
}
}
