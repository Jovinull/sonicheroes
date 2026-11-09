// Loads three files named from the format strings lbl_80242500 / 80242514 / 8024252C with arg1 through fn_8004B920 into lbl_8042C150/54/58; returns 0 when the first fails, else 1.

extern "C" {
int sprintf(char*, const char*, ...);
unsigned fn_8004B920(int, char*);
extern char lbl_80242500[];
extern char lbl_80242514[];
extern char lbl_8024252C[];
extern unsigned lbl_8042C150;
extern unsigned lbl_8042C154;
extern unsigned lbl_8042C158;

int fn_8004B9D4(int a, int b)
{
	char sp8[0x100];
	unsigned t;
	sprintf(sp8, lbl_80242500, b);
	t            = fn_8004B920(a, sp8);
	lbl_8042C150 = t;
	if (t == 0) {
		return 0;
	}
	sprintf(sp8, lbl_80242514, b);
	lbl_8042C154 = fn_8004B920(a, sp8);
	sprintf(sp8, lbl_8024252C, b);
	lbl_8042C158 = fn_8004B920(a, sp8);
	return 1;
}
}
