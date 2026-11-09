// Calls fn_801A5370 on the object, sets bit 0 of its byte 3 and returns the object.

extern "C" {
struct Obj80152220 {
	unsigned char pad[3];
	unsigned char b3;
};
void fn_801A5370(Obj80152220*);

Obj80152220* fn_80152220(Obj80152220* o)
{
	fn_801A5370(o);
	o->b3 |= 1;
	return o;
}
}
