#include "types.h"
#include "game/link.h"

// eff_muteki.cpp: all twelve surviving functions match natively. PS2 C++
// DWARF corroborates the classes and methods; GameCube is authoritative.
// Deferred emission inlines the factory/update helpers before reversing
// definitions into retail order. See docs/language-audit.md.
struct RwV3d {
	f32 x, y, z;
};
struct RwTexCoords {
	f32 u, v;
};
struct RwMatrix {
	f32 data[16];
};
struct RwTexture {
	void* raster;
};
struct MutekiVertex {
	RwV3d pos, normal;
	u8 r, g, b, a;
	void SetPos(const RwV3d& p)
	{
		f32 z, y;
		y     = p.y;
		z     = p.z;
		pos.x = p.x;
		pos.y = y;
		pos.z = z;
	}

	f32 u, v;
};
struct TObjectBase {
	char* ClassName;
	u16 Signal, Tag;
	void* Prev;
	void* Next;
	void* Parent;
	void* Child;
};
struct THeapCtrl {
	void* Malloc(u32);
	void Free(void*);
};
extern "C" THeapCtrl* lbl_8042C148;
class TObject : public TObjectBase
{
public:
	TObject(TObject*);
	virtual ~TObject();
	virtual void Exec();
	virtual void Disp();
	virtual void TDisp();
	virtual void PDisp();
	virtual void ImmAftSetRaster();
	virtual void Debug();
	virtual void Error(char*);
	virtual void Render();
	u16 ExecTime, DispTime, TDispTime, PDispTime, ImmAftSetRasterTime, pad26;
	static void* operator new(unsigned long size) { return lbl_8042C148->Malloc(size); }
	static void operator delete(void* p) { lbl_8042C148->Free(p); }
};
struct MutekiMotion {
	u8 pad[8];
	RwV3d pos;
};
struct MutekiPlayer {
	u8 pad00[0x38];
	MutekiMotion* motion;
	u8 pad3c[0x760 - 0x3c];
	s8 playerNo, character;
};
struct MutekiTeam {
	u8 pad00[0x3b];
	s8 leader;
	u8 pad3c[0x114 - 0x3c];
	MutekiPlayer* players[3];
	u8 pad120[0x206 - 0x120];
	s16 flags;
};
struct MutekiGameMode {
	u8 pad[0x20];
	s8 hidden;
};
extern "C" {
extern MutekiTeam* lbl_80303DC8[];
extern MutekiPlayer* lbl_802AD070[];
extern TObject* lbl_8042C2A0;
extern TObject* lbl_8042C110;
extern MutekiGameMode* lbl_8042C180;
extern RwV3d lbl_80239978, lbl_80239990;
s32 rand();
f64 __frsqrte(f64);
f64 __fabs(f64);
f32 fn_801990E0(RwV3d*, const RwV3d*);
RwMatrix* fn_80195A74(RwMatrix*, const RwV3d*, f32, s32);
RwV3d* fn_8019947C(RwV3d*, const RwV3d*, s32, const RwMatrix*);
s32 fn_80194294(s32, void*);
s32 fn_80194234(s32, void*);
void* fn_801B2934(MutekiVertex*, u32, RwMatrix*, u32);
s32 fn_801B2C00(s32);
s32 fn_801B2A14();
void* fn_8005EC0C();
RwTexture* fn_801A4BBC(void*, const char*);
}
class EffMuteki : public CLASS_LINK
{
public:
	EffMuteki();
	~EffMuteki();
	s32 Exec();
	s32 Disp();
	s32 mode;
	s8 team;
	s16 nowAlpha;
	f32 nowPattern;
	RwV3d pos_org, pos_offset, vec, edg;
};
class EffMutekiManager : public TObject, public CLASS_LINK_MANAGER
{
public:
	EffMutekiManager(TObject*);
	virtual ~EffMutekiManager();
	virtual void Exec();
	virtual void TDisp();
	s32 InsertEffect(EffMuteki*);
	s32 EraseEffect(EffMuteki*);
};
class TObjPlayerMuteki : public TObject
{
public:
	TObjPlayerMuteki(TObject*, s32);
	virtual ~TObjPlayerMuteki();
	virtual void Exec();
	virtual void TDisp();
	s8 team, timer;
};
char* CL_EffMutekiManager    = "EffMutekiManager";
RwTexCoords MutekiUV[4]      = { { 0, 0 }, { 0, .25f }, { .25f, 0 }, { .25f, .25f } };
RwTexCoords MutekiPattern[8] = { { 0, 0 }, { .25f, 0 }, { .5f, 0 }, { .75f, 0 }, { 0, .25f },
	{ .25f, .25f }, { .5f, .25f }, { .75f, .25f } };
char* CL_TObjPlayerMuteki    = "TObjPlayerMuteki";
f32 MutekiRadius[12]         = { 5.5f, 5.5f, 5, 5.5f, 6.5f, 5, 5.5f, 8, 5, 5.5f, 8, 4.5f };
RwTexture* MutekiTexture;
EffMutekiManager* MutekiManager;
static EffMuteki* Create(RwV3d*, RwV3d*, f32, f32);

inline f32 MutekiSqrt(f32 value)
{
	if (value > 0.0f) {
		f64 estimate        = __frsqrte(value);
		estimate            = .5 * estimate * (3.0 - estimate * estimate * value);
		estimate            = .5 * estimate * (3.0 - estimate * estimate * value);
		estimate            = .5 * estimate * (3.0 - estimate * estimate * value);
		volatile f32 result = value * estimate;
		value               = result;
	}
	return value;
}

void InitEffMuteki()
{
	if (!MutekiTexture)
		MutekiTexture = fn_801A4BBC(fn_8005EC0C(), "ef_mtk");
	MutekiManager = 0;
}

void EndEffMuteki()
{
	if (MutekiManager) {
		delete MutekiManager;
		MutekiManager = 0;
	}
	MutekiTexture = 0;
}

EffMutekiManager::EffMutekiManager(TObject* p)
    : TObject(p)
{
	ClassName = CL_EffMutekiManager;
	DispTime  = sizeof(*this);
}

EffMutekiManager::~EffMutekiManager()
{
	pCurrent = pHead;
	while (pCurrent) {
		EffMuteki* p = (EffMuteki*)pCurrent->pData;
		pCurrent     = pCurrent->pNext;
		if (p)
			delete p;
	}
	if (MutekiManager == this)
		MutekiManager = 0;
}

s32 EffMutekiManager::InsertEffect(EffMuteki* p)
{
	if (LinkClass(p)) {
		p->pData = p;
		return 1;
	}
	return 0;
}

s32 EffMutekiManager::EraseEffect(EffMuteki* p)
{
	return UnlinkClass(p) != 0;
}

void EffMutekiManager::Exec()
{
	pCurrent = pHead;
	while (pCurrent) {
		EffMuteki* p = (EffMuteki*)pCurrent->pData;
		pCurrent     = pCurrent->pNext;
		if (p && p->Exec())
			delete p;
	}
}

void EffMutekiManager::TDisp()
{
	if (!MutekiTexture)
		return;
	if (lbl_8042C180->hidden)
		return;
	void *src, *dst, *ztest, *zwrite;
	fn_80194294(10, &src);
	fn_80194294(11, &dst);
	fn_80194294(20, &ztest);
	fn_80194294(14, &zwrite);
	fn_80194234(10, (void*)5);
	fn_80194234(11, (void*)2);
	fn_80194234(20, (void*)1);
	fn_80194234(14, 0);
	fn_80194234(1, MutekiTexture->raster);
	for (pCurrent = pHead; pCurrent; pCurrent = pCurrent->pNext) {
		EffMuteki* p = (EffMuteki*)pCurrent->pData;
		if (p)
			p->Disp();
	}
	fn_801B2A14();
	fn_80194234(14, zwrite);
	fn_80194234(20, ztest);
	fn_80194234(10, src);
	fn_80194234(11, dst);
}

EffMuteki::EffMuteki()
{
	team = -1;
	mode = 0;
	MutekiManager->InsertEffect(this);
}

EffMuteki::~EffMuteki()
{
	MutekiManager->EraseEffect(this);
}

s32 EffMuteki::Exec()
{
	if (team != -1)
		pos_org = lbl_80303DC8[team]->players[lbl_80303DC8[team]->leader]->motion->pos;
	switch (mode) {
		case 0:
			nowPattern += 1.0f;
			if (nowPattern >= 8.0f) {
				nowPattern = 7.0f;
				if (nowAlpha > 0)
					nowAlpha -= 64;
				else {
					nowAlpha = 0;
					return 1;
				}
			}
			break;
		case 1:
			nowPattern += 1.0f;
			if (nowPattern >= 8.0f)
				nowPattern = 0.0f;
			if (nowAlpha > 0)
				nowAlpha -= 64;
			else {
				nowAlpha = 0;
				return 1;
			}
			break;
	}
	return 0;
}

s32 EffMuteki::Disp()
{
	if (nowAlpha <= 0)
		return 0;
	u8 alpha;
	if (nowAlpha >= 255)
		alpha = 255;
	else
		alpha = nowAlpha;
	RwV3d positions[4];
	f32 x = pos_org.x + pos_offset.x, y = pos_org.y + pos_offset.y, z = pos_org.z + pos_offset.z;
	positions[2].x = x + edg.x;
	positions[2].y = y + edg.y;
	positions[2].z = z + edg.z;
	positions[3].x = x - edg.x;
	positions[3].y = y - edg.y;
	positions[3].z = z - edg.z;
	x += vec.x;
	y += vec.y;
	z += vec.z;
	positions[0].x = x + edg.x;
	positions[0].y = y + edg.y;
	positions[0].z = z + edg.z;
	positions[1].x = x - edg.x;
	positions[1].y = y - edg.y;
	positions[1].z = z - edg.z;
	MutekiVertex vertices[4];
	MutekiVertex* v = vertices;
	u32 pattern     = (u32)nowPattern;
	f32 u           = MutekiPattern[pattern].u;
	f32 vBase       = MutekiPattern[pattern].v;
	f32* offset     = (f32*)MutekiUV;
	for (s32 i = 0; i < 4; v++, i++) {
		v->SetPos(positions[i]);
		v->u = u + offset[0];
		v->v = vBase + offset[1];
		offset += 2;
		v->r = 255;
		v->g = 255;
		v->b = 255;
		v->a = alpha;
	}
	if (fn_801B2934(vertices, 4, 0, 0x19))
		fn_801B2C00(4);
	return 1;
}

static EffMuteki* Create(RwV3d* pPos_Org, RwV3d* pDir, f32 rotSpread, f32 fScl)
{
	if (!MutekiManager) {
		TObject* pTO = lbl_8042C2A0;
		if (!pTO)
			pTO = lbl_8042C110;
		MutekiManager = new EffMutekiManager(pTO);
	}
	EffMuteki* p = new EffMuteki;
	if (!p)
		return 0;
	f32 rot    = 360.0f * (rand() * (1.0f / 32768.0f));
	f32 spread = rotSpread * (2.0f * (rand() * (1.0f / 32768.0f) - .5f));
	RwV3d vCross_Temp, vDir_Temp;
	fn_801990E0(&vDir_Temp, pDir);
	if ((f32)__fabs(vDir_Temp.y) >= .9961f)
		vCross_Temp = lbl_80239978;
	else {
		vCross_Temp.y = 0.0f;
		f32 z2        = vDir_Temp.z * vDir_Temp.z;
		vCross_Temp.x = z2 / (z2 + vDir_Temp.x * vDir_Temp.x);
		if ((f32)__fabs(vDir_Temp.z) > .001f) {
			vCross_Temp.z = -vCross_Temp.x * vDir_Temp.x / vDir_Temp.z;
			fn_801990E0(&vCross_Temp, &vCross_Temp);
		} else
			vCross_Temp = lbl_80239990;
	}
	RwMatrix mat_Temp;
	fn_80195A74(&mat_Temp, &vCross_Temp, spread, 0);
	fn_80195A74(&mat_Temp, &vDir_Temp, rot, 2);
	RwV3d vLine_Temp;
	fn_8019947C(&vLine_Temp, pDir, 1, &mat_Temp);
	p->pos_offset = vLine_Temp;
	p->pos_org    = *pPos_Org;
	fn_801990E0(&vLine_Temp, &vLine_Temp);
	p->vec.x = vLine_Temp.x * fScl;
	p->vec.y = vLine_Temp.y * fScl;
	p->vec.z = vLine_Temp.z * fScl;
	p->edg.x = vCross_Temp.x * (.1f * fScl);
	p->edg.y = vCross_Temp.y * (.1f * fScl);
	p->edg.z = vCross_Temp.z * (.1f * fScl);
	return p;
}

void CreateChargeObi(RwV3d* pos, RwV3d* dir, f32 spread, f32 scale)
{
	EffMuteki* p = Create(pos, dir, spread, scale);
	if (p) {
		p->nowPattern = 7.99f * (rand() * (1.0f / 32768.0f));
		p->nowAlpha   = 255;
		p->mode       = 1;
	}
}

void SetPlayerMuteki(s32 team)
{
	MutekiTeam* pTeam = lbl_80303DC8[team];
	if (!pTeam)
		return;
	switch (pTeam->flags & 0x8000) {
		case 0:
			break;
		default:
			return;
	}
	TObject* parent = lbl_8042C2A0;
	if (!parent)
		parent = lbl_8042C110;
	TObjPlayerMuteki* p = new TObjPlayerMuteki(parent, team);
	if (p)
		pTeam->flags |= 0x8000;
}

TObjPlayerMuteki::TObjPlayerMuteki(TObject* p, s32 n)
    : TObject(p)
{
	team      = n;
	timer     = 0;
	ClassName = CL_TObjPlayerMuteki;
	DispTime  = sizeof(*this);
}

TObjPlayerMuteki::~TObjPlayerMuteki() { }

void TObjPlayerMuteki::Exec()
{
	MutekiTeam* pTeam = lbl_80303DC8[team];
	if (!pTeam) {
		Signal |= 1;
		return;
	}
	s32 player = pTeam->players[pTeam->leader]->playerNo;
	if (!(pTeam->flags & 0x8000)) {
		Signal |= 1;
		return;
	}
	MutekiPlayer* pPlayer = lbl_802AD070[player];
	RwV3d pos;
	pos.x      = pPlayer->motion->pos.x;
	pos.y      = pPlayer->motion->pos.y;
	pos.z      = pPlayer->motion->pos.z;
	f32 radius = MutekiRadius[pPlayer->character];
	for (s32 i = 0; i < 2; i++) {
		RwV3d dir;
		dir.x = rand() * (1.0f / 32768.0f);
		dir.y = 0.0f;
		dir.z = 1.0f - MutekiSqrt(dir.x * dir.x);
		if (timer & 1)
			dir.x = -dir.x;
		if (timer++ & 2)
			dir.z = -dir.z;
		dir.x *= radius;
		dir.z *= radius;
		EffMuteki* p = Create(&pos, &dir, 6144.0f, radius);
		if (!p)
			return;
		p->nowPattern = 0.0f;
		p->nowAlpha   = 255;
		p->team       = team;
		p->mode       = 0;
	}
}

void TObjPlayerMuteki::TDisp() { }
