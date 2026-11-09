// Returns 1 when the header starts with the SPSD marker (lbl_8023DF90).

extern "C" {
int memcmp(const void*, const void*, unsigned);
extern unsigned char lbl_8023DF90[];

int ADXB_CheckSpsd(void* p)
{
	return (memcmp(p, lbl_8023DF90, 4) == 0) ? 1 : 0;
}
}
