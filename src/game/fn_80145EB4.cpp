// Registers the RenderWare plugin (id 0x129), stores its offset in lbl_8042C848 and returns whether it succeeded.

extern "C" {
extern int lbl_8042C848;
void* fn_80143A9C(void*);
void fn_80143AE0();
int RwEngineRegisterPlugin(int, int, void (*)(), void (*)());

int fn_80145EB4()
{
	lbl_8042C848 = RwEngineRegisterPlugin(8, 0x129, (void (*)())fn_80143A9C, fn_80143AE0);
	return lbl_8042C848 >= 0 ? 1 : 0;
}
}
