// Registers the id lbl_8042C404 in the first free slot of the 64-entry table lbl_803042C8, marks the record active and sets its float at +0x4C.
struct Ctl800C1978 {
	unsigned char pad0[0x48];
	int f48;
	float f4C;
};

extern "C" {
extern unsigned int lbl_803042C8[];
extern unsigned int lbl_8042C404;
extern Ctl800C1978* lbl_8042C40C;
extern float lbl_8042DE54;

static inline void AddId800C1978(unsigned int id)
{
	int i;
	for (i = 0; i < 0x40; i++) {
		unsigned int v = lbl_803042C8[i];
		if (v == 0) {
			lbl_803042C8[i] = id;
			break;
		}
	}
}

void fn_800C1978()
{
	Ctl800C1978* c = lbl_8042C40C;
	if (c != 0 && c->f48 == 0) {
		c->f48 = 1;
		AddId800C1978(lbl_8042C404);
		c->f4C = lbl_8042DE54;
	}
}
}
