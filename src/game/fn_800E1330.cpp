// Zeroes each vector component lying strictly between the two thresholds unless fn_800E27D8 reports the entity as busy.
struct V3_800E1330 {
	float x;
	float y;
	float z;
};

extern "C" {
extern float lbl_8042E1F0;
extern float lbl_8042E21C;
extern float lbl_8042E220;
int fn_800E27D8(int h, int a, int b, int c);

void fn_800E1330(int h, V3_800E1330* v, int a)
{
	if (fn_800E27D8(h, a, 0, 0) == 0) {
		if (lbl_8042E21C > v->x && lbl_8042E220 < v->x) {
			v->x = lbl_8042E1F0;
		}
		if (lbl_8042E21C > v->y && lbl_8042E220 < v->y) {
			v->y = lbl_8042E1F0;
		}
		if (lbl_8042E21C > v->z && lbl_8042E220 < v->z) {
			v->z = lbl_8042E1F0;
		}
	}
}
}
