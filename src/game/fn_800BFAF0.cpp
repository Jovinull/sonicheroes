// Runs the per-frame update chain for the current scene object.
extern "C" {
extern int lbl_8042C440;
extern int* lbl_8042C9A4;
extern float lbl_8042DE50;
void fn_8016EE88(int a);
void fn_802033F4(int a);
void fn_802041EC(int a);
void fn_802043B4(int a, float f);
void fn_802048CC(int a);

void fn_800BFAF0()
{
	fn_8016EE88(*lbl_8042C9A4);
	fn_802043B4(lbl_8042C440, lbl_8042DE50);
	fn_802041EC(lbl_8042C440);
	fn_802033F4(lbl_8042C440);
	fn_802048CC(lbl_8042C440);
}
}
