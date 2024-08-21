#pragma once
#include <functional>
#include <vector>
class Time
{
public:
	Time() = default;
	~Time() = default;

	void restart()
	{
		pass_time = 0;
		shotted = false;
	}

	void set_wait_time(int val) {
		wait_time = val;

	}

	void pause() {
		paused = true;
	}

	void resume() {
		paused = false;
	}

	void on_update(int delta) {
		//这里想要有一个按钮点击后才可以继续游戏的，可是我不会写QAQ
		if (paused)
			return;
		pass_time += delta;
		if (pass_time >= wait_time) {
			//不会写
			}
			shotted = true;
			pass_time = 0;
		
	}

	void set_callback(std::function<void()>callback) {
		this->callback = callback;
	}

protected:
	std::function<void()>callback;
private:
	int pass_time = 0;   //已过时间
	int wait_time = 0;   //等待时间
	bool paused = false;   //是否暂停
	bool shotted = false; //是否触发
	std::vector<int> time;     //时间组，加入接下来所要度过的什么样的时间。
};

