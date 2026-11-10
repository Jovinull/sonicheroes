// Stores the inverted RGB components (1 - c) and the alpha into lbl_80253A64.
struct V4_800B7B04 {
	float a;
	float b;
	float c;
	float d;
};

extern "C" {
extern V4_800B7B04 lbl_80253A64;
extern float lbl_8042DD4C;

void fn_800B7B04(float a, float b, float c, float d)
{
	lbl_80253A64.a = lbl_8042DD4C - a;
	lbl_80253A64.b = lbl_8042DD4C - b;
	lbl_80253A64.c = lbl_8042DD4C - c;
	lbl_80253A64.d = d;
}
}
