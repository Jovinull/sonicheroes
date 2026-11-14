// Creates an empty container (the counterpart of fn_8014705C): allocates it with the engine memory
// function, empties its entry list and links it at the head of the container list at the start of
// the module globals tracked by lbl_8042BCE0. On failure records error 0x80000013 (out of memory,
// 0x10 bytes) for plugin 0x120 and returns null. Names are UNKNOWN.
#include "game/rw_engine.h"

#define PLUGIN_ID_80146FAC 0x120

struct Container80146FAC {
	RwLinkList entries; // 0x0
	RwLLLink link;      // 0x8
};

extern "C" {
extern RwModuleInfo lbl_8042BCE0;
}

#define LIST80146FAC (*(RwLinkList*)((u8*)lbl_8042C9A4 + lbl_8042BCE0.globalsOffset))

extern "C" {
Container80146FAC* fn_80146FAC(void)
{
	Container80146FAC* container
	    = (Container80146FAC*)lbl_8042C9A4->rwmalloc(sizeof(Container80146FAC));
	if (container == 0) {
		RwError error;
		error.pluginID  = PLUGIN_ID_80146FAC;
		error.errorCode = fn_8019408C(RW_ERROR_NO_MEMORY, sizeof(Container80146FAC));
		fn_80193FE8(&error);
		return 0;
	}
	container->entries.link.next = &container->entries.link;
	container->entries.link.prev = &container->entries.link;
	container->link.next         = LIST80146FAC.link.next;
	container->link.prev         = &LIST80146FAC.link;
	LIST80146FAC.link.next->prev = &container->link;
	LIST80146FAC.link.next       = &container->link;
	return container;
}
}
