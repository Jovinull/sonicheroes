// Returns 1 when the header starts with either AU marker (lbl_8023D6F8 / lbl_8023D700).

extern "C" {
int memcmp(const void*, const void*, unsigned);
extern unsigned char lbl_8023D6F8[];
extern unsigned char lbl_8023D700[];

int ADXB_CheckAu(unsigned char* p)
{
	if (memcmp(p, lbl_8023D6F8, 4) == 0 || memcmp(p, lbl_8023D700, 4) == 0) {
		return 1;
	}
	return 0;
}
}
