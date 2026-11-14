// Returns 1 when one of the object's players (signed byte count at 0x39, pointers from 0x114) has
// halfword 0x6F0 equal to 0x28 or 0x12, or halfword 0x6F4 equal to 0x3D or 2 with bit 0x1000 of
// halfword 0x6F6 set; otherwise 0.
struct P8009D0E8 {
	unsigned char pad0[0x6F0];
	short f6F0;
	unsigned char pad6F2[0x2];
	short f6F4;
	short f6F6;
};
struct O8009D0E8 {
	unsigned char pad0[0x39];
	signed char count;
	unsigned char pad3A[0x114 - 0x3A];
	P8009D0E8* players[1];
};
extern "C" {
int fn_8009D0E8(O8009D0E8* o)
{
	int i;
	for (i = 0; i < o->count; i++) {
		P8009D0E8* p = o->players[i];
		if (p->f6F0 == 0x28 || (p->f6F4 == 0x3D && (p->f6F6 & 0x1000)) || p->f6F0 == 0x12
		    || (p->f6F4 == 2 && (p->f6F6 & 0x1000))) {
			return 1;
		}
	}
	return 0;
}
}
