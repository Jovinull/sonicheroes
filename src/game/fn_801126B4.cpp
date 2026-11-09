// Starts the stopwatch embedded at 0x138 of the object (init, reset, start) and sets lbl_803E73B0 when the object's first word is 0.

extern "C" {
void OSInitStopwatch(void*, const void*);
void OSResetStopwatch(void*);
void OSStartStopwatch(void*);
extern unsigned char lbl_80288B94[];
extern int lbl_803E73B0[];

void fn_801126B4(int* o)
{
	OSInitStopwatch(o + 0x4e, lbl_80288B94);
	OSResetStopwatch(o + 0x4e);
	OSStartStopwatch(o + 0x4e);
	if (*o == 0) {
		lbl_803E73B0[0] = 1;
	}
}
}
