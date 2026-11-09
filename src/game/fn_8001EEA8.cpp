// Keeps the low 24 bits of the words at 0x2C and 0x30 and clears word 0x28.

extern "C" {
struct Obj8001EEA8 {
	unsigned char pad[0x28];
	int f28;
	unsigned f2c;
	unsigned f30;
};

void fn_8001EEA8(Obj8001EEA8* o)
{
	o->f2c &= 0xffffff;
	o->f30 &= 0xffffff;
	o->f28 = 0;
}
}
