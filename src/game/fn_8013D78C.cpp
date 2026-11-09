// Registers the 0x122 engine plugin and its two stages (fn_8013C99C, fn_8013D2B8); returns whether all succeeded.

extern "C" {
extern unsigned char fn_8013D764[];
extern unsigned char fn_8013D778[];
int RwEngineRegisterPlugin(int, int, void*, void*);
int fn_8013C99C(void);
int fn_8013D2B8(void);

int fn_8013D78C(void)
{
	if (RwEngineRegisterPlugin(0, 0x122, fn_8013D764, fn_8013D778) < 0) {
		return 0;
	}
	if (fn_8013C99C() == 0) {
		return 0;
	}
	return fn_8013D2B8() != 0;
}
}
