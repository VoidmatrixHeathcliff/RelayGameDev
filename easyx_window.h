#ifndef _EASYX_WINDOW_H_
#define _EASYX_WINDOW_H_

#include "./include/game/Game.h"
#include"throw_ exception.h"

//这里是对于游戏窗口的简单封装
//如果想自定义加载界面，请修改InitFakeLoadUI函数里的第一行代码
//更正：请修改LoadScene类

class PGameWindow
{
public:
	PGameWindow()//默认的窗口
	{
		game_window = new PLGame(640,480,"demo");
	}

	PGameWindow(const int& Width, const int& Height, const PString& window_title)//自定义的窗口
	{
		game_window = new PLGame(Width, Height, window_title);
	}
	
	~PGameWindow()
	{
		delete game_window;
	}

	void Loop()//启动并运行游戏主窗口的消息循环
	{
		game_window->Loop();
	}

private:
	PLGame* game_window = nullptr;
};

#endif // !_EASYX_WINDOW_H_