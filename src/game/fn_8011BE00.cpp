// Same table reader as fn_8011BA54, but a negative offset leaves the entry's pointer null instead of pointing into the table.
struct Hdr8011BE00 {
	unsigned char pad0[4];
	int f4;
	unsigned char pad8[8];
	char* f10;
};

extern "C" {
unsigned int fn_801937A0(int h, void* dst, int n);
unsigned int fn_80193884(int h, unsigned int* out, int n);

Hdr8011BE00* fn_8011BE00(int h, Hdr8011BE00* o)
{
	unsigned int sp8;
	char* p;
	char* base;
	int i;
	base = o->f10;
	if (base == 0) {
		return 0;
	}
	i = 0;
	p = base;
	while (i < o->f4) {
		if (fn_801937A0(h, p + 4, 0x18) == 0) {
			return 0;
		}
		if (fn_80193884(h, &sp8, 4) == 0) {
			return 0;
		}
		if ((int)sp8 >= 0) {
			*(char**)p = base + (sp8 / 0x1C) * 0x1C;
		} else {
			*(char**)p = 0;
		}
		p += 0x1C;
		i++;
	}
	return o;
}
}
