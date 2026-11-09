// Unpacks the RGB565 value into the color, alpha 0xFF.

extern "C" {
struct Color801A94F0 {
	unsigned char r;
	unsigned char g;
	unsigned char b;
	unsigned char a;
};

void fn_801A94F0(Color801A94F0* c, unsigned v)
{
	c->r = (v >> 8) & 0xf8;
	c->g = (v >> 3) & 0xfc;
	c->b = (v << 3) & 0xf8;
	c->a = 0xff;
}
}
