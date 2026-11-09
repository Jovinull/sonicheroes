// Gets the record from fn_8006298C, flags it (bit 28 of word 0x2C) and returns it; returns 0 when there is none.

extern "C" {
struct Rec80062894 {
	unsigned char pad[0x2c];
	int f2c;
};
Rec80062894* fn_8006298C();

Rec80062894* fn_80062894()
{
	Rec80062894* r = fn_8006298C();
	if (r == 0) {
		return 0;
	}
	r->f2c |= 0x10000000;
	return r;
}
}
