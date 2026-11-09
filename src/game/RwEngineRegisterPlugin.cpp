// Registers a plugin with the engine plugin list lbl_802904E0, forwarding its four arguments and a trailing 0.

extern "C" {
extern unsigned char lbl_802904E0[];
void fn_80198A90(void*, int, int, int, int, int);

void RwEngineRegisterPlugin(int a, int b, int c, int d)
{
	fn_80198A90(lbl_802904E0, a, b, c, d, 0);
}
}
