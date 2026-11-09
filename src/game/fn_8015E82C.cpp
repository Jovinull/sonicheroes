// When flag 0x01000000 of the word at 8 is set and a linked record is held at 0x58, returns its word 8 minus 7; otherwise 0.

extern "C" {
struct Linked8015E82C {
	unsigned char pad[8];
	int f8;
};
struct Obj8015E82C {
	unsigned char pad[8];
	unsigned f8;
	unsigned char pad1[0x58 - 0xc];
	Linked8015E82C* f58;
};

int fn_8015E82C(Obj8015E82C* o)
{
	Linked8015E82C* t;
	if (o->f8 & 0x01000000) {
		t = o->f58;
		if (t != 0) {
			return t->f8 - 7;
		}
	}
	return 0;
}
}
