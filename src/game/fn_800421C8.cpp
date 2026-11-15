// Unloads the first loaded module (REL) whose name matches `name` (any module when `name` is null)
// from the list lbl_8042C1C4: runs its epilog (+0x38 of the module header), unlinks it (OSUnlink),
// frees its two buffers (+0x18, +0x14; RwFree), removes the record from the list and deletes it.
// Then resets the performance counters (PERF::InitPerfomance on lbl_803A6690). The first argument
// is unused. HYPOTHESIS: the stage REL loader's unload; the record layout is inferred.
#include "types.h"

struct ModuleHeader800421C8 {
	u8 pad0[0x38];
	void (*epilog)(void); // 0x38
};

struct Module800421C8 {
	u8 pad0[8];
	Module800421C8* next;         // 0x8
	char* name;                   // 0xC
	ModuleHeader800421C8* module; // 0x10
	void* bss;                    // 0x14
	void* image;                  // 0x18
};

struct RwEngine800421C8 {
	u8 pad0[0x138];
	void (*rwfree)(void* block); // 0x138
};

class PERF
{
public:
	void InitPerfomance();
};

extern "C" {
extern Module800421C8* lbl_8042C1C4;
extern RwEngine800421C8* lbl_8042C9A4;
extern u8 lbl_803A6690[]; // the PERF object (size UNKNOWN)
int strcmp(const char* a, const char* b);
s32 OSUnlink(void* module);
void __dl__FPv(void* p);

void fn_800421C8(void* unused, const char* name)
{
	Module800421C8* m    = lbl_8042C1C4;
	Module800421C8* prev = NULL;

	while (m != NULL) {
		if (name == NULL || strcmp(m->name, name) == 0) {
			m->module->epilog();
			OSUnlink(m->module);
			if (m->image != NULL) {
				lbl_8042C9A4->rwfree(m->image);
			}
			if (m->bss != NULL) {
				lbl_8042C9A4->rwfree(m->bss);
			}
			if (prev != NULL) {
				prev->next = m->next;
			} else {
				lbl_8042C1C4 = m->next;
			}
			__dl__FPv(m);
			m = NULL;
		}
		if (m != NULL) {
			prev = m;
			m    = m->next;
		}
	}
	((PERF*)lbl_803A6690)->InitPerfomance();
}
}
