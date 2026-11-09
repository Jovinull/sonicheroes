// Forwards to ADXB_TakeSnapshot with the decoder handle at +4.

extern "C" {
struct ObjADXSJD_TakeSnapshot {
	unsigned char pad[4];
	int f4;
};
void ADXB_TakeSnapshot(int);

void ADXSJD_TakeSnapshot(ObjADXSJD_TakeSnapshot* o)
{
	ADXB_TakeSnapshot(o->f4);
}
}
