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
		//������Ҫ��һ����ť�����ſ��Լ�����Ϸ�ģ������Ҳ���дQAQ
		if (paused)
			return;
		pass_time += delta;
		if (pass_time >= wait_time) {
			//����д
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
	int pass_time = 0;   //�ѹ�ʱ��
	int wait_time = 0;   //�ȴ�ʱ��
	bool paused = false;   //�Ƿ���ͣ
	bool shotted = false; //�Ƿ񴥷�
	std::vector<int> time;     //ʱ���飬�����������Ҫ�ȹ���ʲô����ʱ�䡣
};

