// Unpacks the RGB555 value into the color (low 3 bits dropped), alpha 0xFF.

extern "C" {
struct Color801A94CC {
	unsigned char r;
	unsigned char g;
	unsigned char b;
	unsigned char a;
};

void fn_801A94CC(Color801A94CC* c, unsigned v)
{
	c->r = (v >> 7) & 0xf8;
	c->g = (v >> 2) & 0xf8;
	c->b = (v << 3) & 0xf8;
	c->a = 0xff;
}
}
