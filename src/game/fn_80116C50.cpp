// Pushes the object's fields into the quest-sequence variable table (0x15, 0x12, 0x13, 0x14), refreshes the stage config, copies the 0x80-byte default block and stores the clamped timer (x60) as variable 0x2D.
struct Obj80116C50 {
	unsigned char pad0[0x1C];
	signed char f1C;
	signed char f1D;
	unsigned char pad1E[5];
	signed char f23;
	unsigned char pad24[8];
	unsigned int f2C;
	unsigned char pad30[8];
	int f38;
};
struct Cfg80116C50 {
	unsigned char pad0[0x12];
	signed char f12;
};

extern "C" {
extern char lbl_80303EC8[];
extern char lbl_803E774C[];
extern char seqVars__13TQuestSeqCtrl[];
extern Cfg80116C50* lbl_8042C180;
void fn_800A96B0(char* p, int idx, int v);
void fn_800B41A0(int v);
void* memcpy(void* d, const void* s, unsigned int n);

void fn_80116C50(Obj80116C50* o)
{
	unsigned int v;
	fn_800A96B0(lbl_80303EC8, 0x15, o->f23);
	fn_800A96B0(lbl_80303EC8, 0x12, o->f38);
	fn_800A96B0(lbl_80303EC8, 0x13, o->f1C);
	fn_800A96B0(lbl_80303EC8, 0x14, o->f1D);
	fn_800B41A0(lbl_8042C180->f12);
	memcpy(seqVars__13TQuestSeqCtrl, lbl_803E774C + 0x5A1, 0x80);
	v = o->f2C * 0x3C;
	if (v > 0x7FFFFFFFU) {
		v = 0x7FFFFFFFU;
	}
	fn_800A96B0(lbl_80303EC8, 0x2D, v);
}
}
