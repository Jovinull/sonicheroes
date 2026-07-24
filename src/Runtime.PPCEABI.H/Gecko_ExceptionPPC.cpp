#include "Runtime.PPCEABI.H/NMWException.h"

#ifdef __MWERKS__
#pragma exceptions on
#endif

typedef struct ProcessInfo {
	__eti_init_info* exception_info;
	char* TOC;
	int active;
} ProcessInfo;

typedef struct ExceptionTableIndex {
	u32 function_start;
	u32 function_size;
	u32 exception_info;
} ExceptionTableIndex;

typedef struct FragmentInfo {
	ExceptionTableIndex* exception_start;
	ExceptionTableIndex* exception_end;
	char* code_start;
	char* code_end;
	char* data_start;
	char* data_end;
	char* TOC;
	int active;
} FragmentInfo;

typedef struct ExceptionInfo {
	void* exception_record;
	char* current_function;
	char* action_pointer;
	char* code_section;
	char* data_section;
	char* TOC;
} ExceptionInfo;

typedef struct ExceptionRangeSmall {
	u16 start;
	u16 end;
	u16 action;
} ExceptionRangeSmall;

typedef struct ExceptionTableSmall {
	u16 field;
	ExceptionRangeSmall ranges[0];
} ExceptionTableSmall;

typedef struct ExceptionRangeLarge {
	u32 start;
	u16 size;
	u16 action;
} ExceptionRangeLarge;

typedef struct ExceptionTableLarge {
	u16 field;
	u16 field2;
	ExceptionRangeLarge ranges[0];
} ExceptionTableLarge;

static ProcessInfo fragmentinfo[1];

static inline int find_fragment(char* returnaddr, FragmentInfo* fragment)
{
	ProcessInfo* process;
	__eti_init_info* info;
	int i;

	for (i = 0, process = fragmentinfo; i < 1; ++i, ++process) {
		if (process->active != 0) {
			info = process->exception_info;
			while (1) {
				if (info->code_size == 0) {
					break;
				}
				if (returnaddr >= info->code_start
				    && returnaddr < (char*)info->code_start + info->code_size) {
					fragment->exception_start = (ExceptionTableIndex*)info->eti_start;
					fragment->exception_end   = (ExceptionTableIndex*)info->eti_end;
					fragment->code_start      = 0;
					fragment->code_end        = 0;
					fragment->data_start      = 0;
					fragment->data_end        = 0;
					fragment->TOC             = process->TOC;
					fragment->active          = process->active;
					return 1;
				}
				++info;
			}
		}
	}
	return 0;
}

extern "C" void ExPPC_FindExceptionRecord(char* returnaddr, ExceptionInfo* result)
{
	FragmentInfo* fragment;
	FragmentInfo frag;
	ExceptionTableIndex* exceptionindex;
	ExceptionTableIndex* p;
	unsigned long returnoffset;
	long i;
	long m;
	long n;

	result->exception_record = 0;
	result->action_pointer   = 0;

	if (find_fragment(returnaddr, &frag) == 0) {
		return;
	}
	fragment = &frag;

	result->code_section = fragment->code_start;
	result->data_section = fragment->data_start;
	result->TOC          = fragment->TOC;

	returnoffset   = returnaddr - fragment->code_start;
	exceptionindex = fragment->exception_start;
	for (i = 0, n = fragment->exception_end - fragment->exception_start;;) {
		if (i > n) {
			return;
		}
		p = &exceptionindex[m = (i + n) / 2];

		if (returnoffset < p->function_start) {
			n = m - 1;
		} else if (returnoffset > p->function_start + (p->function_size & 0x7fffffff)) {
			i = m + 1;
		} else {
			break;
		}
	}
	result->current_function = fragment->code_start + p->function_start;
	result->exception_record = (p->function_size >> 31) != 0
	    ? (void*)&p->exception_info
	    : (void*)(fragment->data_start + p->exception_info);

	returnoffset -= p->function_start;

	if (((*(u16*)result->exception_record >> 3) & 1) != 0) {
		ExceptionTableLarge* table = (ExceptionTableLarge*)result->exception_record;
		ExceptionRangeLarge* range;
		unsigned long range_start;

		for (range = table->ranges; (range_start = range->start) != 0; ++range) {
			unsigned long range_end = range->start + (range->size * 4);

			if (range_start <= returnoffset && range_end >= returnoffset) {
				result->action_pointer = (char*)table + range->action;
				break;
			}
		}
	} else {
		ExceptionTableSmall* table = (ExceptionTableSmall*)result->exception_record;
		ExceptionRangeSmall* range;

		for (range = table->ranges; range->start != 0; ++range) {
			if (range->start <= returnoffset && range->end >= returnoffset) {
				result->action_pointer = (char*)table + range->action;
				break;
			}
		}
	}
}

void __unregister_fragment(int fragmentID)
{
	ProcessInfo* fragment;

	if (fragmentID >= 0 && fragmentID < 1) {
		fragment                 = &fragmentinfo[fragmentID];
		fragment->exception_info = 0;
		fragment->TOC            = 0;
		fragment->active         = 0;
	}
}

int __register_fragment(__eti_init_info* info, char* TOC)
{
	ProcessInfo* fragment;
	int i;

	for (i = 0, fragment = fragmentinfo; i < 1; ++i, ++fragment) {
		if (fragment->active == 0) {
			fragment->exception_info = info;
			fragment->TOC            = TOC;
			fragment->active         = 1;
			return i;
		}
	}

	return -1;
}
