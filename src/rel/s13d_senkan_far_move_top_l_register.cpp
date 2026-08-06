#include "types.h"

// The records that register S13D SENKAN FAR MOVE TOP L and S13D SENKAN FAR MOVE TOP R and S13D SENKAN FAR MOVE SIDE L and S13D SENKAN FAR MOVE SIDE R and S13D SENKAN FAR MOVE BIG and S13D SENKAN FAR and S13D SENKAN FAR and S13D SENKAN FAR and S13D SENKAN FAR and S13D SENKAN FAR and S13D SENKAN FAR and S13D SENKAN FAR and S13D SENKAN FAR with the editor.
//
// The claim is .text 0x8F468 to 0x8FC40 and the .ctors word that names it.
// Only the record is taken: the hooks it points at stay assembly and are
// reached by the names each module's symbols.txt gives them.
//
// The object's name is the display string the record itself installs, and each
// hook is named from the entry offset it is stored into.
//
// "ccssSfff" is S13D SENKAN FAR MOVE TOP L's field type string: one character per parameter the
// editor shows, and the array beside it holds their labels.
// "ccssSfff" is S13D SENKAN FAR MOVE TOP R's field type string: one character per parameter the
// editor shows, and the array beside it holds their labels.
// "ccssSfff" is S13D SENKAN FAR MOVE SIDE L's field type string: one character per parameter the
// editor shows, and the array beside it holds their labels.
// "ccssSfff" is S13D SENKAN FAR MOVE SIDE R's field type string: one character per parameter the
// editor shows, and the array beside it holds their labels.
// "ccssSfff" is S13D SENKAN FAR MOVE BIG's field type string: one character per parameter the
// editor shows, and the array beside it holds their labels.
//
// Only stage13D carries this run.

typedef struct ObjectEntry {
	const char* name;        // 0x00
	void (*load)(void);      // 0x04
	void (*unload)(void);    // 0x08
	void (*create)(void);    // 0x0C
	void (*reset)(void);     // 0x10
	u32 flags;               // 0x14
	u32 unk18;               // 0x18
	s16 unk1C;               // 0x1C
	s16 unk1E;               // 0x1E
	u8 unk20;                // 0x20
	u8 unk21;                // 0x21
	u8 pad22[2];             // 0x22
	const char* fieldTypes;  // 0x24
	const char** fieldNames; // 0x28
} ObjectEntry;               // 0x2C

// Defined by each module, renamed to these names in its own symbols.txt.
extern "C" void s13dSenkanFarMoveTopLLoad(void);
extern "C" void s13dSenkanFarMoveTopLUnload(void);
extern "C" void s13dSenkanFarMoveTopLCreate(void);
extern "C" ObjectEntry s13dSenkanFarMoveTopLEntry;
extern "C" char s13dSenkanFarMoveTopLDisplayName[];
extern "C" char s13dSenkanFarMoveTopLFieldTypes[];
extern "C" const char* s13dSenkanFarMoveTopLFieldNames[];

extern "C" void s13dSenkanFarMoveTopRCreate(void);
extern "C" ObjectEntry s13dSenkanFarMoveTopREntry;
extern "C" char s13dSenkanFarMoveTopRDisplayName[];

extern "C" void s13dSenkanFarMoveSideLCreate(void);
extern "C" ObjectEntry s13dSenkanFarMoveSideLEntry;
extern "C" char s13dSenkanFarMoveSideLDisplayName[];

extern "C" void s13dSenkanFarMoveSideRCreate(void);
extern "C" ObjectEntry s13dSenkanFarMoveSideREntry;
extern "C" char s13dSenkanFarMoveSideRDisplayName[];

extern "C" void s13dSenkanFarMoveBigCreate(void);
extern "C" ObjectEntry s13dSenkanFarMoveBigEntry;
extern "C" char s13dSenkanFarMoveBigDisplayName[];

extern "C" void s13dSenkanFar1Create(void);
extern "C" ObjectEntry s13dSenkanFar1Entry;
extern "C" char s13dSenkanFar1DisplayName[];

extern "C" void s13dSenkanFar2Create(void);
extern "C" ObjectEntry s13dSenkanFar2Entry;

extern "C" void s13dSenkanFar3Create(void);
extern "C" ObjectEntry s13dSenkanFar3Entry;

extern "C" void s13dSenkanFar4Create(void);
extern "C" ObjectEntry s13dSenkanFar4Entry;

extern "C" void s13dSenkanFar5Create(void);
extern "C" ObjectEntry s13dSenkanFar5Entry;

extern "C" void s13dSenkanFar6Create(void);
extern "C" ObjectEntry s13dSenkanFar6Entry;

extern "C" void s13dSenkanFar7Create(void);
extern "C" ObjectEntry s13dSenkanFar7Entry;

extern "C" void s13dSenkanFar8Create(void);
extern "C" ObjectEntry s13dSenkanFar8Entry;

extern "C" void s13dSenkanFarMoveTopLRegister(void)
{
	s13dSenkanFarMoveTopLEntry.flags = 0;
	s13dSenkanFarMoveTopLEntry.unk18 = 0;

	s13dSenkanFarMoveTopLEntry.name   = s13dSenkanFarMoveTopLDisplayName;
	s13dSenkanFarMoveTopLEntry.load   = s13dSenkanFarMoveTopLLoad;
	s13dSenkanFarMoveTopLEntry.unload = s13dSenkanFarMoveTopLUnload;
	s13dSenkanFarMoveTopLEntry.create = s13dSenkanFarMoveTopLCreate;
	s13dSenkanFarMoveTopLEntry.reset  = NULL;

	s13dSenkanFarMoveTopLEntry.flags = 0x1000;
	s13dSenkanFarMoveTopLEntry.unk18 = 0;
	s13dSenkanFarMoveTopLEntry.unk20 = 0x1e;
	s13dSenkanFarMoveTopLEntry.unk1C = 0x1395;
	s13dSenkanFarMoveTopLEntry.unk1E = 2;
	s13dSenkanFarMoveTopLEntry.unk21 = 0x0;

	s13dSenkanFarMoveTopLEntry.fieldTypes = s13dSenkanFarMoveTopLFieldTypes;
	s13dSenkanFarMoveTopLEntry.fieldNames = s13dSenkanFarMoveTopLFieldNames;

	if (s13dSenkanFarMoveTopLFieldTypes != NULL) {
		s13dSenkanFarMoveTopLEntry.flags |= 8;
	} else {
		s13dSenkanFarMoveTopLEntry.flags &= ~8;
	}

	s13dSenkanFarMoveTopREntry.flags = 0;
	s13dSenkanFarMoveTopREntry.unk18 = 0;

	s13dSenkanFarMoveTopREntry.name   = s13dSenkanFarMoveTopRDisplayName;
	s13dSenkanFarMoveTopREntry.load   = s13dSenkanFarMoveTopLLoad;
	s13dSenkanFarMoveTopREntry.unload = s13dSenkanFarMoveTopLUnload;
	s13dSenkanFarMoveTopREntry.create = s13dSenkanFarMoveTopRCreate;
	s13dSenkanFarMoveTopREntry.reset  = NULL;

	s13dSenkanFarMoveTopREntry.flags = 0x1000;
	s13dSenkanFarMoveTopREntry.unk18 = 0;
	s13dSenkanFarMoveTopREntry.unk20 = 0x1e;
	s13dSenkanFarMoveTopREntry.unk1C = 0x1396;
	s13dSenkanFarMoveTopREntry.unk1E = 2;
	s13dSenkanFarMoveTopREntry.unk21 = 0x0;

	s13dSenkanFarMoveTopREntry.fieldTypes = s13dSenkanFarMoveTopLFieldTypes;
	s13dSenkanFarMoveTopREntry.fieldNames = s13dSenkanFarMoveTopLFieldNames;

	if (s13dSenkanFarMoveTopLFieldTypes != NULL) {
		s13dSenkanFarMoveTopREntry.flags |= 8;
	} else {
		s13dSenkanFarMoveTopREntry.flags &= ~8;
	}

	s13dSenkanFarMoveSideLEntry.flags = 0;
	s13dSenkanFarMoveSideLEntry.unk18 = 0;

	s13dSenkanFarMoveSideLEntry.name   = s13dSenkanFarMoveSideLDisplayName;
	s13dSenkanFarMoveSideLEntry.load   = s13dSenkanFarMoveTopLLoad;
	s13dSenkanFarMoveSideLEntry.unload = s13dSenkanFarMoveTopLUnload;
	s13dSenkanFarMoveSideLEntry.create = s13dSenkanFarMoveSideLCreate;
	s13dSenkanFarMoveSideLEntry.reset  = NULL;

	s13dSenkanFarMoveSideLEntry.flags = 0x1000;
	s13dSenkanFarMoveSideLEntry.unk18 = 0;
	s13dSenkanFarMoveSideLEntry.unk20 = 0x1e;
	s13dSenkanFarMoveSideLEntry.unk1C = 0x1397;
	s13dSenkanFarMoveSideLEntry.unk1E = 2;
	s13dSenkanFarMoveSideLEntry.unk21 = 0x0;

	s13dSenkanFarMoveSideLEntry.fieldTypes = s13dSenkanFarMoveTopLFieldTypes;
	s13dSenkanFarMoveSideLEntry.fieldNames = s13dSenkanFarMoveTopLFieldNames;

	if (s13dSenkanFarMoveTopLFieldTypes != NULL) {
		s13dSenkanFarMoveSideLEntry.flags |= 8;
	} else {
		s13dSenkanFarMoveSideLEntry.flags &= ~8;
	}

	s13dSenkanFarMoveSideREntry.flags = 0;
	s13dSenkanFarMoveSideREntry.unk18 = 0;

	s13dSenkanFarMoveSideREntry.name   = s13dSenkanFarMoveSideRDisplayName;
	s13dSenkanFarMoveSideREntry.load   = s13dSenkanFarMoveTopLLoad;
	s13dSenkanFarMoveSideREntry.unload = s13dSenkanFarMoveTopLUnload;
	s13dSenkanFarMoveSideREntry.create = s13dSenkanFarMoveSideRCreate;
	s13dSenkanFarMoveSideREntry.reset  = NULL;

	s13dSenkanFarMoveSideREntry.flags = 0x1000;
	s13dSenkanFarMoveSideREntry.unk18 = 0;
	s13dSenkanFarMoveSideREntry.unk20 = 0x1e;
	s13dSenkanFarMoveSideREntry.unk1C = 0x1398;
	s13dSenkanFarMoveSideREntry.unk1E = 2;
	s13dSenkanFarMoveSideREntry.unk21 = 0x0;

	s13dSenkanFarMoveSideREntry.fieldTypes = s13dSenkanFarMoveTopLFieldTypes;
	s13dSenkanFarMoveSideREntry.fieldNames = s13dSenkanFarMoveTopLFieldNames;

	if (s13dSenkanFarMoveTopLFieldTypes != NULL) {
		s13dSenkanFarMoveSideREntry.flags |= 8;
	} else {
		s13dSenkanFarMoveSideREntry.flags &= ~8;
	}

	s13dSenkanFarMoveBigEntry.flags = 0;
	s13dSenkanFarMoveBigEntry.unk18 = 0;

	s13dSenkanFarMoveBigEntry.name   = s13dSenkanFarMoveBigDisplayName;
	s13dSenkanFarMoveBigEntry.load   = s13dSenkanFarMoveTopLLoad;
	s13dSenkanFarMoveBigEntry.unload = s13dSenkanFarMoveTopLUnload;
	s13dSenkanFarMoveBigEntry.create = s13dSenkanFarMoveBigCreate;
	s13dSenkanFarMoveBigEntry.reset  = NULL;

	s13dSenkanFarMoveBigEntry.flags = 0x1000;
	s13dSenkanFarMoveBigEntry.unk18 = 0;
	s13dSenkanFarMoveBigEntry.unk20 = 0x1e;
	s13dSenkanFarMoveBigEntry.unk1C = 0x139b;
	s13dSenkanFarMoveBigEntry.unk1E = 2;
	s13dSenkanFarMoveBigEntry.unk21 = 0x0;

	s13dSenkanFarMoveBigEntry.fieldTypes = s13dSenkanFarMoveTopLFieldTypes;
	s13dSenkanFarMoveBigEntry.fieldNames = s13dSenkanFarMoveTopLFieldNames;

	if (s13dSenkanFarMoveTopLFieldTypes != NULL) {
		s13dSenkanFarMoveBigEntry.flags |= 8;
	} else {
		s13dSenkanFarMoveBigEntry.flags &= ~8;
	}

	s13dSenkanFar1Entry.flags = 0;
	s13dSenkanFar1Entry.unk18 = 0;

	s13dSenkanFar1Entry.name   = s13dSenkanFar1DisplayName;
	s13dSenkanFar1Entry.load   = s13dSenkanFarMoveTopLLoad;
	s13dSenkanFar1Entry.unload = s13dSenkanFarMoveTopLUnload;
	s13dSenkanFar1Entry.create = s13dSenkanFar1Create;
	s13dSenkanFar1Entry.reset  = NULL;

	s13dSenkanFar1Entry.flags = 0x1400;
	s13dSenkanFar1Entry.unk18 = 0;
	s13dSenkanFar1Entry.unk20 = 0x64;
	s13dSenkanFar1Entry.unk1C = 0x1387;
	s13dSenkanFar1Entry.unk1E = 2;
	s13dSenkanFar1Entry.unk21 = 0x0;

	s13dSenkanFar1Entry.fieldTypes = NULL;
	s13dSenkanFar1Entry.fieldNames = NULL;

	if (s13dSenkanFar1Entry.fieldTypes != NULL) {
		s13dSenkanFar1Entry.flags |= 8;
	} else {
		s13dSenkanFar1Entry.flags &= ~8;
	}

	s13dSenkanFar2Entry.flags = 0;
	s13dSenkanFar2Entry.unk18 = 0;

	s13dSenkanFar2Entry.name   = s13dSenkanFar1DisplayName;
	s13dSenkanFar2Entry.load   = s13dSenkanFarMoveTopLLoad;
	s13dSenkanFar2Entry.unload = s13dSenkanFarMoveTopLUnload;
	s13dSenkanFar2Entry.create = s13dSenkanFar2Create;
	s13dSenkanFar2Entry.reset  = NULL;

	s13dSenkanFar2Entry.flags = 0x1400;
	s13dSenkanFar2Entry.unk18 = 0;
	s13dSenkanFar2Entry.unk20 = 0x64;
	s13dSenkanFar2Entry.unk1C = 0x1388;
	s13dSenkanFar2Entry.unk1E = 2;
	s13dSenkanFar2Entry.unk21 = 0x0;

	s13dSenkanFar2Entry.fieldTypes = NULL;
	s13dSenkanFar2Entry.fieldNames = NULL;

	if (s13dSenkanFar2Entry.fieldTypes != NULL) {
		s13dSenkanFar2Entry.flags |= 8;
	} else {
		s13dSenkanFar2Entry.flags &= ~8;
	}

	s13dSenkanFar3Entry.flags = 0;
	s13dSenkanFar3Entry.unk18 = 0;

	s13dSenkanFar3Entry.name   = s13dSenkanFar1DisplayName;
	s13dSenkanFar3Entry.load   = s13dSenkanFarMoveTopLLoad;
	s13dSenkanFar3Entry.unload = s13dSenkanFarMoveTopLUnload;
	s13dSenkanFar3Entry.create = s13dSenkanFar3Create;
	s13dSenkanFar3Entry.reset  = NULL;

	s13dSenkanFar3Entry.flags = 0x1400;
	s13dSenkanFar3Entry.unk18 = 0;
	s13dSenkanFar3Entry.unk20 = 0x64;
	s13dSenkanFar3Entry.unk1C = 0x1389;
	s13dSenkanFar3Entry.unk1E = 2;
	s13dSenkanFar3Entry.unk21 = 0x0;

	s13dSenkanFar3Entry.fieldTypes = NULL;
	s13dSenkanFar3Entry.fieldNames = NULL;

	if (s13dSenkanFar3Entry.fieldTypes != NULL) {
		s13dSenkanFar3Entry.flags |= 8;
	} else {
		s13dSenkanFar3Entry.flags &= ~8;
	}

	s13dSenkanFar4Entry.flags = 0;
	s13dSenkanFar4Entry.unk18 = 0;

	s13dSenkanFar4Entry.name   = s13dSenkanFar1DisplayName;
	s13dSenkanFar4Entry.load   = s13dSenkanFarMoveTopLLoad;
	s13dSenkanFar4Entry.unload = s13dSenkanFarMoveTopLUnload;
	s13dSenkanFar4Entry.create = s13dSenkanFar4Create;
	s13dSenkanFar4Entry.reset  = NULL;

	s13dSenkanFar4Entry.flags = 0x1400;
	s13dSenkanFar4Entry.unk18 = 0;
	s13dSenkanFar4Entry.unk20 = 0x64;
	s13dSenkanFar4Entry.unk1C = 0x138a;
	s13dSenkanFar4Entry.unk1E = 2;
	s13dSenkanFar4Entry.unk21 = 0x0;

	s13dSenkanFar4Entry.fieldTypes = NULL;
	s13dSenkanFar4Entry.fieldNames = NULL;

	if (s13dSenkanFar4Entry.fieldTypes != NULL) {
		s13dSenkanFar4Entry.flags |= 8;
	} else {
		s13dSenkanFar4Entry.flags &= ~8;
	}

	s13dSenkanFar5Entry.flags = 0;
	s13dSenkanFar5Entry.unk18 = 0;

	s13dSenkanFar5Entry.name   = s13dSenkanFar1DisplayName;
	s13dSenkanFar5Entry.load   = s13dSenkanFarMoveTopLLoad;
	s13dSenkanFar5Entry.unload = s13dSenkanFarMoveTopLUnload;
	s13dSenkanFar5Entry.create = s13dSenkanFar5Create;
	s13dSenkanFar5Entry.reset  = NULL;

	s13dSenkanFar5Entry.flags = 0x1400;
	s13dSenkanFar5Entry.unk18 = 0;
	s13dSenkanFar5Entry.unk20 = 0x64;
	s13dSenkanFar5Entry.unk1C = 0x138b;
	s13dSenkanFar5Entry.unk1E = 2;
	s13dSenkanFar5Entry.unk21 = 0x0;

	s13dSenkanFar5Entry.fieldTypes = NULL;
	s13dSenkanFar5Entry.fieldNames = NULL;

	if (s13dSenkanFar5Entry.fieldTypes != NULL) {
		s13dSenkanFar5Entry.flags |= 8;
	} else {
		s13dSenkanFar5Entry.flags &= ~8;
	}

	s13dSenkanFar6Entry.flags = 0;
	s13dSenkanFar6Entry.unk18 = 0;

	s13dSenkanFar6Entry.name   = s13dSenkanFar1DisplayName;
	s13dSenkanFar6Entry.load   = s13dSenkanFarMoveTopLLoad;
	s13dSenkanFar6Entry.unload = s13dSenkanFarMoveTopLUnload;
	s13dSenkanFar6Entry.create = s13dSenkanFar6Create;
	s13dSenkanFar6Entry.reset  = NULL;

	s13dSenkanFar6Entry.flags = 0x1400;
	s13dSenkanFar6Entry.unk18 = 0;
	s13dSenkanFar6Entry.unk20 = 0x64;
	s13dSenkanFar6Entry.unk1C = 0x138c;
	s13dSenkanFar6Entry.unk1E = 2;
	s13dSenkanFar6Entry.unk21 = 0x0;

	s13dSenkanFar6Entry.fieldTypes = NULL;
	s13dSenkanFar6Entry.fieldNames = NULL;

	if (s13dSenkanFar6Entry.fieldTypes != NULL) {
		s13dSenkanFar6Entry.flags |= 8;
	} else {
		s13dSenkanFar6Entry.flags &= ~8;
	}

	s13dSenkanFar7Entry.flags = 0;
	s13dSenkanFar7Entry.unk18 = 0;

	s13dSenkanFar7Entry.name   = s13dSenkanFar1DisplayName;
	s13dSenkanFar7Entry.load   = s13dSenkanFarMoveTopLLoad;
	s13dSenkanFar7Entry.unload = s13dSenkanFarMoveTopLUnload;
	s13dSenkanFar7Entry.create = s13dSenkanFar7Create;
	s13dSenkanFar7Entry.reset  = NULL;

	s13dSenkanFar7Entry.flags = 0x1400;
	s13dSenkanFar7Entry.unk18 = 0;
	s13dSenkanFar7Entry.unk20 = 0x64;
	s13dSenkanFar7Entry.unk1C = 0x138d;
	s13dSenkanFar7Entry.unk1E = 2;
	s13dSenkanFar7Entry.unk21 = 0x0;

	s13dSenkanFar7Entry.fieldTypes = NULL;
	s13dSenkanFar7Entry.fieldNames = NULL;

	if (s13dSenkanFar7Entry.fieldTypes != NULL) {
		s13dSenkanFar7Entry.flags |= 8;
	} else {
		s13dSenkanFar7Entry.flags &= ~8;
	}

	s13dSenkanFar8Entry.flags = 0;
	s13dSenkanFar8Entry.unk18 = 0;

	s13dSenkanFar8Entry.name   = s13dSenkanFar1DisplayName;
	s13dSenkanFar8Entry.load   = s13dSenkanFarMoveTopLLoad;
	s13dSenkanFar8Entry.unload = s13dSenkanFarMoveTopLUnload;
	s13dSenkanFar8Entry.create = s13dSenkanFar8Create;
	s13dSenkanFar8Entry.reset  = NULL;

	s13dSenkanFar8Entry.flags = 0x1400;
	s13dSenkanFar8Entry.unk18 = 0;
	s13dSenkanFar8Entry.unk20 = 0x64;
	s13dSenkanFar8Entry.unk1C = 0x138e;
	s13dSenkanFar8Entry.unk1E = 2;
	s13dSenkanFar8Entry.unk21 = 0x0;

	s13dSenkanFar8Entry.fieldTypes = NULL;
	s13dSenkanFar8Entry.fieldNames = NULL;

	if (s13dSenkanFar8Entry.fieldTypes != NULL) {
		s13dSenkanFar8Entry.flags |= 8;
	} else {
		s13dSenkanFar8Entry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const s13dSenkanFarMoveTopLCtorEntry)(void)
    = s13dSenkanFarMoveTopLRegister;
