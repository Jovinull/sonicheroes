#ifndef GAME_OBJ_TRAIN_SWITCH_H
#define GAME_OBJ_TRAIN_SWITCH_H

// TrainSwitchManager, the empty third base of stage07D's train switch objects
// (TObjTrainChangeBoard, TObjTrainChangeRail, TObjTrainChangeSwitch). Its
// constructor and destructor are out of line (rel/train_switch_manager.cpp):
// the derived constructors call the first and the derived destructors the
// second, at the base's offset 0x30, which it shares with the first member.
class TrainSwitchManager
{
public:
	TrainSwitchManager();
	~TrainSwitchManager();
};

#endif
