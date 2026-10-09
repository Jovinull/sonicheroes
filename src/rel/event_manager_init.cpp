#include "game/effect/eff_bomb.h"
#include "game/one.h"
#include "MSL_C/string.h"

// InitEventManager, the PS2 build's name for the function that sets up a
// stage's event playback: the same 97 instructions in the thirteen stage
// modules that share the engine core, at a different address and under a
// different placeholder name in each, so each module's splits.txt names its
// own range and its symbols.txt gives it this name.
//
// It creates the EventManager under the task at lbl_8042C104 and the
// EventScript, keeping them in what the PS2 build calls EventManagerTp and
// EventScriptTp (lbl_8042C6E4 and lbl_8042C6E0 here), and returns whether the
// manager exists. Both allocations are real new-expressions; the manager's
// constructor and Init are inlined, the script's constructor is not.
//
// Init gives the manager a 256 KiB buffer and a ONEFILE reading into it, then
// clears its state, the fourteen scene slots (each marked free with -1) and
// the sixteen entries after them. The slot is reached through a local pointer
// and the two loops have their own counters, which is how the original
// spreads them over five saved registers.

struct EventSlot {
	u8 unk00[0x44];
	s32 id; // 0x44
	u8 unk48[0xA4 - 0x48];
};

struct EventEntry {
	u8 unk00[0x50];
};

class EventScript
{
public:
	u8 unk00[0x94];
	EventScript();
};

extern "C" void* fn_80012994(u32 size);
extern "C" TObject* lbl_8042C104;

class EventManager : public TObject
{
public:
	s32 unk28;                // 0x28
	s32 unk2C;                // 0x2C
	u8 unk30[4];              // 0x30
	s32 unk34;                // 0x34
	s32 unk38;                // 0x38
	s32 unk3C;                // 0x3C
	u8 unk40[4];              // 0x40
	s32 unk44;                // 0x44
	EventSlot slots[14];      // 0x48
	EventEntry entries[16];   // 0x940
	s32 unkE40;               // 0xE40
	u8 unkE44[0x1C];          // 0xE44
	void* buffer;             // 0xE60
	ONEFILE* file;            // 0xE64
	u8 unkE68[0xFA8 - 0xE68]; // 0xE68

	EventManager(TObject* parent)
	    : TObject(parent)
	{
		Init();
	}

	void Init()
	{
		buffer          = fn_80012994(0x40000);
		file            = new ONEFILE(NULL, 0);
		file->exBuffer  = buffer;
		file->showError = 0;
		unk28           = -1;
		unk34           = 0;
		unk2C           = 0;
		unkE40          = 0;
		unk38           = 0;
		unk3C           = 0;
		unk44           = 0;
		for (int i = 0; i < 14; i++) {
			EventSlot* slot = &slots[i];
			memset(slot, 0, sizeof(EventSlot));
			slot->id = -1;
		}
		for (int j = 0; j < 16; j++) {
			memset(&entries[j], 0, sizeof(EventEntry));
		}
	}

	virtual ~EventManager();
	virtual void Exec();
	virtual void Disp();
	virtual void TDisp();
};

extern "C" EventScript* lbl_8042C6E0;
extern "C" EventManager* lbl_8042C6E4;

s32 InitEventManager()
{
	lbl_8042C6E4 = new EventManager(lbl_8042C104);
	lbl_8042C6E0 = new EventScript();
	return lbl_8042C6E4 != NULL;
}
