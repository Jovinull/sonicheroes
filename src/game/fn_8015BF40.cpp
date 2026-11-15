// Stores v at +0x3C of the table entry; for v == 0 it uses the object held at +0x54 instead (or 0).

extern "C" {
extern unsigned char* lbl_8042C9A4;
extern int lbl_8042CA80;

unsigned fn_8015BF40(unsigned v)
{
	if (v == 0) {
		unsigned t = *(unsigned*)(lbl_8042C9A4 + lbl_8042CA80 + 0x54);
		if (t != 0) {
			v = t;
		} else {
			v = 0;
		}
	}
	*(unsigned*)(lbl_8042C9A4 + lbl_8042CA80 + 0x3C) = v;
	return v;
}
}
