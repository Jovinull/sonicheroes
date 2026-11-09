// Opens the stream for pathname arg1 (fn_80198000 type 2 mode 1) and, if fn_80192F38 accepts it with 0x10, returns fn_80150B88 of it (closing the stream afterwards); 0 otherwise.

extern "C" {
int RsPathnameCreate(int);
void RsPathnameDestroy(int);
int fn_80150B88(unsigned);
int fn_80192F38(unsigned, int, int, int);
void fn_80197ED8(unsigned, int);
unsigned fn_80198000(int, int, int);

int fn_8004A774(int unused, int a)
{
	unsigned h;
	int p;
	int r;
	p = RsPathnameCreate(a);
	h = fn_80198000(2, 1, p);
	RsPathnameDestroy(p);
	if (h == 0) {
		return 0;
	}
	if (fn_80192F38(h, 0x10, 0, 0) != 0) {
		r = fn_80150B88(h);
	} else {
		return 0;
	}
	fn_80197ED8(h, 0);
	return r;
}
}
