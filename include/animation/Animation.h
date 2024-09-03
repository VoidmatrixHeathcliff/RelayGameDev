//
//��PAnimtor����ĸ�����
//
#pragma once
//������������ṩ��ģ��ֻ��״̬��������
#include <string>
#include <vector>

#include "../time/Timer.h"

/*
	Z���ع��󲿷ֶ����ࡣ
*/
template<typename T = int>
class PAnimation
{
public:
	PAnimation(bool isLoopFlag = true, float fInterval = 0.2f, std::string name = "") :
		bIsLoop(isLoopFlag),
		animName(name),
		oTimer()
	{
		oTimer.set(fInterval, [&]() {
			switchToNext();
		});
		oTimer.start();
	}
	~PAnimation() = default;
	
public:
	/*
		��Ӷ���֡��
	*/
	void addFrame(T* oFrame) { vecFrameList.push_back(oFrame); }

	/*
		ɾ������֡��
	*/
	void removeFrame(int iIndex) {
		if (iIndex >= vecFrameList.size() || iIndex < 0) return;
		vecFrameList.erase(vecFrameList.begin() + iIndex);
	}

	/*
		�л�����һ������֡��
	*/
	void switchToNext() {
		int iSize = (int)vecFrameList.size();
		iFrameIndex++;
		// ��ѭ������
		if (iFrameIndex >= iSize && !bIsLoop) {
			iFrameIndex = 0;
			oTimer.pause();
			if (fCallback) fCallback();
			return;
		}
		iFrameIndex %= iSize;
	}

	/*
		���¶�����
	*/
	void onUpdate(float deltaTime) {
		oTimer.update(deltaTime);
	}
	
	/*
		��Ϊû���޸�ǰ�˵�ģ���࣬�ɴ�ֱ�ӷ��ص�ǰ����ָ���ָ�롣
		����дһ�� Renderable �ĳ���ӿڣ�Ȼ����ģ���Ϊ Renderable �ӿڡ�
	*/
	T* getCurrentFrame() const {
		int iSize = (int)vecFrameList.size();
		if (iFrameIndex < 0 || iFrameIndex >= iSize) return nullptr;
		return vecFrameList[iFrameIndex];
	}

	/*
		����index��ȡ����֡��
		�����������ȡͼƬ��
	*/
	T* getFrame(int _iIndex) const {
		int iSize = (int)vecFrameList.size();
		if (_iIndex < 0 || _iIndex >= iSize) return nullptr;
		return vecFrameList[_iIndex];
	}


public:
	/*
		�Ƿ�ѭ�����š�
	*/
	bool isLoop() const { return bIsLoop; }

	/*
		�����Ƿ�ѭ�����š�
	*/
	void setLoop(bool flag) { bIsLoop = flag; }

	/*
		���ûص�������
	*/
	void setCallback(std::function<void()> fCallback) {
		this->fCallback = fCallback;
	}

	/*
		���ø��¼����
	*/
	void setInterval(float fInterval) { 
		oTimer.set(fInterval);
	}


private:
	std::string animName;				// ����������
	bool bIsLoop;						// �Ƿ�ѭ�����Ŷ���
	std::function<void()> fCallback;	// ���������ص�����

	int iFrameIndex = 0;				// ����֡����
	std::vector<T*> vecFrameList;		// ����֡�б�
	Timer oTimer;						// �������¼�ʱ��
};