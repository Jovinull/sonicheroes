// Calls fn_8015BE24(key, object) when the word at the object + lbl_8042C924 equals the key; returns the object.

extern "C" {
extern int lbl_8042C924;
void fn_8015BE24(unsigned, int);

int fn_8015B230(int a, unsigned key)
{
	unsigned* t = (unsigned*)(a + lbl_8042C924);
	if (t != 0 && key == *t) {
		fn_8015BE24(key, a);
	}
	return a;
}
}
