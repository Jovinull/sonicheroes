// Fires the pending voice callback once when the voice is active and not locked.
struct Obj80206FB0 {
	unsigned int f0;
	unsigned char pad4[0x30];
	unsigned int f34;
	unsigned char pad38[0xAC];
	int fE4;
	int fE8;
	int fEC;
	int fF0;
	int fF4;
	int fF8;
	int fFC;
};

extern "C" {
void fn_80207E1C(int a, Obj80206FB0* o, int b, int c, int d, int e, int f, int g);

void fn_80206FB0(Obj80206FB0* o)
{
	if (o != 0 && o->f34 != 0) {
		unsigned int t = o->f0;
		if ((t & 0x80000000) && (t & 1)) {
			if (!(t & 0x40000000)) {
				fn_80207E1C(o->fE4, o, o->fE8, o->fEC, o->fF0, o->fF4, o->fF8, o->fFC);
			}
			o->f0 = o->f0 & 0xFFFFFFFE;
		}
	}
}
}
