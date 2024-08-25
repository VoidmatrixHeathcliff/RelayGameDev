#ifndef _EASYX_WINDOW_H_
#define _EASYX_WINDOW_H_

#include "./include/game/Game.h"
#include"throw_ exception.h"

//�����Ƕ�����Ϸ���ڵļ򵥷�װ
//������Զ�����ؽ��棬���޸�InitFakeLoadUI������ĵ�һ�д���
//���������޸�LoadScene��

class PGameWindow
{
public:
	PGameWindow()//Ĭ�ϵĴ���
	{
		game_window = new PLGame(640,480,"demo");
	}

	PGameWindow(const int& Width, const int& Height, const PString& window_title)//�Զ���Ĵ���
	{
		game_window = new PLGame(Width, Height, window_title);
	}
	
	~PGameWindow()
	{
		delete game_window;
	}

	void Loop()//������������Ϸ�����ڵ���Ϣѭ��
	{
		game_window->Loop();
	}

private:
	PLGame* game_window = nullptr;
};

#endif // !_EASYX_WINDOW_H_