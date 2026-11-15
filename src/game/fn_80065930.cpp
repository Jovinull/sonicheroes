// Second PARTICLE_MATERIAL constructor (HYPOTHESIS): the same setup as
// PARTICLE_MATERIAL(Pt_FLAGS, SPRITE_INFO*) (see __ct__17PARTICLE_MATERIALF8Pt_FLAGSP11SPRITE_INFO.cpp)
// for a model material: flag 0x20000 instead of 0x10000, and the texture word read from +0x2C of
// the source record. Its parameter type and mangled name are UNKNOWN (no PS2 counterpart), so it
// is written as a function taking the material; it returns it, as a constructor does.
#include "types.h"

enum Pt_FLAGS {
	PT_FLAGS_SPRITE = 0x10000, // HYPOTHESIS: set by this constructor
	PT_FLAGS_MODEL  = 0x20000  // HYPOTHESIS: set by the other constructor, fn_80065930
};

struct SPRITE_INFO {
	u8 pad0[0xC];
	void* texture; // 0xC
	u8 pad10[0x2C - 0x10];
	void* texture2C; // 0x2C (written for PT_FLAGS_MODEL materials)
};

// Source record of a model material: only the texture word is read.
struct ModelInfo80065930 {
	u8 pad0[0x2C];
	void* texture; // 0x2C
};

class PARTICLE_MATERIAL;

struct ParticleManager80065930 {
	u8 pad0[0x28];
	PARTICLE_MATERIAL* materials; // 0x28
};

extern "C" {
extern void* lbl_80243BF8[]; // the PARTICLE_MATERIAL vtable (defined in another split)
extern ParticleManager80065930* lbl_8042C2E0;
extern const f32 lbl_8042D4A8; // 0.0f
extern const f32 lbl_8042D4DC; // 0.2f
extern const f32 lbl_8042D4E0; // -0.2f
extern const f32 lbl_8042D4E4; // 100.0f
}

struct Vec800657EC {
	f32 x;
	f32 y;
	f32 z;
};

// Local view. The class is polymorphic in the original (vtable pointer at +0x54, destructor in
// __dt__17PARTICLE_MATERIALFv.cpp); the vtable lives in another split, so the pointer is a data
// member here and the constructor stores it first, as the compiler would.
class PARTICLE_MATERIAL
{
public:
	// Stores the texture into the sprite record (at +0xC or +0x2C by material kind) and here.
	void SetTexture(void* texture)
	{
		if (sprite) {
			if (flags & PT_FLAGS_SPRITE) {
				sprite->texture = texture;
				this->texture   = texture;
			} else if (flags & PT_FLAGS_MODEL) {
				sprite->texture2C = texture;
				this->texture     = texture;
			}
		}
	}

	s16 unknown0; // 0x0
	u8 pad2[2];
	s32 flags;      // 0x4
	s32 registered; // 0x8 (1 once in the manager's list)
	s16 unknownC;   // 0xC
	s16 unknownE;   // 0xE
	f32 unknown10;  // 0x10
	f32 unknown14;  // 0x14
	f32 unknown18;  // 0x18
	f32 unknown1C;  // 0x1C
	u8 pad20[4];
	f32 unknown24; // 0x24
	u8 pad28[4];
	SPRITE_INFO* sprite;     // 0x2C
	s32 unknown30;           // 0x30
	s32 unknown34;           // 0x34
	void* texture;           // 0x38
	s32 unknown3C;           // 0x3C
	s32 unknown40;           // 0x40
	PARTICLE_MATERIAL* prev; // 0x44
	PARTICLE_MATERIAL* next; // 0x48
	s32 unknown4C;           // 0x4C
	s32 unknown50;           // 0x50
	void** vtable;           // 0x54
	Vec800657EC unknown58;   // 0x58
	s32 unknown64;           // 0x64
	s32 unknown68;           // 0x68
	s32 unknown6C;           // 0x6C
	Vec800657EC unknown70;   // 0x70
};

extern "C" PARTICLE_MATERIAL* fn_80065930(
    PARTICLE_MATERIAL* m, Pt_FLAGS flags, ModelInfo80065930* info)
{
	ParticleManager80065930* manager;

	m->vtable      = lbl_80243BF8;
	m->registered  = 0;
	m->flags       = flags | PT_FLAGS_MODEL;
	m->unknownC    = 0;
	m->unknownE    = 0;
	m->unknown10   = lbl_8042D4A8;
	m->unknown14   = lbl_8042D4A8;
	m->unknown18   = lbl_8042D4DC;
	m->unknown1C   = lbl_8042D4E0;
	m->unknown24   = lbl_8042D4E4;
	m->prev        = NULL;
	m->next        = NULL;
	m->unknown4C   = 0;
	m->unknown50   = 0;
	m->unknown34   = 0;
	m->unknown0    = 0;
	m->unknown3C   = 0;
	m->unknown40   = 0;
	m->unknown58.z = lbl_8042D4A8;
	m->unknown58.y = lbl_8042D4A8;
	m->unknown58.x = lbl_8042D4A8;
	m->unknown70.z = lbl_8042D4A8;
	m->unknown70.y = lbl_8042D4A8;
	m->unknown70.x = lbl_8042D4A8;
	m->unknown6C   = 0;
	m->unknown68   = 0;
	m->unknown64   = 0;
	m->unknown30   = 0;
	m->texture     = NULL;
	manager        = lbl_8042C2E0;
	if (!manager) {
		m->registered = 0;
	} else if (m->registered != 1) {
		PARTICLE_MATERIAL* last;

		if ((last = manager->materials) == NULL) {
			manager->materials = m;
			m->next            = NULL;
			m->prev            = NULL;
		} else {
			while (last->next != NULL) {
				last = last->next;
			}
			last->next = m;
			m->prev    = last;
			m->next    = NULL;
		}
		m->registered = 1;
	}
	m->sprite = (SPRITE_INFO*)info;
	m->SetTexture(info->texture);
	return m;
}
