#include "types.h"

#pragma force_active on

struct RwV3d {
	f32 x, y, z;
};
struct PARTICLE_INSTANCE {
	u8 pad00[0xC];
	s16 angle;
	u8 pad0E[6];
	f32 life;
	u8 pad18[4];
	RwV3d position;
	f32 frame;
	u8 pad2C[4];
	RwV3d scale;
};
struct PARTICLE_OFFSET_INFO {
	f32 values[24];
};
struct SPRITE_INFO {
	u32 flags;
	u32 color;
	s32 field08;
	void* texture;
	PARTICLE_OFFSET_INFO* offsets;
	u32 field14;
};
enum Pt_FLAGS { PT_RAIN = 5 };
struct TEXTURE_ENTRY {
	void* texture;
	char* name;
};
struct TEXTURE_LIST {
	TEXTURE_ENTRY* entries;
	u32 count;
};

class PARTICLE_MATERIAL
{
public:
	u8 pad00[0xC];
	s16 field0C;
	s16 frameCount;
	f32 speed;
	u8 pad14[0xC];
	f32 field20;
	u8 pad24[0x10];
	void* texture;
	u8 pad38[0x1C];
	PARTICLE_MATERIAL(Pt_FLAGS, SPRITE_INFO*);
	~PARTICLE_MATERIAL();
	virtual void MoveManager();
	virtual void DispManager();
	virtual int Move(PARTICLE_INSTANCE*);
	virtual void Disp(PARTICLE_INSTANCE*);
	virtual PARTICLE_INSTANCE* AllocInstance();
	virtual PARTICLE_INSTANCE* CreateInstance();
};

class EfRain : public PARTICLE_MATERIAL
{
public:
	u8 pad58[0x24];
	EfRain();
	virtual int Move(PARTICLE_INSTANCE*);
};

extern "C" {
void* fn_80057644(u32);
void* fn_8005FAE8(char*, TEXTURE_LIST*);
void fn_8005FA8C(void*, TEXTURE_LIST*);
}

inline void* operator new(unsigned long size)
{
	return fn_80057644(size);
}

extern TEXTURE_ENTRY texDir[];
extern PARTICLE_OFFSET_INFO poi_Rain;
void* pRainTex;
SPRITE_INFO rainInfo     = { 0x502, 0x01000000, -1, pRainTex, &poi_Rain, 0 };
TEXTURE_LIST RainTexlist = { texDir, 1 };
extern char rainTextureFilename[];
void* RainTexDictionary;
struct EfRainGlobal {
	EfRain* value;
	u32 padding;
};
EfRainGlobal pEfRain;

PARTICLE_INSTANCE* CreateRain(RwV3d* position, f32 life)
{
	if (pEfRain.value == 0)
		return 0;
	PARTICLE_INSTANCE* instance = pEfRain.value->CreateInstance();
	if (instance == 0)
		return 0;
	instance->position.x = position->x;
	instance->position.y = position->y;
	instance->position.z = position->z;
	instance->scale.x    = 0.0f;
	instance->scale.y    = 0.0f;
	instance->scale.z    = 0.0f;
	instance->life       = life;
	return instance;
}

int EfRain::Move(PARTICLE_INSTANCE* instance)
{
	instance->angle += 182;
	if (texture != 0) {
		instance->frame += speed;
		if ((u16)(int)instance->frame >= frameCount) {
			instance->frame = (f32)frameCount - 1.0f;
			return 0;
		}
		return 1;
	}
	return 1;
}

EfRain::EfRain()
    : PARTICLE_MATERIAL(PT_RAIN, &rainInfo)
{
	field0C    = 0;
	frameCount = 6;
	speed      = 1.0f;
	field20    = 0.0f;
}

void ReleaseTextureRain()
{
	if (pEfRain.value != 0) {
		delete pEfRain.value;
		pEfRain.value = 0;
	}
	fn_8005FA8C(RainTexDictionary, &RainTexlist);
	RainTexDictionary = 0;
	pRainTex          = 0;
}

void LoadTextureRain()
{
	if (RainTexDictionary == 0)
		RainTexDictionary = fn_8005FAE8(rainTextureFilename, &RainTexlist);
	pRainTex         = RainTexlist.entries[0].texture;
	rainInfo.texture = pRainTex;
	if (pEfRain.value == 0) {
		EfRain* rain  = new EfRain();
		pEfRain.value = rain;
	}
}

char rainTextureFilename[] = "textures/ef_rain.txd";

#pragma force_active reset
