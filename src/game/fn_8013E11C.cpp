// Reads the table entries from the stream and rebases each pointer onto the first entry.
struct Entry8013E11C {
	unsigned char* f0;
	unsigned char data[0x20];
};
struct Hdr8013E11C {
	unsigned char pad0[4];
	int f4;
	unsigned char pad8[8];
	Entry8013E11C* f10;
};

extern "C" {
unsigned int fn_801937A0(int a, void* b, int c);
unsigned int fn_80193884(int a, unsigned int* b, int c);

Hdr8013E11C* fn_8013E11C(int a, Hdr8013E11C* h)
{
	unsigned int sp8;
	Entry8013E11C* e;
	int i;
	Entry8013E11C* base = h->f10;
	i                   = 0;
	e                   = base;
	for (; i < h->f4;) {
		if (fn_801937A0(a, e->data, 0x20) == 0) {
			return 0;
		}
		if (fn_80193884(a, &sp8, 4) == 0) {
			return 0;
		}
		i++;
		e->f0 = (unsigned char*)base + (sp8 / 36) * 0x24;
		e++;
	}
	return h;
}
}
