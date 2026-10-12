// TObjColliCommunication's EditOnChange: the kind and the byte after it are
// each held between two byte limits of the module and name the editor's first
// two fields, and the volume's extent takes the placement's position. The
// limits go through a clamp that returns a reference, as in
// rel/flyer_collision_edit.cpp. The class is in game/obj_colli_communication.h.

#include "game/obj_colli_communication.h"

extern "C" s8 rinoColKindMin;
extern "C" s8 rinoColKindMax;
extern "C" s8 rinoColActionMin;
extern "C" s8 rinoColActionMax;
extern "C" const char* rinoColKindNames[];
extern "C" const char* rinoColActionNames[];
extern "C" const char* rinoColObjectFieldNames[];

template <typename T>
static inline const T& rinoColClamp(const T& value, const T& low, const T& high)
{
	return value < low ? low : (value > high ? high : value);
}

void TObjColliCommunication::EditOnChange(SETDATA_PARAM* data)
{
	ColliCommunicationParam* param = (ColliCommunicationParam*)data->setBuffer;

	*(s8*)&param->kind   = rinoColClamp(*(s8*)&param->kind, rinoColKindMin, rinoColKindMax);
	*(s8*)&param->action = rinoColClamp(*(s8*)&param->action, rinoColActionMin, rinoColActionMax);
	rinoColObjectFieldNames[0] = rinoColKindNames[*(s8*)&param->kind];
	rinoColObjectFieldNames[1] = rinoColActionNames[*(s8*)&param->action];
	param->extent              = data->pos;
}
