#include "types.h"

// The original C++ unit is identified by the retained PS2 o_system4.cpp source
// marker and its TObjSystem4 constructor, destructor, Disp, Exec, lifecycle,
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

class TObjSystem4
{
public:
	TObject object;
	TMotion motion;

	TObjSystem4(TObject* owner);
	~TObjSystem4();

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
void Error__7TObjectFPc();
extern TObject* lbl_8042C110;

TObjSystem4* __ct__11TObjSystem4FP7TObject(TObjSystem4* object, TObject* owner);
TObjSystem4* __dt__11TObjSystem4Fv(TObjSystem4* object, s16 flags);
void Disp__11TObjSystem4Fv(TObjSystem4* object);
void Exec__11TObjSystem4Fv(TObjSystem4* object);
}

char TObjSystem4ClassName[] = "TObjSystem4";
char* CL_TObjSystem4        = TObjSystem4ClassName;

void* __vt__11TObjSystem4[] = {
	0,
	0,
	(void*)__dt__11TObjSystem4Fv,
	(void*)Exec__11TObjSystem4Fv,
	(void*)Disp__11TObjSystem4Fv,
	(void*)sampleHook0,
	(void*)sampleHook1,
	(void*)sampleHook2,
	(void*)sampleHook3,
	(void*)Error__7TObjectFPc,
	(void*)sampleHook4,
	0,
	0,
	(void*)fn_8005B8B8,
};

char TObjSystem4DisplayName[16] = "SYSTEM OBJECT4";

SETOBJ_PARAM ObjSystem4Param;

void TObjSystem4::Disp() { }

void TObjSystem4::Exec()
{
	if (fn_8005B9F0(&motion) != 0 || fn_8005B8BC(&motion) != 0) {
		markSampleForDeletion(&object);
		return;
	}
}

TObjSystem4::~TObjSystem4()
{
	object.vtable = __vt__11TObjSystem4;
	motion.vtable = __vt__11TObjSystem4 + 11;
	dtor_8005BD3C(&motion, 0);
	__dt__7TObjectFv(&object, 0);
}

TObjSystem4::TObjSystem4(TObject* owner)
{
	__ct__7TObjectFP7TObject(&object, owner);
	fn_8005BE6C(&motion);
	object.vtable     = __vt__11TObjSystem4;
	motion.vtable     = __vt__11TObjSystem4 + 11;
	object.className  = CL_TObjSystem4;
	object.objectSize = sizeof(TObjSystem4);
}

static void continueSystem4(SETOBJ_PARAM*) { }

static void endObjSystem4() { }

static void initObjSystem4() { }

static void startObjSystem4()
{
	// The object-registration callback discards the new object. The constructor
	// result still remains in r3, as it does in the retail callback.
	TObjSystem4* object = (TObjSystem4*)__nw__10TObjSampleFUl(sizeof(TObjSystem4));
	if (object != 0) {
		object = __ct__11TObjSystem4FP7TObject(object, lbl_8042C110);
	}
}

static void registerObjSystem4()
{
	setupObjClass(&ObjSystem4Param, TObjSystem4DisplayName, initObjSystem4, endObjSystem4,
	    startObjSystem4, continueSystem4, 0x80, 0, 0x1E, 0xFFF3, 2, 0, 0, 0);
}

__declspec(section ".ctors") void (*const TObjSystem4CtorEntry)() = registerObjSystem4;
