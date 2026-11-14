// Module shutdown for the module tracked by lbl_8042C970: runs fn_80197770, releases the object
// stored at +0xC of its globals through fn_80199984, frees that block with the engine memory
// function, clears the slot and drops the instance count. Returns the instance.
#include "game/rw_engine.h"

extern "C" {
extern RwModuleInfo lbl_8042C970;
void fn_80197770(void);
void fn_80199984(void* object);

void* fn_80197300(void* instance)
{
	fn_80197770();
	fn_80199984(*(void**)((u8*)lbl_8042C9A4 + lbl_8042C970.globalsOffset + 0xC));
	lbl_8042C9A4->rwfree(*(void**)((u8*)lbl_8042C9A4 + lbl_8042C970.globalsOffset + 0xC));
	*(void**)((u8*)lbl_8042C9A4 + lbl_8042C970.globalsOffset + 0xC) = 0;
	lbl_8042C970.numInstances--;
	return instance;
}
}
