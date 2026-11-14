// Returns the index of the first 12-byte entry whose leading word equals the key, or -1.
struct Entry801B56A4 {
	unsigned int id;
	unsigned char pad4[0x8];
};

struct Table801B56A4 {
	unsigned int count;
	Entry801B56A4* entries;
};

extern "C" {
int fn_801B56A4(Table801B56A4* t, unsigned int id)
{
	int i;
	for (i = 0; i < t->count; i++) {
		unsigned int e = t->entries[i].id;
		if (e == id) {
			return i;
		}
	}
	return -1;
}
}
