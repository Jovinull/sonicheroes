// Scales the value at +4 by the length returned by fn_801992A4 for the vector produced by fn_8016EBC0.
struct Obj8016E0C0 {
	unsigned char pad0[4];
	float f4;
};

extern "C" {
void fn_8016EBC0(unsigned char* a, unsigned char* b, unsigned char* c);
float fn_801992A4(unsigned char* a);

float fn_8016E0C0(Obj8016E0C0* o)
{
	unsigned char a[8];
	unsigned char b[8];
	unsigned char c[8];
	fn_8016EBC0(a, b, c);
	return o->f4 * fn_801992A4(b);
}
}
