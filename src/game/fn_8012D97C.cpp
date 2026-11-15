#include "types.h"

// SetStageTitleDisp (CORROBORATED by PS2 metadata and the stored class name "TObjStageTitle"): creates a TObjStageTitle, unless one already exists (lbl_8042C760)
// through TObject's task-heap operator new. Names are from PS2; the symbol keeps its address-based name.

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

extern "C" void fn_8012E918(void* self, TObject* parent);

class TObjStageTitle : public TObject
{
public:
	TObjStageTitle(TObject* parent) { fn_8012E918(this, parent); }

private:
	u8 unk00[0xA0];
};

extern "C" TObjStageTitle* lbl_8042C760;
extern "C" TObject* lbl_8042C100;

extern "C" void fn_8012D97C(void)
{
	if (lbl_8042C760 == NULL)
		new TObjStageTitle(lbl_8042C100);
}
