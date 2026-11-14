// Resets a 0x708-byte record: clears it and its 0x24 bytes at 0x18, sets bytes 0x1C/0x1D and 0x6F2/0x6F3
// to 1, fills its 26 three-byte slots at 0x553 from the 13 pairs of lbl_80288DF0 (two slots per
// pair, third byte 0) and sets the four words at 0x3C of lbl_803E774C to 3. fn_80116D30 and
// fn_80117080 have identical bodies. Layouts are inferred.
struct Pair80116D30 {
	unsigned char a;
	unsigned char b;
};
struct Slot80116D30 {
	unsigned char a;
	unsigned char b;
	unsigned char c;
};
struct Obj80116D30 {
	unsigned char pad0[0x18];
	unsigned char f18[0x4];
	unsigned char f1C;
	unsigned char f1D;
	unsigned char pad1E[0x38 - 0x1E];
	int f38;
	unsigned char pad3C[0x553 - 0x3C];
	Slot80116D30 slots[13][2];
	unsigned char pad[0x6F2 - 0x553 - 13 * 2 * 3];
	unsigned char f6F2;
	unsigned char f6F3;
};
struct Global80116D30 {
	unsigned char pad0[0x3C];
	int f3C;
	int f40;
	int f44;
	int f48;
};
extern "C" {
extern Pair80116D30 lbl_80288DF0[13];
extern Global80116D30 lbl_803E774C;
void* memset(void* dst, int value, unsigned long n);
void fn_80117080(Obj80116D30* o)
{
	int i;
	int j;
	memset(o, 0, 0x708);
	memset(o->f18, 0, 0x24);
	o->f1C = 1;
	o->f1D = 1;
	o->f38 = 0;
	for (i = 0; i < 13; i++) {
		Slot80116D30* d = o->slots[i];
		for (j = 0; j < 2; j++) {
			d[j].a = lbl_80288DF0[i].a;
			d[j].b = lbl_80288DF0[i].b;
			d[j].c = 0;
		}
	}
	lbl_803E774C.f3C = 3;
	lbl_803E774C.f40 = 3;
	lbl_803E774C.f44 = 3;
	lbl_803E774C.f48 = 3;
	o->f6F2          = 1;
	o->f6F3          = 1;
}
}
