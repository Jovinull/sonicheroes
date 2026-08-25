#include "types.h"

#pragma inline_depth(10)
#pragma inline_max_size(10000)

typedef struct {
	char gpr;
	char fpr;
	char reserved[2];
	char* inputArgArea;
	char* regSaveArea;
} SvmVaList[1];

typedef s32 (*SvmServerFunc)(void* object);
typedef void (*SvmLockFunc)(void* object);
typedef void (*SvmErrorFunc)(void* object, const char* message);

typedef struct SvmCallback {
	SvmServerFunc function;
	void* object;
} SvmCallback;

typedef struct SvmErrorCallback {
	SvmErrorFunc function;
	void* object;
} SvmErrorCallback;

typedef struct SvmLockCallback {
	SvmLockFunc function;
	void* object;
} SvmLockCallback;

typedef struct SvmState {
	volatile s32 initCount;
	volatile s32 lockDepth;
	volatile s32 lockType;
	u8 reserved0C[0x20];
	s32 (*testAndSet)(s32* value);
} SvmState;

typedef struct SvmTables {
	SvmCallback direct[8];
	SvmCallback server[8][6];
	s32 active[8];
	s32 counts[8];
} SvmTables;

typedef struct SvmFullState {
	SvmState core;
	char message[0x80];
	SvmErrorCallback error;
	SvmLockCallback unlock;
	SvmLockCallback lock;
	SvmCallback direct[8];
	SvmCallback server[8][6];
	s32 active[8];
	s32 counts[8];
} SvmFullState;

void* memset(void* destination, s32 value, u32 size);
char* strncpy(char* destination, const char* source, u32 size);
void __builtin_va_info(void* arguments);
int vsprintf(char* destination, const char* format, SvmVaList arguments);

void fn_80222464(const char* format, ...);

static const char lbl_8023FFC0[]      = "\nSVM/GC Ver.1.51 Build:May  9 2003 17:10:11\n";
static const char* const lbl_8023FFF0 = lbl_8023FFC0;
static const char lbl_8023FFF4[]
    = "2103102:SVM:svm_unlock:lock type miss match.(type org=%d, type now=%d)";
const char lbl_8024003C[]        = "1071301:SVM_ExecSvrFuncId:illegal id";
const char lbl_80240064[]        = "1071302:SVM_ExecSvrFuncId:illegal svtype";
const char lbl_80240090[]        = "1071201:SVM_SetCbSvrId:illegal id";
const char lbl_802400B4[]        = "1071202:SVM_SetCbSvrId:illegal svtype";
static const char lbl_802400DC[] = "2100801:SVM_SetCbSvrId:over write callback function.";
static const char lbl_80240114[] = "1051002:SVM_DelCbSvr:illegal id";
static const char lbl_80240134[] = "1051001:SVM_SetCbSvr:too many server function";
const u32 gap_06_80240164_rodata = 0x20000000;

static SvmState lbl_80427CB0;
char lbl_80427CE0[0x80];
SvmErrorCallback lbl_80427D60;
SvmLockCallback lbl_80427D68;
SvmLockCallback lbl_80427D70;
SvmCallback lbl_80427D78[8];
SvmCallback lbl_80427DB8[8][6];
s32 lbl_80427F38[8];
s32 lbl_80427F58[8];

#define SVM_ERROR  lbl_80427D60
#define SVM_UNLOCK lbl_80427D68
#define SVM_LOCK   lbl_80427D70
#define SVM_SERVER lbl_80427DB8
#define SVM_ACTIVE lbl_80427F38
#define SVM_COUNTS lbl_80427F58

static s32 svm_touch(void)
{
	return lbl_80427F38[0] + lbl_80427F58[0] + (lbl_80427DB8[0][0].function != NULL)
	    + (lbl_80427D78[0].function != NULL) + (lbl_80427D70.function != NULL)
	    + (lbl_80427D68.function != NULL) + (lbl_80427D60.function != NULL) + lbl_80427CE0[0]
	    + lbl_80427CB0.initCount;
}

static inline void svm_report(const char* message)
{
	strncpy(lbl_80427CE0, message, 0x7F);
	if (SVM_ERROR.function != NULL) {
		SVM_ERROR.function(SVM_ERROR.object, lbl_80427CE0);
	}
}

static inline void svm_report_overlay(SvmFullState* state, const char* message)
{
	strncpy(state->message, message, 0x7F);
	if (state->error.function != NULL) {
		state->error.function(state->error.object, state->message);
	}
}

static inline void svm_lock(s32 type)
{
	SvmState* state = &lbl_80427CB0;
	if (SVM_LOCK.function != NULL) {
		SVM_LOCK.function(SVM_LOCK.object);
		if (state->lockDepth == 0) {
			state->lockType = type;
		}
		state->lockDepth++;
	}
}

static inline void svm_unlock(s32 type)
{
	SvmState* state = &lbl_80427CB0;
	if (SVM_UNLOCK.function != NULL) {
		state->lockDepth--;
		if (state->lockDepth == 0) {
			if (state->lockType != type) {
				fn_80222464(lbl_8023FFF4, state->lockType, type);
			}
			state->lockType = 0;
		}
		SVM_UNLOCK.function(SVM_UNLOCK.object);
	}
}

static inline void svm_lock_overlay(SvmFullState* state, s32 type)
{
	if (state->lock.function != NULL) {
		state->lock.function(state->lock.object);
		if (state->core.lockDepth == 0) {
			state->core.lockType = type;
		}
		state->core.lockDepth++;
	}
}

static inline void svm_unlock_overlay(SvmFullState* state, s32 type)
{
	if (state->unlock.function != NULL) {
		state->core.lockDepth--;
		if (state->core.lockDepth == 0) {
			if (state->core.lockType != type) {
				fn_80222464(lbl_8023FFF4, state->core.lockType, type);
			}
			state->core.lockType = 0;
		}
		state->unlock.function(state->unlock.object);
	}
}

static inline void svm_lock_global(s32 type)
{
	SvmFullState* state = (SvmFullState*)&lbl_80427CB0;
	if (state->lock.function != NULL) {
		state->lock.function(state->lock.object);
		if (state->core.lockDepth == 0) {
			state->core.lockType = type;
		}
		state->core.lockDepth++;
	}
}

static inline void svm_unlock_global(s32 type)
{
	SvmFullState* state = (SvmFullState*)&lbl_80427CB0;
	if (state->unlock.function != NULL) {
		state->core.lockDepth--;
		if (state->core.lockDepth == 0) {
			if (state->core.lockType != type) {
				fn_80222464(lbl_8023FFF4, state->core.lockType, type);
			}
			state->core.lockType = 0;
		}
		state->unlock.function(state->unlock.object);
	}
}

u32 fn_802218A8(s32* value)
{
	SvmState* state         = &lbl_80427CB0;
	SvmFullState* fullState = (SvmFullState*)state;
	s32 previous;
	u32 result;

	if (lbl_80427CB0.testAndSet != NULL) {
		return lbl_80427CB0.testAndSet(value);
	}
	svm_lock_overlay(fullState, 1);
	previous = *value;
	*value   = 1;
	result   = (u32)((1 - previous) | (previous - 1)) >> 31;
	svm_unlock_overlay(fullState, 1);
	return result;
}

void fn_802219BC(void)
{
	SvmState* state         = &lbl_80427CB0;
	SvmFullState* fullState = (SvmFullState*)state;
	s32* counts;
	state->initCount--;
	if (state->initCount == 0) {
		memset(fullState->active, 0, sizeof(fullState->active));
		memset(&fullState->lock, 0, sizeof(fullState->lock));
		memset(&fullState->unlock, 0, sizeof(fullState->unlock));
		counts            = (s32*)((char*)state + 0x2A8);
		counts[0]         = 0;
		counts[1]         = 0;
		counts[2]         = 0;
		counts[3]         = 0;
		counts[4]         = 0;
		counts[5]         = 0;
		state->testAndSet = NULL;
		memset(&fullState->error, 0, sizeof(fullState->error));
	}
}

void fn_80221A64(void)
{
	SvmState* state         = &lbl_80427CB0;
	SvmFullState* fullState = (SvmFullState*)state;
	s32* counts;
	if (state->initCount == 0) {
		memset(fullState->active, 0, sizeof(fullState->active));
		memset(&fullState->lock, 0, sizeof(fullState->lock));
		memset(&fullState->unlock, 0, sizeof(fullState->unlock));
		counts            = (s32*)((char*)state + 0x2A8);
		counts[0]         = 0;
		counts[1]         = 0;
		counts[2]         = 0;
		counts[3]         = 0;
		counts[4]         = 0;
		counts[5]         = 0;
		state->testAndSet = NULL;
	}
	state->initCount++;
}

s32 fn_80221AFC(void)
{
	SvmState* state;
	s32 result;
	s32 i;
	SvmCallback* callback;
	s32* active;
	s32* counts;
	s32 one;
	s32 zero;
	SvmServerFunc function;

	state    = &lbl_80427CB0;
	result   = 0;
	one      = 1;
	callback = &lbl_80427DB8[0][0];
	active   = lbl_80427F38;
	i        = result;
	zero     = result;
	callback += 6 * 6;
	do {
		function = callback->function;
		if (function != NULL) {
			active[6] = one;
			result |= function(callback->object);
			active[6] = zero;
		}
		i++;
		callback++;
	} while (i < 6);
	counts = SVM_COUNTS;
	counts[6]++;
	return result;
}

s32 fn_80221B8C(void)
{
	SvmServerFunc function;
	s32 result;
	s32 i;
	SvmCallback* callback;
	s32* active;
	s32* counts;
	s32 one;
	s32 zero;
	result   = 0;
	one      = 1;
	callback = &SVM_SERVER[0][0];
	active   = SVM_ACTIVE;
	i        = result;
	zero     = result;
	callback += 5 * 6;
	do {
		function = callback->function;
		if (function != NULL) {
			active[5] = one;
			result |= function(callback->object);
			active[5] = zero;
		}
		i++;
		callback++;
	} while (i < 6);
	counts = SVM_COUNTS;
	counts[5]++;
	return result;
}

s32 fn_80221C1C(void)
{
	SvmServerFunc function;
	s32 result;
	s32 i;
	SvmCallback* callback;
	s32* active;
	s32* counts;
	s32 one;
	s32 zero;
	result   = 0;
	one      = 1;
	callback = &SVM_SERVER[0][0];
	active   = SVM_ACTIVE;
	i        = result;
	zero     = result;
	callback += 4 * 6;
	do {
		function = callback->function;
		if (function != NULL) {
			active[4] = one;
			result |= function(callback->object);
			active[4] = zero;
		}
		i++;
		callback++;
	} while (i < 6);
	counts = SVM_COUNTS;
	counts[4]++;
	return result;
}

s32 fn_80221CAC(void)
{
	SvmServerFunc function;
	s32 result;
	s32 i;
	SvmCallback* callback;
	s32* active;
	s32* counts;
	s32 one;
	s32 zero;
	result   = 0;
	one      = 1;
	callback = &SVM_SERVER[0][0];
	active   = SVM_ACTIVE;
	i        = result;
	zero     = result;
	callback += 2 * 6;
	do {
		function = callback->function;
		if (function != NULL) {
			active[2] = one;
			result |= function(callback->object);
			active[2] = zero;
		}
		i++;
		callback++;
	} while (i < 6);
	counts = SVM_COUNTS;
	counts[2]++;
	return result;
}

void fn_80221D3C(SvmLockFunc function, void* object)
{
	lbl_80427D68.function = function;
	lbl_80427D68.object   = object;
}

void fn_80221D4C(SvmLockFunc function, void* object)
{
	lbl_80427D70.function = function;
	lbl_80427D70.object   = object;
}

void fn_80221D5C(SvmErrorFunc function, void* object)
{
	SvmState* state         = &lbl_80427CB0;
	SvmFullState* fullState = (SvmFullState*)state;
	svm_lock_overlay(fullState, 1);
	lbl_80427D60.function = function;
	lbl_80427D60.object   = object;
	svm_unlock_overlay(fullState, 1);
}

void fn_80221E4C(s32 id)
{
	if (lbl_80427D78[id].function != NULL) {
		lbl_80427D78[id].function(lbl_80427D78[id].object);
	}
}

void fn_80221E90(s32 id, SvmServerFunc function, void* object)
{
	SvmState* state         = &lbl_80427CB0;
	SvmFullState* fullState = (SvmFullState*)state;
	svm_lock_overlay(fullState, 1);
	lbl_80427D78[id].function = function;
	lbl_80427D78[id].object   = object;
	svm_unlock_overlay(fullState, 1);
}

void fn_80221F94(s32 type, s32 id, SvmServerFunc function, void* object)
{
	SvmCallback* callback;

	if (id < 0 || id >= 6) {
		svm_report(lbl_80240090);
	}
	if (type < 0 || type >= 8) {
		svm_report(lbl_802400B4);
	}
	svm_lock(1);
	callback = &SVM_SERVER[type][id];
	if (callback->function != NULL) {
		svm_report(lbl_802400DC);
	}
	callback->function = function;
	callback->object   = object;
	svm_unlock(1);
}

void fn_80222148(s32 type, s32 id)
{
	if (id < 0 || id >= 6) {
		svm_report(lbl_80240114);
	}
	svm_lock(1);
	SVM_SERVER[type][id].function = NULL;
	SVM_SERVER[type][id].object   = NULL;
	svm_unlock(1);
}

s32 fn_80222290(s32 type, SvmServerFunc function, void* object)
{
	SvmState* state         = &lbl_80427CB0;
	SvmFullState* fullState = (SvmFullState*)state;
	SvmCallback* callback;
	s32 id;

	svm_lock_overlay(fullState, 1);
	callback = &fullState->server[type][0];
	for (id = 0; id < 6; id++, callback++) {
		if (callback->function == NULL) {
			callback->function = function;
			callback->object   = object;
			break;
		}
	}
	if (id == 6) {
		svm_report_overlay(fullState, lbl_80240134);
	}
	svm_unlock_overlay(fullState, 1);
	if (id == 6) {
		return -1;
	}
	return id;
}

void fn_8022240C(const char* message)
{
	strncpy(lbl_80427CE0, message, 0x7F);
	if (lbl_80427D60.function != NULL) {
		lbl_80427D60.function(lbl_80427D60.object, lbl_80427CE0);
	}
}

void fn_80222464(const char* format, ...)
{
	SvmVaList arguments;

	memset(lbl_80427CE0, 0, sizeof(lbl_80427CE0));
	__builtin_va_info(arguments);
	vsprintf(lbl_80427CE0, format, arguments);
	if (lbl_80427D60.function != NULL) {
		lbl_80427D60.function(lbl_80427D60.object, lbl_80427CE0);
	}
}

void fn_8022253C(void)
{
	svm_unlock_global(5);
}

void fn_802225CC(void)
{
	svm_unlock_global(4);
}

void fn_8022265C(void)
{
	svm_unlock_global(3);
}

void fn_802226EC(void)
{
	svm_unlock_global(2);
}

void fn_8022277C(void)
{
	svm_lock_global(5);
}

void fn_802227E4(void)
{
	svm_lock_global(4);
}

void fn_8022284C(void)
{
	svm_lock_global(3);
}

void fn_802228B4(void)
{
	svm_lock_global(2);
}

void fn_8022291C(void)
{
	svm_unlock_global(1);
}

void fn_802229AC(void)
{
	svm_lock_global(1);
}
