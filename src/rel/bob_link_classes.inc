// The special stages' sled link classes as C++ (the classes have no PS2
// names), in stage01D and stage07D: the derived constructors inline the base
// one (rel/bob_link_base.cpp has it as bobLinkCtor), and the copy of this
// that inlining leaves needs real classes. The C view of the same objects is
// rel/bob_link_class.inc.

typedef struct RwV3d {
	f32 x, y, z;
} RwV3d;

typedef struct sAngle {
	s32 x, y, z;
} sAngle;

struct TObjectBase {
	const char* className; // 0x00
	u16 signal;            // 0x04
	u8 unk06[0x12];
};

extern "C" void* lbl_8042C148;
extern "C" void* Malloc__9THeapCtrlFUi(void* heap, u32 size);

class TObject : public TObjectBase
{
public:
	TObject(TObject* parent);
	virtual ~TObject();

	static void* operator new(unsigned long size)
	{
		return Malloc__9THeapCtrlFUi(lbl_8042C148, size);
	}

	u8 unk1C[0x2];
	u16 dispTime; // 0x1E
	u8 unk20[0x8];
}; // 0x28

class BobLink;

extern "C" BobLink* bobLinkCurrent;
extern "C" const char* bobLinkClassName;
extern "C" void* lbl_8042C1F8;
extern "C" TObject* lbl_8042C110;
extern "C" void fn_80130F78(s32 kind, void* object);
extern "C" void fn_80131088(s32 kind, void* object);
extern "C" void fn_8004D99C(void* world);
extern "C" void fn_8004D9B8(void* world);
extern "C" void* fn_8004E608(void* world);
extern "C" void fn_8004DEC0(void* world, void* list, s32 slot);

class BobLink : public TObject
{
public:
	BobLink();
	virtual ~BobLink();

	s32 linked;  // 0x28
	s32 slotIn;  // 0x2C
	s32 slotOut; // 0x30
}; // 0x34

// Takes a linked object's slot out of the world's list and tells the sound
// side.
static inline void bobLinkSlotOut(BobLink* object)
{
	if (object->linked != 0) {
		fn_8004D99C(lbl_8042C1F8);
		fn_8004DEC0(lbl_8042C1F8, fn_8004E608(lbl_8042C1F8), object->slotOut);
		fn_80130F78(0xE, object);
		object->linked = 0;
	}
}

inline BobLink::BobLink()
    : TObject(lbl_8042C110)
{
	className = bobLinkClassName;
	dispTime  = 0x34;

	if (bobLinkCurrent != NULL) {
		BobLink* current = bobLinkCurrent;

		bobLinkSlotOut(current);
		if (current == bobLinkCurrent) {
			bobLinkCurrent = NULL;
		}
		current->signal |= 1;
	}

	linked         = 0;
	slotIn         = 0;
	slotOut        = 0;
	bobLinkCurrent = this;
}

// The target the links attach through.
typedef struct BobLinkTarget {
	s32 mode;     // 0x00
	s32 unk04[3]; // 0x04
	RwV3d dir;    // 0x10
	sAngle ang;   // 0x1C
	u8 unk28[0xC];
	RwV3d at; // 0x34
} BobLinkTarget;

extern "C" BobLinkTarget lbl_803EA4E8;
