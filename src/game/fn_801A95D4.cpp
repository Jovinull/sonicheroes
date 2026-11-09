// Unpacks 0xAARRGGBB into the color.

extern "C" {
struct Color801A95D4 {
	unsigned char r;
	unsigned char g;
	unsigned char b;
	unsigned char a;
};

void fn_801A95D4(Color801A95D4* c, unsigned v)
{
	c->a = v >> 24;
	c->r = v >> 16;
	c->g = v >> 8;
	c->b = v;
}
}
