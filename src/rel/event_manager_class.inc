// EventManager and EventScript, shared by rel/event_manager_init.cpp and the
// units that define the manager's virtuals.

#include "game/effect/eff_bomb.h"
#include "game/one.h"
#include "MSL_C/string.h"

struct EventSlot {
	u8 unk00[0x44];
	s32 id; // 0x44
	u8 unk48[0xA4 - 0x48];
};

struct EventEntry {
	u8 unk00[0x50];
};

// The message board the script shows text on, defined in src/game/message.cpp.
class MESSAGE
{
public:
	u8 unk000[0x1B4];
	MESSAGE(char* name);
	~MESSAGE();
};

class EventScript
{
public:
	u8 unk00[0x44];        // 0x00
	MESSAGE* message;      // 0x44
	s32 unk48;             // 0x48
	u8 unk4C[0x94 - 0x4C]; // 0x4C
	EventScript();
	~EventScript();
	void ScriptTDisp();
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

	// Whether an event is loaded. rel/event_manager_exist.cpp emits the
	// out-of-line copy; the others inline it.
	s32 Exist();

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

	// The first virtual declared is the key function, and the unit that defines
	// it emits the vtable. These are all overrides, whose order does not move
	// their slots: rel/event_manager_disp.cpp (TDisp and Disp) declares the
	// destructor first, the others Exec.
#ifdef EVENT_MANAGER_DTOR_FIRST
	virtual ~EventManager();
#endif
	virtual void Exec();
	virtual void Disp();
	virtual void TDisp();
#ifndef EVENT_MANAGER_DTOR_FIRST
	virtual ~EventManager();
#endif
};

#ifndef EVENT_EXIST_INLINE
#define EVENT_EXIST_INLINE inline
#endif

EVENT_EXIST_INLINE s32 EventManager::Exist()
{
	return unk28 >= 0 ? TRUE : FALSE;
}

extern "C" EventScript* lbl_8042C6E0;
extern "C" EventManager* lbl_8042C6E4;
