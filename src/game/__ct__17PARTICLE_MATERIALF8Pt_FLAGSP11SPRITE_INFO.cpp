// PARTICLE_MATERIAL::PARTICLE_MATERIAL(Pt_FLAGS, SPRITE_INFO*) (symbol name from the retail map):
// sets up a particle material for a sprite. The material gets the material vtable, the given
// flags plus 0x10000 (sprite material), default values, and is appended to the material list of
// the particle manager lbl_8042C2E0 (head at +0x28) when there is a manager. The sprite's texture
// word (+0xC) is then stored back into the sprite and at +0x38 (SetTexture). Field names are
// HYPOTHESIS.
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
	PARTICLE_MATERIAL(Pt_FLAGS flags, SPRITE_INFO* sprite);

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

PARTICLE_MATERIAL::PARTICLE_MATERIAL(Pt_FLAGS flags, SPRITE_INFO* sprite)
{
	ParticleManager80065930* manager;

	vtable        = lbl_80243BF8;
	registered    = 0;
	this->flags   = flags | PT_FLAGS_SPRITE;
	unknownC      = 0;
	unknownE      = 0;
	unknown10     = lbl_8042D4A8;
	unknown14     = lbl_8042D4A8;
	unknown18     = lbl_8042D4DC;
	unknown1C     = lbl_8042D4E0;
	unknown24     = lbl_8042D4E4;
	prev          = NULL;
	next          = NULL;
	unknown4C     = 0;
	unknown50     = 0;
	unknown34     = 0;
	unknown0      = 0;
	unknown3C     = 0;
	unknown40     = 0;
	unknown58.z   = lbl_8042D4A8;
	unknown58.y   = lbl_8042D4A8;
	unknown58.x   = lbl_8042D4A8;
	unknown70.z   = lbl_8042D4A8;
	unknown70.y   = lbl_8042D4A8;
	unknown70.x   = lbl_8042D4A8;
	unknown6C     = 0;
	unknown68     = 0;
	unknown64     = 0;
	unknown30     = 0;
	this->texture = NULL;
	manager       = lbl_8042C2E0;
	if (!manager) {
		registered = 0;
	} else if (registered != 1) {
		PARTICLE_MATERIAL* last;

		if ((last = manager->materials) == NULL) {
			manager->materials = this;
			next               = NULL;
			prev               = NULL;
		} else {
			while (last->next != NULL) {
				last = last->next;
			}
			last->next = this;
			prev       = last;
			next       = NULL;
		}
		registered = 1;
	}
	this->sprite = sprite;
	SetTexture(sprite->texture);
}
