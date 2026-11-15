// Menu scene manager lbl_8042C778 (HYPOTHESIS; names inferred): a scene object driven by a table
// of state handlers lbl_8042C77C (16-byte entries {state, init, start, end}, ended by state -1),
// rendered with a camera, the two scene lights lbl_8042C784 and the scene world lbl_8042C780.
#include "types.h"

struct SceneObject80130484 {
	u8 pad0[0x14];
	u32 busy; // 0x14
	virtual ~SceneObject80130484();
};

struct Handler80130484 {
	s32 state;                                  // 0x0
	void (*init)(void);                         // 0x4
	void (*start)(SceneObject80130484* object); // 0x8
	void (*end)(void);                          // 0xC
};

struct Light80130484 {
	u8 pad0[0x4];
	void* frame; // 0x4
};

extern "C" {
extern Handler80130484* lbl_8042C77C;
extern Light80130484* lbl_8042C784[2];
extern void* lbl_8042C780;
extern u8 lbl_8042C1C0;
extern char lbl_8028AEC0[];
void fn_80018368(SceneObject80130484* object);
void fn_80177C50(void);
void fn_8019CC00(void* camera);
void fn_801A5370(Light80130484* light, void* frame);
void fn_8019E480(void* frame);
void fn_801543B4(Light80130484* light);
void fn_80159798(void* world);
void fn_8012ECE0(void);
s32 fn_800421C8(void* archive, const char* name);
void fn_80196D00(void);
}

struct Manager80130484 {
	s32 state;                   // 0x0
	s32 nextState;               // 0x4
	void* camera;                // 0x8
	SceneObject80130484* object; // 0xC
	Handler80130484* handler;    // 0x10

	// Flushes and destroys the camera, deletes the scene object and ends the current handler.
	~Manager80130484()
	{
		if (camera != 0) {
			fn_80177C50();
			fn_8019CC00(camera);
			camera = 0;
		}
		delete object;
		if (handler != 0) {
			handler->end();
			handler = 0;
		}
	}
};

extern "C" {
extern Manager80130484* lbl_8042C778;
void fn_801302B0(Manager80130484* manager);
}

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

extern "C" {
// Steps the manager: updates its scene object (fn_80018368) and, once the object is idle, enters
// the requested state. Renders the scene (fn_801302B0) and returns whether the manager is still
// running (state other than 3); returns 0 without a manager.
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

// Shuts the menu scene down: deletes the manager, clears the handler table, destroys the two
// scene lights with their frames and the scene world, then runs fn_8012ECE0, fn_800421C8 on
// lbl_8042C1C0 with the name lbl_8028AEC0 and fn_80196D00.
void fn_8013057C(void)
{
	s32 i;

	if (lbl_8042C778 != 0) {
		delete lbl_8042C778;
		lbl_8042C778 = 0;
	}
	lbl_8042C77C = 0;
	for (i = 0; i != 2; i++) {
		Light80130484* light = lbl_8042C784[i];
		if (light != 0) {
			void* frame = light->frame;
			if (frame != 0) {
				fn_801A5370(light, 0);
				fn_8019E480(frame);
			}
			fn_801543B4(lbl_8042C784[i]);
			lbl_8042C784[i] = 0;
		}
	}
	if (lbl_8042C780 != 0) {
		fn_80159798(lbl_8042C780);
		lbl_8042C780 = 0;
	}
	fn_8012ECE0();
	fn_800421C8(&lbl_8042C1C0, lbl_8028AEC0);
	fn_80196D00();
}
}
