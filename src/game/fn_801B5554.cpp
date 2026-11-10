// Validates that the entry pointer lies inside the list's 0x28-byte element array and stores its index into the output when it was unset.
struct E801B5554 {
	unsigned char pad[0x28];
};
struct L801B5554 {
	int f0;
	unsigned int f4;
	E801B5554* f8;
};

extern "C" {
static inline unsigned int IndexOf801B5554(L801B5554* l, E801B5554* e)
{
	E801B5554* base  = l->f8;
	unsigned int idx = e - base;
	if (base + idx == e && idx < l->f4) {
		return idx;
	}
	return 0xFFFFFFFFu;
}

L801B5554* fn_801B5554(L801B5554* l, unsigned int* out, E801B5554* e)
{
	if (l != 0 && l->f0 != 0 && out != 0 && *out == 0xFFFFFFFFu && e != 0
	    && *(unsigned int*)e != 0) {
		unsigned int idx = IndexOf801B5554(l, e);
		if (idx != 0xFFFFFFFFu) {
			*out = idx;
			return l;
		}
	}
	return 0;
}
}
