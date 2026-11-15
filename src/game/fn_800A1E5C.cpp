// Destructor of the team-blast task (the TObject class with vtable lbl_8024FE84): for each of the
// four teams (lbl_80303DC8) it clears the team flags 0x8 and 0x10 and the flag 0x10 of each member
// (+0x114, count +0x39), runs fn_8009C704(team, 0) and calls each member's virtual at vtable +0x2C;
// then it runs fn_80019778 on the stage (lbl_8029C310), clears lbl_8042C310 when it points here,
// runs the TObject destructor and frees the object when the delete flag is positive.
// HYPOTHESIS: the roles (team blast end) are UNKNOWN.
// NonMatching (one instruction short): retail reloads a member's flags (+0x4) for the clear after
// testing 0x10; MWCC reuses the tested value. A volatile field reproduces the reload (13 words of
// register swaps remain: the loops' counter and member pointer) but is not plausible source.
// Tried: nested ifs, flag inlines, per-loop counters, opt_common_subs off.

struct MemberBase800A1E5C {
	unsigned char pad0[0x4];
	unsigned short flags; // 0x4 (TObject::Signal)
	unsigned char pad6[0x18 - 0x6];
};

// A team member (a TObject: vtable pointer at +0x18). Only the slot at +0x2C is called; the
// earlier slots are the TObject virtuals. Nothing here is defined, so no vtable is emitted.
class Member800A1E5C : public MemberBase800A1E5C
{
public:
	virtual ~Member800A1E5C();
	virtual void Exec();
	virtual void Disp();
	virtual void TDisp();
	virtual void PDisp();
	virtual void ImmAftSetRaster();
	virtual void Debug();
	virtual void Error(char*);
	virtual void Render();
	virtual void Virtual2C(); // +0x2C
};

struct Team800A1E5C {
	unsigned char pad0[0x4];
	unsigned short flags; // 0x4
	unsigned char pad6[0x39 - 0x6];
	signed char count; // 0x39
	unsigned char pad3A[0x114 - 0x3A];
	Member800A1E5C* members[3]; // 0x114
};

struct Obj800A1E5C {
	unsigned char pad[0x18];
	void* vt; // 0x18
};

extern "C" {
extern unsigned char lbl_8024FE84[];
extern Team800A1E5C* lbl_80303DC8[4];
extern unsigned char lbl_8029C310[];
extern Obj800A1E5C* lbl_8042C310;
extern void* lbl_8042C148;
void fn_8009C704(Team800A1E5C* team, int unknown);
void fn_80019778(void* stage);
void __dt__7TObjectFv(void*, int);
void Free__9THeapCtrlFPv(void*, void*);

Obj800A1E5C* fn_800A1E5C(Obj800A1E5C* o, short flags)
{
	if (o != 0) {
		int i;

		o->vt = lbl_8024FE84;
		for (i = 0; i < 4; i++) {
			Team800A1E5C* team = lbl_80303DC8[i];
			int j;

			if (team == 0) {
				continue;
			}
			team->flags &= ~0x8;
			team->flags &= ~0x10;
			for (j = 0; j < team->count; j++) {
				Member800A1E5C* member = team->members[j];
				if (member != 0 && (member->flags & 0x10)) {
					member->flags &= ~0x10;
				}
			}
			fn_8009C704(team, 0);
			for (j = 0; j < team->count; j++) {
				Member800A1E5C* member = team->members[j];
				if (member != 0) {
					member->Virtual2C();
				}
			}
		}
		fn_80019778(lbl_8029C310);
		if (lbl_8042C310 == o) {
			lbl_8042C310 = 0;
		}
		__dt__7TObjectFv(o, 0);
		if (flags > 0) {
			Free__9THeapCtrlFPv(lbl_8042C148, o);
		}
	}
	return o;
}
}
