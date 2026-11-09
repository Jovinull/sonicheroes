// Clears the slot (fn_8015BF40(0)) and, if the table entry at +0x54 holds an object, releases it (fn_801B3A10) and clears the entry.

extern "C" {
extern int lbl_8042C9A4;
extern int lbl_8042CA80;
void fn_8015BF40(unsigned);
void fn_801B3A10(unsigned);

void fn_8015CB68()
{
	fn_8015BF40(0);
	if (*(unsigned*)(lbl_8042C9A4 + lbl_8042CA80 + 0x54) != 0) {
		fn_801B3A10(*(unsigned*)(lbl_8042C9A4 + lbl_8042CA80 + 0x54));
		*(unsigned*)(lbl_8042C9A4 + lbl_8042CA80 + 0x54) = 0;
	}
}
}
