#include "Runtime.PPCEABI.H/__va_arg.h"
#include "types.h"

// Shared CRI error-reporting plumbing between GCCI and LSC. The exact unit is
// the four-function run from 0x8021F410 through 0x8021F544 and its private BSS
// from 0x80420770 through 0x80420878. Both adjacent CRI translation units are
// already established, leaving this complete range between them.
// MATCHING: all four functions and the complete BSS block are byte-exact.

typedef void (*CriErrorCallback)(void* object, char* message);

typedef struct {
	void* object;
	char message[0x100];
} CriErrorState;

typedef struct {
	CriErrorCallback callback;
	void* object;
	char message[0x100];
} CriErrorBlock;

static CriErrorCallback lbl_80420770;
static CriErrorState lbl_80420774;

s32 vsprintf(char* s, const char* format, __va_list args);
void fn_80220544(void);
void fn_80220590(void);

void fn_8021F410(const char* format, ...)
{
	__va_list args;
	CriErrorBlock* state = (CriErrorBlock*)&lbl_80420770;
	CriErrorCallback callback;

	__builtin_va_info(args);
	vsprintf(state->message, format, args);
	callback = state->callback;

	if (callback != NULL) {
		callback(state->object, state->message);
	}
}

void fn_8021F4D0(CriErrorCallback callback, void* object)
{
	if (callback == NULL) {
		lbl_80420770        = NULL;
		lbl_80420774.object = NULL;
	} else {
		lbl_80420770        = callback;
		lbl_80420774.object = object;
	}
}

void fn_8021F504(void)
{
	fn_80220544();
}

void fn_8021F524(void)
{
	fn_80220590();
}
