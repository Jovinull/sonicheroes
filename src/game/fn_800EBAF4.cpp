// Clears the global's counter field and returns 1 when bit 15 of the object's flags is clear.
struct Obj800EBAF4 {
	unsigned char pad[0x18];
	unsigned f18;
};
struct G188 {
	unsigned char pad[0x188];
	int f188;
};
extern "C" {
extern G188* lbl_8042C150;
int fn_800EBAF4(Obj800EBAF4* o)
{
	lbl_8042C150->f188 = 0;
	return (unsigned int)__cntlzw(o->f18 & 0x8000) >> 5;
}
}
