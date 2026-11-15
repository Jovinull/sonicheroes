// Menu scene manager lbl_8042C778 (HYPOTHESIS; names inferred): a scene object driven by a table
// of state handlers lbl_8042C77C (16-byte entries {state, init, start, end}, ended by state -1),
// rendered with a camera, the two scene lights lbl_8042C784 and the scene world lbl_8042C780.
#include "game/rw_engine.h"

struct THeapCtrl {
	void* Malloc(u32 size);
	void Free(void* p);
};
extern "C" THeapCtrl* lbl_8042C148;

class TObject;
struct TObjectBase {
	char* ClassName;
	u16 Signal, Tag;
	TObject* Prev;
	TObject* Next;
	TObject* Parent;
	TObject* Child; // 0x14
};

// Task object (only the members used here; vtable pointer at 0x18, size 0x28; the full class is
// in game/effect/eff_footprints.h).
class TObject : public TObjectBase
{
public:
	TObject(TObject* parent);
	virtual ~TObject();
	u16 ExecTime, DispTime, TDispTime, PDispTime, ImmAftSetRasterTime;
	static void* operator new(unsigned long size) { return lbl_8042C148->Malloc(size); }
	// Out of line in retail (__dl__7TObjectFPv), as the exception table of fn_801306BC shows.
	static void operator delete(void* p);
};

struct Handler80130484 {
	s32 state;                      // 0x0
	void (*init)(void);             // 0x4
	void (*start)(TObject* object); // 0x8
	void (*end)(void);              // 0xC
};

struct Light80130484 {
	u8 pad0[0x4];
	RwFrame* frame; // 0x4
};

extern "C" {
extern Handler80130484* lbl_8042C77C;
extern Light80130484* lbl_8042C784[2];
extern void* lbl_8042C780;
extern u8 lbl_8042C1C0;
extern char lbl_8028AEC0[];
extern void* lbl_8042C1F8;
extern f32 lbl_8042C20C;
extern f32 lbl_802C216C[8];
extern const RwV3d AxisX;
extern const RwV3d AxisY;
extern const f32 lbl_8042EE68;
extern const f32 lbl_8042EE6C;
extern const f32 lbl_8042EE70;
extern const f32 lbl_8042EE74;
extern const f32 lbl_8042EE78;
extern const f32 lbl_8042EE7C;
extern const f32 lbl_8042EE80;
extern const f32 lbl_8042EE84;
void fn_80042310(void* archive, const char* name);
void fn_8012ED38(void);
void* fn_80159920(RwBBox* box);
Light80130484* fn_80154414(s32 type);
void fn_80153EE0(Light80130484* light, const RwRGBAReal* colour);
RwFrame* fn_8019E344(void);
void fn_8019ED68(RwFrame* frame, const RwV3d* axis, f32 angle, s32 combine);
void fn_80018368(TObject* object);
void fn_80177C50(void);
void fn_8019CC00(void* camera);
void fn_801A5370(Light80130484* light, RwFrame* frame);
void fn_8019E480(RwFrame* frame);
void fn_801543B4(Light80130484* light);
void fn_80159798(void* world);
void fn_8012ECE0(void);
s32 fn_800421C8(void* archive, const char* name);
void fn_80196D00(void);
}

struct Manager80130484 {
	s32 state;                // 0x0
	s32 nextState;            // 0x4
	void* camera;             // 0x8
	TObject* object;          // 0xC
	Handler80130484* handler; // 0x10

	Manager80130484()
	{
		state     = 0;
		nextState = 0;
		camera    = 0;
		object    = new TObject(0);
		handler   = 0;
		startHandler();
	}

	// Ends the current handler and starts the handler of the current state, if the table has one.
	void startHandler()
	{
		s32 current            = state;
		Handler80130484* entry = lbl_8042C77C;

		if (handler != 0) {
			handler->end();
			handler = 0;
		}
		for (; entry->state != -1; entry++) {
			if (current == entry->state) {
				handler = entry;
				entry->init();
				entry->start(object);
				break;
			}
		}
	}

	// Enters the requested state.
	void enterState()
	{
		state = nextState;
		startHandler();
	}

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

extern "C" {
// Steps the manager: updates its scene object (fn_80018368) and, once the object has no children, enters
// the requested state. Renders the scene (fn_801302B0) and returns whether the manager is still
// running (state other than 3); returns 0 without a manager.
s32 fn_80130484(void)
{
	Manager80130484* manager = lbl_8042C778;

	if (manager != 0) {
		if (manager->object != 0) {
			fn_80018368(manager->object);
			if (manager->object->Child == 0) {
				manager->enterState();
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
			RwFrame* frame = light->frame;
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

// Starts the menu scene: loads lbl_8028AEC0 into lbl_8042C1C0 (fn_80042310), runs fn_8012ED38,
// creates the scene world with an unbounded box, an ambient light (0.3 grey) and a directional
// light (0.7 grey) on a frame turned 45 degrees about X then Y, and the manager in its first state;
// with a game context, sets lbl_8042C20C and the first value of lbl_802C216C.
void fn_801306BC(void)
{
	RwBBox box;
	RwRGBAReal ambient;
	RwRGBAReal directional;

	fn_80042310(&lbl_8042C1C0, lbl_8028AEC0);
	fn_8012ED38();
	box.inf.x = box.inf.y = box.inf.z = lbl_8042EE6C;
	box.sup.x = box.sup.y = box.sup.z = lbl_8042EE70;
	lbl_8042C780                      = fn_80159920(&box);

	lbl_8042C784[0] = fn_80154414(2);
	if (lbl_8042C784[0] != 0) {
		ambient.red   = lbl_8042EE74;
		ambient.green = lbl_8042EE74;
		ambient.blue  = lbl_8042EE74;
		ambient.alpha = lbl_8042EE78;
		fn_80153EE0(lbl_8042C784[0], &ambient);
	}
	lbl_8042C784[1] = fn_80154414(1);
	if (lbl_8042C784[1] != 0) {
		RwFrame* frame;

		directional.red   = lbl_8042EE7C;
		directional.green = lbl_8042EE7C;
		directional.blue  = lbl_8042EE7C;
		directional.alpha = lbl_8042EE78;
		frame             = fn_8019E344();
		if (frame != 0) {
			fn_8019ED68(frame, &AxisX, lbl_8042EE80, 0);
			fn_8019ED68(frame, &AxisY, lbl_8042EE80, 2);
			fn_801A5370(lbl_8042C784[1], frame);
		}
		fn_80153EE0(lbl_8042C784[1], &directional);
	}

	lbl_8042C778 = new Manager80130484;
	if (lbl_8042C1F8 != 0) {
		lbl_8042C20C    = lbl_8042EE68;
		lbl_802C216C[0] = lbl_8042EE84;
	}
}
}
