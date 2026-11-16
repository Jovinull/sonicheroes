typedef signed char s8;
struct CLIGHT {
	void SetLightRegular(s8);
};
struct OBJ {
	char pad[0x4BE];
	s8 v;
};
extern "C" void fn_16_48C4(OBJ* o)
{
	((CLIGHT*)o)->SetLightRegular(o->v);
}
