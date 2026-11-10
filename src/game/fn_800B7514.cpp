// Scales the float triple by lbl_8042DD64 into integers and forwards them with the passthrough arguments to fn_800B7584.
struct V3_800B7514 {
	float x;
	float y;
	float z;
};
struct I3_800B7514 {
	int x;
	int y;
	int z;
};

extern "C" {
extern float lbl_8042DD64;
void fn_800B7584(int a, I3_800B7514* v, float s);

void fn_800B7514(int a, V3_800B7514* v, float s)
{
	I3_800B7514 i;
	i.x = (int)(lbl_8042DD64 * v->x);
	i.y = (int)(lbl_8042DD64 * v->y);
	i.z = (int)(lbl_8042DD64 * v->z);
	fn_800B7584(a, &i, s);
}
}
