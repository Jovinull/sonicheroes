// Runs the second callback on the handle with a stack copy of the float and returns the possibly updated value.
extern "C" {
void fn_800C480C();
void fn_80204144(int h, void (*cb)(), float* v);

float fn_800C47D4(int unused, int h, float v)
{
	float x = v;
	fn_80204144(h, fn_800C480C, &x);
	return x;
}
}
