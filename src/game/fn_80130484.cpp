// Steps the menu scene manager lbl_8042C778 (HYPOTHESIS; names inferred): updates its scene
// object (fn_80018368) and, once the object is idle (0x14), enters the requested state: ends the
// current handler, then finds the handler of the new state in the table lbl_8042C77C (ended by
// id -1), makes it current, runs its init and starts it on the object. Renders the scene
// (fn_801302B0) and returns whether the manager is still running (state other than 3); returns 0
// without a manager.
#include "types.h"

struct SceneObject80130484 {
	u8 pad0[0x14];
	u32 busy; // 0x14
};

struct Handler80130484 {
	s32 state;                                  // 0x0
	void (*init)(void);                         // 0x4
	void (*start)(SceneObject80130484* object); // 0x8
	void (*end)(void);                          // 0xC
};

struct Manager80130484 {
	s32 state;     // 0x0
	s32 nextState; // 0x4
	u8 pad8[0xC - 0x8];
	SceneObject80130484* object; // 0xC
	Handler80130484* handler;    // 0x10
};

extern "C" {
extern Manager80130484* lbl_8042C778;
extern Handler80130484* lbl_8042C77C;
void fn_80018368(SceneObject80130484* object);
void fn_801302B0(Manager80130484* manager);

// Ends the current handler and starts the handler of the requested state, if the table has one.
static inline void enterState(Manager80130484* manager)
{
	s32 state;
	Handler80130484* handler;

	manager->state = manager->nextState;
	state          = manager->state;
	handler        = lbl_8042C77C;
	if (manager->handler != 0) {
		manager->handler->end();
		manager->handler = 0;
	}
	for (; handler->state != -1; handler++) {
		if (state == handler->state) {
			manager->handler = handler;
			handler->init();
			handler->start(manager->object);
			break;
		}
	}
}

s32 fn_80130484(void)
{
	Manager80130484* manager = lbl_8042C778;

	if (manager != 0) {
		if (manager->object != 0) {
			fn_80018368(manager->object);
			if (manager->object->busy == 0) {
				enterState(manager);
			}
		}
		fn_801302B0(lbl_8042C778);
		return lbl_8042C778->state != 3;
	}
	return 0;
}
}
