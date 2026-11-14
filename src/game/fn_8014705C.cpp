// Destroys a container: stops it being the current one (+0x8 of the module globals tracked by
// lbl_8042BCE0), releases every entry of its list (head at +0x0, entries linked at +0x28) through
// fn_80147178, unlinks its own link at +0x8 and frees it with the engine memory function. Names are
// UNKNOWN.
#include "game/rw_engine.h"

struct Container8014705C {
	RwLinkList entries; // 0x0
	RwLLLink link;      // 0x8
};

extern "C" {
extern RwModuleInfo lbl_8042BCE0;
void* fn_80147178(void* entry);

void fn_8014705C(Container8014705C* container)
{
	RwLLLink* cur;
	if (container == *(Container8014705C**)((u8*)lbl_8042C9A4 + lbl_8042BCE0.globalsOffset + 8)) {
		*(Container8014705C**)((u8*)lbl_8042C9A4 + lbl_8042BCE0.globalsOffset + 8) = 0;
	}
	cur = container->entries.link.next;
	while (cur != &container->entries.link) {
		void* entry = (u8*)cur - 0x28;
		cur         = cur->next;
		fn_80147178(entry);
	}
	RwLLLinkRemove(&container->link);
	lbl_8042C9A4->rwfree(container);
}
}
