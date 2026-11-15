// Runs the TObjCamera constructor and fills in the object: vtable-like pointer at 0x18, word 0 from lbl_8042B058 and the halfword 0x5C at 0x1E; returns the object.

extern "C" {
struct Obj8004FFB4 {
	int f0;
	unsigned char pad[0x14];
	void* f18;
	unsigned char pad1[2];
	short s1e;
};
extern unsigned char lbl_802428E0[];
extern int lbl_8042B058;
void __ct__10TObjCameraFP7TObject();

Obj8004FFB4* fn_8004FFB4(Obj8004FFB4* o)
{
	__ct__10TObjCameraFP7TObject();
	o->f18 = lbl_802428E0;
	o->f0  = lbl_8042B058;
	o->s1e = 0x5c;
	return o;
}
}
