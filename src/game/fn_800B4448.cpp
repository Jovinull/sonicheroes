// Retags every matching entry of the 0x2B-entry table: sets its value and swaps the flag bits.
struct Ent800B4448 {
	unsigned char pad0[0xC];
	unsigned int fC;
	short f10;
	unsigned char pad12[6];
	unsigned short f18;
	unsigned char pad1A[2];
	unsigned int f1C;
	unsigned char pad20[0x18];
};

extern "C" {
void fn_800B4448(char* base, unsigned short key, unsigned int tag, short v)
{
	int i;
	Ent800B4448* e = (Ent800B4448*)(base + 8);
	for (i = 0; i < 0x2B; i++, e++) {
		if (e->f1C == tag && (e->f18 == key || key == 0)) {
			e->f10 = v;
			e->fC  = e->fC & 0xFFFFFEFF;
			e->fC  = e->fC | 0x200;
		}
	}
}
}
