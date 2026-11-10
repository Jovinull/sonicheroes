// Runs the first callback on the handle with a stack copy of the float and returns the possibly updated value.
extern "C" {
void fn_800C4758();
void fn_80204144(int h, void (*cb)(), float* v);

float fn_800C4720(int unused, int h, float v)
{
	float x = v;
	fn_80204144(h, fn_800C4758, &x);
	return x;
}
}
