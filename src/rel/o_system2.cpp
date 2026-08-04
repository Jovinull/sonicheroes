#include "types.h"

// The original C++ unit is identified by the retained PS2 o_system2.cpp source
// marker and its TObjSystem2 constructor, destructor, Disp, Exec, lifecycle,
// and vtable symbols. The GameCube unit carries the same class strings, method
// behavior, vtable relationships, factory, and static registration record.

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

class TObjSystem2
{
public:
	TObject object;
	TMotion motion;

	TObjSystem2(TObject* owner);
	~TObjSystem2();

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
    void (*create)(), void (*reset)(SETOBJ_PARAM*), u32 flags, u32 field18, u32 field20,
    u32 objectId, u32 field1E, u32 field21, void* fieldTypes, void* fieldNames);
void fn_8005B2C4(void* scene);
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
extern void* lbl_8042C298;

TObjSystem2* __ct__11TObjSystem2FP7TObject(TObjSystem2* object, TObject* owner);
TObjSystem2* __dt__11TObjSystem2Fv(TObjSystem2* object, s16 flags);
void Disp__11TObjSystem2Fv(TObjSystem2* object);
void Exec__11TObjSystem2Fv(TObjSystem2* object);
}

char TObjSystem2ClassName[] = "TObjSystem2";
char* CL_TObjSystem2        = TObjSystem2ClassName;

void* __vt__11TObjSystem2[] = {
	0,
	0,
	(void*)__dt__11TObjSystem2Fv,
	(void*)Exec__11TObjSystem2Fv,
	(void*)Disp__11TObjSystem2Fv,
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

char TObjSystem2DisplayName[16] = "SYSTEM OBJECT2";

SETOBJ_PARAM ObjSystem2Param;

void TObjSystem2::Disp() { }

void TObjSystem2::Exec()
{
	if (fn_8005B9F0(&motion) != 0 || fn_8005B8BC(&motion) != 0) {
		markSampleForDeletion(&object);
		return;
	}
}

TObjSystem2::~TObjSystem2()
{
	object.vtable = __vt__11TObjSystem2;
	motion.vtable = __vt__11TObjSystem2 + 11;
	dtor_8005BD3C(&motion, 0);
	__dt__7TObjectFv(&object, 0);
}

TObjSystem2::TObjSystem2(TObject* owner)
{
	__ct__7TObjectFP7TObject(&object, owner);
	fn_8005BE6C(&motion);
	object.vtable     = __vt__11TObjSystem2;
	motion.vtable     = __vt__11TObjSystem2 + 11;
	object.className  = CL_TObjSystem2;
	object.objectSize = sizeof(TObjSystem2);
}

static void continueSystem2(SETOBJ_PARAM*) { }

static void endObjSystem2() { }

static void initObjSystem2()
{
	fn_8005B2C4(lbl_8042C298);
}

static void startObjSystem2()
{
	// The object-registration callback discards the new object. The constructor
	// result still remains in r3, as it does in the retail callback.
	TObjSystem2* object = (TObjSystem2*)__nw__10TObjSampleFUl(sizeof(TObjSystem2));
	if (object != 0) {
		object = __ct__11TObjSystem2FP7TObject(object, lbl_8042C110);
	}
}

static void registerObjSystem2()
{
	setupObjClass(&ObjSystem2Param, TObjSystem2DisplayName, initObjSystem2, endObjSystem2,
	    startObjSystem2, continueSystem2, 0x80, 0, 0x1E, 0xFFF1, 2, 0, 0, 0);
}

__declspec(section ".ctors") void (*const TObjSystem2CtorEntry)() = registerObjSystem2;
