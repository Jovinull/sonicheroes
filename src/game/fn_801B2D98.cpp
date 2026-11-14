// Sends a two-halfword request through the engine instance's request block (HYPOTHESIS): when the
// module globals (lbl_8042CA74 offset) are ready (word 0x3C), fills the request block at 0x44 with
// the target object from 0x10, a two-entry halfword buffer allocated from the module heap
// (fn_801B3884 returns the shared handle lbl_8042CA8C of rw_module_801B3414.h;
// fn_801B7174, released again with fn_801B6EAC) and the two values, then runs it through
// fn_801B388C. Returns 1 when that succeeds, 0 when it fails; an unready module records core
// error 0x23 and returns 0. Field names are inferred from this function only.
#include "game/rw_engine.h"

// Request block passed to fn_801B388C (only the fields set here are named).
struct Request801B2D98 {
	u8 pad0[0x20];
	void* object; // 0x20
	s32 flag;     // 0x24
	u16* values;  // 0x28
	s32 count;    // 0x2C
};

struct Globals801B2D98 {
	u8 pad0[0x10];
	void* object; // 0x10
	u8 pad14[0x3C - 0x14];
	void* ready; // 0x3C
	u8 pad40[0x4];
	Request801B2D98 request; // 0x44
};

extern "C" {
extern s32 lbl_8042CA74;

void* fn_801B3884(void);
void* fn_801B7174(void* heap, s32 size);
void fn_801B6EAC(void* heap, void* block);
void* fn_801B388C(void* object, Request801B2D98* request, s32 refresh);

s32 fn_801B2D98(u16 first, u16 second)
{
	void* heap               = fn_801B3884();
	Globals801B2D98* globals = (Globals801B2D98*)((u8*)lbl_8042C9A4 + lbl_8042CA74);

	if (globals->ready) {
		Request801B2D98* request = &globals->request;
		request->object          = globals->object;
		request->flag            = 1;
		request->values          = 0;
		request->count           = 2;
		request->values          = (u16*)fn_801B7174(heap, request->count * sizeof(u16));
		request->values[0]       = first;
		request->values[1]       = second;
		if (fn_801B388C(request->object, request, 0)) {
			fn_801B6EAC(heap, request->values);
			return 1;
		}
		fn_801B6EAC(heap, request->values);
	} else {
		RwError error;
		error.pluginID  = RW_ID_CORE_PLUGIN;
		error.errorCode = fn_8019408C(0x23);
		fn_80193FE8(&error);
	}
	return 0;
}
}
