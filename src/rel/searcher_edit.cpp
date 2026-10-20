#include "types.h"

// TObjEnemySearcher::EditOnChange (the PS2 build's name): holds each edited
// parameter between its limits through the nVariable::Limit template (which
// returns a reference to the value or to the limit it crossed) and names the
// editor's fields for the values that pick them. The fields are named by their
// offsets; some upper limits are literal constants in the original (bound to
// the template's references), named here.

namespace nVariable
{

template <class T> inline const T& Limit(const T& value, const T& min, const T& max)
{
	if (value < min) {
		return min;
	}
	if (value > max) {
		return max;
	}
	return value;
}

} // namespace nVariable

typedef struct SearcherParams {
	s8 f00;  // 0x00
	s8 f01;  // 0x01
	s8 f02;  // 0x02
	s8 f03;  // 0x03
	s16 f04; // 0x04
	u8 pad06[0x2];
	s16 f08; // 0x08
	s16 f0A; // 0x0A
	u8 pad0C[0x4];
	f32 f10; // 0x10
	f32 f14; // 0x14
	f32 f18; // 0x18
	s16 f1C; // 0x1C
	s16 f1E; // 0x1E
} SearcherParams;

typedef struct SearcherEdit {
	u8 unk00[0x2C];
	SearcherParams* params; // 0x2C
} SearcherEdit;

extern "C" s8 searcherMin00, searcherMax00, searcherMin01, searcherMax01;
extern "C" s8 searcherMin02, searcherMax02, searcherMin03, searcherMax03;
extern "C" s16 searcherMin04, searcherMin08, searcherMin0A;
extern "C" const s16 searcherMax04, searcherMax08, searcherMax0A;
extern "C" const f32 searcherMin14, searcherMax14;
extern "C" f32 searcherMin10, searcherMin18;
extern "C" const f32 searcherMax10, searcherMax18;
extern "C" s16 searcherMin1C, searcherMax1C, searcherMin1E, searcherMax1E;

extern "C" const char* searcherObjectFieldNames[];
extern "C" const char* searcherFields0[];
extern "C" const char* searcherFields1[];
extern "C" const char* searcherFields2[];
extern "C" const char* searcherFields3[];
extern "C" const char* searcherFields8[];

extern "C" void EditOnChange__17TObjEnemySearcherFP13SETDATA_PARAM(void* object, SearcherEdit* edit)
{
	SearcherParams* params = edit->params;

	params->f00                 = nVariable::Limit(params->f00, searcherMin00, searcherMax00);
	params->f01                 = nVariable::Limit(params->f01, searcherMin01, searcherMax01);
	params->f02                 = nVariable::Limit(params->f02, searcherMin02, searcherMax02);
	params->f03                 = nVariable::Limit(params->f03, searcherMin03, searcherMax03);
	params->f04                 = nVariable::Limit(params->f04, searcherMin04, searcherMax04);
	params->f08                 = nVariable::Limit(params->f08, searcherMin08, searcherMax08);
	params->f0A                 = nVariable::Limit(params->f0A, searcherMin0A, searcherMax0A);
	params->f14                 = nVariable::Limit(params->f14, searcherMin14, searcherMax14);
	params->f10                 = nVariable::Limit(params->f10, searcherMin10, searcherMax10);
	params->f18                 = nVariable::Limit(params->f18, searcherMin18, searcherMax18);
	params->f1C                 = nVariable::Limit(params->f1C, searcherMin1C, searcherMax1C);
	params->f1E                 = nVariable::Limit(params->f1E, searcherMin1E, searcherMax1E);
	searcherObjectFieldNames[0] = searcherFields0[params->f00];
	searcherObjectFieldNames[1] = searcherFields1[params->f01];
	searcherObjectFieldNames[2] = searcherFields2[params->f02];
	searcherObjectFieldNames[3] = searcherFields3[params->f03];
	searcherObjectFieldNames[8] = searcherFields8[params->f01];
}
