// Stores four signed bytes at 0x3C..0x3F of the record (the fourth first).

extern "C" {
struct Rec80136C10 {
	unsigned char pad[0x3c];
	signed char b3c;
	signed char b3d;
	signed char b3e;
	signed char b3f;
};

void fn_80136C10(Rec80136C10* o, signed char a, signed char b, signed char c, signed char d)
{
	o->b3f = d;
	o->b3c = a;
	o->b3d = b;
	o->b3e = c;
}
}
