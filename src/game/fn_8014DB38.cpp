// Registers the plugin (id 0x102) with RenderWare and returns whether the registration succeeded.

extern "C" {
void fn_8014CF24();
void fn_8014CE74();
int RwEngineRegisterPlugin(int, int, void (*)(), void (*)());

int fn_8014DB38()
{
	int r = RwEngineRegisterPlugin(0, 0x102, fn_8014CF24, fn_8014CE74);
	return r >= 0 ? 1 : 0;
}
}
