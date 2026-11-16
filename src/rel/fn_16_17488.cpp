struct Elem {
	char pad[0x34];
};
struct Obj {
	char pad[0x68];
	Elem* elems;
};
extern "C" {
extern void* lbl_8042C180;
int fn_16_F20(void* game, int flag);
void fn_16_16F68(Elem* p);
void fn_16_17488(register Obj* arg0)
{
	register int i;
	if (fn_16_F20(lbl_8042C180, 0x20) == 0) {
		for (i = 0; i < 3; i++) {
			fn_16_16F68(&arg0->elems[i]);
		}
	}
}
}
