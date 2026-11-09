// Initializes an MD5 context: zeroes the 64-bit bit count and loads the four
// standard chaining constants.

extern "C" {
struct Md5Ctx8012316C {
	unsigned lo;
	unsigned hi;
	unsigned a;
	unsigned b;
	unsigned c;
	unsigned d;
};

void fn_8012316C(Md5Ctx8012316C* c)
{
	c->lo = 0;
	c->hi = 0;
	c->a  = 0x67452301;
	c->b  = 0xEFCDAB89;
	c->c  = 0x98BADCFE;
	c->d  = 0x10325476;
}
}
