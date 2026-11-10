// Looks up the entry by name from the object, the config or the default table.
struct Cfg801591D8 {
	unsigned char pad0[0x6C];
	unsigned int f6C;
};
struct Mgr801591D8 {
	unsigned char pad0[4];
	Cfg801591D8* f4;
};
struct Obj801591D8 {
	unsigned char pad0[0x84];
	unsigned int f84;
	unsigned char pad88[4];
	unsigned short f8C;
};

extern "C" {
extern Mgr801591D8* lbl_8042C9A4;
extern int lbl_8042CA80;
unsigned int fn_801B388C(unsigned int a, Obj801591D8* o, int c);

Obj801591D8* fn_801591D8(Obj801591D8* o)
{
	unsigned int v;
	if (o->f8C == 0) {
		return o;
	}
	if (o->f84 != 0) {
		v = o->f84;
	} else {
		unsigned int w = lbl_8042C9A4->f4->f6C;
		if (w != 0) {
			v = w;
		} else {
			int a = lbl_8042CA80;
			int b = (int)lbl_8042C9A4;
			v     = ((unsigned int*)(b + a))[0x40 / 4];
		}
	}
	if (fn_801B388C(v, o, 1) != 0) {
		return o;
	}
	return 0;
}
}
