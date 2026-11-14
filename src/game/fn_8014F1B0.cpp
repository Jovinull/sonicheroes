// Calls fn_801B388C(ctx, o, 1), where ctx is the object's pointer at 0x6C or, when null, the
// pointer at offset lbl_8042CA80 + 0x3C of the block lbl_8042C9A4 points to. Returns o on success,
// null otherwise.
struct Obj8014F1B0 {
	unsigned char pad0[0x6C];
	void* f6C;
};
extern "C" {
extern unsigned char* lbl_8042C9A4;
extern int lbl_8042CA80;
void* fn_801B388C(void* ctx, Obj8014F1B0* o, int mode);
Obj8014F1B0* fn_8014F1B0(Obj8014F1B0* o)
{
	void* ctx = o->f6C;
	if (ctx == 0) {
		ctx = *(void**)(lbl_8042C9A4 + lbl_8042CA80 + 0x3C);
	}
	if (fn_801B388C(ctx, o, 1) != 0) {
		return o;
	}
	return 0;
}
}
