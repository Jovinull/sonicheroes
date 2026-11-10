// Returns the float stored in slot idx of the pointer table lbl_803EB3F8, or the default when the slot is empty.
extern "C" {
extern float* lbl_803EB3F8[];
extern float lbl_8042EF38;

float fn_80132958(int idx)
{
	float* p = lbl_803EB3F8[idx];
	if (p == 0) {
		return lbl_8042EF38;
	}
	return *p;
}
}
