#include "types.h"

struct RwV3d {
	f32 x;
	f32 y;
	f32 z;
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

enum Pt_FLAGS {
	PT_RAIN = 5,
};

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

	PARTICLE_MATERIAL(Pt_FLAGS flags, SPRITE_INFO* info);
	~PARTICLE_MATERIAL();

	virtual void MoveManager();
	virtual void DispManager();
	virtual int Move(PARTICLE_INSTANCE* instance);
	virtual void Disp(PARTICLE_INSTANCE* instance);
	virtual PARTICLE_INSTANCE* AllocInstance();
	virtual PARTICLE_INSTANCE* CreateInstance();
};

class EfRain : public PARTICLE_MATERIAL
{
public:
	u8 pad58[0x24];

	EfRain();
	~EfRain();
	virtual int Move(PARTICLE_INSTANCE* instance);
};

extern "C" {
void fn_16_2C8(RwV3d* destination, RwV3d* source);
void* fn_80057644(u32 size);
void* fn_8005FAE8(char* filename, TEXTURE_LIST* textureList);
void fn_8005FA8C(void* dictionary, TEXTURE_LIST* textureList);
void __dl__FPv(void* object);
EfRain* __ct__6EfRainFv(EfRain*);
}

char rainTextureName[] = "rein_fx_01";
TEXTURE_ENTRY texDir[] = {
	{ 0, rainTextureName },
};

PARTICLE_OFFSET_INFO poi_Rain = { {
	0.0f,
	0.0f,
	0.25f,
	0.25f,
	0.25f,
	0.0f,
	0.5f,
	0.25f,
	0.5f,
	0.0f,
	0.75f,
	0.25f,
	0.75f,
	0.0f,
	1.0f,
	0.25f,
	0.0f,
	0.25f,
	0.25f,
	0.5f,
	0.25f,
	0.25f,
	0.5f,
	0.5f,
} };

void* pRainTex;
SPRITE_INFO rainInfo = {
	0x502,
	0x01000000,
	-1,
	pRainTex,
	&poi_Rain,
	0,
};

TEXTURE_LIST RainTexlist = {
	texDir,
	1,
};

extern char rainTextureFilename[];

void* RainTexDictionary;
struct EfRainGlobal {
	EfRain* value;
	u32 padding;
};
EfRainGlobal pEfRain;

PARTICLE_INSTANCE* CreateRain(RwV3d* position, f32 life)
{
	if (pEfRain.value == 0) {
		return 0;
	}

	PARTICLE_INSTANCE* instance = pEfRain.value->CreateInstance();
	if (instance == 0) {
		return 0;
	}

	fn_16_2C8(&instance->position, position);
	instance->scale.x = 0.0f;
	instance->scale.y = 0.0f;
	instance->scale.z = 0.0f;
	instance->life    = life;
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
	if (RainTexDictionary == 0) {
		RainTexDictionary = fn_8005FAE8(rainTextureFilename, &RainTexlist);
	}

	pRainTex         = RainTexlist.entries[0].texture;
	rainInfo.texture = pRainTex;

	if (pEfRain.value == 0) {
		EfRain* rain = (EfRain*)fn_80057644(sizeof(EfRain));
		if (rain != 0) {
			rain = __ct__6EfRainFv(rain);
		}
		pEfRain.value = rain;
	}
}

EfRain::~EfRain() { }

extern "C" const f32 efRainUnusedTail[3] = {
	0.0f,
	1.5f,
	0.0f,
};
