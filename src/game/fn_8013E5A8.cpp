// Creates the pool of 0x24-byte records (fn_801966CC, kept in word 4 of lbl_8042C828) and registers
// the handler descriptor (kind 1, sizes 0x24, eight callbacks fn_8013D7F8..fn_8013E280) with
// fn_8020C088. Returns ok, or 0 when the pool could not be created.
struct Plugin8013E5A8 {
	int offset;
	void* pool;
};

struct Desc8013E5A8 {
	int kind;
	int size;
	int size2;
	void (*f[8])(void);
	int end;
};

extern "C" {
extern Plugin8013E5A8 lbl_8042C828;
extern int lbl_8042BCD8;
extern int lbl_8042BCDC;
extern unsigned char lbl_803EC3C0[];
void* fn_801966CC(int size, int a, int b, int c, void* d);
void fn_8020C088(Desc8013E5A8* d);
void fn_8013D7F8(void);
void fn_8013DD18(void);
void fn_8013D904(void);
void fn_8013E3D0(void);
void fn_8013E290(void);
void fn_8013E11C(void);
void fn_8013E1D8(void);
void fn_8013E280(void);

int fn_8013E5A8(int ok)
{
	Desc8013E5A8 d;
	lbl_8042C828.pool = fn_801966CC(0x24, lbl_8042BCD8, 4, lbl_8042BCDC, lbl_803EC3C0);
	if (lbl_8042C828.pool == 0) {
		ok = 0;
	}
	d.kind  = 1;
	d.size  = 0x24;
	d.size2 = 0x24;
	d.f[0]  = fn_8013D7F8;
	d.f[1]  = fn_8013DD18;
	d.f[2]  = fn_8013D904;
	d.f[3]  = fn_8013E3D0;
	d.f[4]  = fn_8013E290;
	d.f[5]  = fn_8013E11C;
	d.f[6]  = fn_8013E1D8;
	d.f[7]  = fn_8013E280;
	d.end   = 0;
	fn_8020C088(&d);
	return ok;
}
}
