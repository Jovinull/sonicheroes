// Returns the default output volume from the decoder (handle at +4) when it has AINF data and the state at +1 is 2 or 3; 0 otherwise.

extern "C" {
struct Obj_ADXSJD_GetDefOutVol {
	unsigned char pad0;
	signed char c1;
	unsigned char pad2[2];
	int f4;
};
int ADXB_GetAinfLen(int);
int ADXB_GetDefOutVol(int);

int ADXSJD_GetDefOutVol(Obj_ADXSJD_GetDefOutVol* o)
{
	if (ADXB_GetAinfLen(o->f4) > 0 && (o->c1 == 2 || o->c1 == 3)) {
		return ADXB_GetDefOutVol(o->f4);
	}
	return 0;
}
}
