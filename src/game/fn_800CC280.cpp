// Stops and unpauses the ADX stream of the music object in lbl_8042B624, resets its queued entry and clears its state.

extern "C" {
struct Entry800CC280 {
	signed char f0;
	unsigned char pad[7];
	int f8;
};
struct Music800CC280 {
	unsigned char pad[0x29];
	signed char c29;
	unsigned char pad1;
	unsigned char b2b;
	unsigned char pad2[0x44 - 0x2c];
	int f44;
	unsigned char pad3[0x4c - 0x48];
	Entry800CC280* f4c;
};
extern Music800CC280* lbl_8042B624;
void ADXT_Stop(int);
void ADXT_Pause(int, int);
void ADXT_ResetEntry(int);

void fn_800CC280()
{
	Music800CC280* b = lbl_8042B624;
	Entry800CC280* c;
	if (b != 0) {
		ADXT_Stop(b->f44);
		ADXT_Pause(b->f44, 0);
		c = b->f4c;
		if (c != 0) {
			ADXT_ResetEntry(c->f8);
			c->f0 = -1;
		}
		b->c29 = 0;
		b->b2b &= ~1;
	}
}
}
