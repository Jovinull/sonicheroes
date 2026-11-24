// Runs fn_80137D0C for a team (lbl_80303DC8[team]) with the kind of its player (0x114, byte 0x761)
// and its byte 0x110. When the task root lbl_8042C2A0 exists it does so through a new task
// (vtable lbl_8028C388, class name lbl_8042BC68, display priority 0x30) whose inlined constructor
// stores the team and the argument and makes the call, and returns -1; otherwise it calls
// fn_80137D0C directly and returns its result. A team without an entry returns -1. The class and
// the roles are UNKNOWN.
#include "types.h"

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

// Local view of TObject for an inlined constructor: the vtable pointer is a data member, the
// destructor is declared for the exception cleanup and operator delete is the out-of-line
// __dl__7TObjectFPv, as the retail exception table shows.
class TObject : public TObjectBase
{
public:
	TObject(TObject* parent);
	~TObject();
	static void* operator new(unsigned long size) { return lbl_8042C148->Malloc(size); }
	static void operator delete(void* p);

	void* vtable; // 0x18
	u16 ExecTime, DispTime, TDispTime, PDispTime, ImmAftSetRasterTime;
};

struct Player801379EC {
	u8 pad0[0x761];
	s8 kind; // 0x761
};

struct Team801379EC {
	u8 pad0[0x110];
	s8 f110; // 0x110
	u8 pad111[0x114 - 0x111];
	Player801379EC* player; // 0x114
};

extern "C" {
extern Team801379EC* lbl_80303DC8[];
extern TObject* lbl_8042C2A0;
extern void* lbl_8028C388[];
extern char* lbl_8042BC68;
s32 fn_80137D0C(void* a, s32 kind, s32 b);
}

class Obj801379EC : public TObject
{
public:
	Obj801379EC(TObject* parent, void* a, s32 team)
	    : TObject(parent)
	{
		vtable     = lbl_8028C388;
		ClassName  = lbl_8042BC68;
		DispTime   = 0x30;
		f28        = 0;
		this->a    = a;
		this->team = team;
		if (lbl_80303DC8[this->team] != NULL) {
			fn_80137D0C(
			    this->a, lbl_80303DC8[this->team]->player->kind, lbl_80303DC8[this->team]->f110);
		}
	}

	s16 f28;  // 0x28
	s16 team; // 0x2A
	void* a;  // 0x2C
};

extern "C" s32 fn_801379EC(void* a, s32 team)
{
	if (lbl_80303DC8[team] == NULL) {
		return -1;
	}
	TObject* parent = lbl_8042C2A0;
	if (parent != NULL) {
		new Obj801379EC(parent, a, team);
		return -1;
	}
	return fn_80137D0C(a, lbl_80303DC8[team]->player->kind, lbl_80303DC8[team]->f110);
}
