struct T8009D160 {
	unsigned char pad0[0x6F0];
};

struct O8009D160 {
	unsigned char pad0[0x39];
	signed char f39;
	signed char f3A;
	unsigned char pad3B[0xD5];
	signed char f110[4];
	T8009D160* f114[4];
};

extern "C" {
void fn_800898F0(T8009D160* t, int a);
void fn_800E124C(int a);

void fn_8009D160(O8009D160* o)
{
	O8009D160* p;
	int i;
	i = 0;
	p = o;
	for (; i < o->f39; i++) {
		int c = o->f110[i];
		fn_800E124C(c);
		if (i == o->f3A) {
			fn_800898F0(p->f114[0], 0);
		} else {
			fn_800898F0(p->f114[0], 4);
		}
		p = (O8009D160*)((char*)p + 4);
	}
}
}
