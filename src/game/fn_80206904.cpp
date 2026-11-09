// Creates the 8-byte record for arg0 with fn_802064DC and stores arg1 at +4 when it was created.

extern "C" {
struct Rec80206904 {
	unsigned char pad[4];
	int f4;
};
Rec80206904* fn_802064DC(int, int, int);

void fn_80206904(int a, int b)
{
	Rec80206904* t = fn_802064DC(8, a, 0);
	if (t != 0) {
		t->f4 = b;
	}
}
}
