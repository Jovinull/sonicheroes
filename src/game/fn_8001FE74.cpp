// Whether a collision object has a hit against another object's shape of kind 0xC, 0xE or 0x10
// (1) or not (0). Each search is the cached hit iterator of fn_80020BD8 (search cache
// lbl_802AD060, tag 0x23F6) inlined, after one reset; see fn_8001FAE0. The meaning of the shape
// kinds is UNKNOWN.
#include "types.h"

// Search cache shared by the iterators (see fn_8001F9F8).
struct SearchCache8001FE74 {
	void* list; // 0x0
	s32 tag;    // 0x4
	s32 index;  // 0x8
	s32 key;    // 0xC
};

struct Shape8001FE74 {
	u8 kind; // 0x0
	u8 pad1[0x30 - 0x1];
};

struct Colli8001FE74;

struct Hit8001FE74 {
	s8 entry;      // 0x0
	s8 otherEntry; // 0x1 (-1: unused, ends the list)
	u8 pad2[2];
	Colli8001FE74* other; // 0x4
};

struct Colli8001FE74 {
	u8 pad0[0x8];
	u16 flags; // 0x8 (bit 0: has hits)
	u8 padA[0x10 - 0xA];
	Shape8001FE74* shapes; // 0x10
	Hit8001FE74 hits[8];   // 0x14
};

extern "C" {
extern SearchCache8001FE74 lbl_802AD060;
}

static inline void ResetSearch()
{
	lbl_802AD060.list  = NULL;
	lbl_802AD060.tag   = -1;
	lbl_802AD060.index = -1;
	lbl_802AD060.key   = -1;
}

// Body of fn_80020BD8: the next hit whose other shape has kind `kind`.
static inline Hit8001FE74* NextHit(Colli8001FE74* c, u8 kind)
{
	if (lbl_802AD060.list != c) {
		lbl_802AD060.list  = c;
		lbl_802AD060.tag   = -1;
		lbl_802AD060.key   = -1;
		lbl_802AD060.index = -1;
	}
	if (lbl_802AD060.tag != 0x23F6) {
		lbl_802AD060.tag   = 0x23F6;
		lbl_802AD060.key   = -1;
		lbl_802AD060.index = -1;
	}
	if (kind != -1 && lbl_802AD060.key != kind) {
		lbl_802AD060.key   = kind;
		lbl_802AD060.index = -1;
	}
	int n              = lbl_802AD060.index + 1;
	lbl_802AD060.index = n;
	if (n > 8) {
		lbl_802AD060.index = 8;
	}
	int i   = lbl_802AD060.index;
	int idx = i;
	if (!(c->flags & 1)) {
		return NULL;
	}
	Hit8001FE74* p;
	Hit8001FE74* end;
	end = &c->hits[8];
	p   = &c->hits[i];
	for (; p < end; p++, idx++) {
		int k                = p->otherEntry;
		Colli8001FE74* other = p->other;
		if (k == -1) {
			return NULL;
		}
		if (other != NULL && other->shapes[k].kind == kind) {
			lbl_802AD060.index = idx;
			return p;
		}
	}
	return NULL;
}

// The object hit, or null when there is no hit.
static inline Colli8001FE74* HitObject(Hit8001FE74* hit)
{
	return hit != NULL ? hit->other : NULL;
}

extern "C" s32 fn_8001FE74(Colli8001FE74* c)
{
	ResetSearch();
	if (HitObject(NextHit(c, 0xC)) != NULL || HitObject(NextHit(c, 0xE)) != NULL
	    || HitObject(NextHit(c, 0x10)) != NULL) {
		return 1;
	}
	return 0;
}
