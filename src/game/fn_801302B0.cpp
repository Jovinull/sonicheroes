// Menu scene manager lbl_8042C778 (HYPOTHESIS; names inferred): a scene object driven by a table
// of state handlers lbl_8042C77C (16-byte entries {state, init, start, end}, ended by state -1),
// rendered from the current camera with the two scene lights lbl_8042C784 in the scene world
// lbl_8042C780.
#include "game/rw_engine.h"

struct RwCamera;

struct Camera801302B0 {
	u8 pad0[0x4];
	RwFrame* frame; // 0x4
};

RwCamera* GetCurrentCameraPointer();

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

struct Handler801302B0 {
	s32 state;                      // 0x0
	void (*init)(void);             // 0x4
	void (*start)(TObject* object); // 0x8
	void (*end)(void);              // 0xC
};

struct Light801302B0 {
	u8 pad0[0x4];
	RwFrame* frame; // 0x4
};

extern "C" {
extern Handler801302B0* lbl_8042C77C;
extern Light801302B0* lbl_8042C784[2];
extern void* lbl_8042C780;
extern u8 lbl_8042C1C0;
extern char lbl_8028AEC0[];
extern void* lbl_8042C1F8;
extern u8 lbl_8042AEB0[4];
extern RwV3d lbl_8028AEA8;
extern RwV3d lbl_8028AEB4;
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
Light801302B0* fn_80154414(s32 type);
void fn_80153EE0(Light801302B0* light, const RwRGBAReal* colour);
RwFrame* fn_8019E344(void);
void fn_8019ED68(RwFrame* frame, const RwV3d* axis, f32 angle, s32 combine);
void fn_80018368(TObject* object);
void fn_80177C50(void);
// HYPOTHESIS: RwCameraEndUpdate and RwCameraBeginUpdate (0x28 bytes each).
RwCamera* fn_8019CC00(RwCamera* camera);
RwCamera* fn_8019CC28(RwCamera* camera);
void fn_8004DC80(void* context, s32 value);
void fn_8019CD68(RwCamera* camera, f32 farPlane);
void fn_8019CF28(RwCamera* camera, void* colour, s32 mode);
void fn_8015B8E8(void* world, RwCamera* camera);
void fn_8015B93C(void* world, RwCamera* camera);
void fn_8015BD84(void* world, Light801302B0* light);
void fn_8015BE24(void* world, Light801302B0* light);
void fn_8019EB94(RwFrame* frame, RwV3d* translation, s32 combine);
void fn_8004D650(void* context);
void fn_8004D678(void* context);
void fn_80018064(TObject* object);
void fn_80017AEC(TObject* object);
void RsCameraShowRaster(RwCamera* camera);
void fn_801A5370(Light801302B0* light, RwFrame* frame);
void fn_8019E480(RwFrame* frame);
void fn_801543B4(Light801302B0* light);
void fn_80159798(void* world);
void fn_8012ECE0(void);
s32 fn_800421C8(void* archive, const char* name);
void fn_80196D00(void);
}

struct Manager801302B0 {
	s32 state;                // 0x0
	s32 nextState;            // 0x4
	RwCamera* camera;         // 0x8
	TObject* object;          // 0xC
	Handler801302B0* handler; // 0x10

	Manager801302B0()
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
		Handler801302B0* entry = lbl_8042C77C;

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

	// Ends a camera update still open (after a flush, fn_80177C50), deletes the scene object and
	// ends the current handler.
	~Manager801302B0()
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
extern Manager801302B0* lbl_8042C778;

// Renders the scene in two camera passes: sets the far distance (through the game context
// lbl_8042C1F8 when there is one, otherwise lbl_8042EE68), clears the camera with the colour
// lbl_8042AEB0, adds the camera and the lights to the world, then renders the scene object from the
// camera placed at lbl_8028AEA8 (fn_80018064) and again from lbl_8028AEB4 (fn_80017AEC), each pass
// inside a camera update and the context's begin/end hooks; finally removes the camera and lights,
// flushes (fn_80177C50) and shows the raster.
void fn_801302B0(Manager801302B0* manager)
{
	RwFrame* frame;

	if (lbl_8042C1F8 != 0) {
		fn_8004DC80(lbl_8042C1F8, 0);
	} else {
		fn_8019CD68(GetCurrentCameraPointer(), lbl_8042EE68);
	}
	fn_8019CF28(GetCurrentCameraPointer(), lbl_8042AEB0, 3);
	fn_8015B8E8(lbl_8042C780, GetCurrentCameraPointer());
	if (lbl_8042C784[0] != 0) {
		fn_8015BD84(lbl_8042C780, lbl_8042C784[0]);
	}
	if (lbl_8042C784[1] != 0) {
		fn_8015BD84(lbl_8042C780, lbl_8042C784[1]);
	}

	frame = ((Camera801302B0*)GetCurrentCameraPointer())->frame;
	if (frame != 0) {
		fn_8019EB94(frame, &lbl_8028AEA8, 0);
	}
	if (fn_8019CC28(GetCurrentCameraPointer()) != 0) {
		if (lbl_8042C1F8 != 0) {
			fn_8004D650(lbl_8042C1F8);
		}
		if (manager->object != 0) {
			fn_80018064(manager->object);
		}
		if (lbl_8042C1F8 != 0) {
			fn_8004D678(lbl_8042C1F8);
		}
		fn_8019CC00(GetCurrentCameraPointer());
	}

	frame = ((Camera801302B0*)GetCurrentCameraPointer())->frame;
	if (frame != 0) {
		fn_8019EB94(frame, &lbl_8028AEB4, 0);
	}
	if (fn_8019CC28(GetCurrentCameraPointer()) != 0) {
		if (lbl_8042C1F8 != 0) {
			fn_8004D650(lbl_8042C1F8);
		}
		if (manager->object != 0) {
			fn_80017AEC(manager->object);
		}
		if (lbl_8042C1F8 != 0) {
			fn_8004D678(lbl_8042C1F8);
		}
		fn_8019CC00(GetCurrentCameraPointer());
	}

	fn_8015B93C(lbl_8042C780, GetCurrentCameraPointer());
	if (lbl_8042C784[0] != 0) {
		fn_8015BE24(lbl_8042C780, lbl_8042C784[0]);
	}
	if (lbl_8042C784[1] != 0) {
		fn_8015BE24(lbl_8042C780, lbl_8042C784[1]);
	}
	fn_80177C50();
	RsCameraShowRaster(GetCurrentCameraPointer());
}

// Sets the state the manager enters once its scene object has no children.
void fn_80130464(s32 state)
{
	if (lbl_8042C778 != 0) {
		lbl_8042C778->nextState = state;
	}
}

// Sets the handler table (HYPOTHESIS: passed through a pointer to the table pointer).
void fn_80130478(Handler801302B0** table)
{
	lbl_8042C77C = *table;
}

// Steps the manager: updates its scene object (fn_80018368) and, once the object has no children,
// enters the requested state. Renders the scene (fn_801302B0) and returns whether the manager is
// still running (state other than 3); returns 0 without a manager.
s32 fn_80130484(void)
{
	Manager801302B0* manager = lbl_8042C778;

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
		Light801302B0* light = lbl_8042C784[i];
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

	lbl_8042C778 = new Manager801302B0;
	if (lbl_8042C1F8 != 0) {
		lbl_8042C20C    = lbl_8042EE68;
		lbl_802C216C[0] = lbl_8042EE84;
	}
}
}
