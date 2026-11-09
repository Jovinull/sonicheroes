// Initialises the ADXPD decoder, bumps the module counter lbl_80410488 and clears the 0xD80-byte decoder pool adxb_obj.

extern "C" {
void ADXPD_Init(void);
void* memset(void*, int, unsigned);
extern unsigned char adxb_obj[];
extern int lbl_80410488[];

void ADXB_Init(void)
{
	int* p;
	int t;
	ADXPD_Init();
	p  = lbl_80410488;
	t  = *p;
	*p = t + 1;
	memset(adxb_obj, 0, 0xd80);
}
}
