// Calls fn_8015BA28(key, object) when the word at the object + lbl_8042C91C equals the key; returns the object.

extern "C" {
extern int lbl_8042C91C;
void fn_8015BA28(unsigned, int);

int fn_8015B1A8(int a, unsigned key)
{
	unsigned* t = (unsigned*)(a + lbl_8042C91C);
	if (t != 0 && key == *t) {
		fn_8015BA28(key, a);
	}
	return a;
}
}
