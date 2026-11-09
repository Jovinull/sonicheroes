// Stops the stopwatch at 0x138 of the object and clears the first word of lbl_803E73B0.

extern "C" {
extern int lbl_803E73B0[];
void OSStopStopwatch(void*);

void fn_80112618(unsigned char* o)
{
	OSStopStopwatch(o + 0x138);
	lbl_803E73B0[0] = 0;
}
}
