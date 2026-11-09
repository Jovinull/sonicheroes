// Returns the index (in 8-byte units) of the cursor at 0x14 relative to fn_8019460C(word 0), or fn_8019469C(word 0) when there is no cursor.

extern "C" {
struct Obj80201318 {
	int f0;
	unsigned char pad[0xc];
	unsigned f10;
	unsigned f14;
};
int fn_8019460C(int);
int fn_8019469C(int);

int fn_80201318(Obj80201318* o)
{
	if (o->f14 != 0) {
		return (int)(o->f14 - fn_8019460C(o->f0)) / 8;
	}
	return fn_8019469C(o->f0);
}
}
