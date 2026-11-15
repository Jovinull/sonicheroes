// Tears down the screen objects: deletes the tasks lbl_8042C238 and lbl_8042C248, and for the
// screen object lbl_8042C1F8 destroys its rasters (fn_801A173C; the four at +0x30 and +0x44, then
// the camera's frame buffer +0x2C and z buffer +0x40, cleared in the camera at +0x60/+0x64),
// detaches and destroys the camera's frame (fn_801A5370, fn_8019E480) and the camera itself (+0x28,
// fn_8019D178), and deletes the object. HYPOTHESIS: RwRasterDestroy, RwCameraSetFrame,
// RwFrameDestroy and RwCameraDestroy; the field names are UNKNOWN. NonMatching (register allocation
// only; same instructions otherwise): the retail loop keeps the two NULL stores in two saved
// registers copied from the counter's initial 0 (mr r30/r31, r29), which makes the prologue save
// r27..r31 with _savegpr_27; MWCC shares one zero (li r31, 0) and saves four registers. Tried: an
// inline per store, a plain loop body, a setter taking the value, u32/long/int counters, distinct
// element types, array base locals, opt_common_subs and opt_loop_invariants off. Same family as
// fn_80090F9C.
#include "game/enemy/e_obj_enemy.h"

struct Camera8004EF98 {
	u8 pad0[0x4];
	void* frame; // 0x4
	u8 pad8[0x60 - 0x8];
	void* frameBuffer; // 0x60
	void* zBuffer;     // 0x64
};

class Screen8004EF98 : public TObject
{
public:
	Camera8004EF98* camera; // 0x28
	void* frameBuffer;      // 0x2C
	void* rasters30[4];     // 0x30
	void* zBuffer;          // 0x40
	void* rasters44[4];     // 0x44
};

extern "C" {
extern TObject* lbl_8042C238;
extern TObject* lbl_8042C248;
extern Screen8004EF98* lbl_8042C1F8;
void fn_801A173C(void* raster);
void fn_801A5370(Camera8004EF98* camera, void* frame);
void fn_8019E480(void* frame);
void fn_8019D178(Camera8004EF98* camera);
}

static inline void DestroyRaster(void*& raster)
{
	if (raster != NULL) {
		fn_801A173C(raster);
		raster = NULL;
	}
}

extern "C" void fn_8004EF98(void)
{
	if (lbl_8042C238 != NULL) {
		delete lbl_8042C238;
		lbl_8042C238 = NULL;
	}
	if (lbl_8042C248 != NULL) {
		delete lbl_8042C248;
		lbl_8042C248 = NULL;
	}
	Screen8004EF98* screen = lbl_8042C1F8;
	if (screen != NULL) {
		for (s32 i = 0; i < 4; i++) {
			DestroyRaster(screen->rasters30[i]);
			DestroyRaster(screen->rasters44[i]);
		}
		fn_801A173C(screen->frameBuffer);
		screen->camera->frameBuffer = NULL;
		screen->frameBuffer         = NULL;
		fn_801A173C(screen->zBuffer);
		screen->camera->zBuffer = NULL;
		screen->zBuffer         = NULL;
		void* frame             = screen->camera->frame;
		if (frame != NULL) {
			fn_801A5370(screen->camera, NULL);
			fn_8019E480(frame);
		}
		fn_8019D178(screen->camera);
		screen->camera = NULL;
		delete lbl_8042C1F8;
		lbl_8042C1F8 = NULL;
	}
}
