// Returns the default pan of channel k from the decoder (handle at +4) when it has AINF data and the state at +1 is 2 or 3; -0x80 otherwise.

extern "C" {
struct Obj_ADXSJD_GetDefPan {
	unsigned char pad0;
	signed char c1;
	unsigned char pad2[2];
	int f4;
};
int ADXB_GetAinfLen(int);
int ADXB_GetDefPan(int, int);

int ADXSJD_GetDefPan(Obj_ADXSJD_GetDefPan* o, int k)
{
	if (ADXB_GetAinfLen(o->f4) > 0 && (o->c1 == 2 || o->c1 == 3)) {
		return ADXB_GetDefPan(o->f4, k);
	}
	return -0x80;
}
}
