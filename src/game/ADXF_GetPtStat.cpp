// Forwards to ADXF_GetPtStatEx with the same arguments and returns its result.

extern "C" {
int ADXF_GetPtStatEx(int, int, int);

int ADXF_GetPtStat(int a, int b, int c)
{
	return ADXF_GetPtStatEx(a, b, c);
}
}
