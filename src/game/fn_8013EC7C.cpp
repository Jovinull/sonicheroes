// Returns the byte size of the entry at arg0 in the table lbl_8042C828: 0 when the entry is empty, 0xC when it has no payload (or a payload flagged with bit 0), otherwise 0x14 + count * 0xC.

extern "C" {
struct Payload8013EC7C {
	unsigned f0;
	int f4;
};
struct Entry8013EC7C {
	int f0;
	Payload8013EC7C* f4;
};
extern int lbl_8042C828;

int fn_8013EC7C(int a)
{
	int v            = 0;
	Entry8013EC7C* e = (Entry8013EC7C*)(a + lbl_8042C828);
	Payload8013EC7C* s;
	int r;
	if (e->f0 != -1 || e->f4 != 0) {
		v = 1;
	}
	if (v != 0) {
		s = e->f4;
		r = 0xc;
		if (s != 0 && !(s->f0 & 1)) {
			r = s->f4 * 0xc + 0x14;
		}
		return r;
	}
	return 0;
}
}
