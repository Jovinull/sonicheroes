// Writes the value into the linked record (field 0xC or 0x2C, chosen by flags 0x10000 / 0x20000) and into 0x60 of the object; returns whether it did.

extern "C" {
struct Linked8005FD34 {
	unsigned char pad[0xc];
	int fc;
	unsigned char pad1[0x2c - 0x10];
	int f2c;
};
struct Obj8005FD34 {
	unsigned char pad[0x2c];
	int f2c;
	unsigned char pad1[0x54 - 0x30];
	Linked8005FD34* f54;
	unsigned char pad2[4];
	int f5c;
	int f60;
};

int fn_8005FD34(Obj8005FD34* o, int v)
{
	Linked8005FD34* t = o->f54;
	int fl;
	if (t == 0) {
		return 0;
	}
	fl = o->f2c;
	if ((fl & 0x10000) != 0) {
		t->fc  = v;
		o->f60 = v;
		return 1;
	}
	if ((fl & 0x20000) != 0) {
		t->f2c = v;
		o->f60 = v;
		return 1;
	}
	return 0;
}
}
