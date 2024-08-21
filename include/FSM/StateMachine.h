//
//PEntity类所用到的状态机
//
#pragma once

#include "../../include/FSM/EntityState.h"

class PStateMachine
{
public:
	PStateMachine() = default;
	~PStateMachine() = default;

public:
	PEntityState formerState; //用于记录上一个状态，以备不时之需
	PEntityState currentState; //用于记录当前状态

public:
	void ChangeState(PEntityState nextState); //调用此函数切换到下一个某某状态
};