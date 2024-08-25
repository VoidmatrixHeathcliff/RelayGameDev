#ifndef _TIMER_H_
#define _TIMER_H_

#include <functional>

class Timer
{
public:
	Timer() = default;
	~Timer() = default;

	void restart()//���¿�ʼ
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


	void set_shotted(bool is_shotted)//�����Ƿ񴥷�
	{
		shotted = is_shotted;
	}

	void set_callback(std::function<void()>callback)
	{
		this->callback = callback;
	}

	void on_update(double delta)//ʵʱ����
	{
		if (paused)
			return;
		pass_time += delta;
		if (pass_time >= wait_time) {
			pass_time = 0;
			shotted = true;
		}
	}

	bool get_is_pause()//��ȡ�Ƿ���ͣ
	{
		return paused;
	}

	bool get_is_shotted()//��ȡ�Ƿ񴥷�
	{
		return shotted;
	}

protected:
	std::function<void()>callback;
private:
	double pass_time = 0;//�ѹ�ʱ��
	double wait_time = 0;//�ȴ�ʱ��
	bool paused = false;//�Ƿ���ͣ
	bool shotted = false;//�Ƿ񴥷�

};

#endif // !_TIMER_H_
