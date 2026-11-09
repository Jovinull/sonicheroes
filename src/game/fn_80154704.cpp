// Returns 8 when the record the object points to at 0x8 exists and has a non-zero word at 0x2C, otherwise 0.

extern "C" {
struct Rec80154704 {
	unsigned char pad[0x2c];
	unsigned f2c;
};
struct Obj80154704 {
	unsigned char pad[0x8];
	Rec80154704* p;
};

int fn_80154704(Obj80154704* o)
{
	Rec80154704* t = o->p;
	if (t != 0 && t->f2c != 0) {
		return 8;
	}
	return 0;
}
}
