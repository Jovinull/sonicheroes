// Forwards the object's handle with the float plus the constant lbl_8042EB28; returns 1.
struct Obj8011B844 {
	unsigned char pad0[4];
	int f4;
};

extern "C" {
extern float lbl_8042EB28;
void fn_8020CC18(int h, float v);

int fn_8011B844(Obj8011B844* o, float v)
{
	fn_8020CC18(o->f4, lbl_8042EB28 + v);
	return 1;
}
}
