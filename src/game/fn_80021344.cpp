// Copies the vector at +0x54 into the output when bit 2 of the flag word is set; returns whether it did.
struct Src80021344 {
	unsigned char pad0[8];
	unsigned short f8;
	unsigned char padA[0x4A];
	float f54;
	float f58;
	float f5C;
};
struct Vec80021344 {
	float x;
	float y;
	float z;
};

extern "C" {
int fn_80021344(Src80021344* s, Vec80021344* v)
{
	if ((s->f8 & 4) == 0) {
		return 0;
	}
	v->x = s->f54;
	v->y = s->f58;
	v->z = s->f5C;
	return 1;
}
}
