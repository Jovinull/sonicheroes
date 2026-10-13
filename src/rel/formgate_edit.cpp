#include "types.h"

// TObjFormGate::EditOnChange (the PS2 build's name): it keeps the edited kind
// between 0 and 2 and the width within its limits.
//
// The limits are pooled constants of the TU (named externs here). Read through
// a pointer taken inside the comparison, they load after the width and land in
// f0 with the width in f1, as the retail's literals do.

#include "src/rel/formgate_class.inc"

extern "C" const f32 formgateMinWidth[1];
extern "C" const f32 formgateMaxWidth[1];

void TObjFormGate::EditOnChange(SETDATA_PARAM* param)
{
	FormGateParams* params = (FormGateParams*)param->setBuffer;

	if (params->kind < 0) {
		params->kind = 0;
	}
	if (params->kind >= 3) {
		params->kind = 2;
	}
	const f32* limit;
	if (params->width < *(limit = formgateMinWidth)) {
		params->width = *limit;
	}
	if (params->width > *(limit = formgateMaxWidth)) {
		params->width = *limit;
	}
}
