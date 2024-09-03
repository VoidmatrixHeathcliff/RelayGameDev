#ifndef _P_RESOURSE_MANAGER_H_
#define _P_RESOURSE_MANAGER_H_

#include <unordered_map>
#include <string>
#include <memory>

#include "../singleton/Singleton.h"
#include "../EasyXBase.h"

/*
	Z��ͼƬ��Դ�������ࡣ

	ʹ������ָ�����ͼƬ����ΪImageLabel���档
	����Ȥ�Ŀ��ԸĽ��ô��룬��ͼƬ�����Ϊ���ú���ʱ�������֡�

	Ŀǰ������������ͽ�����ͼƬ����Ϊ���ô����ˡ�
*/
class PResourseManager : public Singleton<PResourseManager> {
	friend class Singleton<PResourseManager>;
public:
	/*
		�����µ�ͼƬ��
	*/
	void loadImage(PString sPath, std::string name) {
		if (mapImageAtlas.find(name) == mapImageAtlas.end()) {	// û��ע���������
			mapImageAtlas.insert({ name, std::make_shared<PImage>(sPath) });
		}
	}
	
	/*
		��ȡ�Ѿ������ͼƬ��
	*/
	PImage* findImage(std::string name) {
		auto it = mapImageAtlas.find(name);
		if (it == mapImageAtlas.end()) return nullptr;	// û��ע���������
		return it->second.get();
	}

protected:
	PResourseManager() = default;
	~PResourseManager() noexcept = default;

private:
	std::unordered_map<std::string, std::shared_ptr<PImage> > mapImageAtlas;
};

#endif // !_P_RESOURSE_MANAGER_H_
