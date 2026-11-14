// Registers handler id for key: fn_801549E8(4, key, ...) with fn_80146014/fn_80146020/fn_801460D0
// and fn_80154A28(key, ...) with fn_801463F8/fn_801462B4/fn_80146214; the first result goes to word
// 0x08 of record id of lbl_803EC3F8, which then records id, key and extra. Returns 1, or 0 when a
// registration fails.
struct Rec801467E4 {
	int id;
	int key;
	int handle;
	int extra;
};

extern "C" {
extern Rec801467E4 lbl_803EC3F8[];
void fn_80146014(void);
void fn_80146020(void);
void fn_801460D0(void);
void fn_801463F8(void);
void fn_801462B4(void);
void fn_80146214(void);
int fn_801549E8(int size, int key, void (*a)(void), void (*b)(void), void (*c)(void));
int fn_80154A28(int key, void (*a)(void), void (*b)(void), void (*c)(void));

int fn_801467E4(int id, int key, int extra)
{
	int handle = fn_801549E8(4, key, fn_80146014, fn_80146020, fn_801460D0);
	Rec801467E4* r;
	if (handle < 0) {
		return 0;
	}
	r         = &lbl_803EC3F8[id];
	r->handle = handle;
	if (fn_80154A28(key, fn_801463F8, fn_801462B4, fn_80146214) < 0) {
		return 0;
	}
	r->id    = id;
	r->key   = key;
	r->extra = extra;
	return 1;
}
}
