// Returns the index (in 8-byte units) of the cursor at 0x10 relative to fn_8019460C(word 0), or -1 when there is no cursor.

extern "C" {
struct Obj802012C4 {
	int f0;
	unsigned char pad[0xc];
	unsigned f10;
	unsigned f14;
};
int fn_8019460C(int);

int fn_802012C4(Obj802012C4* o)
{
	if (o->f10 != 0) {
		return (int)(o->f10 - fn_8019460C(o->f0)) / 8;
	}
	return -1;
}
}
