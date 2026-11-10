// Reads the entries of a table from the stream: each entry's 0x18-byte record, then a 4-byte offset that is turned into a pointer into the same table (rounded to 0x1C-byte elements); returns the header, or 0 on a read error or missing table.
struct Hdr8011BA54 {
	unsigned char pad0[4];
	int f4;
	unsigned char pad8[8];
	char* f10;
};

extern "C" {
unsigned int fn_801937A0(int h, void* dst, int n);
unsigned int fn_80193884(int h, unsigned int* out, int n);

Hdr8011BA54* fn_8011BA54(int h, Hdr8011BA54* o)
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
		*(char**)p = base + (sp8 / 0x1C) * 0x1C;
		p += 0x1C;
		i++;
	}
	return o;
}
}
