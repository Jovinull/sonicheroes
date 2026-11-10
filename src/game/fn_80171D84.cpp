// Reads a 0x10-byte header from the handle and, when its type word is 1, lets fn_80171BFC process the object; returns the (possibly updated) object, or 0 when the header read fails.

extern "C" {
unsigned fn_801979AC(int, int*, int);
void fn_80193270(int*, int);
int fn_80171BFC(int, int*, int);

int fn_80171D84(int a, int h)
{
	int sp8[4];
	if (fn_801979AC(h, sp8, 0x10) != 0x10) {
		return 0;
	}
	fn_80193270(sp8, 0x10);
	switch (sp8[0]) {
		case 1:
			a = fn_80171BFC(a, sp8, h);
			break;
		default:
			break;
	}
	return a;
}
}
