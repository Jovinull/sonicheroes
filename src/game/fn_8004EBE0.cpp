// Copies the pair at +0x30/+0x44 indexed by arg1 (or the defaults at +0x2C/+0x40) into fields 0x60/0x64 of the object at 0x28; the indexed pair is used only when the two globals differ by one and arg1 is non-negative.

extern "C" {
struct Dest8004EBE0 {
	unsigned char pad[0x60];
	int f60;
	int f64;
};
struct Obj8004EBE0 {
	unsigned char pad[0x28];
	Dest8004EBE0* f28;
	int f2c;
	unsigned char pad1[0x40 - 0x30];
	int f40;
	unsigned char pad2[4];
};
extern int lbl_8042C21C;
extern int lbl_8042C224;

void fn_8004EBE0(Obj8004EBE0* o, int idx)
{
	if (lbl_8042C224 - lbl_8042C21C == 1) {
		if (idx >= 0) {
			int* p      = (int*)((unsigned char*)o + idx * 4);
			o->f28->f60 = p[0x30 / 4];
			o->f28->f64 = p[0x44 / 4];
			return;
		}
		o->f28->f60 = o->f2c;
		o->f28->f64 = o->f40;
		return;
	}
	o->f28->f60 = o->f2c;
	o->f28->f64 = o->f40;
}
}
