// Copies the four-float colour/blend record lbl_80253A54 to lbl_80253A64.
struct V4_800B7AD0 {
	float a;
	float b;
	float c;
	float d;
};

extern "C" {
extern V4_800B7AD0 lbl_80253A54;
extern V4_800B7AD0 lbl_80253A64;

void fn_800B7AD0()
{
	lbl_80253A64.a = lbl_80253A54.a;
	lbl_80253A64.b = lbl_80253A54.b;
	lbl_80253A64.c = lbl_80253A54.c;
	lbl_80253A64.d = lbl_80253A54.d;
}
}
