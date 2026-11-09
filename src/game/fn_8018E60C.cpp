// Reports the name to the handler unless all four characters are letters or digits.
extern "C" {
extern char lbl_8028FE54[];
void fn_8017C6D4(int a, char* s);

void fn_8018E60C(int a, unsigned char* p)
{
	unsigned char c;
	if ((c = p[0]) < 0x29 || c > 0x7A || (c > 0x5A && c < 0x61) || (c = p[1]) < 0x29 || c > 0x7A
	    || (c > 0x5A && c < 0x61) || (c = p[2]) < 0x29 || c > 0x7A || (c > 0x5A && c < 0x61)
	    || (c = p[3]) < 0x29 || c > 0x7A || (c > 0x5A && c < 0x61)) {
		fn_8017C6D4(a, lbl_8028FE54);
	}
}
}
