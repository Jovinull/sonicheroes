// Zeroes the 0xB4-byte block at lbl_803EC488 and returns 1.

extern "C" {
extern unsigned char lbl_803EC488[];
void* memset(void*, int, unsigned);

int fn_80146BF8()
{
	memset(lbl_803EC488, 0, 0xb4);
	return 1;
}
}
