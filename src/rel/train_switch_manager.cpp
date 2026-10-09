// TrainSwitchManager's out-of-line destructor and constructor, both empty, in
// stage07D (see game/obj_train_switch.h). The destructor is the compiler's
// `if (this && flag > 0) delete this;`, through the global operator delete
// since the class has none of its own.

#include "game/obj_train_switch.h"

TrainSwitchManager::~TrainSwitchManager() { }

TrainSwitchManager::TrainSwitchManager() { }
