// Creates the game's custom render pipelines (HYPOTHESIS): saves the default atomic pipeline
// (fn_8015C798) and configures it (fn_8015C704 with 4, 1), then builds an atomic pipeline and a
// world-sector pipeline, each a single all-in-one GameCube node (fn_8015D4B8 / fn_8015D898) tagged
// with plugin 0x120. The original node callbacks are kept in lbl_8042C840/lbl_8042C844 and
// lbl_8042C83C and replaced by the game's (fn_801427C4, fn_801428A0, fn_80142988, fn_80142A0C).
// The pipelines go to lbl_8042C834 and lbl_8042C838 (null on failure). Returns 1.
#include "types.h"

#define PLUGIN_ID_80142C20 0x120

struct RxPipeline80142C20 {
	u8 pad0[0x2C];
	u32 pluginId; // 0x2C
};

struct RxNodeDefinition80142C20 {
	const char* name; // 0x0
};

extern "C" {
extern void* lbl_8042C830;
extern RxPipeline80142C20* lbl_8042C834;
extern RxPipeline80142C20* lbl_8042C838;
extern void* lbl_8042C83C;
extern void* lbl_8042C840;
extern void* lbl_8042C844;

void* fn_8015C798(void);
void fn_8015C704(void* pipeline, s32 a, s32 b);
// HYPOTHESIS: RxPipelineCreate, RxPipelineLock, RxLockedPipeAddFragment, RxLockedPipeUnlock,
// RxPipelineFindNodeByName and RxPipelineDestroy.
RxPipeline80142C20* fn_801B3984(void);
void* fn_801B4EB4(RxPipeline80142C20* pipeline);
void* fn_801B52BC(void* lockedPipe, u32* firstIndex, RxNodeDefinition80142C20* nodeDef, ...);
void* fn_801B43EC(void* lockedPipe);
void* fn_801B51B8(RxPipeline80142C20* pipeline, const char* name, void* start, s32* index);
void fn_801B3A10(RxPipeline80142C20* pipeline);
// HYPOTHESIS: the GameCube all-in-one node definitions and their callback accessors.
RxNodeDefinition80142C20* fn_8015D4B8(void);
RxNodeDefinition80142C20* fn_8015D898(void);
void* fn_8015C364(void* node);
void* fn_8015C37C(void* node);
void fn_8015C358(void* node, void* callback);
void fn_8015C370(void* node, void* callback);
void fn_8015C388(void* node, void* callback);
void fn_801427C4(void);
void fn_801428A0(void);
void fn_80142988(void);
void fn_80142A0C(void);
}

static inline RxPipeline80142C20* CreateAtomicPipeline80142C20(void)
{
	RxPipeline80142C20* pipeline = fn_801B3984();
	if (pipeline != 0) {
		void* lockedPipe;
		pipeline->pluginId = PLUGIN_ID_80142C20;
		lockedPipe         = fn_801B4EB4(pipeline);
		if (lockedPipe != 0) {
			RxNodeDefinition80142C20* nodeDef = fn_8015D4B8();
			void* node;
			fn_801B43EC(fn_801B52BC(lockedPipe, 0, nodeDef, 0));
			node         = fn_801B51B8(pipeline, nodeDef->name, 0, 0);
			lbl_8042C844 = fn_8015C364(node);
			lbl_8042C840 = fn_8015C37C(node);
			fn_8015C358(node, (void*)fn_801427C4);
			fn_8015C370(node, (void*)fn_801428A0);
			fn_8015C388(node, (void*)fn_80142A0C);
			return pipeline;
		}
		fn_801B3A10(pipeline);
	}
	return 0;
}

static inline RxPipeline80142C20* CreateSectorPipeline80142C20(void)
{
	RxPipeline80142C20* pipeline = fn_801B3984();
	if (pipeline != 0) {
		void* lockedPipe;
		pipeline->pluginId = PLUGIN_ID_80142C20;
		lockedPipe         = fn_801B4EB4(pipeline);
		if (lockedPipe != 0) {
			RxNodeDefinition80142C20* nodeDef = fn_8015D898();
			void* node;
			fn_801B43EC(fn_801B52BC(lockedPipe, 0, nodeDef, 0));
			node         = fn_801B51B8(pipeline, nodeDef->name, 0, 0);
			lbl_8042C83C = fn_8015C364(node);
			fn_8015C358(node, (void*)fn_80142988);
			fn_8015C388(node, (void*)fn_80142A0C);
			return pipeline;
		}
		fn_801B3A10(pipeline);
	}
	return 0;
}

extern "C" {
s32 fn_80142C20(void)
{
	lbl_8042C830 = fn_8015C798();
	fn_8015C704(lbl_8042C830, 4, 1);
	lbl_8042C834 = CreateAtomicPipeline80142C20();
	lbl_8042C838 = CreateSectorPipeline80142C20();
	return 1;
}
}
