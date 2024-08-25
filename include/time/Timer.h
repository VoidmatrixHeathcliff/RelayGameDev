#pragma once
#ifndef _TIMER_H_
#define _TIMER_H_

#include <functional>

#pragma push_macro("max")
#undef max

class Timer {
private:
	static constexpr float MIN_DURATION = 0.0001f;
	static constexpr size_t MAX_FRAME_TRIGGER = 10;
	std::function<void()> onTimeout_ = {};
	float remainingTime = 0;
	float duration = MIN_DURATION;
	int _triggers = 0;
	bool _isRunning = false;

public:
	static constexpr int INF_TRIGGER = -1;

	Timer() = default;

	Timer(float duration, const std::function<void()> onTimeout = {})
		:duration(std::max(duration, MIN_DURATION)), onTimeout_(onTimeout) {
	}

	~Timer() {
		pause();
	}

	Timer& set(float duration, const std::function<void()> onTimeout = {}) {
		this->duration = std::max(duration, MIN_DURATION);
		this->onTimeout_ = onTimeout;
		return *this;
	}

	/// <summary>
	/// start the timer
	/// </summary>
	/// <param name="_triggers">
	/// determines how many times the Timer would run and trigger timeout. default: infinite
	/// </param>
	void start(int _triggers = INF_TRIGGER) {
		reset();
		if (_triggers == 0)return;
		_isRunning = true;
		this->_triggers = _triggers;
		remainingTime = duration;
	}

	void pause() {
		_isRunning = false;
	}

	void reset() {
		remainingTime = 0;
		_triggers = 0;
		_isRunning = false;
	}

	void clear() {
		remainingTime = 0;
		_triggers = 0;
		_isRunning = false;
		onTimeout_ = {};
		duration = MIN_DURATION;
	}

	void update(float deltaTime) {
		if (!_isRunning)return;
		remainingTime -= deltaTime;
		size_t currentFrameTrigger = 0;
		while (remainingTime <= 0 && currentFrameTrigger < MAX_FRAME_TRIGGER) {
			if (onTimeout_) {
				onTimeout_();
			}
			_triggers--;
			currentFrameTrigger++;
			if (_triggers == 0) {
				reset();
				break;
			}
			remainingTime += duration;
		}
	}

	inline bool isRunning()const { return this->_isRunning; }
	inline float getRemainingTime()const { return this->remainingTime; }
};

//class Timer
//{
//public:
//	Timer() = default;
//	~Timer() = default;
//
//	void restart()//���¿�ʼ
//	{
//		pass_time = 0;
//		shotted = false;
//	}
//
//	void set_wait_time(double val)
//	{
//		wait_time = val;
//	}
//
//	void set_pause(bool is_pause)
//	{
//		paused = is_pause;
//	}
//
//
//	void set_shotted(bool is_shotted)//�����Ƿ񴥷�
//	{
//		shotted = is_shotted;
//	}
//
//	void set_callback(std::function<void()>callback)
//	{
//		this->callback = callback;
//	}
//
//	void on_update(double delta)//ʵʱ����
//	{
//		if (paused)
//			return;
//		pass_time += delta;
//		if (pass_time >= wait_time) {
//			pass_time = 0;
//			shotted = true;
//		}
//	}
//
//	bool get_is_pause()//��ȡ�Ƿ���ͣ
//	{
//		return paused;
//	}
//
//	bool get_is_shotted()//��ȡ�Ƿ񴥷�
//	{
//		return shotted;
//	}
//
//protected:
//	std::function<void()> callback;
//private:
//	double pass_time = 0;//�ѹ�ʱ��
//	double wait_time = 0;//�ȴ�ʱ��
//	bool paused = false;//�Ƿ���ͣ
//	bool shotted = false;//�Ƿ񴥷�
//
//};

#pragma pop_macro("max")
#endif // !_TIMER_H_
