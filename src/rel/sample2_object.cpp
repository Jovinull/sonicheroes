#include "types.h"

// TObjSample2, the second of the two sample objects every stage module ships.
//
// The run is .text 0x564 to 0x804, five functions, and it is the same code at
// the same addresses in every stage module, so it is written once here and
// each module's splits.txt names it, the way rel/prolog.c is already shared.
// Each module's symbols.txt renames its own copies to the names below.
//
// Thirteen of the fourteen stage modules carry the run byte for byte; stage40D
// does not, and is left out for the same reason it is left out of rel/prolog.c.
// Its Exec is 0x94 rather than 0xB0 and the run around it does not line up, so
// that module was built from a different revision of the source. Everything
// except the two data symbols also sits at the same addresses in all thirteen;
// stage13D's strings are shorter, so its vtable is at .data 0xA0 rather than
// 0xB0, which the rename in its symbols.txt takes care of.
//
// Four of the five are claimed, 0x564 to 0x740. sample2Create, the factory at
// 0x740, is left to the module: it comes out one instruction short, and the
// missing one is a register copy no source form produces. The original keeps
// the allocator's result in r0 for the null test and copies it into r31 inside
// the branch; the compiler here folds the two into r31 and tests that. About
// twenty five ways of writing it were measured, including `new` with the class
// carrying its own operator new, an inlined construction helper, both orders
// of declaring the two locals, an early return, and a ternary. What decides it
// is the call the construction makes on the second base at 0x28: with that one
// argument written as the object plus nothing, every shape keeps the two
// registers apart, and with it written as the address of the member at 0x28 --
// which is what the original does -- every shape folds them. No optimisation
// flag or pragma moves it either: -O2 through -O4 in all three modes, the four
// combinations of noschedule and nopeephole, -inline off, noauto and deferred,
// and opt_propagation, opt_lifetimes, opt_dead_assignments, opt_common_subs
// and opt_dead_code turned off one at a time all produce the folded form.
//
// The boundary is read off the two sample vtables. TObjSample's is at .data
// 0x50 and TObjSample2's at .data 0xB0, and they share their last six slots:
// only the destructor, Exec and Disp differ. The shared ones are the base's,
// defined in the run that ends at 0x564; the three that differ are this run's,
// and they are laid out Disp before Exec, the same order TObjSample uses.
//
// The class layout comes from TObject.hpp in heroes-extended-multiplayer (see
// REFERENCES.md), and the code agrees with it field for field: the class name
// pointer at 0x0, the signal halfword at 0x4 that Exec sets to Msg_KillOk, the
// vtable at 0x18 right after the four list pointers, and the object size at
// 0x1E, which is written here as 0x48 and is exactly sizeof(TObjSample2).
//
// The second base at 0x28 keeps its own vtable at 0x2C, and both are stored
// out of one address: the compiler loads the table once and adds 0x2C, which
// is why the vtable is declared as one array and indexed rather than split in
// two.
//
// Only .text is claimed. The vtable, the class name and the registration
// record stay with the module, so the constructor reaches them as externals
// and the layout of .data and .bss is left exactly as it was.
//
// Exec reads the keyframe through a local rather than assigning the position
// across whole. Both spellings compile to one load and three moves, but a
// struct assignment inside a branch makes the compiler hold the function back
// and emit it after the rest of the file, which puts Exec last instead of
// second. The two constructors assign whole structs at the top level and are
// not held back, which is also why the constructor reloads the keyframe
// between the position and the rotation: each assignment reads it again.

typedef struct Vec3 {
	f32 x;
	f32 y;
	f32 z;
} Vec3;

typedef struct Rot3 {
	s32 x;
	s32 y;
	s32 z;
} Rot3;

// One keyframe of the path the second base plays back.
typedef struct Frame {
	Vec3 position; // 0x00
	Rot3 rotation; // 0x0C
} Frame;

typedef struct TObject {
	const char* className;  // 0x00
	u16 signal;             // 0x04
	u16 tag;                // 0x06
	struct TObject* prev;   // 0x08
	struct TObject* next;   // 0x0C
	struct TObject* parent; // 0x10
	struct TObject* child;  // 0x14
	void** vtable;          // 0x18
	s16 unk1C;              // 0x1C
	s16 objectSize;         // 0x1E
	s16 unk20;              // 0x20
	s16 unk22;              // 0x22
	s16 unk24;              // 0x24
	s16 unk26;              // 0x26
} TObject;

typedef struct Motion {
	Frame* frame;  // 0x00
	void** vtable; // 0x04
} Motion;

typedef struct Sample2 {
	TObject base;  // 0x00
	Motion motion; // 0x28
	Vec3 position; // 0x30
	Rot3 rotation; // 0x3C
} Sample2;         // 0x48

// Msg_KillOk, the bit Exec raises once the path has run out.
#define SIGNAL_KILL_OK 1

extern "C" void* lbl_8042C110;
extern "C" void* lbl_8042C148;
extern "C" Vec3* lbl_8042C208;

extern "C" void __dt__7TObjectFv(TObject* object, s32 flags);
extern "C" void __ct__7TObjectFP7TObject(TObject* object, void* owner);
extern "C" void fn_800189A4(void* heap, TObject* object);
extern "C" void* fn_80018A34(void* heap, u32 size);
extern "C" s32 fn_8005B8BC(Motion* motion);
extern "C" s32 fn_8005B8D8(Motion* motion);
extern "C" s32 fn_8005B9F0(Motion* motion);
extern "C" void dtor_8005BD3C(Motion* motion, s32 flags);
extern "C" void fn_8005BE6C(Motion* motion);
extern "C" void fn_800D72C0(const Vec3* a, const Vec3* b, Vec3* out);

// Defined by each module, renamed to these names in its own symbols.txt.
extern "C" const char* sample2ClassName;
extern "C" void* sample2Vtable[];

extern "C" void sample2Disp(void) { }

extern "C" void sample2Exec(Sample2* object)
{
	Vec3 delta;

	if (fn_8005B9F0(&object->motion) != 0 || fn_8005B8BC(&object->motion) != 0) {
		object->base.signal |= SIGNAL_KILL_OK;
	} else if (fn_8005B8D8(&object->motion) != 0) {
		Frame* frame = object->motion.frame;

		object->position.x = frame->position.x;
		object->position.y = frame->position.y;
		object->position.z = frame->position.z;
	} else {
		object->rotation.y += 0x38E;
		fn_800D72C0(lbl_8042C208, &object->motion.frame->position, &delta);
	}
}

extern "C" Sample2* sample2Dtor(Sample2* object, s16 flags)
{
	if (object != NULL) {
		object->base.vtable   = sample2Vtable;
		object->motion.vtable = sample2Vtable + 0xB;
		dtor_8005BD3C(&object->motion, 0);
		__dt__7TObjectFv(&object->base, 0);
		if (flags > 0) {
			fn_800189A4(lbl_8042C148, &object->base);
		}
	}
	return object;
}

extern "C" Sample2* sample2Ctor(Sample2* object, void* owner)
{
	__ct__7TObjectFP7TObject(&object->base, owner);
	fn_8005BE6C(&object->motion);

	object->base.vtable   = sample2Vtable;
	object->motion.vtable = sample2Vtable + 0xB;

	object->base.className  = sample2ClassName;
	object->base.objectSize = 0x48;

	object->position = object->motion.frame->position;
	object->rotation = object->motion.frame->rotation;
	return object;
}
