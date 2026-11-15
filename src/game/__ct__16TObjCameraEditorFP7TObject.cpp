// TObjCameraEditor::TObjCameraEditor(TObject*) (the mangled name is CORROBORATED by the PS2 build;
// the class name string it installs is "TObjCameraEditor"). Builds the TObjCamera base, installs
// the class name and the object size (+0x1E), clears the 0x178 bytes from +0x70 and the word
// +0x6C. Field roles are UNKNOWN.
#include "types.h"

class TObject;

struct TObjectBase {
	char* ClassName;
	u16 Signal, Tag;
	TObject* Prev;
	TObject* Next;
	TObject* Parent;
	TObject* Child;
};

class TObject : public TObjectBase
{
public:
	TObject(TObject* parent);
	virtual ~TObject();
	virtual void Exec();
	virtual void Disp();
	virtual void TDisp();
	virtual void PDisp();
	virtual void ImmAftSetRaster();
	virtual void Debug();
	virtual void Error(char*);
	virtual void Render();
	u16 ExecTime, DispTime, TDispTime, PDispTime, ImmAftSetRasterTime;
};

// Local views; the destructors are not defined here, so this unit does not emit a vtable.
class TObjCamera : public TObject
{
public:
	TObjCamera(TObject* parent);
	virtual ~TObjCamera();

	u8 unknown28[0x5C - 0x28];
};

class TObjCameraEditor : public TObjCamera
{
public:
	TObjCameraEditor(TObject* parent);
	virtual ~TObjCameraEditor();

	u8 unknown5C[0x6C - 0x5C];
	s32 unknown6C;       // 0x6C
	u8 unknown70[0x178]; // 0x70
};

extern "C" {
extern char* lbl_8042B070; // -> "TObjCameraEditor"
void* memset(void* dst, int c, unsigned long n);
}

TObjCameraEditor::TObjCameraEditor(TObject* parent)
    : TObjCamera(parent)
{
	ClassName = lbl_8042B070;
	DispTime  = sizeof(*this);
	memset(unknown70, 0, sizeof(unknown70));
	unknown6C = 0;
}
