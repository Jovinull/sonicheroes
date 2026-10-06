#include "game/light.h"
// Whole-unit reconstruction, GameCube 0x80052184--0x80053FB8.
// Nonmatching: remaining GPR allocation differences are documented in language-audit.md.
// C++ names/layouts correlated with PS2 metadata. No PS2 instructions used.
// Pointer-only prefix view of the SDK light object; SDK allocation owns its size.
struct RpLight {
	u8 type, subType, flags, privateFlags;
	RwFrame* frame;
};
void* operator new(unsigned long);
extern "C" {
void* memcpy(void*, const void*, unsigned long);
void fn_800B7B04(f32, f32, f32, f32);
extern const f32 lbl_8042D390;
RpLight* fn_80154414(s32);
RwFrame* fn_8019E344();
s8 lbl_8042B160[8] = { 2, 1, -128, -127, -126, 0, 0, 0 };
RpLight* fn_80153EE0(RpLight*, const RwRGBAReal*);
RpLight* fn_80153EA0(RpLight*, f32);
RpLight* fn_80154160(RpLight*, f32);
RpWorld* fn_8015BEF8(RpLight*);
RpWorld* fn_8015BE24(RpWorld*, RpLight*);
RpWorld* fn_8015BD84(RpWorld*, RpLight*);
void* fn_801A5370(void*, RwFrame*);
s32 fn_8019E480(RwFrame*);
s32 fn_801543B4(RpLight*);
RwFrame* fn_8019ED68(RwFrame*, const RwV3d*, f32, s32);
RwFrame* fn_8019EB94(RwFrame*, const RwV3d*, s32);
RwV3d lbl_80242A98           = { 1.0f, 0.0f, 0.0f };
RwV3d lbl_80242AA4           = { 0.0f, 1.0f, 0.0f };
REGLIGHT_STRUCT lbl_80242AB0 = { { 0.3f, 0.3f, 0.4f, 1.0f }, { 1.0f, 1.0f, 1.0f, 1.0f },
	{ 0.0f, -0.866f, 0.5f }, { 150, 0 } };
REGLIGHT_STRUCT lbl_80242AE4
    = { { 1.0f, 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 1.0f }, { 0, 0 } };
char lbl_80242B18[] = "%s_light.bin";
char* fn_800194C4(void*);
s32 fn_80042554(const char*);
s32 fn_80042048(const char*, void*);
s32 sprintf(char*, const char*, ...);
extern u8 lbl_8029C310[];
}
typedef char LightInfoSize[(sizeof(RP_LightInfo) == 0x30) ? 1 : -1];
typedef char RegularLightSize[(sizeof(REGLIGHT_STRUCT) == 0x34) ? 1 : -1];
typedef char LightSize[(sizeof(RP_Light) == 0x40) ? 1 : -1];
typedef char LightManagerSize[(sizeof(CLIGHT) == 0x4d0) ? 1 : -1];

inline s32 RP_Light::SetFlag(u32 flags)
{
	if (!pLight)
		return 0;
	setflag       = flags;
	pLight->flags = setflag & 0xff;
	return 1;
}
inline s32 RP_Light::SetColor(RwRGBAReal* rgba)
{
	RwRGBAReal* color;
	if (pLight) {
		color        = &NowInfo.rgba;
		color->red   = rgba->red;
		color->green = rgba->green;
		color->blue  = rgba->blue;
		color->alpha = rgba->alpha;
		fn_80153EE0(pLight, color);
	} else {
		return 0;
	}
	return 1;
}
inline s32 RP_Light::SetRadius(f32 radius)
{
	if (!pLight)
		return 0;
	if (lighttype == 0 || lighttype == 1)
		return 0;
	NowInfo.Radius = radius;
	fn_80153EA0(pLight, NowInfo.Radius);
	return 1;
}
inline s32 RP_Light::SetConeAngle(f32 angle)
{
	if (!pLight)
		return 0;
	if (lighttype != 3 && lighttype != 4)
		return 0;
	NowInfo.ConeAngle = angle;
	fn_80154160(pLight, NowInfo.ConeAngle);
	return 1;
}
inline s32 RP_Light::SetPosition(RwV3d* position)
{
	RwV3d* pos;
	RwFrame* frame;
	if (!pLight)
		return 0;
	if (lighttype == 0 || lighttype == 1)
		return 0;
	pos    = &NowInfo.pos;
	pos->x = position->x;
	pos->y = position->y;
	pos->z = position->z;
	frame  = pLight->frame;
	if (lighttype == 2) {
		fn_8019EB94(frame, pos, 0);
	} else {
		fn_8019ED68(frame, &lbl_80242A98, NowInfo.ang_x, 0);
		fn_8019ED68(frame, &lbl_80242AA4, NowInfo.ang_y, 2);
		fn_8019EB94(frame, pos, 2);
	}
	return 1;
}
inline s32 RP_Light::SetAngle(f32 x, f32 y)
{
	RwFrame* frame;
	if (!pLight)
		return 0;
	if (lighttype == 0 || lighttype == 2)
		return 0;
	NowInfo.ang_x = x;
	NowInfo.ang_y = y;
	frame         = pLight->frame;
	fn_8019ED68(frame, &lbl_80242A98, x, 0);
	fn_8019ED68(frame, &lbl_80242AA4, y, 2);
	if (lighttype != 1)
		fn_8019EB94(frame, &NowInfo.pos, 2);
	return 1;
}
inline void RP_Light::Disable()
{
	if (pLight) {
		RpWorld* world = fn_8015BEF8(pLight);
		if (world)
			fn_8015BE24(world, pLight);
	}
}
inline void RP_Light::Enable(RpWorld* world)
{
	RpWorld* oldWorld;
	if (pLight) {
		oldWorld = fn_8015BEF8(pLight);
		if (oldWorld)
			fn_8015BE24(oldWorld, pLight);
		fn_8015BD84(world, pLight);
		CurrWorld = world;
	}
}
inline void RP_Light::DestroyLight()
{
	RpWorld* world;
	RwFrame* frame;
	if (pLight) {
		world = fn_8015BEF8(pLight);
		frame = pLight->frame;
		if (world)
			fn_8015BE24(world, pLight);
		if (frame) {
			fn_801A5370(pLight, 0);
			fn_8019E480(frame);
		}
		fn_801543B4(pLight);
	}
	lighttype = -1;
}
inline RP_Light::~RP_Light()
{
	if (pLight)
		DestroyLight();
}

inline void CLIGHT::Restore(s8 number)
{
	RP_Light* light = rpLight[number];
	if (light && light->CurrWorld)
		light->Enable(light->CurrWorld);
}

inline s32 CLIGHT::SetAngle(s8 number, f32 x, f32 y)
{
	RP_Light* light = rpLight[number];
	if (light)
		return light->SetAngle(x, y);
	return 0;
}

inline RpLight* RP_Light::CreateLight(s8 type)
{
	if (pLight)
		DestroyLight();
	pLight = fn_80154414(lbl_8042B160[type]);
	if (pLight) {
		if (type != 0) {
			RwFrame* frame = fn_8019E344();
			if (!frame) {
				DestroyLight();
				return 0;
			}
			fn_801A5370(pLight, frame);
		}
		lighttype = type;
		return pLight;
	}
	return 0;
}

// Pointer-only view of the RenderWare allocation callbacks used by this TU.
struct LightRwGlobals {
	u8 reserved[0x134];
	void* (*allocate)(u32);
	void (*release)(void*);
};
extern "C" LightRwGlobals* lbl_8042C9A4;
inline s32 CLIGHT::LoadLightData(REGLIGHT_STRUCT* data, char* filename)
{
	s32 size;
	void* buffer;
	data = data ? data : reglight_struct;
	size = fn_80042554(filename);
	if (size > 0) {
		buffer = lbl_8042C9A4->allocate(size);
		if (buffer) {
			fn_80042048(filename, buffer);
			if ((u32)size >= 16 * sizeof(REGLIGHT_STRUCT))
				memcpy(data, buffer, 16 * sizeof(REGLIGHT_STRUCT));
			else
				memcpy(data, buffer, size);
			lbl_8042C9A4->release(buffer);
			return 1;
		}
		return 0;
	}
	return 0;
}

inline void CLIGHT::InitRegTable()
{
	for (s8 i = 0; i < 19; ++i) {
		if (i == 16)
			reglight_struct[i] = lbl_80242AE4;
		else
			reglight_struct[i] = lbl_80242AB0;
	}
}
inline void CLIGHT::DestroyRegularLight()
{
	DestroyLight(0);
	DestroyLight(1);
}
inline void CLIGHT::DestroyAllSPLight()
{
	for (s8 i = 2; i < 8; ++i)
		DestroyLight(i);
}
void CLIGHT::Init()
{
	char filename[40];
	now_num = -1;
	InitRegTable();
	sprintf(filename, lbl_80242B18, fn_800194C4(lbl_8029C310));
	if (LoadLightData(0, filename))
		AssignData(0);
	CreateRegularLight();
}

void CLIGHT::End()
{
	DestroyRegularLight();
	DestroyAllSPLight();
}

void CLIGHT::AssignData(REGLIGHT_STRUCT* data)
{
	if (!data)
		data = reglight_struct;
	if (reglight_struct != data)
		memcpy(reglight_struct, data, 16 * sizeof(REGLIGHT_STRUCT));
	fn_800B7B04(
	    data[12].amb_rgba.red, data[12].amb_rgba.green, data[12].amb_rgba.blue, lbl_8042D390);
}

void CLIGHT::CopyLightData(REGLIGHT_STRUCT* data)
{
	memcpy(data, reglight_struct, 16 * sizeof(REGLIGHT_STRUCT));
}

s32 CLIGHT::CreateRegularLight()
{
	RP_Light* light = new RP_Light(0);
	if (light)
		rpLight[0] = light;
	else
		return 0;
	light = new RP_Light(1);
	if (light)
		rpLight[1] = light;
	else {
		DestroyLight(0);
		return 0;
	}
	default_num = 4;
	SetCurrentNum(default_num);
	SetLightRegular(current_num);
	for (s8 i = 0; i < 8; ++i) {
		player_current[i] = 0;
		player_default[i] = 0;
	}
	ChangeWorld(0);
	return 1;
}

s8 CLIGHT::CreateSpecialLight(RP_LightInfo* info)
{
	for (s8 i = 2; i < 8; ++i) {
		if (!rpLight[i]) {
			RP_Light* light = new RP_Light(i, info);
			if (light) {
				rpLight[i] = light;
				return i;
			}
			return -1;
		}
	}
	return -1;
}

void CLIGHT::DestroyLight(s8 number)
{
	RP_Light* light = rpLight[number];
	if (light) {
		delete light;
		rpLight[number] = 0;
	}
}

void CLIGHT::SetCurrentNum(s8 number)
{
	if (number < 0 || number >= 19)
		return;
	current_num = number;
}

void CLIGHT::SetLightRegular(s8 number)
{
	if (number != now_num) {
		REGLIGHT_STRUCT* light = &reglight_struct[number];
		SetColor(0, &light->amb_rgba);
		SetColor(1, &light->dir_rgba);
		SetAngle(1, light->dir_ang[0], light->dir_ang[1]);
		now_num = number;
	}
}

void CLIGHT::SetRegTableColor(s8 number, RwRGBAReal* color)
{
	reglight_struct[number].dir_rgba = *color;
}

void CLIGHT::SetRegTableAngle(s8 number, f32 x, f32 y)
{
	reglight_struct[number].dir_ang[0] = x;
	reglight_struct[number].dir_ang[1] = y;
}

s32 CLIGHT::SetColor(s8 number, RwRGBAReal* color)
{
	if (rpLight[number])
		return rpLight[number]->SetColor(color);
	return 0;
}

s32 CLIGHT::SetPosition(s8 number, RwV3d* pos)
{
	if (rpLight[number])
		return rpLight[number]->SetPosition(pos);
	return 0;
}

s32 CLIGHT::SetRadius(s8 number, f32 radius)
{
	if (rpLight[number])
		return rpLight[number]->SetRadius(radius);
	return 0;
}

void CLIGHT::Enable(s8 number, RpWorld* world)
{
	RP_Light* light = rpLight[number];
	if (light)
		light->Enable(world);
}

void CLIGHT::RestoreAll()
{
	s8 i;
	RP_Light* light;
	for (i = 0; i < 8; i++) {
		light = rpLight[i];
		if (light)
			light->Enable(light->CurrWorld);
	}
}

void CLIGHT::Disable(s8 number)
{
	RP_Light* light = rpLight[number];
	if (light)
		light->Disable();
}

void CLIGHT::DisableAll()
{
	s8 i;
	RP_Light* light;
	for (i = 0; i < 8; i++) {
		light = rpLight[i];
		if (light)
			light->Disable();
	}
}

void CLIGHT::ChangeWorld(RpWorld* world)
{
	for (s8 i = 0; i < 8; ++i) {
		if (!world)
			Disable(i);
		else {
			Enable(i, world);
			SetCurrentNum(default_num);
			SetLightRegular(current_num);
		}
	}
}

void CLIGHT::SetCurrentNumPlayer(s8 player, s8 number)
{
	if (number < 0 || number >= 19)
		return;
	player_current[player] = number;
}

void CLIGHT::SetLightCurrentPlayer(s8 player)
{
	SetLightRegular(player_current[player]);
}

RP_Light::RP_Light(s8 number)
{
	lightNo   = number;
	lighttype = -1;
	pLight    = 0;
	if (lightNo == 0)
		CreateLight(0);
	else if (lightNo == 1)
		CreateLight(1);
	setflag = 3;
}

RP_Light::RP_Light(s8 number, RP_LightInfo* info)
{
	lightNo   = number;
	lighttype = -1;
	pLight    = 0;
	CreateLightFromTable(info);
	setflag = 3;
}

RpLight* RP_Light::CreateLightFromTable(RP_LightInfo* info)
{
	if (pLight)
		DestroyLight();
	pLight = fn_80154414(lbl_8042B160[info->type]);
	if (pLight) {
		if (info->type != 0) {
			RwFrame* frame = fn_8019E344();
			if (!frame) {
				DestroyLight();
				return 0;
			}
			fn_801A5370(pLight, frame);
		}
		lighttype = info->type;
		SetColor(&info->rgba);
		SetPosition(&info->pos);
		SetAngle(info->ang_x, info->ang_y);
		SetRadius(info->Radius);
		SetConeAngle(info->ConeAngle);
		return pLight;
	}
	return 0;
}

void CLIGHT::StartIgnoreLight(RpWorld*)
{
	DisableAll();
	SetCurrentNum(16);
	SetLightRegular(current_num);
	if (rpLight[0])
		rpLight[0]->SetFlag(3);
	Restore(0);
}

void CLIGHT::EndIgnoreLight(RpWorld*)
{
	SetCurrentNum(default_num);
	SetLightRegular(current_num);
	if (rpLight[0])
		rpLight[0]->SetFlag(3);
	RestoreAll();
}

extern "C" const f32 lbl_8042D390 = 1.0f;
