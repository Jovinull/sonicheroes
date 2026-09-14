#include "MSL_C/stdio.h"
#include "MSL_C/string.h"
#include "cri/svm.h"

#ifdef __cplusplus
extern "C" {
#endif

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
/* Retained read-only word following the diagnostic strings. */
extern const u32 lbl_80240164 = 0x20000000;

volatile s32 svm_init_level;
volatile s32 svm_lock_level;
volatile s32 svm_locking_type;
/* Owned storage has no references in the surviving GameCube functions. */
s32 lbl_80427CBC[8];
s32 (*svm_tas_fptr)(s32* value);
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

static inline void svm_report(const char* message)
{
	strncpy(lbl_80427CE0, message, 0x7F);
	if (SVM_ERROR.function != NULL) {
		SVM_ERROR.function(SVM_ERROR.object, lbl_80427CE0);
	}
}

static inline void svm_lock(s32 type)
{
	if (SVM_LOCK.function != NULL) {
		SVM_LOCK.function(SVM_LOCK.object);
		if (svm_lock_level == 0) {
			svm_locking_type = type;
		}
		svm_lock_level++;
	}
}

static inline void svm_unlock(s32 type)
{
	if (SVM_UNLOCK.function != NULL) {
		svm_lock_level--;
		if (svm_lock_level == 0) {
			if (svm_locking_type != type) {
				fn_80222464(lbl_8023FFF4, svm_locking_type, type);
			}
			svm_locking_type = 0;
		}
		SVM_UNLOCK.function(SVM_UNLOCK.object);
	}
}

u32 fn_802218A8(s32* value)
{
	s32 previous;
	u32 result;

	if (svm_tas_fptr != NULL) {
		result = svm_tas_fptr(value);
	} else {
		svm_lock(1);
		previous = *value;
		*value   = 1;
		result   = (u32)((1 - previous) | (previous - 1)) >> 31;
		svm_unlock(1);
	}
	return result;
}

static inline void svm_reset_variable(void)
{
	s32* counts;
	s32 i;
	memset(SVM_ACTIVE, 0, sizeof(SVM_ACTIVE));
	memset(&SVM_LOCK, 0, sizeof(SVM_LOCK));
	memset(&SVM_UNLOCK, 0, sizeof(SVM_UNLOCK));
	counts = SVM_COUNTS;
	for (i = 0; i < 6; i++) {
		counts[i] = 0;
	}
	svm_tas_fptr = NULL;
}

void fn_802219BC(void)
{
	svm_init_level--;
	if (svm_init_level == 0) {
		svm_reset_variable();
		memset(&SVM_ERROR, 0, sizeof(SVM_ERROR));
	}
}

void fn_80221A64(void)
{
	if (svm_init_level == 0) {
		svm_reset_variable();
	}
	svm_init_level++;
}

static inline s32 svm_exec_server(s32 type)
{
	s32* active;
	SvmCallback* callback;
	s32 i;
	s32 result;
	s32* counts;
	s32 one;
	s32 zero;
	SvmServerFunc function;

	result   = 0;
	one      = 1;
	callback = &lbl_80427DB8[0][0];
	active   = lbl_80427F38;
	i        = result;
	zero     = result;
	callback += type * 6;
	do {
		function = callback->function;
		if (function != NULL) {
			active[type] = one;
			result |= function(callback->object);
			active[type] = zero;
		}
		i++;
		callback++;
	} while (i < 6);
	counts = SVM_COUNTS;
	counts[type]++;
	return result;
}

s32 fn_80221AFC(void)
{
	return svm_exec_server(6);
}

s32 fn_80221B8C(void)
{
	return svm_exec_server(5);
}

s32 fn_80221C1C(void)
{
	return svm_exec_server(4);
}

s32 fn_80221CAC(void)
{
	return svm_exec_server(2);
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
	svm_lock(1);
	lbl_80427D60.function = function;
	lbl_80427D60.object   = object;
	svm_unlock(1);
}

void fn_80221E4C(s32 id)
{
	if (lbl_80427D78[id].function != NULL) {
		lbl_80427D78[id].function(lbl_80427D78[id].object);
	}
}

void fn_80221E90(s32 id, SvmServerFunc function, void* object)
{
	svm_lock(1);
	lbl_80427D78[id].function = function;
	lbl_80427D78[id].object   = object;
	svm_unlock(1);
}

void fn_80221F94(s32 type, s32 id, SvmServerFunc function, void* object)
{
	SvmCallback* callback;

	if (id < 0 || id >= 6) {
		svm_report(lbl_80240090);
	}
	/* The original upper-bound check uses id, rather than type. */
	if (type < 0 || id >= 8) {
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
	SvmCallback* callback;
	s32 id;

	svm_lock(1);
	callback = &SVM_SERVER[type][0];
	for (id = 0; id < 6; callback++, id++) {
		if (callback->function == NULL) {
			callback->function = function;
			callback->object   = object;
			break;
		}
	}
	if (id == 6) {
		svm_report(lbl_80240134);
	}
	svm_unlock(1);
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
	__va_list arguments;

	memset(lbl_80427CE0, 0, sizeof(lbl_80427CE0));
	__builtin_va_info(arguments);
	vsprintf(lbl_80427CE0, format, arguments);
	if (lbl_80427D60.function != NULL) {
		lbl_80427D60.function(lbl_80427D60.object, lbl_80427CE0);
	}
}

void fn_8022253C(void)
{
	svm_unlock(5);
}

void fn_802225CC(void)
{
	svm_unlock(4);
}

void fn_8022265C(void)
{
	svm_unlock(3);
}

void fn_802226EC(void)
{
	svm_unlock(2);
}

void fn_8022277C(void)
{
	svm_lock(5);
}

void fn_802227E4(void)
{
	svm_lock(4);
}

void fn_8022284C(void)
{
	svm_lock(3);
}

void fn_802228B4(void)
{
	svm_lock(2);
}

void fn_8022291C(void)
{
	svm_unlock(1);
}

void fn_802229AC(void)
{
	svm_lock(1);
}

#ifdef __cplusplus
}
#endif
