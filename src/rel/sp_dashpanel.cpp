#include "types.h"

// Retained type metadata identifies SPSTAGEOBJ::TObjDashpanel, its three
// bases, field offsets and method family. The GameCube vtable and resource
// references establish the complete text/data boundaries for this object.
// Deferred code generation emits these definitions in reverse source order.
//
// Address-named resources and the direction helper have descriptive local
// types/names; their original C++ spelling is not retained.
struct Vec3 {
	f32 x, y, z;
};
struct sAngle {
	s32 x, y, z;
};
struct sRealAngle3 {
	f32 x, y, z;
};
struct DASHPANEL_MEMBER {
	f32 Power;
	s16 nocon_time;
};
struct SETDATA_PARAM {
	Vec3 pos;
	sAngle ang;
	u8 pad18[0x14];
	DASHPANEL_MEMBER* member;
};
struct RwMatrix {
	u8 data[0x40];
};
struct RwFrame {
	u8 data[0x10];
	RwMatrix matrix;
};
struct RpClump {
	u8 data[4];
	RwFrame* frame;
};
struct SPSTG_CLUMP_INSTANCE {
	s32 num;
	RpClump** pClump;
	s32 world_index;
};
struct SPSTG_CLUMP {
	RpClump* clump;
	char* filename;
};
struct SPSTG_UV {
	void* animation;
	char* filename;
	char* material;
};
class TObjSample
{
public:
	static void* operator new(unsigned long);
};
struct TObjectHdr : public TObjSample {
	char* className;
	u8 pad04[0x14];
};
class TObject : public TObjectHdr
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
	s16 pad1C, objectSize;
	u8 pad20[8];
};
struct SetObjHdr {
	SETDATA_PARAM* frame;
};
class TObjSetObj : public SetObjHdr
{
public:
	TObjSetObj();
	virtual void EditOnChange(SETDATA_PARAM*);
};
class CSetObjAutoRemove
{
public:
	CSetObjAutoRemove();
	u8 storage[8];
};
extern "C" {
void* __nw__10TObjSampleFUl(u32);
void __dl__10TObjSampleFPv(void*);
void* __nw__FUl(u32);
void __dl__FPv(void*);
void __ct__7TObjectFP7TObject(void*, void*);
void __dt__7TObjectFv(void*, s16);
void __ct__10TObjSetObjFv(void*);
void __dt__10TObjSetObjFv(void*, s16);
void fn_16_93C3C(void*);
void fn_16_93BE8(void*, s32);
s32 fn_16_93ACC(void*, SETDATA_PARAM*, f32);
s32 CheckRangeOut__10TObjSetObjFv(void*);
s32 CheckMustKill__10TObjSetObjFv(void*);
s32 OnEdit__10TObjSetObjFv(void*);
void SetEnd__10TObjSetObjFv(void*);
void markSampleForDeletion(void*);
void copyVec3(Vec3*, const void*);
void fn_16_6B5C(sRealAngle3*, sAngle*);
void fn_80195A74(RwMatrix*, Vec3*, f32, s32);
void fn_80196050(RwMatrix*, Vec3*, s32);
void fn_80195B5C(void*, RwMatrix*);
void fn_16_4E374(Vec3*, f32, f32, f32);
void fn_8019941C(Vec3*, Vec3*, s32, void*);
void fn_16_4D444(sAngle*, Vec3*);
s32 fn_8003E2E4(s32, s32, Vec3*, s32);
f32 fn_16_11DC(f32);
void fn_800E0880(s32, Vec3*, sAngle*, s16);
void fn_800B52E8(void*, s32, s32, s32);
s32 fn_16_D64(void*);
void fn_8001F674(s32, s32, s32, s32);
f32 fn_800D7B00(s32);
f32 fn_800D7AE4(s32);
void fn_80195790(RwMatrix*, Vec3*, f32, f32, s32);
void fn_8019E880(RwFrame*);
void fn_8019EB94(RwFrame*, Vec3*, s32);
void fn_16_4DF58(void*);
void fn_16_4DEC8(void*);
void fn_16_4D7D8(void*);
void fn_16_4E554(void*);
void fn_16_4E384(void*);
void fn_16_4E3F0(void*, void*, f32);
void fn_16_4E090(void*, void*, s32);
void fn_16_4DFE8(void*, void*);
s32 fn_16_170C(void*);
void fn_16_4DE68(void*, s32);
void fn_16_4E49C(void*, void*);
void fn_16_4E154(void*, void*, void*, void*);
void fn_16_4E5D0(void*, void*, void*);
void OSReport(const char*, ...);
void* setupObjClass(
    void*, char*, void*, void*, void*, void*, u32, u32, u8, u16, u16, u8, char*, char**);
extern Vec3 AxisX, AxisY, AxisZ;
extern void* lbl_8042C388;
extern void* lbl_8042C1D0;
extern void* lbl_8042C298;
extern u8 lbl_802FF5A0;
extern TObject* lbl_16_bss_1058;
struct Player {
	u8 pad00[6];
	s16 flags;
};
struct Team {
	u8 pad00[0x258];
	void* controller;
};
extern Player* lbl_802AD090[];
extern Team* lbl_802AD0D0[];
}
namespace SPSTAGEOBJ
{
class TObjDashpanel : public TObject, public TObjSetObj, public CSetObjAutoRemove
{
public:
	s32 mode;
	s8 wait[8];
	s16 nocon_time;
	u8 pad46[2];
	Vec3 pos;
	sRealAngle3 ang;
	s32 timer;
	f32 Power;
	SPSTG_CLUMP_INSTANCE ClumpInstanceTbl;
	void* pMatrix;
	virtual void ImmAftSetRaster();
	sAngle GetDirection(); // Descriptive name: retained GC body returns a direction angle.
	void DashpanelPlayer();
	virtual void TDisp();
	virtual void Exec();
	void SetPosition();
	inline virtual ~TObjDashpanel();
	TObjDashpanel(TObject*);
	virtual void EditOnChange(SETDATA_PARAM*);
};
}
using SPSTAGEOBJ::TObjDashpanel;
extern "C" {
TObjDashpanel* __dt__Q210SPSTAGEOBJ13TObjDashpanelFv(TObjDashpanel*, s16);
extern void* __vt__Q210SPSTAGEOBJ13TObjDashpanel[];
}

// These data names preserve their GameCube address labels until their types
// and source names can be correlated independently.
extern "C" {
char lbl_16_data_44180[] = "so_dpuv.dff";
char lbl_16_data_4418C[] = "soL_dmoto.dff";
SPSTG_CLUMP lbl_16_data_4419C[3]
    = { { NULL, lbl_16_data_44180 }, { NULL, lbl_16_data_4418C }, { NULL, NULL } };
s32 lbl_16_data_441B4[2] = { 4, 2 };
// Adjacent resource-name strings share byte-aligned storage.
struct DashpanelUVNames {
	char uv1[14];
	char mat1[11];
	char uv2[16];
	char mat2[11];
};
DashpanelUVNames dashpanelUVNames
    = { "so_dpuv_1.uvb", "so2_dash01", "so_dpuv_1_1.uvb", "so3_dash01" };
SPSTG_UV lbl_16_data_441F0[3] = { { NULL, dashpanelUVNames.uv1, dashpanelUVNames.mat1 },
	{ NULL, dashpanelUVNames.uv2, dashpanelUVNames.mat2 }, { NULL, NULL, NULL } };
struct DashpanelFieldNames {
	char power[17];
	char timer[18];
};
DashpanelFieldNames dashpanelFieldNames = { "Power(Def. 5.0f)", "No Ctrl Time(Frm)" };
char* spDashpanelFieldNames[]           = { dashpanelFieldNames.power, dashpanelFieldNames.timer };
char spDashpanelClassName[]             = "TObjDashpanel";
char* lbl_16_data_44250                 = spDashpanelClassName;
u8 lbl_16_bss_6450[0x90];
void fn_16_8046C();
void fn_16_804A0();
void fn_16_80518();
}

extern "C" {
extern const f32 dashpanelZero;
extern const f32 dashpanelOne;
extern const f32 dashpanelExtent;
extern const f32 dashpanelNegativeExtent;
extern const f32 dashpanelRemoveRange;
extern const f32 dashpanelAnimationSpeed;
extern const f32 dashpanelDefaultPower;
extern const f32 dashpanelAngleScale;
extern const f32 dashpanelConversionBias;
extern const f32 dashpanelNegativeZero;
extern const f32 dashpanelAngleUnits;
extern const f32 dashpanelMinimumPower;
extern const f32 dashpanelMaximumPower;
}
#pragma optimization_level 0
extern "C" void fn_16_80568()
{
	setupObjClass(lbl_16_bss_6450, "SP DASHPANEL OBJECT", (void*)fn_16_804A0, (void*)fn_16_8046C,
	    (void*)fn_16_80518, NULL, 0x20000, 0, 0x1E, 0x15F0, 2, 0, "fs", spDashpanelFieldNames);
}

extern "C" void fn_16_80518()
{
	new TObjDashpanel(lbl_16_bss_1058);
}

extern "C" void fn_16_804A0()
{
	fn_16_4E154(lbl_16_data_4419C, *(void**)((u8*)lbl_8042C1D0 + 0x8C18),
	    *(void**)((u8*)lbl_8042C298 + 0xA50), &lbl_802FF5A0);
	fn_16_4E5D0(lbl_16_data_441F0, *(void**)((u8*)lbl_8042C298 + 0xA50), &lbl_802FF5A0);
}

extern "C" void fn_16_8046C()
{
	fn_16_4D7D8(lbl_16_data_4419C);
	fn_16_4E554(lbl_16_data_441F0);
}

void TObjDashpanel::EditOnChange(SETDATA_PARAM* setData)
{
	register DASHPANEL_MEMBER* _member = setData->member;
	if (_member->Power < dashpanelMinimumPower)
		_member->Power = dashpanelMinimumPower;
	if (_member->Power > dashpanelMaximumPower)
		_member->Power = dashpanelMaximumPower;
	if (_member->nocon_time < 0)
		_member->nocon_time = 0;
	if (_member->nocon_time > 32767)
		_member->nocon_time = 32767;
}

TObjDashpanel::TObjDashpanel(TObject* ptp)
    : TObject(ptp)
    , TObjSetObj()
    , CSetObjAutoRemove()
{
	register DASHPANEL_MEMBER* _member;
	register s32 i;
	className  = lbl_16_data_44250;
	objectSize = sizeof(TObjDashpanel);
	copyVec3(&pos, frame);
	fn_16_6B5C(&ang, &frame->ang);
	_member    = frame->member;
	Power      = dashpanelDefaultPower + _member->Power;
	nocon_time = _member->nocon_time;
	timer      = 0;
	for (i = 0; i < 8; ++i)
		wait[i] = 0;
	pMatrix = NULL;
	mode    = 1;
	fn_16_4E090(&ClumpInstanceTbl, lbl_16_data_4419C, 2);
	fn_16_4DFE8(&ClumpInstanceTbl, lbl_16_data_441B4);
	SetPosition();
	if ((u32)&ClumpInstanceTbl.world_index == 0x80720630)
		OSReport("test\n");
	fn_16_4DE68(&ClumpInstanceTbl, fn_16_170C(&(TObjSetObj&)*this) + 4);
	fn_16_4E49C(&ClumpInstanceTbl, lbl_16_data_441F0);
}

extern "C" TObjDashpanel* __dt__Q210SPSTAGEOBJ13TObjDashpanelFv(TObjDashpanel* object, s16 flags)
{
	if (object != NULL) {
		*(void**)((u8*)object + 0x18) = __vt__Q210SPSTAGEOBJ13TObjDashpanel;
		*(void**)((u8*)object + 0x2c) = __vt__Q210SPSTAGEOBJ13TObjDashpanel + 11;
		if (object->pMatrix != NULL) {
			__dl__FPv(object->pMatrix);
			object->pMatrix = NULL;
		}
		fn_16_4DF58(&object->ClumpInstanceTbl);
		fn_16_4DEC8(&object->ClumpInstanceTbl);
		fn_16_93BE8(&(CSetObjAutoRemove&)*object, 0);
		__dt__10TObjSetObjFv(&(TObjSetObj&)*object, 0);
		__dt__7TObjectFv(object, 0);
		if (flags > 0)
			__dl__10TObjSampleFPv(object);
	}
	return object;
}

void TObjDashpanel::SetPosition()
{
	register s32 i;
	register RwFrame* pFrame;
	for (i = 0; i < 2; ++i) {
		pFrame = ClumpInstanceTbl.pClump[i]->frame;
		fn_80195790(
		    &pFrame->matrix, &AxisX, dashpanelOne - fn_800D7AE4(0xC000), fn_800D7B00(0xC000), 0);
		fn_8019E880(pFrame);
		fn_80195790(&pFrame->matrix, &AxisY,
		    dashpanelOne - fn_800D7AE4((s32)(dashpanelAngleUnits * ang.y)),
		    fn_800D7B00((s32)(dashpanelAngleUnits * ang.y)), 2);
		fn_8019E880(pFrame);
		fn_80195790(&pFrame->matrix, &AxisX,
		    dashpanelOne - fn_800D7AE4((s32)(dashpanelAngleUnits * ang.x)),
		    fn_800D7B00((s32)(dashpanelAngleUnits * ang.x)), 2);
		fn_8019E880(pFrame);
		fn_80195790(&pFrame->matrix, &AxisZ,
		    dashpanelOne - fn_800D7AE4((s32)(dashpanelAngleUnits * ang.z)),
		    fn_800D7B00((s32)(dashpanelAngleUnits * ang.z)), 2);
		fn_8019E880(pFrame);
		fn_8019EB94(pFrame, &pos, 2);
	}
}

void TObjDashpanel::Exec()
{
	register DASHPANEL_MEMBER* _member = frame->member;
	register s32 pno;
	if (!fn_16_93ACC(&(CSetObjAutoRemove&)*this, frame, dashpanelRemoveRange)) {
		SetEnd__10TObjSetObjFv(&(TObjSetObj&)*this);
		markSampleForDeletion(this);
		return;
	}
	if (CheckRangeOut__10TObjSetObjFv(&(TObjSetObj&)*this)
	    || CheckMustKill__10TObjSetObjFv(&(TObjSetObj&)*this)) {
		markSampleForDeletion(this);
		return;
	}
	fn_16_4E3F0(&ClumpInstanceTbl, lbl_16_data_441F0, dashpanelAnimationSpeed);
	if (OnEdit__10TObjSetObjFv(&(TObjSetObj&)*this)) {
		copyVec3(&pos, frame);
		fn_16_6B5C(&ang, &frame->ang);
		Power      = dashpanelDefaultPower + _member->Power;
		nocon_time = _member->nocon_time;
		SetPosition();
	} else {
		DashpanelPlayer();
		for (pno = 0; pno < 8; ++pno)
			if (wait[pno] > 0)
				--wait[pno];
	}
}

void TObjDashpanel::TDisp() { }

void TObjDashpanel::DashpanelPlayer()
{
	register s32 pno;
	RwMatrix TempMatrix;
	register void* pInvertMatrix;
	Vec3 player_pos;
	Vec3 vVelocity;
	if (pMatrix == NULL) {
		pMatrix       = __nw__FUl(sizeof(RwMatrix));
		pInvertMatrix = pMatrix;
		fn_80195A74(&TempMatrix, &AxisY, ang.y, 0);
		fn_80195A74(&TempMatrix, &AxisX, ang.x, 2);
		fn_80195A74(&TempMatrix, &AxisZ, ang.z, 2);
		fn_80196050(&TempMatrix, &pos, 2);
		fn_80195B5C(pInvertMatrix, &TempMatrix);
	}
	for (pno = 0; pno < 8; ++pno) {
		if (wait[pno] > 0)
			continue;
		if (!fn_8003E2E4(pno, 1, &player_pos, 0))
			continue;
		fn_8019941C(&player_pos, &player_pos, 1, pMatrix);
		if (lbl_802AD090[pno] == NULL || !(lbl_802AD090[pno]->flags & 1))
			continue;
		if (fn_16_11DC(player_pos.x) > dashpanelExtent || fn_16_11DC(player_pos.y) > dashpanelExtent
		    || player_pos.z > dashpanelExtent || player_pos.z < dashpanelNegativeExtent)
			continue;
		vVelocity.x = Power;
		vVelocity.y = vVelocity.z = dashpanelZero;
		sAngle angle3             = frame->ang;
		angle3.y -= 0x8000;
		fn_800E0880(pno, &vVelocity, &angle3, nocon_time);
		wait[pno] = 4;
		if (lbl_8042C388 != NULL)
			fn_800B52E8(lbl_8042C388, 0x101D, 0, 0);
		fn_8001F674(fn_16_D64(lbl_802AD0D0[pno]->controller), 4, 15, 0);
	}
}

sAngle TObjDashpanel::GetDirection()
{
	RwMatrix matrix;
	Vec3 direction;
	sAngle angle;
	fn_80195A74(&matrix, &AxisY, ang.y, 0);
	fn_80195A74(&matrix, &AxisX, ang.x, 2);
	fn_80195A74(&matrix, &AxisZ, ang.z, 2);
	fn_16_4E374(&direction, dashpanelZero, dashpanelZero, dashpanelOne);
	fn_8019941C(&direction, &direction, 1, &matrix);
	fn_16_4D444(&angle, &direction);
	if (angle.x == 0 && angle.y == 0)
		angle.y -= 0x8000;
	return angle;
}

void TObjDashpanel::ImmAftSetRaster()
{
	fn_16_4E384(lbl_16_data_441F0);
}
__declspec(section ".ctors") void (*const spDashpanelCtorEntry)() = fn_16_80568;

#pragma force_active on
extern "C" {
extern const f32 dashpanelZero           = 0.0f;
extern const f32 dashpanelOne            = 1.0f;
extern const f32 dashpanelExtent         = 15.0f;
extern const f32 dashpanelNegativeExtent = -15.0f;
extern const f32 dashpanelRemoveRange    = 10.0f;
extern const f32 dashpanelAnimationSpeed = 3.0f;
extern const f32 dashpanelDefaultPower   = 5.0f;
// Unreferenced conversion constants retained in this unit's read-only pool.
extern const f32 dashpanelAngleScale     = 0.0054931640625f;
extern const f32 dashpanelConversionBias = 176.0f;
extern const f32 dashpanelNegativeZero   = -0.0f;
extern const f32 dashpanelAngleUnits     = 182.04445f;
extern const f32 dashpanelMinimumPower   = -5.0f;
extern const f32 dashpanelMaximumPower   = 20.0f;
}
#pragma force_active reset
