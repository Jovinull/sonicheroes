// Returns the address of the 32-byte entry `i` of the table at word 4.

extern "C" {
struct Obj800ECA74 {
	unsigned char pad[4];
	int f4;
};

int fn_800ECA74(Obj800ECA74* o, int i)
{
	return o->f4 + (i << 5);
}
}
