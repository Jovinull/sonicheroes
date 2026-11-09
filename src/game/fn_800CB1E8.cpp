// Stops and unpauses the ADX stream of music slot i (0 or 1) and resets its state fields.

extern "C" {
struct Slot800CB1E8 {
	unsigned char pad[0x29];
	signed char c29;
	signed char b2a;
	unsigned char b2b;
	int f2c;
	int f30;
	unsigned char pad1[0x3c - 0x34];
	int f3c;
};
extern Slot800CB1E8* lbl_8042B634[2];
void ADXT_Stop(int);
void ADXT_Pause(int, int);

void fn_800CB1E8(int i)
{
	Slot800CB1E8* a;
	if (i >= 0 && i < 2) {
		a = lbl_8042B634[i];
		ADXT_Stop(a->f3c);
		ADXT_Pause(a->f3c, 0);
		a->f2c = -1;
		a->f30 = -1;
		a->b2a = -1;
		a->c29 = 0;
		a->b2b &= ~1;
	}
}
}
