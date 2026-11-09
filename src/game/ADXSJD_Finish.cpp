// Clears the 0x9C0-byte decoder pool adxsjd_obj.

extern "C" {
extern unsigned char adxsjd_obj[];
void* memset(void*, int, unsigned);

void ADXSJD_Finish(void)
{
	memset(adxsjd_obj, 0, 0x9c0);
}
}
