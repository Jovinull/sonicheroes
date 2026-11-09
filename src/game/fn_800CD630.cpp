// Initializes the ADX audio library (DVD filesystem, thread setup, ADXT init) and records the two embedded sound banks (start and end addresses) in lbl_8042B62C and lbl_8042B63C.

extern "C" {
void ADXGC_SetupDvdFs(int);
void ADXM_SetupThrd(int);
void ADXT_Init();
extern unsigned char lbl_8030707C[];
extern unsigned char lbl_80378444[];
struct Bank800CD630 {
	void* a;
	void* b;
};
extern Bank800CD630 lbl_8042B62C;
extern Bank800CD630 lbl_8042B63C;
extern signed char lbl_8042B644;

void fn_800CD630()
{
	ADXGC_SetupDvdFs(0);
	ADXM_SetupThrd(0);
	ADXT_Init();
	lbl_8042B62C.a = lbl_8030707C;
	lbl_8042B62C.b = lbl_8030707C + 0x389e4;
	lbl_8042B63C.a = lbl_80378444;
	lbl_8042B63C.b = lbl_80378444 + 0x17124;
	lbl_8042B644   = -1;
}
}
