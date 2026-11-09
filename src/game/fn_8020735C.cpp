// Creates the 8-byte record for arg0 with fn_802064DC and stores arg1 at +4 when it was created.

extern "C" {
struct Rec8020735C {
	unsigned char pad[4];
	int f4;
};
Rec8020735C* fn_802064DC(int, int, int);

void fn_8020735C(int a, int b)
{
	Rec8020735C* t = fn_802064DC(8, a, 0);
	if (t != 0) {
		t->f4 = b;
	}
}
}
