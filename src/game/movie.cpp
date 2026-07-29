#include "types.h"

struct TObjectBase {
	u8 kind[4];
	u16 flags;
	u8 pad06[2];
	TObjectBase* prev;
	TObjectBase* next;
	TObjectBase* parent;
	TObjectBase* child;
};

struct THeapCtrl;

extern "C" {
void* fn_80018A34(THeapCtrl*, u32);
void fn_800189A4(THeapCtrl*, void*);
extern THeapCtrl* lbl_8042C148;
}

struct TObject : public TObjectBase {
	TObject(TObject* parent);
	virtual ~TObject();
	virtual void StartFadeOut();
	virtual void Virtual1();
	virtual void Exec();
	virtual void Disp();
	virtual void ImmAftSetRaster();
	virtual void Debug();
	virtual void Error(char* message);
	virtual void Render();

	u16 field1C;
	u16 field1E;
	u16 field20;
	u16 pad22;
	u16 field24;
	u16 pad26;

	static void* operator new(unsigned long size) { return fn_80018A34(lbl_8042C148, size); }
	static void operator delete(void* object) { fn_800189A4(lbl_8042C148, object); }
};

class MovieTask : public TObject
{
public:
	MovieTask(TObject* parent);
	virtual ~MovieTask();
	virtual void StartFadeOut();
	virtual void Virtual1();

	s32 counter;
};

// The PS2 beta has no counterpart for this GameCube-only task: its movie.cpp
// contains overlay glue, while its unrelated MOVIESCRIPT lives in
// movieScript.cpp.  MovieTask and Virtual1 are therefore neutral descriptive
// guesses.  StartFadeOut is independently established by its retail TObject
// vtable slot.

struct GameSettings {
	u8 pad00[0x1E];
	s8 field1E;
};

struct EventController : public TObject {
	virtual void E2C();
	virtual void E30();
	virtual void E34();
	virtual void E38();
	virtual void E3C();
	virtual void E40();
	virtual void E44();
	virtual void E48();
	virtual void E4C();
	virtual void E50();
	virtual void E54();
	virtual void E58();
	virtual void E5C();
	virtual void E60();
	virtual void E64();
	virtual void E68();
	virtual void E6C();
	virtual void E70(s32);
};

extern "C" {
void fn_800194E0(void*);
void fn_80019540(void*);
s32 fn_80018E6C(void*);
void fn_800197D4(void*);

extern TObject* lbl_8042C104;
extern EventController* lbl_8042C170;
extern GameSettings* lbl_8042C180;
extern u8 lbl_8029C310[];
extern char* lbl_8042BC78;
}

extern MovieTask* lbl_8042C7E8;
// This task-list label is referenced through lbl_8042BC78.  The retail atom is
// 16 bytes: the string terminator is followed by one zero alignment byte.
char CL_SpAdvStgFailed[16] = "SpAdvStgFailed";

void MovieTask::Virtual1() { }

void MovieTask::StartFadeOut()
{
	if (counter++ >= 180) {
		if (lbl_8042C180->field1E == 0)
			fn_80019540(lbl_8029C310);
		flags |= 1;
	}
}

MovieTask::~MovieTask()
{
	lbl_8042C7E8 = 0;
}

inline MovieTask::MovieTask(TObject* parent)
    : TObject(parent)
{
	*(char**)&kind = lbl_8042BC78;
	field1E        = sizeof(MovieTask);
	fn_800194E0(lbl_8029C310);
	if (fn_80018E6C(lbl_8029C310))
		lbl_8042C170->E4C();
	else
		lbl_8042C170->E54();
	lbl_8042C170->E70(1);
	fn_800197D4(lbl_8029C310);
	counter = 0;
}

// Descriptive name inferred from the sole GC caller and the constructed type;
// the PS2 beta does not contain an equivalent task factory.
void InitMovieTask()
{
	if (lbl_8042C7E8 == 0)
		lbl_8042C7E8 = new MovieTask(lbl_8042C104);
}
