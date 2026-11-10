// Initializes the table entry at the given offset and copies its list head.
struct S8015A9F8 {
	int f0;
	int f4;
};

extern "C" {
extern int lbl_8042C920;
extern int lbl_8042C928;
extern int lbl_8042C9A4;
int fn_8015A9F8(int a)
{
	S8015A9F8* s = (S8015A9F8*)(a + lbl_8042C920);
	s->f0        = 0;
	s->f4        = ((int*)(lbl_8042C9A4 + lbl_8042C928))[8 / 4];
	return a;
}
}
