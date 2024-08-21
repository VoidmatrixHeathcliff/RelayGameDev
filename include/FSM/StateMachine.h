//
//PEntity�����õ���״̬��
//
#pragma once

#include "../../include/FSM/EntityState.h"

class PStateMachine
{
public:
	PStateMachine() = default;
	~PStateMachine() = default;

public:
	PEntityState formerState; //���ڼ�¼��һ��״̬���Ա���ʱ֮��
	PEntityState currentState; //���ڼ�¼��ǰ״̬

public:
	void ChangeState(PEntityState nextState); //���ô˺����л�����һ��ĳĳ״̬
};