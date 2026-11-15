#include "types.h"

// SetPlayerWLaser (CORROBORATED by PS2 metadata and the stored class name "TObjPlayerWLaser"): creates a TObjPlayerWLaser
// through TObject's task-heap operator new. Names are from PS2; the symbol keeps its address-based name.

struct THeapCtrl {
	void* Malloc(u32 size);
	void Free(void* p);
};
extern "C" THeapCtrl* lbl_8042C148;

class TObject
{
public:
	TObject(TObject* parent);
	~TObject();
	static void* operator new(unsigned long size) { return lbl_8042C148->Malloc(size); }
	static void operator delete(void* p);

	const char* className; // 0x00
	u16 flags;             // 0x04
	u8 pad06[0x12];        // 0x06
	void** vtable;         // 0x18
	u8 pad1c[0xc];         // 0x1c
};

struct C_COLLI {
	C_COLLI();
	~C_COLLI();

	u8 data[0x78];
};

extern "C" char lbl_80289FB4[];      // TObjPlayerWLaser vtable
extern "C" const char* lbl_8042B978; // class name pointer
extern "C" void* lbl_80289F80[4];    // clump templates
extern "C" char lbl_8042B97C[8];     // texture name
extern "C" TObject* lbl_8042C108;    // TL_03
extern "C" TObject* lbl_8042C2A0;
extern "C" TObject* lbl_8042C110;
extern "C" f32 lbl_8042ECDC;

extern "C" void* fn_80150588(void* clump);
extern "C" void fn_801491A8(void* atomic);
extern "C" void fn_801286B8(TObject* self);
extern "C" void objRpClumpForAllAtomicsToSetRenderCallbackToUseLight__FP7RpClumpUi(
    void* clump, u32 callback);
extern "C" void* objRpClumpGetAtomicWithTexture__FP7RpClumpP8RpAtomicPc(
    void* clump, void* atomic, char* texture);

class TObjPlayerWLaser : public TObject, public C_COLLI
{
public:
	TObjPlayerWLaser(s32 player, s32 type, TObject* parent)
	    : TObject(parent)
	{
		vtable                    = (void**)lbl_80289FB4;
		className                 = lbl_8042B978;
		*(u16*)((u8*)this + 0x1e) = 0xe8;
		field_b4                  = type;
		field_b0                  = player;
		f32 zero                  = lbl_8042ECDC;
		field_d0                  = zero;
		field_d4                  = zero;
		for (s32 i = 0; i < 4; i++) {
			clumps[i] = fn_80150588(lbl_80289F80[i]);
			objRpClumpForAllAtomicsToSetRenderCallbackToUseLight__FP7RpClumpUi(clumps[i], 4);
			if (clumps[i] != NULL)
				fn_801491A8(objRpClumpGetAtomicWithTexture__FP7RpClumpP8RpAtomicPc(
				    clumps[i], NULL, lbl_8042B97C));
		}
		fn_801286B8(this);
	}

private:
	u8 pad_a0[0x10]; // 0xa0
	s8 field_b0;     // 0xb0
	u8 pad_b1[3];    // 0xb1
	s32 field_b4;    // 0xb4
	u8 pad_b8[0x18]; // 0xb8
	f32 field_d0;    // 0xd0
	f32 field_d4;    // 0xd4
	void* clumps[4]; // 0xd8
};

extern "C" TObjPlayerWLaser* fn_80128A50(s32 player, s32 type)
{
	TObject* parent;
	switch (type) {
		case 0:
		case 1:
			parent = lbl_8042C108;
			break;
		default:
			parent = lbl_8042C2A0;
			if (parent == NULL)
				parent = lbl_8042C110;
			break;
	}
	return new TObjPlayerWLaser(player, type, parent);
}
