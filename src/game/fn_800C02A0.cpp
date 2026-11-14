// Unregisters the id lbl_8042C428 from the 64-entry table lbl_803042C8 when the control record
// is active (word 0x44 == 1): clears words 0x44/0x48, resets the float at 0x2C to lbl_8042DE54
// and zeroes the first matching table slot. Counterpart of fn_800C0314.
struct Ctl800C02A0 {
	unsigned char pad0[0x2C];
	float f2C;
	unsigned char pad30[0x14];
	int f44;
	int f48;
};

extern "C" {
extern unsigned int lbl_803042C8[];
extern unsigned int lbl_8042C428;
extern Ctl800C02A0* lbl_8042C42C;
extern float lbl_8042DE54;

void fn_800C02A0(void)
{
	Ctl800C02A0* c = lbl_8042C42C;
	int i;
	if (c != 0 && c->f44 == 1) {
		c->f48 = c->f44 = i = 0;
		c->f2C              = lbl_8042DE54;
		{
			unsigned int id = lbl_8042C428;
			for (; i < 0x40; i++) {
				unsigned int v = lbl_803042C8[i];
				if (v == id) {
					lbl_803042C8[i] = 0;
					return;
				}
			}
		}
	}
}
}
