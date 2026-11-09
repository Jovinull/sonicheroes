// Fetches an entry with fn_8019E0F0(arg0, 0); if present clears its low two flag bits (+3) and runs fn_8019E880 on it; returns the entry.

extern "C" {
struct Entry8019E2A0 {
	unsigned char pad[3];
	unsigned char c3;
};
Entry8019E2A0* fn_8019E0F0(int, int);
void fn_8019E880(unsigned);

Entry8019E2A0* fn_8019E2A0(int a)
{
	Entry8019E2A0* t = fn_8019E0F0(a, 0);
	if (t != 0) {
		t->c3 = t->c3 & 0xfc;
		fn_8019E880((unsigned)t);
	}
	return t;
}
}
