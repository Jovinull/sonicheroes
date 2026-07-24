#include "types.h"

#ifdef __MWERKS__
#pragma exceptions on
#endif

typedef void (*Constructor)(void*, int);
typedef void (*Destructor)(void*, int);

extern "C" void fn_80057578(void*);
extern "C" void fn_801BB384(void);
extern "C" void __dl__FPv(void*);

struct exception_object {
	void** vtable;
};

extern "C" exception_object* __dt__Q23std9exceptionFv(exception_object*, short);
extern "C" const char* what__Q23std9exceptionCFv(const exception_object*);

static const char exception_type_name[16] = "std::exception";
static const char exception_what[]        = "exception";

extern "C" {
void* __RTTI__Q23std9exception[2] = {
	(void*)exception_type_name,
	0,
};

void* __vt__Q23std9exception[4] = {
	__RTTI__Q23std9exception,
	0,
	(void*)__dt__Q23std9exceptionFv,
	(void*)what__Q23std9exceptionCFv,
};
}

namespace std
{
typedef void (*terminate_handler)();
typedef void (*unexpected_handler)();

void dthandler();
void duhandler();

terminate_handler __terminate_handler   = dthandler;
unexpected_handler __unexpected_handler = duhandler;
}

extern "C" exception_object* __dt__Q23std9exceptionFv(exception_object* object, short free_object)
{
	if (object != 0) {
		object->vtable = __vt__Q23std9exception;
		if (free_object > 0)
			__dl__FPv(object);
	}
	return object;
}

extern "C" const char* what__Q23std9exceptionCFv(const exception_object*)
{
	return exception_what;
}

extern "C" void __destroy_new_array(void* array, Destructor destructor)
{
	if (array != 0) {
		if (destructor != 0) {
			unsigned long i = 0;
			unsigned long count;
			unsigned long size = ((unsigned long*)array)[-4];
			count              = ((unsigned long*)array)[-3];
			char* object       = (char*)array + size * count;

			while (i < count) {
				object -= size;
				destructor(object, -1);
				i++;
			}
		}
		fn_80057578((char*)array - 16);
	}
}

extern "C" void __destroy_arr(
    void* array, Destructor destructor, unsigned long size, unsigned long count)
{
	char* object = (char*)array + size * count;

	while (count != 0) {
		object -= size;
		destructor(object, -1);
		count--;
	}
}

class __partial_array_destructor
{
public:
	__partial_array_destructor(
	    void* array, unsigned long size, unsigned long count, Destructor destructor)
	    : array(array)
	    , size(size)
	    , count(count)
	    , destructor(destructor)
	    , constructed(count)
	{
	}

	inline ~__partial_array_destructor();

	void* array;
	unsigned long size;
	unsigned long count;
	Destructor destructor;
	unsigned long constructed;
};

#ifdef __MWERKS__
#pragma defer_codegen on
#endif

extern "C" void __construct_array(void* array, Constructor constructor, Destructor destructor,
    unsigned long size, unsigned long count)
{
	unsigned long element_count = count;
	char* object                = (char*)array;
	__partial_array_destructor partial(array, size, count, destructor);
	partial.constructed = 0;

	while (partial.constructed < element_count) {
		constructor(object, 1);
		object += size;
		partial.constructed++;
	}
}

inline __partial_array_destructor::~__partial_array_destructor()
{
	if (constructed < count && destructor != 0) {
		char* object = (char*)array + size * constructed;

		while (constructed != 0) {
			object -= size;
			destructor(object, -1);
			constructed--;
		}
	}
}

#ifdef __MWERKS__
#pragma defer_codegen reset
#pragma opt_propagation off
#endif

extern "C" void* __construct_new_array(void* array, Constructor constructor, Destructor destructor,
    unsigned long size, unsigned long count)
{
	register unsigned long element_count = count;
	void* result;

	if ((result = array) != 0) {
		((unsigned long*)result)[0] = size;
		((unsigned long*)result)[1] = element_count;
		result                      = (char*)result + 16;

		if (constructor != 0) {
			register char* object = (char*)result;
			__partial_array_destructor partial(result, size, element_count, destructor);
			partial.constructed = 0;

			while (partial.constructed < element_count) {
				constructor(object, 1);
				object += size;
				partial.constructed++;
			}
		}
	}

	return result;
}

#ifdef __MWERKS__
#pragma opt_propagation on
#endif

extern "C" char __throw_catch_compare(
    const char* throwtype, const char* catchtype, long* offset_result)
{
	const char* current;
	*offset_result = 0;

	if ((current = catchtype) == 0)
		return 1;

	if (*catchtype == 'P') {
		current++;
		if (*current == 'C')
			current++;
		if (*current == 'V')
			current++;
		if (*current == 'v' && (*throwtype == 'P' || *throwtype == '*'))
			return 1;
		current = catchtype;
	}

	switch (*throwtype) {
	case '*':
	case '!':
		if (*throwtype++ != *current++)
			return 0;

	compare_names:
		{
			do {
				if (*throwtype != *current++)
					goto skip_name;
			} while (*throwtype++ != '!');
		}

		{
			long offset = 0;

			while (*throwtype != '!')
				offset = offset * 10 + *throwtype++ - '0';
			*offset_result = offset;
			return 1;
		}

	skip_name:
		while (*throwtype++ != '!') { }
		while (*throwtype++ != '!') { }
		if (*throwtype == 0)
			return 0;
		current = catchtype + 1;
		goto compare_names;
	default:
		break;
	}

	goto qualifier_test;

qualifier_body:
		throwtype++;
		current++;
		if (*current == 'C') {
			if (*throwtype == 'C')
				throwtype++;
			current++;
		}
		if (*throwtype == 'C')
			return 0;
		if (*current == 'V') {
			if (*throwtype == 'V')
				throwtype++;
			current++;
		}
		if (*throwtype == 'V')
			return 0;

qualifier_test:
	if ((*throwtype == 'P' || *throwtype == 'R')
	    && *throwtype == *current)
		goto qualifier_body;

	while (*throwtype == *current) {
		if (*throwtype == 0)
			return 1;
		throwtype++;
		current++;
	}

	return 0;
}

namespace std
{
void unexpected()
{
	__unexpected_handler();
}

void terminate()
{
	__terminate_handler();
}

void duhandler()
{
	terminate();
}

void dthandler()
{
	fn_801BB384();
}
}
