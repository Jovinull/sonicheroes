// Creates a pathname, opens a stream with fn_80198000, and if fn_80192F38 accepts it returns fn_8014D05C of it (closing it afterwards); 0 otherwise.

extern "C" {
int RsPathnameCreate(void);
void RsPathnameDestroy(int);
int fn_8014D05C(unsigned);
int fn_80192F38(unsigned, int, int, int);
void fn_80197ED8(unsigned, int);
unsigned fn_80198000(int, int, int);

int fn_80042118(void)
{
	unsigned h;
	int r = 0;
	int p;
	p = RsPathnameCreate();
	h = fn_80198000(2, 1, p);
	RsPathnameDestroy(p);
	if (h != 0 && fn_80192F38(h, 0xc, 0, 0) != 0) {
		r = fn_8014D05C(h);
		fn_80197ED8(h, 0);
	}
	return r;
}
}
