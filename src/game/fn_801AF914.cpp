// Switches the alpha compare mode, applying the saved or the default parameters.
struct G801AF914 {
	unsigned char pad0[0x44];
	int f44;
	int f48;
	int f4C;
	int f50;
	unsigned char f54;
	unsigned char f55;
};

extern "C" {
extern G801AF914 lbl_803EDBD0;
void GXSetAlphaCompare(int a, unsigned char b, int c, int d, unsigned char e);
void GXSetZCompLoc(unsigned char v);

void fn_801AF914(int a)
{
	if (lbl_803EDBD0.f44 != a) {
		if (a == 1) {
			GXSetAlphaCompare(7, 0, 0, 7, 0);
		} else {
			GXSetAlphaCompare(lbl_803EDBD0.f48, lbl_803EDBD0.f54, lbl_803EDBD0.f50,
			    lbl_803EDBD0.f4C, lbl_803EDBD0.f55);
		}
		GXSetZCompLoc((unsigned char)a);
		lbl_803EDBD0.f44 = a;
	}
}
}
