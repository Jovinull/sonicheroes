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
	void ReleaseFontFile();
};

// What the script shares with main: a header (the game's word at 0xC and the
// manager's 0x140-byte table at 0x10), two tables of halfwords, a block of
// words and, at 0xAD88, the light table main copies into its CLIGHT.
struct EventScriptData {
	u8 unk0000[0xC];           // 0x0000
	s32 unk000C;               // 0x000C
	u8 info[0x140];            // 0x0010
	u8 halves[0x2000];         // 0x0150
	u8 halves2[0x8C00];        // 0x2150
	u8 words[0x38];            // 0xAD50
	u8 light[0xB1A0 - 0xAD88]; // 0xAD88
};

class EventScript
{
public:
	static EventScriptData scriptData;
	static u8 saveLightBuffer[0x3E0];

	s32 unk00;          // 0x00
	u8 unk04[0x38];     // 0x04
	s32 unk3C;          // 0x3C
	u8 unk40[4];        // 0x40
	MESSAGE* message;   // 0x44
	s32 unk48;          // 0x48
	u8 unk4C[4];        // 0x4C
	void* subtitles;    // 0x50: the language's table
	char bgmName[0x40]; // 0x54: the stream the event plays
	EventScript();
	~EventScript();
	void ScriptTDisp();
	void ReleaseScript();
	void ScriptInit();
};

extern "C" void* fn_80012994(u32 size);
extern "C" TObject* lbl_8042C104;

class EventManager : public TObject
{
public:
	s32 unk28;                // 0x28
	s32 unk2C;                // 0x2C
	s32 unk30;                // 0x30
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

	EventManager(TObject* parent);

	// Whether an event is loaded. rel/event_manager_exist.cpp emits the
	// out-of-line copy; the others inline it.
	s32 Exist();
	void releaseScene(s32* scenes);
	void loadScene(s32 cut);
	void loadEventTexdict();
	void EventRewind();
	void EventPause();
	void EventStart();

	void Init();

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

// The constructor and Init are inline in the units that use them;
// rel/event_manager_ctor.cpp and rel/event_manager_reset.cpp each define one
// macro empty to emit that member's out-of-line copy, which has no caller.
extern "C" EventScript* lbl_8042C6E0;
extern "C" EventManager* lbl_8042C6E4;

#ifndef EVENT_INIT_INLINE
#define EVENT_INIT_INLINE inline
#endif
#ifndef EVENT_CTOR_INLINE
#define EVENT_CTOR_INLINE inline
#endif

EVENT_INIT_INLINE void EventManager::Init()
{
	unk28  = -1;
	unk34  = 0;
	unk2C  = 0;
	unkE40 = 0;
	unk38  = 0;
	unk3C  = 0;
	unk44  = 0;
	for (int i = 0; i < 14; i++) {
		EventSlot* slot = &slots[i];
		memset(slot, 0, sizeof(EventSlot));
		slot->id = -1;
	}
	for (int j = 0; j < 16; j++) {
		memset(&entries[j], 0, sizeof(EventEntry));
	}
}

EVENT_CTOR_INLINE EventManager::EventManager(TObject* parent)
    : TObject(parent)
{
	buffer          = fn_80012994(0x40000);
	file            = new ONEFILE(NULL, 0);
	file->exBuffer  = buffer;
	file->showError = 0;
	Init();
}

#ifndef EVENT_EXIST_INLINE
#define EVENT_EXIST_INLINE inline
#endif

// The manager's own source defines Exist, and its functions inline it; the
// script's source only sees the declaration and calls the out-of-line copy,
// so the script's units define EVENT_SCRIPT_SOURCE first.
#ifndef EVENT_SCRIPT_SOURCE
EVENT_EXIST_INLINE s32 EventManager::Exist()
{
	return unk28 >= 0 ? TRUE : FALSE;
}

extern "C" void* lbl_8042C180;
extern "C" void* lbl_80303DC8;
extern "C" char eventTexdictFormat[];
extern "C" void SetModeSwitch__10MODESWITCHF15MODESWITCH_ENUMi(void* modes, s32 mode, s32 value);
extern "C" void fn_8009D1F8(void* players);
extern "C" int sprintf(char* buffer, const char* format, ...);
void* texLoadTexDictionaryFile(char* name);

// The rewind and its parts are inline where the manager's hooks use them;
// rel/event_manager_texdict.cpp, rel/event_manager_rewind.cpp,
// rel/event_manager_pause.cpp and rel/event_manager_start.cpp each define one
// of these macros empty to emit that member's out-of-line copy.
#ifndef EVENT_TEXDICT_INLINE
#define EVENT_TEXDICT_INLINE inline
#endif
#ifndef EVENT_REWIND_INLINE
#define EVENT_REWIND_INLINE inline
#endif
#ifndef EVENT_PAUSE_INLINE
#define EVENT_PAUSE_INLINE inline
#endif
#ifndef EVENT_START_INLINE
#define EVENT_START_INLINE inline
#endif

EVENT_TEXDICT_INLINE void EventManager::loadEventTexdict()
{
	char name[64];
	sprintf(name, eventTexdictFormat, unk28);
	unk38 = (s32)texLoadTexDictionaryFile(name);
}

EVENT_PAUSE_INLINE void EventManager::EventPause()
{
	if (unk28 >= 0) {
		unk34 = 0;
	}
}

EVENT_START_INLINE void EventManager::EventStart()
{
	if (Exist()) {
		SetModeSwitch__10MODESWITCHF15MODESWITCH_ENUMi(lbl_8042C180, 0x32, unk28);
		fn_8009D1F8(lbl_80303DC8);
		unk34 = 1;
	}
}

EVENT_REWIND_INLINE void EventManager::EventRewind()
{
	unk2C = 0;
	releaseScene(NULL);
	unk3C = 0;
	memset(slots, 0, sizeof(slots));
	memset(entries, 0, sizeof(entries));
	loadEventTexdict();
	loadScene(unk2C++);
	lbl_8042C6E0->ScriptInit();
	EventStart();
	unk30 = 0;
	Exec();
	EventPause();
}
#endif
