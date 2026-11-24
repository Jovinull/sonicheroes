#ifndef GAME_PARTICLE_TASK_H
#define GAME_PARTICLE_TASK_H

#include "types.h"

// PARTICLE_TASK as seen by its construction helpers. The class name and its constructor
// PARTICLE_TASK(unsigned int, RwV3d*, sAngle*) are CORROBORATED by the PS2 build (see
// src/game/fn_80062384.cpp for the destructor): a TObject with a PARTICLE_MATERIAL base at 0x28,
// whose vtable part is stored at 0x7C. Only the fields used by the helpers are named.
//
// TObject is a local view: allocation goes through the game heap (lbl_8042C148) and the exception
// cleanup of a new-expression calls the out-of-line __dl__7TObjectFPv, as the retail exception
// tables show.

class TObject;

struct TObjectBase {
	char* ClassName;
	u16 Signal, Tag;
	TObject* Prev;
	TObject* Next;
	TObject* Parent;
	TObject* Child;
};

struct THeapCtrl {
	void* Malloc(u32);
};

extern "C" THeapCtrl* lbl_8042C148;

class TObject : public TObjectBase
{
public:
	~TObject();
	static void* operator new(unsigned long size) { return lbl_8042C148->Malloc(size); }
	static void operator delete(void* p);

	void* vtable; // 0x18
	u16 ExecTime, DispTime, TDispTime, PDispTime, ImmAftSetRasterTime;
};

struct RwV3d;
struct sAngle;

struct RwRGBA {
	u8 red, green, blue, alpha;
};

class PARTICLE_TASK : public TObject
{
public:
	PARTICLE_TASK(unsigned int kind, RwV3d* pos, sAngle* ang);
	// Declared so derived constructors do not make the compiler synthesize one; the destructor is
	// fn_80062384, which keeps its address name, and these helpers never call it.
	~PARTICLE_TASK();

	u8 material[0x2C - 0x28]; // 0x28: start of the PARTICLE_MATERIAL base
	u32 flags;                // 0x2C: bit 28 is set by some helpers (meaning UNKNOWN)
	u8 pad30[0x7C - 0x30];
	void* vtable2; // 0x7C: PARTICLE_MATERIAL part of the vtable
	u8 pad80[0xB4 - 0x80];
};

extern "C" {
// Nonzero while a task is still alive (HYPOTHESIS: the task system's validity check).
s32 fn_80017800(void* task);
}

// Particle task with a colour at 0xB4 (vtable lbl_8024FDDC; the class name is UNKNOWN, the PS2
// build has ColorChange variants of the particle constructors). Its constructor is inlined.
extern "C" u8 lbl_8024FDDC[];

class PtclColorTask : public PARTICLE_TASK
{
public:
	PtclColorTask(unsigned int kind, RwV3d* pos, sAngle* ang, RwRGBA* color)
	    : PARTICLE_TASK(kind, pos, ang)
	{
		vtable      = lbl_8024FDDC;
		vtable2     = lbl_8024FDDC + 0x2C;
		this->color = *color;
	}

	RwRGBA color; // 0xB4
};

extern "C" {
u32 fn_800643E8(void* material);
void fn_800643C0(void* material, u32 flags);
}

// Creates a coloured particle task and sets bit 4 of its PARTICLE_MATERIAL flags; NULL when the
// allocation fails or the task is not alive. fn_8009E9BC inlines it; fn_8009EAA4 is the same body
// written out (retail emits fn_8009E9BC first, so the inlined copy cannot come from that unit).
inline PtclColorTask* CreateColorParticleTask(u32 kind, RwV3d* pos, sAngle* ang, RwRGBA* color)
{
	PtclColorTask* task = new PtclColorTask(kind, pos, ang, color);
	if (task == NULL) {
		return NULL;
	}
	if (fn_80017800(task) == 0) {
		return NULL;
	}
	fn_800643C0(task->material, fn_800643E8(task->material) | 0x10);
	return task;
}

#endif
