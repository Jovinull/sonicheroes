// EventManager and EventScript, shared by rel/event_manager_init.cpp and the
// units that define the manager's virtuals.

#include "game/effect/eff_bomb.h"
#include "game/one.h"
#include "MSL_C/string.h"
#include "game/object.h"

struct EventSlot {
	u8 unk00[0x44];
	s32 id;                // 0x44
	u8 unk48[0x4];         // 0x48
	struct RpClump* clump; // 0x4C
	u8 unk50[0xA4 - 0x50];
};

struct EventEntry {
	char name[0x40];       // 0x00: the file the entry was loaded from
	struct RpClump* clump; // 0x40
	u8 unk44[0x4];         // 0x44
	void* interpolator;    // 0x48
	u8 unk4C[0x4];         // 0x4C
}; // 0x50

// What the script keeps for an extra object of the scene.
struct SceneMemEtcObj {
	u8 unk00[0x40];                     // 0x00
	struct RpClump* clump;              // 0x40
	u8 unk44[0x8];                      // 0x44
	struct RpHAnimHierarchy* hierarchy; // 0x4C
};

// What the script keeps for a player of the scene, in the player's slot: its
// models and the eyelid clumps (connectCurrentMabuta shows one at a time).
struct SceneMemPlayerObj {
	struct RpClump* body;      // 0x00
	u8 unk04[0x14];            // 0x04
	struct RpClump* head;      // 0x18
	u8 unk1C[0x8];             // 0x1C
	struct RpClump* mabuta[8]; // 0x24
	s32 mabutaNo;              // 0x44: the one shown, or -1
	s32 mabutaCount;           // 0x48
};

// One of the event's files kept in ARAM: loadSceneFromAram copies it back
// into main memory and releaseSceneAll frees it.
struct EventObject {
	s32 no;     // 0x00
	s32 scene;  // 0x04: the scene file's number
	void* aram; // 0x08
	u32 size;   // 0x0C
	s32 frames; // 0x10: the length of the scene's camera motion
}; // 0x14

// The message board the script shows text on, defined in src/game/message.cpp.
class MESSAGE
{
public:
	u8 unk000[0x1B4];
	MESSAGE(char* name);
	~MESSAGE();
	s32 LoadFontFile(char* name);
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
	s32 voiceOffset;    // 0x40: the event's first voice
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
	s32 LoadScript(s32 event);
};

extern "C" void* fn_80012994(u32 size);
extern "C" TObject* lbl_8042C104;

class EventManager : public TObject
{
public:
	s32 unk28;               // 0x28
	s32 unk2C;               // 0x2C
	s32 unk30;               // 0x30
	s32 unk34;               // 0x34
	void* texDict;           // 0x38: the event's texture dictionary
	s32 unk3C;               // 0x3C
	u8 unk40[4];             // 0x40
	s32 unk44;               // 0x44
	EventSlot slots[14];     // 0x48
	EventEntry entries[16];  // 0x940
	s32 unkE40;              // 0xE40
	u8 unkE44[0xC];          // 0xE44
	s32 unkE50;              // 0xE50
	u8 unkE54[0xC];          // 0xE54
	void* buffer;            // 0xE60
	ONEFILE* file;           // 0xE64
	EventObject objects[16]; // 0xE68

	EventManager(TObject* parent);

	// Whether an event is loaded. rel/event_manager_exist.cpp emits the
	// out-of-line copy; the others inline it.
	s32 Exist();
	s32 releaseScene(s32* scenes);
	s32 checkFileKind(char* name, s32* kind);
	s32 releaseSceneAll();
	s32 ReleaseEvent();
	s32 LoadEvent(s32 event);
	void releaseSceneExtObjs();
	s32 loadSceneFromAram(s32 object);
	s32 loadEventToAMem();
	void setAnimationExt(SceneMemEtcObj* object, f32 time);
	void removeClump(struct RpClump* clump);
	void addClump(struct RpClump* clump);
	void connectCurrentMabuta(SceneMemPlayerObj* player, s32 mabuta);
	s32 evPlayerNo2playerNo(s32 player);
	void showHidePlayer(s32 player, s32 show);
	void setCheeseFrame();
	s32 getPlayerNumber(s32 player, s32 unused);
	struct RpClump* getPlayerBodyClump(s32 player);
	void setDAnimation(struct RpDMorphAnimation* animation, struct RpAtomic* atomic, f32 time);
	void setAnimation(struct RpHAnimHierarchy* hierarchy, f32 time);
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

void ConvertU32Array(u8* data, s32 size);
void ConvertU16Array(u8* data, s32 size);

// It hands the script the manager's file table and swaps the script data's
// byte order. Only the units that define EVENT_UPDATE_ENDIAN_INLINE see the
// body: rel/event_script_load.cpp (inline) and rel/event_script_update_endian.cpp
// (empty, for the out-of-line copy); EventScript's constructor takes its address
// and must not emit a copy of its own.
s32 UpdateEndianandOthers();

#ifdef EVENT_UPDATE_ENDIAN_INLINE
EVENT_UPDATE_ENDIAN_INLINE s32 UpdateEndianandOthers()
{
	if (lbl_8042C6E0 != NULL) {
		memcpy(EventScript::scriptData.info, lbl_8042C6E4->objects, 0x140);
		ConvertU32Array((u8*)&EventScript::scriptData, 0x150);
		ConvertU16Array(EventScript::scriptData.halves, 0x2000);
		ConvertU16Array(EventScript::scriptData.halves2, 0x8C00);
		ConvertU32Array(EventScript::scriptData.words, 0x38);
		return 1;
	}
	return 0;
}
#endif

#ifndef EVENT_INIT_INLINE
#define EVENT_INIT_INLINE inline
#endif
#ifndef EVENT_CTOR_INLINE
#define EVENT_CTOR_INLINE inline
#endif

EVENT_INIT_INLINE void EventManager::Init()
{
	unk28   = -1;
	unk34   = 0;
	unk2C   = 0;
	unkE40  = 0;
	texDict = NULL;
	unk3C   = 0;
	unk44   = 0;
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

extern "C" void* fn_8015BD78(struct RpClump* clump);
extern "C" void fn_8015BBF8(void* world, struct RpClump* clump);
extern "C" u8* lbl_8042C1D0;
extern "C" void fn_8015BB08(void* world, struct RpClump* clump);
extern "C" void fn_8020D02C(void* interpolator, f32 time);
extern "C" void fn_8013FC30(RpHAnimHierarchy* hierarchy);

// The manager's own functions inline these seven; rel/event_manager_remove_clump.cpp,
// rel/event_manager_add_clump.cpp, rel/event_manager_mabuta.cpp,
// rel/event_manager_player_no.cpp, rel/event_manager_player_number.cpp,
// rel/event_manager_release_all.cpp and rel/event_manager_set_animation.cpp
// define their macro empty to emit the out-of-line copy.
#ifndef EVENT_REMOVE_CLUMP_INLINE
#define EVENT_REMOVE_CLUMP_INLINE inline
#endif
#ifndef EVENT_ADD_CLUMP_INLINE
#define EVENT_ADD_CLUMP_INLINE inline
#endif
#ifndef EVENT_PLAYER_NO_INLINE
#define EVENT_PLAYER_NO_INLINE inline
#endif
#ifndef EVENT_RELEASE_ALL_INLINE
#define EVENT_RELEASE_ALL_INLINE inline
#endif
#ifndef EVENT_PLAYER_NUMBER_INLINE
#define EVENT_PLAYER_NUMBER_INLINE inline
#endif
#ifndef EVENT_MABUTA_INLINE
#define EVENT_MABUTA_INLINE inline
#endif
#ifndef EVENT_SET_ANIMATION_INLINE
#define EVENT_SET_ANIMATION_INLINE inline
#endif

EVENT_REMOVE_CLUMP_INLINE void EventManager::removeClump(struct RpClump* clump)
{
	if (clump != NULL) {
		void* world = fn_8015BD78(clump);
		if (world != NULL) {
			fn_8015BBF8(world, clump);
		}
	}
}

// It adds a clump that is in no world to the stage's world.
EVENT_ADD_CLUMP_INLINE void EventManager::addClump(struct RpClump* clump)
{
	if (clump != NULL && fn_8015BD78(clump) == NULL) {
		fn_8015BB08(*(void**)(lbl_8042C1D0 + 0x7258), clump);
	}
}

// It swaps the player's eyelid clump shown in the world.
EVENT_MABUTA_INLINE void EventManager::connectCurrentMabuta(SceneMemPlayerObj* player, s32 mabuta)
{
	if (player->mabutaNo >= 0) {
		struct RpClump* clump = player->mabuta[player->mabutaNo];
		if (clump != NULL) {
			removeClump(clump);
		}
	}
	if (mabuta >= 0) {
		struct RpClump* clump = player->mabuta[mabuta];
		if (clump != NULL) {
			addClump(clump);
		}
	}
	player->mabutaNo = mabuta;
}

extern "C" const s32 eventPlayerNumbers[12];

// The player an event's player number stands for, from the module's table of
// twelve, or -1 past it.
EVENT_PLAYER_NO_INLINE s32 EventManager::evPlayerNo2playerNo(s32 player)
{
	if (player >= 12) {
		return -1;
	}
	return eventPlayerNumbers[player];
}

extern "C" void fn_800D075C(void* aram);
extern "C" void fn_801A46D0(void* dictionary);

// It releases every scene, frees the event's files kept in ARAM and destroys
// the event's texture dictionary, answering what releaseScene answered.
EVENT_RELEASE_ALL_INLINE s32 EventManager::releaseSceneAll()
{
	s32 result = releaseScene(NULL);

	unk3C = 0;
	for (int i = 0; i < 16; i++) {
		if (objects[i].aram != NULL) {
			fn_800D075C(objects[i].aram);
			objects[i].aram = NULL;
		}
	}
	if (texDict != NULL) {
		fn_801A46D0(texDict);
	}
	return result;
}

// A player of the game, as the event sees it.
struct EventPlayerWork {
	s8 unk00;              // 0x000
	s8 characterNo;        // 0x001
	u8 unk002[0x17E];      // 0x002
	struct RpClump* clump; // 0x180: the body's model
};

extern "C" EventPlayerWork* lbl_802AD0D0[8];

// The index of the game's player that plays the event's player number, or -1.
EVENT_PLAYER_NUMBER_INLINE s32 EventManager::getPlayerNumber(s32 player, s32 unused)
{
	s32 character = evPlayerNo2playerNo(player);
	if (character < 0) {
		return -1;
	}
	for (s32 i = 0; i < 8; i++) {
		if (lbl_802AD0D0[i] == NULL) {
			return -1;
		}
		if (character == lbl_802AD0D0[i]->characterNo) {
			return i;
		}
	}
	return -1;
}

EVENT_SET_ANIMATION_INLINE void EventManager::setAnimation(RpHAnimHierarchy* hierarchy, f32 time)
{
	fn_8020D02C(hierarchy->currentAnim, time);
	fn_8013FC30(hierarchy);
}

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
	texDict = texLoadTexDictionaryFile(name);
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

// LoadEvent inlines the release; rel/event_manager_release_event.cpp defines
// the macro empty to emit the out-of-line copy.
#ifndef EVENT_RELEASE_EVENT_INLINE
#define EVENT_RELEASE_EVENT_INLINE inline
#endif

extern "C" void* lbl_8042C1F8;
extern "C" void fn_8004DE10(void* sound, s32 kind);
extern "C" void fn_801329AC();
extern "C" void fn_80018C64();
extern "C" void fn_8009C704(void* players, s32 value);
extern "C" void fn_8004ED48(void* sound);

// It ends the loaded event: the event's sound, the script, every scene with its
// files and textures, the event's file, and the manager's state; then it puts
// the game back. With no event loaded it only turns the mode switch off.
EVENT_RELEASE_EVENT_INLINE s32 EventManager::ReleaseEvent()
{
	if (Exist()) {
		if (unkE50 != 0) {
			fn_8004DE10(lbl_8042C1F8, 0xE);
		}
		lbl_8042C6E0->ReleaseScript();
		releaseSceneAll();
		file->ReleaseOneFile();
		Init();
		fn_801329AC();
		SetModeSwitch__10MODESWITCHF15MODESWITCH_ENUMi(lbl_8042C180, 0x32, -1);
		fn_80018C64();
		fn_8009C704(lbl_80303DC8, 0);
		fn_8004ED48(lbl_8042C1F8);
		return 1;
	}
	SetModeSwitch__10MODESWITCHF15MODESWITCH_ENUMi(lbl_8042C180, 0x32, -1);
	return 0;
}

// _loadEvent inlines the load; rel/event_manager_load_event.cpp defines the
// macro empty to emit the out-of-line copy.
#ifndef EVENT_LOAD_EVENT_INLINE
#define EVENT_LOAD_EVENT_INLINE inline
#endif

extern "C" void fn_80018C4C();

EVENT_LOAD_EVENT_INLINE s32 EventManager::LoadEvent(s32 event)
{
	if (event < 0) {
		return 0;
	}
	ReleaseEvent();
	unk28 = event;
	if (loadEventToAMem()) {
		unkE50 = 0;
		lbl_8042C6E0->LoadScript(event);
		fn_80018C4C();
		return 1;
	}
	return 0;
}
#endif
