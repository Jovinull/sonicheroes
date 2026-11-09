// Loads the texture dictionary file lbl_80288B70 into the object's slot at 4, registers it, then creates the object lbl_80288B88 (stored in lbl_8042C61C) and binds it to the camera pointer.

extern "C" {
struct Obj8011264C {
	unsigned char pad[4];
	int f4;
};
extern unsigned char lbl_80288B70[];
extern unsigned char lbl_80288B88[];
extern int lbl_8042C61C;
int texLoadTexDictionaryFile__FPc(void*);
void fn_801A4C84(int);
int fn_800A91AC(void*);
int GetMObjectCameraPointer__Fv(void);
void fn_800A8D24(int, int);
void fn_800A8CB8(int);

void fn_8011264C(Obj8011264C* o)
{
	o->f4 = texLoadTexDictionaryFile__FPc(lbl_80288B70);
	fn_801A4C84(o->f4);
	lbl_8042C61C = fn_800A91AC(lbl_80288B88);
	fn_800A8D24(lbl_8042C61C, GetMObjectCameraPointer__Fv());
	fn_800A8CB8(lbl_8042C61C);
}
}
