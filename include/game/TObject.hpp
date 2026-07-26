#ifndef GAME_TOBJECT_H
#define GAME_TOBJECT_H

#include <types.h>
#include <stddef.h>

class TObject {
public:
    TObject(TObject* pParent);
public:
    /* 0x00 */ const char* mClassName;
    /* 0x04 */ u8 unk_0x00[0x14];
public:
    // vtbl at 0x18
    /* 0x08 */ virtual ~TObject();
    /* 0x0C */ virtual void Exec();
    /* 0x10 */ virtual void Disp();
    /* 0x14 */ virtual void TDisp();
    /* 0x18 */ virtual void PDisp();
    /* 0x1C */ virtual void ImmAftSetRaster();
    /* 0x20 */ virtual void Debug();
    /* 0x24 */ virtual void Error();
    /* 0x28 */ virtual void Render();
public:
    /* 0x1C */ u8 unk_0x1C[2];
	/* 0x1E */ u16 mSize;
	/* 0x20 */ u8 unk_0x20[8];
public:
    bool Is(const char* pClassName);
    void CheckAlive();
    void Kill();

    void Show();
    void Hide();
    bool Visible();

    void Enable();
    void Disable();
    void Pause();
    void Stop();
    void Continue();

    u32 GetChildCount();
    void DeleteChild();
    void ExecChild();
    void DispChild();
    void TDispChild();
    void PDispChild();
    void KillChild();

    static void* operator new(size_t);
    static void operator delete(void* pData);
};

#define TOBJECT_CLASS_NAME_DEF(class) const char* CL_##class = #class;
#define TOBJECT_SET_CLASS_DATA(class) mClassName = CL_##class; \
    mSize = sizeof(class);

#endif
