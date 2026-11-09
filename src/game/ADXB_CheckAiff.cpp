// Returns 1 when the header starts with the FORM marker (lbl_8023D6E8) and has the AIFF marker (lbl_8023D6F0) at +8.

extern "C" {
int memcmp(const void*, const void*, unsigned);
extern unsigned char lbl_8023D6E8[];
extern unsigned char lbl_8023D6F0[];

int ADXB_CheckAiff(unsigned char* p)
{
	if (memcmp(p, lbl_8023D6E8, 4) == 0 && memcmp(p + 8, lbl_8023D6F0, 4) == 0) {
		return 1;
	}
	return 0;
}
}
