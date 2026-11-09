// Packs the RGB color into 0xFFRRGGBB.

extern "C" {
struct Color801A9298 {
	unsigned char r;
	unsigned char g;
	unsigned char b;
	unsigned char a;
};

int fn_801A9298(Color801A9298* c)
{
	return c->b | ((c->r << 16) | 0xff000000 | (c->g << 8));
}
}
