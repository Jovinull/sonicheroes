// TObjSignal's layout and the two members its Exec inlines, shared by
// rel/signal_exec.cpp and the units that keep the out-of-line copies
// (rel/signal_set_position.cpp, rel/signal_set_parameter.cpp). The PS2 build
// names them TObjSignal::SetPosition and TObjSignal::SetParameter; each is
// inline here and defined plain by the unit that emits its copy.

typedef struct RwV3d {
	f32 x, y, z;
} RwV3d;

typedef struct SignalSetData {
	RwV3d pos;     // 0x00
	s32 angX;      // 0x0C
	s32 angY;      // 0x10
	s32 angZ;      // 0x14
	u8 unk18[0x14]; // 0x18
	u8* params;    // 0x2C
} SignalSetData;

typedef struct SignalModel {
	u8 unk00[0x4];
	void* frame; // 0x04
} SignalModel;

typedef struct Signal {
	u8 unk00[0x4];
	u16 signal;             // 0x04
	u8 unk06[0x22];         // 0x06
	SignalSetData* setdata; // 0x28
	void* setobjVtable;     // 0x2C
	u8 colli[0x60];         // 0x30
	RwV3d colliPos;         // 0x90
	s32 colliAngX;          // 0x9C
	s32 colliAngY;          // 0xA0
	s32 colliAngZ;          // 0xA4
	u8 unkA8[0x4];          // 0xA8
	RwV3d colliOldPos;      // 0xAC
	u8 kind;                // 0xB8
	u8 padB9[0x3];          // 0xB9
	RwV3d pos;              // 0xBC
	RwV3d basePos;          // 0xC8
	s32 angX;               // 0xD4
	s32 angY;               // 0xD8
	s32 angZ;               // 0xDC
	SignalModel* model;     // 0xE0
} Signal;                   // 0xE4

extern "C" const f32 lbl_8_rodata_BB0[1];
extern "C" const RwV3d AxisX;
extern "C" const RwV3d AxisY;
extern "C" const RwV3d AxisZ;

extern "C" f32 fn_800D7B00(s32 angle);
extern "C" f32 fn_800D7AE4(s32 angle);
extern "C" void fn_80195790(void* matrix, const RwV3d* axis, f32 oneMinusCos, f32 sin, s32 combine);
extern "C" void fn_8019EB94(void* frame, RwV3d* translation, s32 combine);

#ifndef SIGNAL_SET_POSITION_INLINE
#define SIGNAL_SET_POSITION_INLINE inline
#endif

// Turns the model's frame by the placement's angles (Y, then X, then Z) and
// moves it to the signal's position. The frame's matrix address is worked out
// again for each turn, as common-subexpression elimination off gives.
#pragma opt_common_subs off
extern "C" SIGNAL_SET_POSITION_INLINE void signalSetPosition(Signal* object)
{
	void* frame = object->model->frame;
	f32 sin;

	sin = fn_800D7B00(object->angY);
	fn_80195790((u8*)frame + 0x10, &AxisY, lbl_8_rodata_BB0[0] - fn_800D7AE4(object->angY), sin, 0);
	sin = fn_800D7B00(object->angX);
	fn_80195790((u8*)frame + 0x10, &AxisX, lbl_8_rodata_BB0[0] - fn_800D7AE4(object->angX), sin, 2);
	sin = fn_800D7B00(object->angZ);
	fn_80195790((u8*)frame + 0x10, &AxisZ, lbl_8_rodata_BB0[0] - fn_800D7AE4(object->angZ), sin, 2);
	fn_8019EB94(frame, &object->pos, 2);
}
#pragma opt_common_subs reset

#ifndef SIGNAL_SET_PARAMETER_INLINE
#define SIGNAL_SET_PARAMETER_INLINE inline
#endif

// Takes the placement: the position (also kept as the base the signal bobs
// around), the angles and the kind from the first parameter byte.
extern "C" SIGNAL_SET_PARAMETER_INLINE void signalSetParameter(Signal* object)
{
	u8* params;
	SignalSetData* setdata;

	setdata = object->setdata;
	params  = setdata->params;

	object->pos.x     = setdata->pos.x;
	object->pos.y     = setdata->pos.y;
	object->pos.z     = setdata->pos.z;
	object->basePos.x = object->pos.x;
	object->basePos.y = object->pos.y;
	object->basePos.z = object->pos.z;
	setdata           = object->setdata;
	object->angX      = setdata->angX;
	object->angY      = setdata->angY;
	object->angZ      = setdata->angZ;
	object->kind      = params[0];
}
