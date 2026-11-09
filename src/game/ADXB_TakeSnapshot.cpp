// Saves the ADXPD decoder delay (+0xA8/+0xAC) and extension parameters (+0xA2/+0xA4/+0xA6).

extern "C" {
struct Obj_ADXB_TakeSnapshot {
	unsigned char pad[8];
	int f8;
	unsigned char pad1[0x96];
	short sa2;
	short sa4;
	short sa6;
	int fa8;
	int fac;
};
void ADXPD_GetDly(int, void*, void*);
void ADXPD_GetExtPrm(int, void*, void*, void*);

void ADXB_TakeSnapshot(Obj_ADXB_TakeSnapshot* o)
{
	ADXPD_GetDly(o->f8, &o->fa8, &o->fac);
	ADXPD_GetExtPrm(o->f8, &o->sa2, &o->sa4, &o->sa6);
}
}
