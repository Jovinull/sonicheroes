// Gets the record from fn_800628D0, flags it (bit 28 of word 0x2C) and returns it; returns 0 when there is none.

extern "C" {
struct Rec80062858 {
	unsigned char pad[0x2c];
	int f2c;
};
Rec80062858* fn_800628D0();

Rec80062858* fn_80062858()
{
	Rec80062858* r = fn_800628D0();
	if (r == 0) {
		return 0;
	}
	r->f2c |= 0x10000000;
	return r;
}
}
