#ifndef _P_RESOURSE_MANAGER_H_
#define _P_RESOURSE_MANAGER_H_

#include <unordered_map>
#include <string>
#include <memory>

#include "../singleton/Singleton.h"
#include "../EasyXBase.h"

/*
	Z：图片资源管理器类。

	使用智能指针管理图片，作为ImageLabel储存。
	有兴趣的可以改进该代码，将图片储存分为永久和临时储存两种。

	目前代码体量不大就将所有图片设置为永久储存了。
*/
class PResourseManager : public Singleton<PResourseManager> {
	friend class Singleton<PResourseManager>;
public:
	/*
		加载新的图片。
	*/
	void loadImage(PString sPath, std::string name) {
		if (mapImageAtlas.find(name) == mapImageAtlas.end()) {	// 没有注册过该名字
			mapImageAtlas.insert({ name, std::make_shared<PImage>(sPath) });
		}
	}
	
	/*
		获取已经储存的图片。
	*/
	PImage* findImage(std::string name) {
		auto it = mapImageAtlas.find(name);
		if (it == mapImageAtlas.end()) return nullptr;	// 没有注册过该名字
		return it->second.get();
	}

protected:
	PResourseManager() = default;
	~PResourseManager() noexcept = default;

private:
	std::unordered_map<std::string, std::shared_ptr<PImage> > mapImageAtlas;
};

#endif // !_P_RESOURSE_MANAGER_H_
