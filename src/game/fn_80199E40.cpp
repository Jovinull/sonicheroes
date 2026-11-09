// Returns whether the string starts with a drive prefix ("X:" with an ASCII letter) or a backslash.

extern "C" {
struct Path80199E40 {
	signed char c0;
	signed char c1;
};

int fn_80199E40(Path80199E40* p)
{
	signed char c;
	if (p->c1 == 0x3a) {
		c = p->c0;
		if ((c >= 0x41 && c <= 0x5a) || (c >= 0x61 && c <= 0x7a)) {
			return 1;
		}
	}
	return (p->c0 == 0x5c) ? 1 : 0;
}
}
