// Hands out four values: two words (lbl_8042BDC8 and lbl_8042BDCC) and the
// addresses of the tables at lbl_8028DA90 and lbl_8028EA90. Returns 0.

extern "C" {
extern int lbl_8042BDC8;
extern int lbl_8042BDCC;
extern unsigned char lbl_8028DA90[];
extern unsigned char lbl_8028EA90[];

int fn_8017AB1C(int* a, int* b, void** c, void** d)
{
	*a = lbl_8042BDC8;
	*b = lbl_8042BDCC;
	*c = lbl_8028DA90;
	*d = lbl_8028EA90;
	return 0;
}
}
