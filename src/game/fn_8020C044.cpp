// Registers the plugin and returns whether registration succeeded.
extern "C" {
int RwEngineRegisterPlugin(int a, int b, int (*c)(), int (*d)());
int fn_8020BF9C();
int fn_8020BFF8();

int fn_8020C044()
{
	return RwEngineRegisterPlugin(0, 0x1B7, fn_8020BF9C, fn_8020BFF8) > 0;
}
}
