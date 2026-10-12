#include "types.h"

// The four hooks rel/chao_register.cpp puts in CHAO OBJECT's editor record, in
// the thirteen stage modules that share it: the empty reset, the unload that
// forgets the chao's model and animation, the load that reads them, and the
// factory, which allocates 0xF0 bytes and hands them to TObjChao's
// constructor (rel/chao_ctor.cpp), called by its symbol as retail does.

typedef struct RpClump RpClump;

extern "C" void* lbl_8042C110;
extern "C" void* lbl_8042C148;
extern "C" char chaoModelName[];
extern "C" char chaoAnimName[];
extern "C" RpClump* chaoModel;
extern "C" RpClump* chaoAnim;

extern "C" void* Malloc__9THeapCtrlFUi(void* heap, u32 size);
extern "C" void* __ct__8TObjChaoFP7TObject(void* object, void* owner);
RpClump* objPointerReadFromClumpAnim(char* name);

extern "C" void chaoObjectReset(void) { }

extern "C" void chaoObjectUnload(void)
{
	chaoModel = NULL;
	chaoAnim  = NULL;
}

extern "C" void chaoObjectLoad(void)
{
	chaoModel = objPointerReadFromClumpAnim(chaoModelName);
	chaoAnim  = objPointerReadFromClumpAnim(chaoAnimName);
}

extern "C" void chaoObjectCreate(void)
{
	void* memory = Malloc__9THeapCtrlFUi(lbl_8042C148, 0xF0);

	if (memory != NULL) {
		__ct__8TObjChaoFP7TObject(memory, lbl_8042C110);
	}
}
