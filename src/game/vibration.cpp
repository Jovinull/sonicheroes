#include "types.h"

// The controller-side vibration task. The PS2 beta symbols identify this
// family as SetVibration and TObjVibration's constructor, Exec and destructor.
// On GameCube, the four functions share the TObjVibration vtable, class-name
// string and four-entry task array, while their contiguous exception records
// establish the complete translation-unit boundary.

struct GameState {
	s8 values[0x2d];
};

struct THeapCtrl;

extern "C" THeapCtrl* lbl_8042C148;
extern "C" void* fn_80018A34(THeapCtrl*, u32);

struct TObject {
	u8 pad0[4];
	u16 flags;
	u8 pad6[0x12];
	void** vtable;

	static void* operator new(unsigned long size) { return fn_80018A34(lbl_8042C148, size); }
	static void operator delete(void*);
	TObject(TObject*);
};

struct VibrationTask : TObject {
	u8 pad1c[0xc];
	s8 controller;
	s8 mode;
	s8 strength;
	s8 duration;
	s32 start;
	s32 end;
	s32 counter;

	VibrationTask(TObject*);
};

extern "C" {
void PADControlMotor(s32, u32);
void fn_80018818(void*, void*);
void dtor_800186D0(void*, s32);
void fn_800189A4(void*, void*);

extern s32 lbl_8029BBD0[0x100];
extern s32 lbl_802399A0[3];
extern GameState* lbl_8042C180;
extern TObject* lbl_8042C110;
extern u32 lbl_8042AEC0;

void fn_8001F600();
void fn_8001F674(s32, s32, s32, s32, s32, s32);
void fn_8001F894(VibrationTask*);
VibrationTask* fn_8001F92C(VibrationTask*, s32);
void fn_8001898C();
void fn_80018984();
void fn_80018988();
void fn_80018950();
void fn_80018954();
void fn_80017854();
void fn_80018958();
}

extern void* lbl_80241328[12];

inline TObject::TObject(TObject* parent)
{
	fn_80018818(this, parent);
}

inline VibrationTask::VibrationTask(TObject* parent)
    : TObject(parent)
{
	vtable                    = lbl_80241328;
	counter                   = 0;
	*(u32*)this               = lbl_8042AEC0;
	*(u16*)((u8*)this + 0x1e) = 0x38;
}

VibrationTask* lbl_80241308[4] = { 0, 0, 0, 0 };
char lbl_80241318[16]          = "TObjVibration";
void* lbl_80241328[12]         = {
	0,
	0,
	(void*)fn_8001F92C,
	(void*)fn_8001F894,
	(void*)fn_8001898C,
	(void*)fn_80018984,
	(void*)fn_80018988,
	(void*)fn_80018950,
	(void*)fn_80018954,
	(void*)fn_80017854,
	(void*)fn_80018958,
	0,
};

inline void updateVibrationTask(s32 controller, s32 mode, s32 strength, s32 duration, s32 amplitude)
{
	// Keep the construction and updates in their original inline helper.
	// Besides avoiding a redundant load, this lets GC/1.3.2 use the same
	// nonvolatile register for the existing task and the exception-safe new
	// result, which is also recorded in the constructor cleanup action.
	VibrationTask** taskSlot = &lbl_80241308[controller];
	VibrationTask* task      = *taskSlot;
	if (task == 0) {
		task      = new VibrationTask(lbl_8042C110);
		*taskSlot = task;
	}
	task->controller = controller;
	task->mode       = mode;
	task->strength   = strength;
	task->duration   = duration;
	task->start      = 0;
	task->end        = amplitude + 1;
	task->counter    = 0;
}

extern "C" void fn_8001F600()
{
	for (s32 i = 0; i < 2; i++) {
		if (lbl_8029BBD0[i] != 0) {
			PADControlMotor(lbl_802399A0[i], 2);
		}
	}
}

#pragma opt_propagation off
extern "C" void fn_8001F674(
    s32 player, s32 strength, s32 duration, s32 amplitude, s32 unused1, s32 unused2)
{
	s32 controller;
	s32 mode;

	if (lbl_8042C180->values[0x15] == 0) {
		return;
	}
	if (lbl_8042C180->values[0x18] == 2) {
		return;
	}
	s32 playerMode = lbl_8042C180->values[0x1e];
	if (playerMode == 0 && player != 0) {
		return;
	}
	if (playerMode != 0 && lbl_8042C180->values[0x22] != 0) {
		return;
	}

	controller = -1;
	if (lbl_8029BBD0[player] != 0) {
		controller = lbl_802399A0[player];
	}
	if (controller == -1) {
		return;
	}

	if (strength > 7) {
		strength = 7;
	} else if (strength < -7) {
		strength = -7;
	}
	if (strength == 1) {
		strength = 2;
	} else if (strength == -1) {
		strength = -2;
	}
	if (duration > 59) {
		duration = 59;
	} else if (duration < 15) {
		duration = 15;
	}
	if (amplitude > 255) {
		amplitude = 255;
	}
	if (amplitude < 0) {
		amplitude = 0;
	}

	if (amplitude == 0) {
		mode = 1;
		f32 amplitudeValue;
		f64 absoluteStrength = __fabs((f32)strength);
		amplitudeValue       = (f32)amplitude;
		f32 adjusted         = amplitudeValue + ((f32)absoluteStrength - 1.0f);
		amplitude            = (s32)adjusted;
	} else {
		mode = 2;
	}

#pragma opt_propagation reset
	updateVibrationTask(controller, mode, strength, duration, amplitude);
}

extern "C" void fn_8001F894(VibrationTask* task)
{
	if (lbl_8042C180->values[0x2b] == 1) {
		task->flags |= 1;
		return;
	}
	if (task->counter == 1) {
		PADControlMotor(task->controller, 1);
	}
	if (task->counter > task->end) {
		task->flags |= 1;
	} else {
		task->counter++;
	}
}

extern "C" VibrationTask* fn_8001F92C(VibrationTask* task, s32 shouldDelete)
{
	if (task != 0) {
		task->vtable = lbl_80241328;
		if (lbl_80241308[task->controller] == task) {
			lbl_80241308[task->controller] = 0;
			if (task->mode == 3) {
				PADControlMotor(task->controller, 0);
			} else {
				PADControlMotor(task->controller, 2);
			}
		}
		dtor_800186D0(task, 0);
		if ((s16)shouldDelete > 0) {
			fn_800189A4(lbl_8042C148, task);
		}
	}
	return task;
}
