// Destructor of a team object (vtable lbl_8024FD84; the class name is UNKNOWN): calls the
// virtual at +0x30 of each member (count +0x39, players at +0x114), runs fn_8001867C, clears its
// slot in lbl_80303DC8 (team number +0x38) when it is this team, destroys the TObject base and
// frees the object when flags > 0. Returns the object.
#include "types.h"

struct Header8009DEF0 {
	u8 pad00[0x18];
};

// Local view of a player: TObject's nine virtuals, then the one used here.
class Player8009DEF0 : public Header8009DEF0
{
public:
	virtual ~Player8009DEF0();
	virtual void Exec();
	virtual void Disp();
	virtual void TDisp();
	virtual void PDisp();
	virtual void ImmAftSetRaster();
	virtual void Debug();
	virtual void Error(char*);
	virtual void Render();
	virtual void UnknownSlot2C();
	virtual void UnknownSlot30();
};

struct Team8009DEF0 {
	u8 pad0[0x18];
	void* vtable; // 0x18
	u8 pad1C[0x38 - 0x1C];
	s8 number; // 0x38
	s8 count;  // 0x39
	u8 pad3A[0x114 - 0x3A];
	Player8009DEF0* players[3]; // 0x114
};

struct THeapCtrl;

extern "C" {
extern void* lbl_8024FD84[];
extern Team8009DEF0* lbl_80303DC8[];
extern THeapCtrl* lbl_8042C148;
void fn_8001867C(Team8009DEF0* team);
void __dt__7TObjectFv(void* o, s32 flags);
void Free__9THeapCtrlFPv(THeapCtrl* heap, void* p);
}

// Calls the virtual at +0x30 of each member (see fn_8009C618).
static inline void RestartMembers(Team8009DEF0* team)
{
	int i;

	for (i = 0; i < team->count; i++) {
		if (team->players[i] != NULL) {
			team->players[i]->UnknownSlot30();
		}
	}
}

extern "C" Team8009DEF0* fn_8009DEF0(Team8009DEF0* team, s16 flags)
{
	if (team != NULL) {
		team->vtable = lbl_8024FD84;
		RestartMembers(team);
		fn_8001867C(team);
		if (lbl_80303DC8[team->number] == team) {
			lbl_80303DC8[team->number] = NULL;
		}
		__dt__7TObjectFv(team, 0);
		if (flags > 0) {
			Free__9THeapCtrlFPv(lbl_8042C148, team);
		}
	}
	return team;
}
