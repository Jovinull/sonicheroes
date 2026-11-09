// Picks the filter string for the current mode lbl_8042C628 (0..4) and, if arg0's text at +0x10 contains it, remembers arg0 in lbl_8042C624; returns arg0.

extern "C" {
extern int lbl_8042C628;
extern int lbl_8042C624;
extern unsigned char lbl_8042B7FC[4];
extern unsigned char lbl_8042B800[4];
extern unsigned char lbl_8042B804[4];
extern unsigned char lbl_8042B808[4];
char* strstr(const char*, const char*);

int fn_80112F9C(int a)
{
	unsigned char* s = 0;
	switch (lbl_8042C628) {
		case 0:
			s = lbl_8042B7FC;
			break;
		case 1:
		case 2:
			s = lbl_8042B800;
			break;
		case 4:
			s = lbl_8042B804;
			break;
		case 3:
			s = lbl_8042B808;
			break;
	}
	if (s == 0) {
		return a;
	}
	if (strstr((char*)(a + 0x10), (char*)s) != 0) {
		lbl_8042C624 = a;
	}
	return a;
}
}
