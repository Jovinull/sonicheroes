// Initialises the ADXB module and clears the 0x9C0-byte decoder pool adxsjd_obj.

extern "C" {
extern unsigned char adxsjd_obj[];
void ADXB_Init(void);
void* memset(void*, int, unsigned);

void ADXSJD_Init(void)
{
	ADXB_Init();
	memset(adxsjd_obj, 0, 0x9c0);
}
}
