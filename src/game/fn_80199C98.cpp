// Finds the first occurrence of the character in the string, including the terminator.
extern "C" {
char* fn_80199C98(char* s, int c)
{
	char* last;
	signed char t;
	signed char cc;
	cc   = (signed char)c;
	last = 0;
	do {
		t = *s;
		if (t == cc) {
			last = s;
			break;
		}
		s++;
	} while (t != 0);
	return last;
}
}
