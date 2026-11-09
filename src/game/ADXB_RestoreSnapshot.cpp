// Restores the delay (+0xA8/+0xAC) and extension parameters (+0xA2/+0xA4/+0xA6) into the ADXPD decoder.

extern "C" {
struct Obj_ADXB_RestoreSnapshot {
	unsigned char pad[8];
	int f8;
	unsigned char pad1[0x96];
	short sa2;
	short sa4;
	short sa6;
	int fa8;
	int fac;
};
void ADXPD_SetDly(int, void*, void*);
void ADXPD_SetExtPrm(int, int, int, int);

void ADXB_RestoreSnapshot(Obj_ADXB_RestoreSnapshot* o)
{
	ADXPD_SetDly(o->f8, &o->fa8, &o->fac);
	ADXPD_SetExtPrm(o->f8, o->sa2, o->sa4, o->sa6);
}
}
