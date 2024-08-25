#ifndef _ASSETS_H_
#define _ASSETS_H_

#include"easyx.h"//easyx库
#include <iostream>
#include <string>
#include"throw_ exception.h"

//？这里是图集类，提供公开的图片资源加载功能
//以及获取长和宽
//需要新的方法可以补充

class PAssets
{
public:

	PAssets(std::wstring wstr)
	{
		img = new IMAGE();
		loadimage(img,wstr.c_str(), 0, 0);
	}

	PAssets(std::wstring wstr,const wchar_t* error)//提供一个判断错误的方法
	{
		img = new IMAGE();
		loadimage(img, wstr.c_str(), 0, 0);

		bool check_img = ((img->getheight() == 0) && (img->getwidth() == 0));//加载失败的条件

		Throw_Exception_Window(!check_img, error);
	}

	~PAssets()
	{
		delete img;
	}

	int GetImgW()
	{
		return img->getwidth();
	}

	int GetImgH()
	{
		return img->getheight();
	}

	IMAGE* GetImg()
	{
		return img;
	}

private:
	IMAGE* img = nullptr;
};

#endif // !_ASSETS_H_