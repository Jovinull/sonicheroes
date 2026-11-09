// Clears the collision info: resets the counter at +2 and low flag bits at +8, drops bit 4 of the byte at +3 of each header entry (count at +0xA, 0x30 bytes each from +0x10), and resets the eight 8-byte slots at +0x14.

extern "C" {
struct Slot7C_COLLI {
	signed char b0;
	signed char b1;
	unsigned short s2;
	int f4;
};
struct Head7C_COLLI {
	unsigned char pad[3];
	unsigned char c3;
	unsigned char pad1[0x2c];
};
struct Info7C_COLLI {
	unsigned char pad[2];
	unsigned short s2;
	unsigned char pad1[4];
	unsigned short s8;
	unsigned short sa;
	unsigned char pad2[4];
	Head7C_COLLI* f10;
	Slot7C_COLLI e[8];
};

void ClearInfo__7C_COLLIFv(Info7C_COLLI* o)
{
	Slot7C_COLLI* p;
	Slot7C_COLLI* end;
	Head7C_COLLI* h;
	unsigned short n;
	p     = o->e;
	end   = (Slot7C_COLLI*)((unsigned char*)o + 0x54);
	o->s2 = 0;
	o->s8 = o->s8 & ~0x13f;
	n     = o->sa;
	h     = o->f10;
	while (n-- != 0) {
		h->c3 = h->c3 & ~0x10;
		h++;
	}
	while (p != end) {
		p->s2 = p->s2 & ~3;
		p->b0 = -1;
		p->b1 = -1;
		p->f4 = 0;
		p++;
	}
}
}
