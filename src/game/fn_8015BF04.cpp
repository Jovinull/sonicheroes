// Stores v at +0x40 of the table entry; for v == 0 it uses the object held at +0x58 instead (or 0).

extern "C" {
extern int lbl_8042C9A4;
extern int lbl_8042CA80;

void fn_8015BF04(unsigned v)
{
	if (v == 0) {
		unsigned t = *(unsigned*)(lbl_8042C9A4 + lbl_8042CA80 + 0x58);
		if (t != 0) {
			v = t;
		} else {
			v = 0;
		}
	}
	*(unsigned*)(lbl_8042C9A4 + lbl_8042CA80 + 0x40) = v;
}
}
