// Calls fn_80146BC8(arg0, 6) and fn_80146918, then copies the four bytes held at +4 of arg0 into the record returned by fn_801439D8 (+0x2E..0x31); returns arg0.

extern "C" {
struct Bytes800F474C {
	unsigned char b[4];
};
struct Obj800F474C {
	unsigned char pad[4];
	Bytes800F474C f4;
};
struct Rec800F474C {
	unsigned char pad[0x2e];
	unsigned char b0;
	unsigned char b1;
	unsigned char b2;
	unsigned char b3;
};
void fn_80146BC8(Obj800F474C*, int);
void fn_80146918(void);
Rec800F474C* fn_801439D8(void);

Obj800F474C* fn_800F474C(Obj800F474C* o)
{
	Bytes800F474C v = o->f4;
	Rec800F474C* r;
	fn_80146BC8(o, 6);
	fn_80146918();
	r     = fn_801439D8();
	r->b0 = v.b[0];
	r->b1 = v.b[1];
	r->b2 = v.b[2];
	r->b3 = v.b[3];
	return o;
}
}
