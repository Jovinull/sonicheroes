// When arg1 matches the id at +0xC of the record at lbl_8042C918 + arg0, calls fn_8015B93C(arg1, arg0); returns arg0.

extern "C" {
extern int lbl_8042C918;
void fn_8015B93C(unsigned, int);
struct Rec8015B2B8 {
	unsigned char pad[0xc];
	unsigned fc;
};

int fn_8015B2B8(int a, unsigned b)
{
	Rec8015B2B8* c = (Rec8015B2B8*)(a + lbl_8042C918);
	if (c != 0 && b == c->fc) {
		fn_8015B93C(b, a);
	}
	return a;
}
}
