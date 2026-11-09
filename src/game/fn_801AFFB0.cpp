// Applies the previous alpha compare mode, then stores the new one.
struct G801AFFB0 {
	unsigned char pad0[0x44];
	int f44;
	int f48;
	int f4C;
	int f50;
	unsigned char f54;
	unsigned char f55;
};

extern "C" {
extern G801AFFB0 lbl_803EDBD0;
void GXSetAlphaCompare(int a, unsigned char b, int c, int d, unsigned char e);

void fn_801AFFB0(int a, unsigned char b, int c, int d, unsigned char e)
{
	if (lbl_803EDBD0.f44 != 1) {
		GXSetAlphaCompare(lbl_803EDBD0.f48, lbl_803EDBD0.f54, lbl_803EDBD0.f50, lbl_803EDBD0.f4C,
		    lbl_803EDBD0.f55);
	}
	lbl_803EDBD0.f48 = a;
	lbl_803EDBD0.f54 = b;
	lbl_803EDBD0.f50 = c;
	lbl_803EDBD0.f4C = d;
	lbl_803EDBD0.f55 = e;
}
}
