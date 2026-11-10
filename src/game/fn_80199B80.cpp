// Case-insensitive comparison of two C strings.
extern "C" {
int fn_80199B80(const unsigned char* a, const unsigned char* b)
{
	signed char c1;
	signed char c2;
	if (a != 0 && b != 0) {
		do {
			c1 = *a;
			c2 = *b;
			if (c1 >= 0x41 && c1 <= 0x5A) {
				c1 += 0x20;
			}
			if (c2 >= 0x41 && c2 <= 0x5A) {
				c2 += 0x20;
			}
			if (c1 != c2) {
				return c1 - c2;
			}
			a++;
			b++;
			if (c1 == 0 || c2 == 0) {
				if (c1 != c2) {
					return c1 - c2;
				}
				break;
			}
		} while (1);
	}
	return 0;
}
}
