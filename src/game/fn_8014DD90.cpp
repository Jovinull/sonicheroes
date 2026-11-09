// Returns 8 when the record the object points to at 0x84 exists and has a non-zero word at 0x2C, otherwise 0.

extern "C" {
struct Rec8014DD90 {
	unsigned char pad[0x2c];
	unsigned f2c;
};
struct Obj8014DD90 {
	unsigned char pad[0x84];
	Rec8014DD90* p;
};

int fn_8014DD90(Obj8014DD90* o)
{
	Rec8014DD90* t = o->p;
	if (t != 0 && t->f2c != 0) {
		return 8;
	}
	return 0;
}
}
