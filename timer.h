#ifndef _TIMER_H_
#define _TIMER_H_

#include <functional>

class Timer
{
public:
	Timer() = default;
	~Timer() = default;

	void restart()//重新开始
	{
		pass_time = 0;
		shotted = false;
	}

	void set_wait_time(double val)
	{
		wait_time = val;
	}

	void set_pause(bool is_pause)
	{
		paused = is_pause;
	}


	void set_shotted(bool is_shotted)//设置是否触发
	{
		shotted = is_shotted;
	}

	void set_callback(std::function<void()>callback)
	{
		this->callback = callback;
	}

	void on_update(double delta)//实时更新
	{
		if (paused)
			return;
		pass_time += delta;
		if (pass_time >= wait_time) {
			pass_time = 0;
			shotted = true;
		}
	}

	bool get_is_pause()//获取是否暂停
	{
		return paused;
	}

	bool get_is_shotted()//获取是否触发
	{
		return shotted;
	}

protected:
	std::function<void()>callback;
private:
	double pass_time = 0;//已过时间
	double wait_time = 0;//等待时间
	bool paused = false;//是否暂停
	bool shotted = false;//是否触发

};

#endif // !_TIMER_H_
