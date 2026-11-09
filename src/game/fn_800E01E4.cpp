// Sets up one slot of the two parallel tables (lbl_802AD090 / lbl_802AD0B0): stores
// the first value, 0x4000 minus the second (mirrored into the other table), and
// the third value.

extern "C" {
struct A800E01E4 {
	int pad0;
	int pad4;
	int pad8;
	int a;
	int b;
	int c;
};
struct B800E01E4 {
	unsigned char pad[0x1c];
	int v;
};
extern A800E01E4* lbl_802AD090[];
extern B800E01E4* lbl_802AD0B0[];
void fn_800E01E4(int index, int a, int b, int c)
{
	A800E01E4* p = lbl_802AD090[index];
	B800E01E4* q = lbl_802AD0B0[index];
	p->a         = a;
	p->b         = 0x4000 - b;
	q->v         = p->b;
	p->c         = c;
}
}
