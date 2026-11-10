// Clears the 0x30-byte node, then links it into the manager's list when the owner id is set.
struct Obj80146E24 {
	int f0;
	int f4;
	unsigned char pad8[0x20];
	int f28;
	int f2C;
};

extern "C" {
extern int lbl_8042BCE0;
extern int lbl_8042C9A4;
void* memset(void* d, int c, unsigned int n);
void fn_801470F4(unsigned int head, Obj80146E24* o);

Obj80146E24* fn_80146E24(Obj80146E24* o, int a)
{
	memset(o, 0, 0x30);
	o->f0  = a;
	o->f4  = 1;
	o->f2C = 0;
	o->f28 = 0;
	if (a != 0 && ((unsigned int*)(lbl_8042C9A4 + lbl_8042BCE0))[8 / 4] != 0) {
		fn_801470F4(((unsigned int*)(lbl_8042C9A4 + lbl_8042BCE0))[8 / 4], o);
	}
	return o;
}
}
