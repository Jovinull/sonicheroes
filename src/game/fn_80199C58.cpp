// Converts the uppercase ASCII letters of the string to lowercase in place and returns it.
extern "C" {
char* fn_80199C58(char* s)
{
	char* p;
	unsigned char c;
	if (s == 0) {
		return s;
	}
	p = s;
	while ((signed char)(c = *p) != 0) {
		if ((signed char)c >= 0x41 && (signed char)c <= 0x5A) {
			*p = c + 0x20;
		}
		p++;
	}
	return s;
}
}
