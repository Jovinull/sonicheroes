#include "types.h"

// The original C++ unit is identified by the retained PS2 o_system1.cpp source
// marker and its TObjSystem1 constructor, destructor, Disp, Exec, and vtable
// symbols. The GameCube unit carries the same class strings, method behavior,
// vtable relationships, factory, and static object-registration record.

struct TObject {
	char* className;
	u16 signal;
	u16 tag;
	TObject* prev;
	TObject* next;
	TObject* parent;
	TObject* child;
	void** vtable;
	s16 field1C;
	s16 objectSize;
	s16 field20;
	s16 field22;
	s16 field24;
	s16 field26;
};

struct TMotion {
	void* frame;
	void** vtable;
};

class TObjSystem1
{
public:
	TObject object;
	TMotion motion;

	TObjSystem1(TObject* owner);
	~TObjSystem1();

	void Disp();
	void Exec();

	static void operator delete(void* object);
};

// GameCube TObject keeps its dispatch table at 0x18 and TMotion's secondary
// table at 0x2C, so this class retains those engine-owned layouts explicitly.
struct SETOBJ_PARAM {
	u8 data[0x30];
};

extern "C" {
void markSampleForDeletion(TObject* object);
void* __nw__10TObjSampleFUl(u32 size);
void setupObjClass(SETOBJ_PARAM* param, char* name, void (*load)(), void (*unload)(),
    void (*create)(), void (*reset)(), u32 flags, u32 field18, u32 field20, u32 objectId,
    u32 field1E, u32 field21, void* fieldTypes, void* fieldNames);
void fn_8005B8B8();
s32 fn_8005B8BC(TMotion* motion);
s32 fn_8005B9F0(TMotion* motion);
void dtor_8005BD3C(TMotion* motion, s16 flags);
void fn_8005BE6C(TMotion* motion);
void __ct__7TObjectFP7TObject(TObject* object, TObject* owner);
void __dt__7TObjectFv(TObject* object, s16 flags);

void sampleHook0();
void sampleHook1();
void sampleHook2();
void sampleHook3();
void sampleHook4();
void fn_80017854();
extern TObject* lbl_8042C110;

TObjSystem1* __ct__11TObjSystem1FP7TObject(TObjSystem1* object, TObject* owner);
TObjSystem1* __dt__11TObjSystem1Fv(TObjSystem1* object, s16 flags);
void Disp__11TObjSystem1Fv(TObjSystem1* object);
void Exec__11TObjSystem1Fv(TObjSystem1* object);
}

char TObjSystem1ClassName[] = "TObjSystem1";
char* CL_TObjSystem1        = TObjSystem1ClassName;

void* __vt__11TObjSystem1[] = {
	0,
	0,
	(void*)__dt__11TObjSystem1Fv,
	(void*)Exec__11TObjSystem1Fv,
	(void*)Disp__11TObjSystem1Fv,
	(void*)sampleHook0,
	(void*)sampleHook1,
	(void*)sampleHook2,
	(void*)sampleHook3,
	(void*)fn_80017854,
	(void*)sampleHook4,
	0,
	0,
	(void*)fn_8005B8B8,
};

char TObjSystem1DisplayName[16] = "SYSTEM OBJECT1";

SETOBJ_PARAM ObjSystem1Param;

void TObjSystem1::Disp() { }

void TObjSystem1::Exec()
{
	if (fn_8005B9F0(&motion) != 0 || fn_8005B8BC(&motion) != 0) {
		markSampleForDeletion(&object);
		return;
	}
}

TObjSystem1::~TObjSystem1()
{
	object.vtable = __vt__11TObjSystem1;
	motion.vtable = __vt__11TObjSystem1 + 11;
	dtor_8005BD3C(&motion, 0);
	__dt__7TObjectFv(&object, 0);
}

TObjSystem1::TObjSystem1(TObject* owner)
{
	__ct__7TObjectFP7TObject(&object, owner);
	fn_8005BE6C(&motion);
	object.vtable     = __vt__11TObjSystem1;
	motion.vtable     = __vt__11TObjSystem1 + 11;
	object.className  = CL_TObjSystem1;
	object.objectSize = sizeof(TObjSystem1);
}

static void continueSystem1() { }

static void endObjSystem1() { }

static void initObjSystem1() { }

static void startObjSystem1()
{
	// The object-registration callback discards the new object. The constructor
	// result still remains in r3, as it does in the retail callback.
	TObjSystem1* object = (TObjSystem1*)__nw__10TObjSampleFUl(sizeof(TObjSystem1));
	if (object != 0) {
		object = __ct__11TObjSystem1FP7TObject(object, lbl_8042C110);
	}
}

static void registerObjSystem1()
{
	setupObjClass(&ObjSystem1Param, TObjSystem1DisplayName, initObjSystem1, endObjSystem1,
	    startObjSystem1, continueSystem1, 0x80, 0, 0x1E, 0xFFF0, 2, 0, 0, 0);
}

__declspec(section ".ctors") void (*const TObjSystem1CtorEntry)() = registerObjSystem1;
