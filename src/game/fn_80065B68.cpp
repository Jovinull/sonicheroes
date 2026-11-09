// Returns the entry `count` steps (0x28 bytes each) into list number a (0-15) of the table at 0x34, or 0 when out of range or the list ends early.

extern "C" {
struct Entry80065B68 {
	unsigned char pad[2];
	short s2;
	unsigned char pad1[0x24];
};
struct Table80065B68 {
	unsigned char pad[0x34];
	Entry80065B68* p[16];
};

Entry80065B68* fn_80065B68(Table80065B68* t, int a, int b)
{
	Entry80065B68* r;
	int c = b;
	if (a < 0 || a >= 0x10) {
		return 0;
	}
	if (c < 0 || c >= 0x20) {
		return 0;
	}
	r = t->p[a];
	if (r == 0) {
		return 0;
	}
	if (c == 0) {
		return r;
	}
	while (c > 0 && r != 0 && r->s2 >= 0) {
		r = (Entry80065B68*)((unsigned char*)r + 0x28);
		c -= 1;
	}
	if (c != 0) {
		return 0;
	}
	return r;
}
}
