// Complete C++ reactor unit, including compiler-generated virtual-base thunks.
// All 42 surviving bodies match before normalization. MWCC places the weak
// 28-byte SetDirection before the factories instead of after the thunks.
// Inline modes, compiler versions, class/definition ordering and whole-TU
// inline pragmas did not recover its placement. The object step moves only
// this compiler-produced body and its ELF references; no instructions change.
// Remove that step when the original weak-inline emission rule is understood.
// See docs/c-colli-react-unit-evidence.md for source-order evidence and trials.

#include "game/c_colli_react.h"

extern "C" {
f32 fn_801991B4(RwV3d*);
RwV3d* fn_801990E0(RwV3d*, RwV3d*);
void fn_8001F24C();
void fn_8001F2D4();
void fn_8001F144(void*, s32);
void fn_8001F014(void*, RwV3d*, RwV3d*);
extern void* lbl_8042C178;
}

CCL_REACTOR::~CCL_REACTOR() { }

void CCL_REACTOR::SetParameter(RwV3d*, sAngle*) { }

void CCL_REACTOR::ClrParameter()
{
	vecParam.x = vecParam.y = vecParam.z = 0.0f;
	angParam.x = angParam.y = angParam.z = 0;
}

void CCL_REACTOR::AddParameter(RwV3d*, sAngle*) { }

void CCL_REACTOR::GetParameter(RwV3d* vec, sAngle* ang)
{
	if (vec)
		*vec = vecParam;
	if (ang)
		*ang = angParam;
}

void CCL_REACTOR::ClrDirection()
{
	vecDirection.x = vecDirection.y = vecDirection.z = 0.0f;
}

f32 CCL_REACTOR::GetDotProductOfDirection(RwV3d*)
{
	return 0.0f;
}

CCL_REACTION CCL_REACTOR::React(RwV3d*, sAngle*)
{
	return CCL_REACTION_NONE;
}

s32 Destruct_CCL_REACTOR(CCL_INFO* info)
{
	delete info->pReactor;
	info->pReactor = NULL;
	return 1;
}

CCL_REACTOR_TRANS::~CCL_REACTOR_TRANS() { }

void CCL_REACTOR_TRANS::SetParameter(RwV3d* vec, sAngle*)
{
	vecParam = *vec;
}

CCL_REACTION CCL_REACTOR_TRANS::React(RwV3d* pos, sAngle* ang)
{
	pos->x += vecParam.x;
	pos->y += vecParam.y;
	pos->z += vecParam.z;
	ang->x = 0;
	ang->z = 0;
	return CCL_REACTION_FORCE;
}

s32 Construct_CCL_REACTOR_TRANS(CCL_INFO* info)
{
	if (!info->pReactor)
		info->pReactor = new CCL_REACTOR_TRANS;
	else if (info->pReactor->CheckReactor(CCL_REACTION_FORCE) == 0L)
		return 0;
	if (info->pReactor) {
		info->pReactor->AddCountReffered();
		return 1;
	}
	return 0;
}

CCL_REACTOR_TRANSROTS::~CCL_REACTOR_TRANSROTS() { }

void CCL_REACTOR_TRANSROTS::SetParameter(RwV3d* vec, sAngle* ang)
{
	vecParam = *vec;
	angParam = *ang;
}

CCL_REACTION CCL_REACTOR_TRANSROTS::React(RwV3d* pos, sAngle* ang)
{
	pos->x += vecParam.x;
	pos->y += vecParam.y;
	pos->z += vecParam.z;
	ang->x = angParam.x;
	ang->z = angParam.z;
	return CCL_REACTION_FORCE;
}

s32 Construct_CCL_REACTOR_TRANSROTS(CCL_INFO* info)
{
	if (!info->pReactor)
		info->pReactor = new CCL_REACTOR_TRANSROTS;
	else if (info->pReactor->CheckReactor(CCL_REACTION_REALFORCE) == 0L)
		return 0;
	if (info->pReactor) {
		info->pReactor->AddCountReffered();
		return 1;
	}
	return 0;
}

CCL_REACTOR_TURNTABLE::~CCL_REACTOR_TURNTABLE() { }

void CCL_REACTOR_TURNTABLE::SetParameter(RwV3d* vec, sAngle* ang)
{
	vecParam = *vec;
	angParam = *ang;
}

CCL_REACTION CCL_REACTOR_TURNTABLE::React(RwV3d* pos, sAngle* ang)
{
	RwV3d vec = { 0, 0, 0 };
	f32 dist;
	vec.x = pos->x - vecDirection.x;
	vec.z = pos->z - vecDirection.z;
	dist  = vec.x * vec.x + vec.z * vec.z;
	if (dist > 0.0f) {
		f64 estimate         = __frsqrte(dist);
		estimate             = (0.5 * estimate) * (3.0 - dist * (estimate * estimate));
		estimate             = (0.5 * estimate) * (3.0 - dist * (estimate * estimate));
		estimate             = (0.5 * estimate) * (3.0 - dist * (estimate * estimate));
		volatile f32 rounded = (f32)(dist * estimate);
		dist                 = rounded;
	}
	dist = ((f32)angParam.y / 65536.0f) * (6.283184051513672f * dist);
	pos->x += vecParam.x;
	pos->y += vecParam.y;
	pos->z += vecParam.z;
	if (dist > 0.001f && fn_801991B4(&vec) > 0.001f) {
		fn_801990E0(&vec, &vec);
		vec.x *= dist;
		vec.z *= dist;
		fn_8001F24C();
		fn_8001F144(lbl_8042C178, angParam.y + 0x4000);
		fn_8001F014(lbl_8042C178, &vec, &vec);
		fn_8001F2D4();
		pos->x += vec.x;
		pos->z += vec.z;
	}
	ang->x = angParam.x;
	ang->y -= angParam.y;
	ang->z = angParam.z;
	return CCL_REACTION_FORCE;
}

s32 Construct_CCL_REACTOR_TURNTABLE(CCL_INFO* info)
{
	if (!info->pReactor)
		info->pReactor = new CCL_REACTOR_TURNTABLE;
	else if (info->pReactor->CheckReactor(CCL_REACTION_REALFORCE) == 0L)
		return 0;
	if (info->pReactor) {
		info->pReactor->AddCountReffered();
		return 1;
	}
	return 0;
}

CCL_REACTOR_PUSHPULL::~CCL_REACTOR_PUSHPULL() { }

void CCL_REACTOR_PUSHPULL::SetParameter(RwV3d* vec, sAngle*)
{
	vecParam = *vec;
}

void CCL_REACTOR_PUSHPULL::AddParameter(RwV3d* vec, sAngle*)
{
	vecParam.x += vec->x;
	vecParam.y += vec->y;
	vecParam.z += vec->z;
}

f32 CCL_REACTOR_PUSHPULL::GetDotProductOfDirection(RwV3d* vec)
{
	return vec->z * vecDirection.z + (vec->x * vecDirection.x + vec->y * vecDirection.y);
}

CCL_REACTION CCL_REACTOR_PUSHPULL::React(RwV3d* pos, sAngle*)
{
	vecParam.x += pos->x;
	vecParam.y += pos->y;
	vecParam.z += pos->z;
	return CCL_REACTION_PUSHPULL;
}
CCL_REACTOR_PUSHPULL* Construct_CCL_REACTOR_PUSHPULL(CCL_INFO* info)
{
	CCL_REACTOR_PUSHPULL* reactor;
	if (!info->pReactor) {
		reactor        = new CCL_REACTOR_PUSHPULL;
		info->pReactor = reactor;
	} else {
		return NULL;
	}
	if (info->pReactor) {
		info->pReactor->AddCountReffered();
		return reactor;
	}
	return NULL;
}
