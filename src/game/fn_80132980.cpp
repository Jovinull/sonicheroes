// Stores the float into slot idx of the pointer table lbl_803EB3F8 and returns 1, or returns 0 when the slot is empty.
extern "C" {
extern float* lbl_803EB3F8[];

int fn_80132980(int idx, float v)
{
	float* p = lbl_803EB3F8[idx];
	if (p == 0) {
		return 0;
	}
	*p = v;
	return 1;
}
}
