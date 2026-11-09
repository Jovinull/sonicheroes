// Dispatches header decoding by detected audio container format.

extern "C" {
int ADXB_DecodeHeaderAdx(int a, unsigned short* b, int c);
int ADXB_CheckSpsd(unsigned short* b);
int ADXB_DecodeHeaderSpsd(int a, unsigned short* b, int c);
int ADXB_CheckWav(unsigned short* b);
int ADXB_DecodeHeaderWav(int a, unsigned short* b, int c);
int ADXB_CheckAiff(unsigned short* b);
int ADXB_DecodeHeaderAiff(int a, unsigned short* b, int c);
int ADXB_CheckAu(unsigned short* b);
int ADXB_DecodeHeaderAu(int a, unsigned short* b, int c);

int ADXB_DecodeHeader(int a, unsigned short* b, int c)
{
	if (*b == 0x8000) {
		return ADXB_DecodeHeaderAdx(a, b, c);
	}
	if (ADXB_CheckSpsd(b) != 0) {
		return ADXB_DecodeHeaderSpsd(a, b, c);
	}
	if (ADXB_CheckWav(b) != 0) {
		return ADXB_DecodeHeaderWav(a, b, c);
	}
	if (ADXB_CheckAiff(b) != 0) {
		return ADXB_DecodeHeaderAiff(a, b, c);
	}
	if (ADXB_CheckAu(b) != 0) {
		return ADXB_DecodeHeaderAu(a, b, c);
	}
	return -1;
}
}
