// Unpacks a 16-bit colour (RGB555 with alpha flag 0x8000, otherwise RGB4443 with a 3-bit alpha) into four bytes.

extern "C" {
struct Color801A9564 {
	unsigned char b0;
	unsigned char b1;
	unsigned char b2;
	unsigned char b3;
};

void fn_801A9564(Color801A9564* o, unsigned v)
{
	if (v & 0x8000) {
		o->b0 = (v >> 7) & 0xf8;
		o->b1 = (v >> 2) & 0xf8;
		o->b2 = (v * 8) & 0xf8;
		o->b3 = 0xff;
		return;
	}
	o->b0 = (v >> 4) & 0xf0;
	o->b1 = v & 0xf0;
	o->b2 = (v * 0x10) & 0xf0;
	o->b3 = (v >> 7) & 0xe0;
}
}
