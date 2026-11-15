// Starts an immediate-mode 3D primitive (HYPOTHESIS: the GameCube Im3D render-primitive entry):
// with the module open, resets the pending batch, records the primitive type and its two
// arguments, picks the module pipeline for the type (types 1 to 5; line and triangle lists round
// the index count down to whole primitives) and runs it (fn_801B388C). An unknown type raises
// error 0x25 of plugin 1 with the type, a closed module error 0x23. Returns 1 when the pipeline
// ran, otherwise 0. Names are inferred from this function only.
#include "game/rw_engine.h"

#define RW_PRIM_TYPE_LINE_LIST 1
#define RW_PRIM_TYPE_POLY_LINE 2
#define RW_PRIM_TYPE_TRI_LIST  3
#define RW_PRIM_TYPE_TRI_STRIP 4
#define RW_PRIM_TYPE_TRI_FAN   5

struct Batch801B2A64 {
	u8 pad0[0x20];
	void* pipeline; // 0x20
	s32 primType;   // 0x24
	s32 arg;        // 0x28
	s32 count;      // 0x2C
};

struct Globals801B2A64 {
	u8 pad0[0x3C];
	void* open; // 0x3C: non-null while the module is open
	u8 pad40[0x44 - 0x40];
	Batch801B2A64 batch; // 0x44
};

extern "C" {
extern RwModuleInfo lbl_8042CA74;
// HYPOTHESIS: runs an Im3D pipeline on the batch.
void* fn_801B388C(void* pipeline, Batch801B2A64* batch, s32 flags);
}

#define IM3D_GLOBALS_801B2A64 ((Globals801B2A64*)((u8*)lbl_8042C9A4 + lbl_8042CA74.globalsOffset))
// Pipelines for the primitive types (+0x4 to +0x14 of the module globals).
#define IM3D_PIPELINE_801B2A64(offset)                                                             \
	(*(void**)((u8*)lbl_8042C9A4 + lbl_8042CA74.globalsOffset + (offset)))

static inline void RecordError801B2A64(s32 code)
{
	RwError error;
	error.pluginID  = 1;
	error.errorCode = fn_8019408C(code);
	fn_80193FE8(&error);
}

static inline void RecordErrorArg801B2A64(s32 code, s32 arg)
{
	RwError error;
	error.pluginID  = 1;
	error.errorCode = fn_8019408C(code, arg);
	fn_80193FE8(&error);
}

extern "C" {
s32 fn_801B2A64(s32 primType, s32 arg, s32 count)
{
	Globals801B2A64* globals = IM3D_GLOBALS_801B2A64;
	if (globals->open != 0) {
		Batch801B2A64* batch = &globals->batch;
		batch->pipeline      = 0;
		batch->primType      = primType;
		batch->arg           = arg;
		batch->count         = count;
		switch (primType) {
			case RW_PRIM_TYPE_TRI_LIST:
				batch->pipeline = IM3D_PIPELINE_801B2A64(0x4);
				batch->count    = count - count % 3;
				break;
			case RW_PRIM_TYPE_TRI_FAN:
				batch->pipeline = IM3D_PIPELINE_801B2A64(0x8);
				break;
			case RW_PRIM_TYPE_TRI_STRIP:
				batch->pipeline = IM3D_PIPELINE_801B2A64(0xC);
				break;
			case RW_PRIM_TYPE_LINE_LIST:
				batch->pipeline = IM3D_PIPELINE_801B2A64(0x10);
				batch->count    = count - count % 2;
				break;
			case RW_PRIM_TYPE_POLY_LINE:
				batch->pipeline = IM3D_PIPELINE_801B2A64(0x14);
				break;
			default:
				RecordErrorArg801B2A64(0x25, primType);
				break;
		}
		if (fn_801B388C(batch->pipeline, batch, 0) != 0) {
			return 1;
		}
	} else {
		RecordError801B2A64(0x23);
	}
	return 0;
}
}
