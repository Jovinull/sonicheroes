// Starts an immediate-mode 3D primitive over the module's whole vertex buffer (HYPOTHESIS: the
// non-indexed counterpart of fn_801B2A64): notes whether the module is open, runs fn_801B3884,
// then with the module open resets the pending batch with the primitive type, no argument and the
// buffered vertex count (+0x38), picks the type's pipeline and runs it (fn_801B388C). An unknown
// type raises error 0x25 of plugin 1 with the type, a closed module error 0x23. Returns 1 when the
// pipeline ran, otherwise 0. Names are inferred from this function and fn_801B2A64.
#include "game/rw_engine.h"

#define RW_PRIM_TYPE_LINE_LIST 1
#define RW_PRIM_TYPE_POLY_LINE 2
#define RW_PRIM_TYPE_TRI_LIST  3
#define RW_PRIM_TYPE_TRI_STRIP 4
#define RW_PRIM_TYPE_TRI_FAN   5

struct Batch801B2C00 {
	u8 pad0[0x20];
	void* pipeline; // 0x20
	s32 primType;   // 0x24
	s32 arg;        // 0x28
	s32 count;      // 0x2C
};

struct Globals801B2C00 {
	u8 pad0[0x38];
	u16 numVertices; // 0x38
	u8 pad3A[0x3C - 0x3A];
	void* open; // 0x3C: non-null while the module is open
	u8 pad40[0x44 - 0x40];
	Batch801B2C00 batch; // 0x44
};

extern "C" {
extern RwModuleInfo lbl_8042CA74;
// HYPOTHESIS: runs an Im3D pipeline on the batch.
void* fn_801B388C(void* pipeline, Batch801B2C00* batch, s32 flags);
void* fn_801B3884(void);
}

#define IM3D_GLOBALS_801B2C00 ((Globals801B2C00*)((u8*)lbl_8042C9A4 + lbl_8042CA74.globalsOffset))
// Pipelines for the primitive types (+0x4 to +0x14 of the module globals).
#define IM3D_PIPELINE_801B2C00(offset)                                                             \
	(*(void**)((u8*)lbl_8042C9A4 + lbl_8042CA74.globalsOffset + (offset)))

static inline void RecordError801B2C00(s32 code)
{
	RwError error;
	error.pluginID  = 1;
	error.errorCode = fn_8019408C(code);
	fn_80193FE8(&error);
}

static inline void RecordErrorArg801B2C00(s32 code, s32 arg)
{
	RwError error;
	error.pluginID  = 1;
	error.errorCode = fn_8019408C(code, arg);
	fn_80193FE8(&error);
}

extern "C" {
s32 fn_801B2C00(s32 primType)
{
	s32 open = (IM3D_GLOBALS_801B2C00->open != 0);
	fn_801B3884();
	if (open) {
		Batch801B2C00* batch = &IM3D_GLOBALS_801B2C00->batch;
		batch->pipeline      = 0;
		batch->primType      = primType;
		batch->arg           = 0;
		batch->count         = IM3D_GLOBALS_801B2C00->numVertices;
		switch (primType) {
			case RW_PRIM_TYPE_TRI_LIST:
				batch->pipeline = IM3D_PIPELINE_801B2C00(0x4);
				break;
			case RW_PRIM_TYPE_TRI_FAN:
				batch->pipeline = IM3D_PIPELINE_801B2C00(0x8);
				break;
			case RW_PRIM_TYPE_TRI_STRIP:
				batch->pipeline = IM3D_PIPELINE_801B2C00(0xC);
				break;
			case RW_PRIM_TYPE_LINE_LIST:
				batch->pipeline = IM3D_PIPELINE_801B2C00(0x10);
				break;
			case RW_PRIM_TYPE_POLY_LINE:
				batch->pipeline = IM3D_PIPELINE_801B2C00(0x14);
				break;
			default:
				RecordErrorArg801B2C00(0x25, primType);
				break;
		}
		if (fn_801B388C(batch->pipeline, batch, 0) != 0) {
			return 1;
		}
	} else {
		RecordError801B2C00(0x23);
	}
	return 0;
}
}
