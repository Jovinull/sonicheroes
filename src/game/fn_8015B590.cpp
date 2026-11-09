// Calls fn_801560C0 with the object's field 0x80 and the result of fn_80159698 on the object.

extern "C" {
struct Obj8015B590 {
	unsigned char pad[0x80];
	int f80;
};
int fn_80159698(Obj8015B590*);
void fn_801560C0(int, int);

void fn_8015B590(Obj8015B590* o)
{
	fn_801560C0(o->f80, fn_80159698(o));
}
}
