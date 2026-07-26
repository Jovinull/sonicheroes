#include "types.h"

// Answers whether a slot is available and fills the panel's text fields from
// the save state.
//
// NonMatching. fn_1_92D0 reproduces exactly; fn_1_945C is the right length
// with the right instructions in the right order, and 79 of its 322
// instructions still differ, almost all of them only in which register the
// allocator picked. The one real difference is that the two branches building
// a row pointer from an offset take four instructions here and three in the
// original, which reassociates the sum so the base is added last.
//
// Measured against it without moving those: declaration order of the locals in
// three arrangements, opt_propagation off, writing the offset accumulation
// into its own variable, and swapping which of the two counters seeds the
// other.
//
// The translation unit runs from fn_1_92D0 at 0x92D0 to the end of fn_1_945C
// at 0x9954. The two tables it reads sit in .rodata at 0xC28, 0xC80 and 0xED0,
// and the text templates in .data; both are left to the module and only
// referenced here, so this unit emits neither.
//
// Two things about how it is built are worth writing down.
//
// Every byte it reads goes through an int on the way out, which is what puts
// an extsb after each lbz. Written as a plain s8 to s8 copy the compiler emits
// only lbz and stb.
//
// The two functions build their row pointers differently, and both forms are
// read off the original rather than chosen. fn_1_92D0 adds the base first and
// then uses a displacement, so it is written as two steps from the base; a
// single expression makes the compiler fold the constant into an indexed load.
// fn_1_945C accumulates on the offset and adds the base last, so there it is
// written as one expression.

typedef struct Panel {
	u8 unk0[0x28];   // 0x000
	s32 state;       // 0x028
	u8 unk2C[0x1F8]; // 0x02C
	s32 slot;        // 0x224
	s32 mode;        // 0x228
	s32 page;        // 0x22C
	u8 unk230[0x8];  // 0x230
	void* labelA;    // 0x238
	void* labelB;    // 0x23C
	void* meter;     // 0x240
} Panel;

typedef struct Row {
	u8 padding[0x393]; // 0x000
	s8 flag;           // 0x393
} Row;

typedef struct SaveState {
	u8 padding[0x22]; // 0x00
	u8 emblems;       // 0x22
	u8 unk23[0x19];   // 0x23
	u8 data[1];       // 0x3C
} SaveState;

extern "C" const s32 lbl_1_rodata_ED0[];
extern "C" u8 lbl_803E774C[];

extern "C" SaveState* fn_80116D2C(void* state);

extern "C" void fn_1_92D0(Panel* panel, s8* out, s32 index, s32 mode)
{
	SaveState* save;
	u8* base;
	s8* entry;
	s32 value;
	Row* row;
	s32 id;

	if (out == NULL) {
		return;
	}

	out[0] = 0;
	out[1] = 0;

	fn_80116D2C(lbl_803E774C);
	save = fn_80116D2C(lbl_803E774C);
	base = save->data;

	id = lbl_1_rodata_ED0[index];
	if (id < 14) {
		switch (mode) {
			case 0:
				entry  = (s8*)(base + id * 0x50);
				value  = entry[0x1B];
				out[0] = value;
				value  = entry[0x27];
				out[1] = value;
				break;
			case 1:
				entry  = (s8*)(base + id * 0x50);
				value  = entry[0x33];
				out[0] = value;
				value  = entry[0x37];
				out[1] = value;
				break;
			case 2:
				entry  = (s8*)(base + id * 0x50);
				value  = entry[0x43];
				out[0] = value;
				value  = entry[0x47];
				out[1] = value;
				break;
			case 3:
				entry  = (s8*)(base + id * 0x50);
				value  = entry[0x53];
				out[0] = value;
				value  = entry[0x5F];
				out[1] = value;
				break;
		}
	} else if (id == 0x15) {
		row    = (Row*)base;
		row    = (Row*)((u8*)row + id * 0x10);
		value  = row->flag;
		out[0] = value;
	} else {
		row    = (Row*)(base + id * 0x10);
		row    = (Row*)((u8*)row + panel->mode * 4);
		value  = row->flag;
		out[0] = value;
	}
}

typedef struct RowA {
	s16 unk0;   // 0x00
	u8 unk2[2]; // 0x02
	s32 unk4;   // 0x04
	s8 unk8;    // 0x08
	s8 unk9;    // 0x09
	s8 unkA;    // 0x0A
	u8 unkB;    // 0x0B
} RowA;

typedef struct RowB {
	s8 unk0; // 0x00
	s8 unk1; // 0x01
	s8 unk2; // 0x02
	s8 unk3; // 0x03
} RowB;

typedef struct Field {
	u8 data[0xC];
} Field;

extern "C" const s32 lbl_1_rodata_C28[];
extern "C" const s32 lbl_1_rodata_C80[];
extern "C" u8 lbl_1_data_2BC8[];
extern "C" u8 lbl_1_data_2F18[];
extern "C" u8 lbl_1_data_300C[];
extern "C" Field lbl_1_data_3018[];
extern "C" u8 lbl_1_data_3054[];
extern "C" u8 lbl_1_data_376C[];
extern "C" u8 lbl_1_data_3774[];
extern "C" u8 lbl_1_data_377C[];
extern "C" u8 lbl_1_data_3784[];
extern "C" u8 lbl_1_data_3788[];

extern "C" s32 fn_80116A8C(void* records, s32 id);
extern "C" void fn_8012C858(void* field, void* format, ...);
extern "C" void fn_1_88C4(void* meter);
extern "C" void fn_1_88D0(void* meter, s32 value);
extern "C" void fn_1_8A68(void* label, s8 value, u8 highlight);
extern "C" void fn_1_8A9C(void* label);
extern "C" void fn_1_8AA8(void* label);

extern "C" void fn_1_945C(Panel* panel)
{
	SaveState* save;
	s32 valueA;
	s32 valueB;
	u8* base;
	RowA* rowA;
	RowB* rowB;
	u8* records;
	u8* entry;
	s32 highlight;
	s32 id;
	s32 offset;

	save    = fn_80116D2C(lbl_803E774C);
	base    = (u8*)fn_80116D2C(lbl_803E774C) + 0x3C;
	records = (u8*)fn_80116D2C(lbl_803E774C) + 0x624;

	rowA   = NULL;
	rowB   = NULL;
	valueA = 0;
	valueB = valueA;

	fn_8012C858(lbl_1_data_3054, lbl_1_data_376C, save->emblems);

	id = lbl_1_rodata_ED0[panel->slot];
	if (id < 14) {
		switch (panel->mode) {
			case 0:
				offset = id * 0x50;
				entry  = base + offset;
				valueA = ((s8*)entry)[0x1B];
				valueB = ((s8*)entry)[0x27];
				rowA   = (RowA*)(base + (offset + panel->page * 0xC + 0x10));
				break;
			case 1:
				offset = id * 0x50;
				entry  = base + offset;
				valueA = ((s8*)entry)[0x33];
				valueB = ((s8*)entry)[0x37];
				if (panel->page == 0) {
					rowA = (RowA*)(base + (offset + 0x28));
				} else {
					rowB = (RowB*)(base + (offset + 0x34));
				}
				break;
			case 2:
				offset = id * 0x50;
				entry  = base + offset;
				valueA = ((s8*)entry)[0x43];
				valueB = ((s8*)entry)[0x47];
				if (panel->page == 0) {
					rowA = (RowA*)(base + (offset + 0x38));
				} else {
					rowB = (RowB*)(base + (offset + 0x44));
				}
				break;
			case 3:
				offset = id * 0x50;
				entry  = base + offset;
				valueA = ((s8*)entry)[0x53];
				valueB = ((s8*)entry)[0x5F];
				rowA   = (RowA*)(base + (offset + panel->page * 0xC + 0x48));
				break;
		}

		if (panel->meter != NULL) {
			if (lbl_1_rodata_C28[panel->slot] != 0) {
				if (fn_80116A8C(records, lbl_1_rodata_C80[panel->slot]) != 0) {
					fn_1_88D0(panel->meter, (panel->slot + 5) / 3);
				} else {
					fn_1_88D0(panel->meter, 0);
				}
			} else {
				fn_1_88C4(panel->meter);
			}
		}
	} else {
		if (id == 0x15) {
			rowB = (RowB*)(base + ((id - 14) * 0x10 + 0x470));
		} else {
			rowB = (RowB*)(base + ((id - 14) * 0x10 + panel->mode * 4 + 0x470));
		}
		valueA = rowB->unk3;
		if (panel->meter != NULL) {
			fn_1_88C4(panel->meter);
		}
	}

	if (rowA != NULL) {
		fn_8012C858(&lbl_1_data_3018[0], lbl_1_data_3774, rowA->unk8);
		fn_8012C858(&lbl_1_data_3018[1], lbl_1_data_3774, rowA->unk9);
		fn_8012C858(&lbl_1_data_3018[2], lbl_1_data_3774, rowA->unkA);
		fn_8012C858(&lbl_1_data_3018[3], lbl_1_data_376C, rowA->unk0);
		fn_8012C858(&lbl_1_data_3018[4], lbl_1_data_377C, rowA->unk4);
	} else if (rowB != NULL) {
		fn_8012C858(&lbl_1_data_3018[0], lbl_1_data_3774, rowB->unk0);
		fn_8012C858(&lbl_1_data_3018[1], lbl_1_data_3774, rowB->unk1);
		fn_8012C858(&lbl_1_data_3018[2], lbl_1_data_3774, rowB->unk2);
		fn_8012C858(&lbl_1_data_3018[3], lbl_1_data_3784);
		fn_8012C858(&lbl_1_data_3018[4], lbl_1_data_3788);
	} else {
		fn_8012C858(&lbl_1_data_3018[0], lbl_1_data_2F18);
		fn_8012C858(&lbl_1_data_3018[1], lbl_1_data_2F18);
		fn_8012C858(&lbl_1_data_3018[2], lbl_1_data_2F18);
		fn_8012C858(&lbl_1_data_3018[3], lbl_1_data_2BC8);
		fn_8012C858(&lbl_1_data_3018[4], lbl_1_data_300C);
	}

	if (id < 14) {
		if (panel->labelB != NULL) {
			fn_1_8AA8(panel->labelB);
		}
	} else {
		if (panel->labelB != NULL) {
			fn_1_8A9C(panel->labelB);
		}
	}

	if (panel->labelA != NULL) {
		highlight = 0;
		if (panel->page == 0 && panel->state == 6) {
			highlight = 1;
		}
		fn_1_8A68(panel->labelA, valueA, highlight);
	}

	if (panel->labelB != NULL) {
		highlight = 0;
		if (panel->page != 0 && panel->state == 6) {
			highlight = 1;
		}
		fn_1_8A68(panel->labelB, valueB, highlight);
	}
}
