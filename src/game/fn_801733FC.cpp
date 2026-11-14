// Copies a 0x40-byte block (four rows of four words) into the object at 0x0C and sets flag bit 2.
struct M801733FC {
	unsigned int w[16];
};
struct O801733FC {
	unsigned char pad0[0x8];
	unsigned int flags;
	M801733FC m;
};
extern "C" {
void fn_801733FC(O801733FC* o, M801733FC* m)
{
	o->m = *m;
	o->flags |= 2;
}
}
