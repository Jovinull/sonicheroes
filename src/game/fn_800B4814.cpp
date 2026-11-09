// For each of the 43 records (0x38 bytes from +8) whose word at 0x1C equals the key, clears its halfword at 0x12, sets bit 2 and clears bit 14 of its flags word at 0xC.

extern "C" {
struct Rec800B4814 {
	unsigned char pad[0xc];
	int fc;
	unsigned char pad1[2];
	short s12;
	unsigned char pad2[4];
	unsigned short f18;
	unsigned char pad3[2];
	unsigned f1c;
	unsigned char pad4[0x38 - 0x20];
};

void fn_800B4814(int base, unsigned key)
{
	signed char i  = 0;
	Rec800B4814* p = (Rec800B4814*)(base + 8);
	for (; i < 0x2b; p++, i++) {
		if (p->f1c == key) {
			p->s12 = 0;
			p->fc |= 4;
			p->fc &= 0xFFFFBFFF;
		}
	}
}
}
