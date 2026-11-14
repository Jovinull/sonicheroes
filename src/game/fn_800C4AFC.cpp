// Constructor of the hook-object base (see fn_800C04B4): builds the TObject part under parent,
// installs the base vtable lbl_80254594 and the class name lbl_8042B470, sets halfword 0x1E to
// 0x30, the float at 0x2C to lbl_8042DE54, the channel byte at 0x28 and clears byte 0x29.
// Returns the object.
struct Obj800C4AFC {
	const char* name; // 0x00
	unsigned char pad4[0x18 - 0x4];
	void* vt; // 0x18
	unsigned char pad1C[0x2];
	unsigned short f1E;
	unsigned char pad20[0x8];
	signed char channel; // 0x28
	unsigned char f29;
	unsigned char pad2A[0x2];
	float f2C;
};

extern "C" {
extern unsigned char lbl_80254594[];
extern const char* lbl_8042B470;
extern float lbl_8042DE54;
void __ct__7TObjectFP7TObject(void* o, void* parent);

Obj800C4AFC* fn_800C4AFC(Obj800C4AFC* o, void* parent, int channel)
{
	__ct__7TObjectFP7TObject(o, parent);
	o->vt      = lbl_80254594;
	o->name    = lbl_8042B470;
	o->f1E     = 0x30;
	o->f2C     = lbl_8042DE54;
	o->channel = channel;
	o->f29     = 0;
	return o;
}
}
