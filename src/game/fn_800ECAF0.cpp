// Copies the float at +0x60 of the indexed record into the output when the slot's header flags (low 2 bits) are set; returns whether it did.
struct Hdr800ECAF0 {
	unsigned char pad0[6];
	short f6;
};
struct Src800ECAF0 {
	unsigned char pad0[0x60];
	float f60;
};

extern "C" {
extern Hdr800ECAF0* lbl_802AD090[];
extern Src800ECAF0* lbl_802AD0D0[];

int fn_800ECAF0(int i, float* out)
{
	Hdr800ECAF0* h = lbl_802AD090[i];
	Src800ECAF0* s = lbl_802AD0D0[i];
	if (h == 0) {
		return 0;
	}
	if ((h->f6 & 3) != 0) {
		*out = s->f60;
	} else {
		return 0;
	}
	return 1;
}
}
