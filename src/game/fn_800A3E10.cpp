// Looks up the entry for the given id and updates the cached handle and flag.
struct Node800A3E10 {
	unsigned char pad0[4];
	unsigned char* f4;
};
struct Obj800A3E10 {
	unsigned char pad0[0x224];
	int f224;
	unsigned char pad228[0x10];
	int f238;
};

extern "C" {
extern int lbl_8042C1A4;
void fn_80021824(int* p);
Node800A3E10* fn_80020BD8(int a, int b);
int fn_80041B64(int a);

int fn_800A3E10(Obj800A3E10* o, int a)
{
	int old = o->f238;
	fn_80021824(&lbl_8042C1A4);
	Node800A3E10* n = fn_80020BD8(a, 0xF);
	unsigned char* p;
	if (n != 0) {
		p = n->f4;
	} else {
		p = 0;
	}
	int r;
	if (p != 0) {
		o->f238 = fn_80041B64(*(int*)(p + 0x78));
		r       = 1;
	} else {
		o->f238 = -1;
		r       = 0;
	}
	if (old == -1) {
		if (o->f238 != -1) {
			o->f224 = 1;
		} else {
			o->f224 = 0;
		}
	} else {
		o->f224 = 0;
	}
	return r;
}
}
