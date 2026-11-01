// The base of the special stages' sled link classes (the classes have no PS2
// names), in stage01D and stage07D: rel/bob_link_base.cpp has its destructor,
// which each derived destructor inlines (flags 0, so the object is not freed
// there).

typedef struct TObject {
	const char* className; // 0x00
	u16 signal;            // 0x04
	u8 unk06[0x12];
	void** vtable; // 0x18
	u8 unk1C[0x2];
	u16 dispTime; // 0x1E
	u8 unk20[0x8];
} TObject;

typedef struct BobLink {
	TObject base; // 0x00
	s32 linked;   // 0x28
	s32 slotIn;   // 0x2C
	s32 slotOut;  // 0x30
} BobLink;

extern "C" BobLink* bobLinkCurrent;
extern "C" void* bobLinkVtable[];
extern "C" void* lbl_8042C1F8;
extern "C" void* lbl_8042C148;

extern "C" void __dt__7TObjectFv(TObject* object, s32 flags);
extern "C" void Free__9THeapCtrlFPv(void* heap, TObject* object);
extern "C" void fn_80130F78(s32 kind, void* object);
extern "C" void fn_8004D99C(void* world);
extern "C" void* fn_8004E608(void* world);
extern "C" void fn_8004DEC0(void* world, void* list, s32 slot);

static inline void bobLinkBaseDtor(BobLink* object)
{
	if (object != NULL) {
		object->base.vtable = bobLinkVtable;
		if (object->linked != 0) {
			fn_8004D99C(lbl_8042C1F8);
			fn_8004DEC0(lbl_8042C1F8, fn_8004E608(lbl_8042C1F8), object->slotOut);
			fn_80130F78(0xE, object);
			object->linked = 0;
		}
		if (object == bobLinkCurrent) {
			bobLinkCurrent = NULL;
		}

		__dt__7TObjectFv(&object->base, 0);
	}
}

// One derived destructor: its own vtable, the base destructor, then the free.
#define BOB_LINK_DTOR(name, table)                                                                 \
	extern "C" void* table[];                                                                      \
	extern "C" BobLink* name(BobLink* object, s16 flags)                                           \
	{                                                                                              \
		if (object != NULL) {                                                                      \
			object->base.vtable = table;                                                           \
			bobLinkBaseDtor(object);                                                               \
                                                                                                   \
			if (flags > 0) {                                                                       \
				Free__9THeapCtrlFPv(lbl_8042C148, &object->base);                                  \
			}                                                                                      \
		}                                                                                          \
		return object;                                                                             \
	}
