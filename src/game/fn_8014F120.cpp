// Returns 8 when the record the object points to at 0x6c exists and has a non-zero word at 0x2C, otherwise 0.

extern "C" {
struct Rec8014F120 {
	unsigned char pad[0x2c];
	unsigned f2c;
};
struct Obj8014F120 {
	unsigned char pad[0x6c];
	Rec8014F120* p;
};

int fn_8014F120(Obj8014F120* o)
{
	Rec8014F120* t = o->p;
	if (t != 0 && t->f2c != 0) {
		return 8;
	}
	return 0;
}
}
