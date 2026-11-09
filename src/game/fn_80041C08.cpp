// Sets an object's value (0xA0) from the table at lbl_80241C80 for an index of 0
// to 5, and to 0 for any other index.

extern "C" {
extern int lbl_80241C80[];
struct Obj80041C08 {
	unsigned char pad[0xA0];
	int value; // 0xA0
};

void fn_80041C08(Obj80041C08* obj, int index)
{
	if (index < 0 || (unsigned int)index >= 6) {
		obj->value = 0;
	} else {
		obj->value = lbl_80241C80[index];
	}
}
}
