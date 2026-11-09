// Forwards to ADXB_RestoreSnapshot with the decoder handle at +4.

extern "C" {
struct ObjADXSJD_RestoreSnapshot {
	unsigned char pad[4];
	int f4;
};
void ADXB_RestoreSnapshot(int);

void ADXSJD_RestoreSnapshot(ObjADXSJD_RestoreSnapshot* o)
{
	ADXB_RestoreSnapshot(o->f4);
}
}
