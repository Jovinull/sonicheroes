// Runs one pass of the module of fn_801B3474 over an object (HYPOTHESIS): optionally refreshes the
// shared handle first (fn_801B73B8), then calls the second entry of the object's handler table
// with a {argument, handle} context kept in a static state block. Escalates the object's state to
// 2 through fn_801B3368 when the handler raised it above 1, clears the static state and returns
// the object, or null when the handler failed.
// NonMatching: the retail code loads the shared handle after the first state stores; ours
// schedules that load earlier (8 words differ).
#include "game/rw_module_801B3414.h"

struct Handler801B388C;

// Object fields used here (layout inferred from this function only).
struct Object801B388C {
	u8 pad0[0x8];
	Handler801B388C* handler; // 0x8
	u8 padC[0x4];
	s32 state;  // 0x10
	void* data; // 0x14
};

// Context handed to the handler.
struct Context801B388C {
	void* arg;    // 0x0
	void* handle; // 0x4
};

struct HandlerTable801B388C {
	void* entry0;
	void* (*run)(Handler801B388C* handler, Context801B388C* context); // 0x4
};

struct Handler801B388C {
	HandlerTable801B388C* table;
};

// Static state block (.bss, 0x18 bytes).
struct State801B388C {
	Object801B388C* object; // 0x0
	u8 pad4[0x4];
	s32 succeeded; // 0x8
	u8 padC[0x4];
	Context801B388C context; // 0x10
};

extern "C" {
extern State801B388C lbl_803EDC28;

// Rebuilds the shared heap while its dirty word 0x18 is set (HYPOTHESIS).
s32 fn_801B73B8(void* heap);
void fn_801B3368(void* data);

Object801B388C* fn_801B388C(Object801B388C* object, void* arg, s32 refresh)
{
	// The shared heap is rebuilt first when its dirty word 0x18 is set.
	if (refresh && ((s32*)lbl_8042CA8C)[6]) {
		fn_801B73B8(lbl_8042CA8C);
	}

	lbl_803EDC28.succeeded      = 1;
	lbl_803EDC28.object         = object;
	lbl_803EDC28.context.arg    = arg;
	lbl_803EDC28.context.handle = lbl_8042CA8C;
	object->state               = 0;
	void* result = object->handler->table->run(object->handler, &lbl_803EDC28.context);
	if (!result) {
		// Stores the null result itself: the retail code reuses r3 rather than loading 0.
		lbl_803EDC28.succeeded = (s32)result;
	}
	if (object->state > 1) {
		object->state = 2;
		fn_801B3368(object->data);
	}

	lbl_803EDC28.context.arg    = 0;
	lbl_803EDC28.object         = 0;
	lbl_803EDC28.context.handle = 0;
	return lbl_803EDC28.succeeded ? object : 0;
}
}
