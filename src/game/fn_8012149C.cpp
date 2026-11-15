#include "types.h"

// InitCaosEmeraldDisp (CORROBORATED by PS2 metadata and the stored class name "SpOutputTex"): for a
// matching stage, creates the SpOutputTex display (pointer lbl_8042C70C) through TObject's task-heap
// operator new and looks up its texture by name. Names are from PS2; the symbol keeps its address-based name.

struct THeapCtrl {
	void* Malloc(u32 size);
	void Free(void* p);
};
extern "C" THeapCtrl* lbl_8042C148;

class TObject
{
public:
	static void* operator new(unsigned long size) { return lbl_8042C148->Malloc(size); }
	static void operator delete(void* p);
};

extern "C" void fn_80136F14(void* self, TObject* parent);

class SpOutputTex : public TObject
{
public:
	SpOutputTex(TObject* parent) { fn_80136F14(this, parent); }

private:
	u8 unk00[0x40];
};

extern "C" {
extern u8 lbl_8029C310[];
extern char lbl_8023ACE0[];
extern void* lbl_8042C70C;
extern void* lbl_8042C708;
extern TObject* lbl_8042C118;
extern u8* lbl_8042C1D0;

s32 fn_80018E30(void* state);
void* fn_801A4BBC(void* dictionary, const char* name);
}

struct TextureNameTable {
	char data[0x78];
};

extern "C" void fn_8012149C(void)
{
	if (fn_80018E30(lbl_8029C310) != 0) {
		s32 n = *(s32*)(*(u8**)(lbl_8029C310 + 0x34) + 4);
		while (n >= 10)
			n -= 10;
		TextureNameTable names = *(TextureNameTable*)lbl_8023ACE0;
		if (lbl_8042C70C == 0)
			lbl_8042C70C = new SpOutputTex(lbl_8042C118);
		if (n < 10)
			lbl_8042C708 = fn_801A4BBC(*(void**)(lbl_8042C1D0 + 0x8C18), ((char*)&names) + n * 12);
	}
}
