// When the handle, record (flag 8 at +8) and output pointers are valid, stores the record's values at +0x10 and +0x14 (u16) into *arg2/*arg3 and returns 8; otherwise 0.

extern "C" {
struct Rec8017CB58 {
	unsigned char pad[8];
	unsigned f8;
	unsigned char pad1[4];
	int f10;
	unsigned short f14;
};

int fn_8017CB58(unsigned a, Rec8017CB58* o, int* p, int* q)
{
	if (a != 0 && o != 0 && (o->f8 & 8) && p != 0) {
		*p = o->f10;
		*q = o->f14;
		return 8;
	}
	return 0;
}
}
