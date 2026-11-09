// Returns 1 when the header starts with the RIFF marker (lbl_8023D6D8) and has the WAVE marker (lbl_8023D6E0) at +8.

extern "C" {
int memcmp(const void*, const void*, unsigned);
extern unsigned char lbl_8023D6D8[];
extern unsigned char lbl_8023D6E0[];

int ADXB_CheckWav(unsigned char* p)
{
	if (memcmp(p, lbl_8023D6D8, 4) == 0 && memcmp(p + 8, lbl_8023D6E0, 4) == 0) {
		return 1;
	}
	return 0;
}
}
