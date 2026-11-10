// Converts the lowercase ASCII letters of the string to uppercase in place and returns it.
extern "C" {
char* fn_80199C18(char* s)
{
	char* p;
	unsigned char c;
	if (s == 0) {
		return s;
	}
	p = s;
	while ((signed char)(c = *p) != 0) {
		if ((signed char)c >= 0x61 && (signed char)c <= 0x7A) {
			*p = c - 0x20;
		}
		p++;
	}
	return s;
}
}
