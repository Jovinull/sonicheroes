// Stores a position and/or an angle triple into slot (idx*256 + base - sub) of the two global record tables if the channel idx is active.
struct V3_8003E244 {
	float x;
	float y;
	float z;
};
struct I3_8003E244 {
	int x;
	int y;
	int z;
};

extern "C" {
extern unsigned int lbl_802AD090[];
extern unsigned char lbl_8042C1A8[8];
extern V3_8003E244* lbl_8042C1B0;
extern I3_8003E244* lbl_8042C1B4;

int fn_8003E244(int a, int idx, int sub, V3_8003E244* pos, I3_8003E244* ang)
{
	unsigned char slot = lbl_8042C1A8[idx] - sub;
	if (lbl_802AD090[idx] == 0) {
		return 0;
	}
	if (pos != 0) {
		V3_8003E244* d = (V3_8003E244*)((unsigned char*)lbl_8042C1B0 + (slot + (idx << 8)) * 0xC);
		d->x           = pos->x;
		d->y           = pos->y;
		d->z           = pos->z;
	}
	if (ang != 0) {
		I3_8003E244* d = (I3_8003E244*)((unsigned char*)lbl_8042C1B4 + (slot + (idx << 8)) * 0xC);
		d->x           = ang->x;
		d->y           = ang->y;
		d->z           = ang->z;
	}
	return 1;
}
}
