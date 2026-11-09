// Clears the first halfword of the first argument and the halfword at 0x18 of the third, then calls fn_800474C4 with the same arguments.

extern "C" {
struct Obj80047B14 {
	unsigned char pad[0x18];
	short s18;
};
void fn_800474C4(short*, int, Obj80047B14*);

void fn_80047B14(short* a, int b, Obj80047B14* c)
{
	*a     = 0;
	c->s18 = 0;
	fn_800474C4(a, b, c);
}
}
