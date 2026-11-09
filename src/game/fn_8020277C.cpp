// Returns the address of entry k (16-byte entries) of the table held at +0xC when k is within the count reported by fn_8019469C, otherwise 0.

extern "C" {
struct Obj8020277C {
	unsigned char pad[0xc];
	unsigned fc;
};
int fn_8019469C(unsigned);
int fn_8019460C(unsigned);

int fn_8020277C(Obj8020277C* o, int k)
{
	int r = 0;
	if (o->fc != 0) {
		int n = fn_8019469C(o->fc);
		if (n > 0 && k < n) {
			r = fn_8019460C(o->fc);
			r += k << 4;
		}
	}
	return r;
}
}
