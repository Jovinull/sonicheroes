// TObjReel (the PS2 build's class), the reel a player hangs from: its layout
// and the SetParameter and SetPosition that Exec inlines (rel/reel_exec.cpp);
// rel/reel_parameter.cpp and rel/reel_set_position.cpp emit the out-of-line
// copies (REEL_SET_PARAMETER_INLINE and REEL_SET_POSITION_INLINE empty).

#ifndef REEL_INC
#define REEL_INC

typedef struct RwV3d {
	f32 x, y, z;
} RwV3d;

typedef struct sAngle {
	s32 x, y, z;
} sAngle;

struct RwMatrixTag {
	u8 data[0x40];
};

struct RwFrame {
	u8 unk00[0x10];
	RwMatrixTag modelling; // 0x10
};

typedef struct RpClump {
	u8 unk0[0x4];
	RwFrame* frame; // 0x04
} RpClump;

typedef struct ReelParams {
	f32 length; // 0x00
	f32 pitch;  // 0x04, degrees
	f32 launch; // 0x08
	s16 kind;   // 0x0C
} ReelParams;

typedef struct ReelFrame {
	RwV3d pos;          // 0x00
	sAngle ang;         // 0x0C
	u8 unk18[0x14];     // 0x18
	ReelParams* params; // 0x2C
} ReelFrame;

typedef struct Reel {
	u8 unk00[0x4];     // 0x00
	u16 signal;        // 0x04
	u8 unk06[0x22];    // 0x06
	ReelFrame* frame;  // 0x28, the set object's
	u8 unk2C[0x4];     // 0x2C
	u8 colli[0x60];    // 0x30 (C_COLLI)
	RwV3d colliPos;    // 0x90
	sAngle colliAng;   // 0x9C
	u8 unkA8[0x4];     // 0xA8
	RwV3d colliPrePos; // 0xAC
	s32 state;         // 0xB8
	s8 kind;           // 0xBC
	s8 holder;         // 0xBD
	u8 unkBE[0x2];     // 0xBE
	f32 current;       // 0xC0
	f32 target;        // 0xC4
	f32 length;        // 0xC8
	f32 speed;         // 0xCC
	s32 pitch;         // 0xD0
	f32 launch;        // 0xD4
	s8 wait;           // 0xD8
	u8 unkD9[0x3];     // 0xD9
	RwV3d pos;         // 0xDC
	sAngle ang;        // 0xE8
	RpClump* model;    // 0xF4
} Reel;

extern "C" const RwV3d AxisY;
extern "C" const f32 reelZero[1];
extern "C" const f32 reelOne[1];
extern "C" const f32 reelAngleScale[1];
extern "C" const f32 reelHeightScale[1];
extern "C" const f32 reelMinHeight[1];

extern "C" f32 fn_800D7B00(s32 angle);
extern "C" f32 fn_800D7AE4(s32 angle);
extern "C" void fn_80195790(
    RwMatrixTag* matrix, const RwV3d* axis, f32 oneMinusCos, f32 sin, s32 combine);
extern "C" void fn_8019EC30(RwFrame* frame, RwV3d* scale, s32 combine);
extern "C" void fn_8019EB94(RwFrame* frame, RwV3d* translation, s32 combine);
RwFrame* objRwFrameGetChildFrame(RwFrame* frame, RwFrame* after);

#ifndef REEL_SET_PARAMETER_INLINE
#define REEL_SET_PARAMETER_INLINE inline
#endif
#ifndef REEL_SET_POSITION_INLINE
#define REEL_SET_POSITION_INLINE inline
#endif

// SetParameter (the PS2 build's name; reelSetParameter here): the placement's
// position and angle, the reel's length, its kind (kind 0 starts wound in,
// kind 1 let out to its length; both kept as the current and target lengths),
// the launch pitch as an angle and the launch speed.
extern "C" REEL_SET_PARAMETER_INLINE void reelSetParameter(Reel* object)
{
	object->pos        = object->frame->pos;
	object->ang        = object->frame->ang;
	ReelParams* params = object->frame->params;
	object->length     = params->length;
	object->kind       = params->kind;
	switch (object->kind) {
		case 0:
			object->current = reelZero[0];
			break;
		case 1:
			object->current = object->length;
			break;
	}
	object->target = object->current;
	object->pitch  = reelAngleScale[0] * params->pitch;
	object->launch = params->launch;
}

// SetPosition (the PS2 build's name; reelSetPosition here): the reel's frame
// is turned to its heading and moved to its position; the rope (the grandchild
// frame) is stretched to the reel's length (a minimum height when the length
// is zero) and the hook below it moved down by the length, undoing the
// stretch.
extern "C" REEL_SET_POSITION_INLINE void reelSetPosition(Reel* object)
{
	RwFrame* frame = object->model->frame;
	RwV3d scale;
	RwV3d offset;

	fn_80195790(&frame->modelling, &AxisY, reelOne[0] - fn_800D7AE4(object->ang.y),
	    fn_800D7B00(object->ang.y), 0);
	fn_8019EB94(frame, &object->pos, 2);
	frame   = objRwFrameGetChildFrame(objRwFrameGetChildFrame(frame, NULL), NULL);
	scale.x = scale.z = reelOne[0];
	if (reelZero[0] != object->target) {
		scale.y = reelHeightScale[0] * object->target;
	} else {
		scale.y = reelMinHeight[0];
	}
	fn_8019EC30(frame, &scale, 0);
	frame    = objRwFrameGetChildFrame(frame, NULL);
	offset.x = offset.z = reelZero[0];
	offset.y            = -object->target;
	fn_8019EB94(frame, &offset, 0);
	scale.y = reelOne[0] / scale.y;
	fn_8019EC30(frame, &scale, 2);
}

#endif
