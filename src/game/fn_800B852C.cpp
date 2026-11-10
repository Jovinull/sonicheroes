// Initialises the record (ids -1, cleared words, default float, a fresh id from fn_8019E344) and returns it.
struct Rec800B852C {
	signed char f0;
	signed char f1;
	unsigned char pad2[2];
	float f4;
	unsigned char pad8[0x18];
	int f20;
	int f24;
	int f28;
	int f2C;
	int f30;
	int f34;
	int f38;
	int f3C;
};

extern "C" {
extern float lbl_8042DD4C;
int fn_8019E344();

Rec800B852C* fn_800B852C(Rec800B852C* r)
{
	r->f0  = -1;
	r->f1  = -1;
	r->f20 = 0;
	r->f24 = 0;
	r->f28 = 0;
	r->f30 = 0;
	r->f38 = 0;
	r->f34 = 0;
	r->f3C = 0;
	r->f4  = lbl_8042DD4C;
	r->f2C = fn_8019E344();
	return r;
}
}
