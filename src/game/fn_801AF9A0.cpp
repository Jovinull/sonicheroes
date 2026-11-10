// Updates the alpha compare mode from the selected entry flag.
struct G801AF9A0 {
	unsigned char pad0[0x44];
	int f44;
	int f48;
	int f4C;
	int f50;
	unsigned char f54;
	unsigned char f55;
};

extern "C" {
extern G801AF9A0 lbl_803EDBD0;
extern int lbl_8042CA48;
extern unsigned int* lbl_8042CA54;
void GXSetAlphaCompare(int a, unsigned char b, int c, int d, unsigned char e);
void GXSetZCompLoc(unsigned char v);
void fn_801B1D0C(unsigned int* p, int a);

void fn_801AF9A0()
{
	int t;
	if (*lbl_8042CA54 != 0) {
		fn_801B1D0C(lbl_8042CA54, 0);
		int a = lbl_8042CA48;
		int b = *lbl_8042CA54;
		t     = (((unsigned int*)(b + a))[0x14 / 4] & 1) ^ 1;
		if (lbl_803EDBD0.f44 != t) {
			if (t == 1) {
				GXSetAlphaCompare(7, 0, 0, 7, 0);
			} else {
				GXSetAlphaCompare(lbl_803EDBD0.f48, lbl_803EDBD0.f54, lbl_803EDBD0.f50,
				    lbl_803EDBD0.f4C, lbl_803EDBD0.f55);
			}
			GXSetZCompLoc((unsigned char)t);
			lbl_803EDBD0.f44 = t;
		}
	}
}
}
