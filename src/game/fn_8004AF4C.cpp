// Unless the flag at 0x1F of the global is set, advances the counter (+4) of each of the entries held at 4 (count at 0x304), wrapping it to 0 at the limit (+0); always returns 1.

extern "C" {
struct Counter8004AF4C {
	int f0;
	int f4;
};
struct Glob8004AF4C {
	unsigned char pad[0x1f];
	signed char c1f;
};
struct Obj8004AF4C {
	int f0;
	Counter8004AF4C* arr[0xc0];
	int cnt;
};
extern Glob8004AF4C* lbl_8042C180;

int fn_8004AF4C(Obj8004AF4C* o)
{
	Counter8004AF4C** p;
	int i;
	if (lbl_8042C180->c1f != 0) {
		return 1;
	}
	i = 0;
	p = (Counter8004AF4C**)o;
	for (; i < o->cnt; i++) {
		Counter8004AF4C* t = p[1];
		t->f4              = t->f4 + 1;
		if (t->f4 >= t->f0) {
			t->f4 = 0;
		}
		p++;
	}
	return 1;
}
}
