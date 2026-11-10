// Runs the follow-up on every slot's owner that is in state 0x27 and not flagged, passing its stored byte.
struct T8009D048 {
	unsigned char pad0[0x6F0];
	short f6F0;
	unsigned char pad6F2[0x7E];
	short f770;
};
struct O8009D048 {
	unsigned char pad0[0x39];
	signed char f39;
	unsigned char pad3A[0xD6];
	signed char f110[4];
	T8009D048* f114[4];
};

extern "C" {
signed char fn_800898F0(T8009D048* t, int a);
int fn_800894A4(T8009D048* t);
void fn_800E124C(int a);

signed char fn_8009D048(O8009D048* o)
{
	O8009D048* p;
	int i;
	signed char r;
	i = 0;
	p = o;
	for (; i < o->f39; i++) {
		int c        = o->f110[i];
		r            = c;
		T8009D048* t = p->f114[0];
		if ((t->f770 & 0x200) == 0 && t->f6F0 == 0x27) {
			fn_800E124C(c);
			r = fn_800898F0(p->f114[0], fn_800894A4(p->f114[0]));
		}
		p = (O8009D048*)((char*)p + 4);
	}
	return r;
}
}
