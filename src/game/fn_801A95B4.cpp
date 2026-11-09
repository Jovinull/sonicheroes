// Unpacks 0x00RRGGBB into the color, alpha 0xFF.

extern "C" {
struct Color801A95B4 {
	unsigned char r;
	unsigned char g;
	unsigned char b;
	unsigned char a;
};

void fn_801A95B4(Color801A95B4* c, unsigned v)
{
	c->a = 0xff;
	c->r = v >> 16;
	c->g = v >> 8;
	c->b = v;
}
}
