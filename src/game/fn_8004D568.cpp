// Configures the screen object: clears the draw state, builds the 2-float parameter and forwards it with the current camera to the setup calls.
struct V2_8004D568 {
	float x;
	float y;
};
struct Ent8004D568 {
	unsigned char pad0[0x28];
	int f28;
};

extern "C" {
extern int lbl_8042B04C;
extern Ent8004D568* lbl_8042C1F8;
extern float lbl_8042D2D4;
extern float lbl_8042D2DC;
void fn_80050AB8(int a);
void fn_8019CC50(int a, int* b);
void fn_8019D0CC(int a, V2_8004D568* v);

void fn_8004D568(Ent8004D568* o)
{
	V2_8004D568 v;
	fn_80050AB8(0);
	v.x = lbl_8042D2D4;
	v.y = lbl_8042D2DC;
	fn_8019CC50(o->f28, &lbl_8042B04C);
	fn_8019D0CC(lbl_8042C1F8->f28, &v);
}
}
