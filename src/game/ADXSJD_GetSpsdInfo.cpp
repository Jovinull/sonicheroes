// Returns the address of the SPSD info block embedded at +0x58.

extern "C" {
int ADXSJD_GetSpsdInfo(int o)
{
	return o + 0x58;
}
}
