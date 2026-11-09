// Searches a list of 0x24-byte entries for the one whose first word equals the
// given key. Returns the entry, or 0 when there is none.

extern "C" {
struct Entry801B55F4 {
	unsigned key;
	unsigned char pad[0x20];
};
struct List801B55F4 {
	unsigned count;
	unsigned pad4;
	unsigned pad8;
	Entry801B55F4* entries; // 0x0C
};

Entry801B55F4* fn_801B55F4(List801B55F4* l, unsigned key)
{
	if (l->count != 0) {
		Entry801B55F4* e = l->entries;
		for (unsigned i = 0; i < l->count; i++, e++) {
			if (e->key == key) {
				return e;
			}
		}
	}
	return 0;
}
}
