// Resets the three-word record at base + lbl_8042C868: words 0 and 8 cleared, word 4 set to
// lbl_8042F2B0. Returns base unchanged.
struct Rec80149E54 {
	int f0;
	float f4;
	int f8;
};

extern "C" {
extern int lbl_8042C868;
extern float lbl_8042F2B0;

unsigned char* fn_80149E54(unsigned char* base)
{
	Rec80149E54* r = (Rec80149E54*)(base + lbl_8042C868);
	r->f0          = 0;
	r->f4          = lbl_8042F2B0;
	r->f8          = 0;
	return base;
}
}
