// Stores two values into the entry at the given offset and returns the offset.
struct P1 {
	unsigned char pad[0x10];
	int f10;
	int f14;
};
struct T4 {
	int a;
	P1* b;
};
extern "C" {
extern int lbl_8042C820;
int fn_8013D748(int a, int b, int c)
{
	T4* t     = (T4*)(a + lbl_8042C820);
	t->b->f10 = b;
	t->b->f14 = c;
	return a;
}
}
